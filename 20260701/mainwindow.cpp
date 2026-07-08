#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QWheelEvent>
#include <QDebug>
#include <QScrollBar>
#include <QDir>
#include <QFileInfo>
#include <QFileInfoList>
#include <QFile>
#include <QSettings>
#include <QJsonDocument>
#include <QJsonArray>
#include <QJsonObject>
#include <QCoreApplication>
#include <QTimer>
#include <QMenu>
#include <QAction>
#include <QFileDialog>
#include <QMessageBox>
#include <QDateTime>
#include <QMouseEvent>
#include <QApplication>
#include <QTextStream>
#include <QSerialPortInfo>
#include <QSerialPort>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    // 1. 初始化视图与画布
    scene = new QGraphicsScene(this);
    ui->graphicsView->setScene(scene);
    ui->graphicsView->setDragMode(QGraphicsView::ScrollHandDrag);
    ui->graphicsView->setTransformationAnchor(QGraphicsView::AnchorUnderMouse);
    ui->graphicsView->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    ui->graphicsView->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);

    ui->graphicsView->installEventFilter(this);
    ui->graphicsView->viewport()->installEventFilter(this);
    ui->listWidget->setSelectionMode(QAbstractItemView::ExtendedSelection);
    ui->listWidget->viewport()->installEventFilter(this);

    ui->listWidget->setContextMenuPolicy(Qt::CustomContextMenu);
    connect(ui->listWidget, &QListWidget::customContextMenuRequested,
            this, &MainWindow::onListWidgetCustomContextMenuRequested);

    connect(ui->btnAddDir, &QPushButton::clicked,
            this, &MainWindow::onBtnAddDirClicked);

    connect(ui->btnClearLog, &QPushButton::clicked,
            this, &MainWindow::on_btnClearLog_clicked);

    connect(ui->btnSaveLog, &QPushButton::clicked,
            this, &MainWindow::on_btnSaveLog_clicked);

    connect(ui->btnClearUdpRxCount, &QPushButton::clicked, this, [=]() {
        m_udpRxCount = 0;
        ui->labelUdpRxCount->setText("UDP接收次数：0");
    });

    connect(ui->btnClearTcpClientRxCount, &QPushButton::clicked, this, [=]() {
        m_tcpClientRxCount = 0;
        ui->labelTcpClientRxCount->setText("TCP接收次数：0");
    });
    // 加载图片列表
    loadSettings();

    // 初始化 UI 状态
    initUiState();

    // 初始化通讯对象 + 信号连接
    initCommunication();

    // 初始化串口 UI
    initSerialUi();

    // 初始化 Modbus Client UI
    initModbusClientUi();

    initModbusRtuUi();

    initModbusRtuSlaveUi();
}

MainWindow::~MainWindow()
{
    if (m_tcpClient) {
        m_tcpClient->disconnectFromServer();
    }

    if (m_tcpServer) {
        m_tcpServer->stop();
    }

    if (m_udpComm) {
        m_udpComm->close();
    }

    if (m_serialComm) {
        m_serialComm->close();
    }

    if (m_modbusClient) {
        m_modbusClient->disconnectFromServer();
    }

    if (m_modbusServer) {
        m_modbusServer->stop();
    }

    if (m_modbusRtuClient) {
        m_modbusRtuClient->close();
    }

    delete ui;
}

void MainWindow::initUiState()
{
    // TCP Client
    ui->labelTcpClientRxCount->setText("TCP接收次数：0");
    ui->btnTcpClientConnect->setEnabled(true);
    ui->btnTcpClientDisconnect->setEnabled(false);
    ui->btnTcpClientSend->setEnabled(false);
    ui->lineEditTcpClientIp->setEnabled(true);
    ui->lineEditTcpClientPort->setEnabled(true);

    // TCP Server
    ui->btnTcpServerStart->setEnabled(true);
    ui->btnTcpServerStop->setEnabled(false);
    ui->lineEditTcpServerPort->setEnabled(true);

    // UDP
    ui->labelUdpRxCount->setText("UDP接收次数：0");
    ui->btnUdpBind->setEnabled(true);
    ui->btnUdpClose->setEnabled(false);
    ui->lineEditUdpLocalPort->setEnabled(true);

    // Modbus TCP Server
    ui->btnModbusServerStart->setEnabled(true);
    ui->btnModbusServerStop->setEnabled(false);
    ui->lineEditModbusServerPort->setEnabled(true);
    ui->lineEditModbusServerId->setEnabled(true);

    // Serial
    ui->btnSerialOpen->setEnabled(true);
    ui->btnSerialClose->setEnabled(false);
    ui->btnSerialSend->setEnabled(false);
    ui->comboBoxSerialPort->setEnabled(true);
    ui->comboBoxSerialBaudRate->setEnabled(true);
    ui->comboBoxSerialDataBits->setEnabled(true);
    ui->comboBoxSerialStopBits->setEnabled(true);
    ui->comboBoxSerialParity->setEnabled(true);
}

void MainWindow::displayImage(const QString &filePath)
{
    QFile file(filePath);
    if (!file.open(QIODevice::ReadOnly)) {
        qDebug() << "Failed to open file:" << filePath;
        return;
    }

    QByteArray fileData = file.readAll();
    file.close();

    std::vector<uchar> buffer(fileData.constData(), fileData.constData() + fileData.size());
    cvImage = cv::imdecode(buffer, cv::IMREAD_UNCHANGED);

    if (cvImage.empty()) {
        qDebug() << "Failed to decode image!";
        return;
    }

    // 记录当前正在显示的图片路径
    m_currentImagePath = filePath;

    scene->clear();
    pixmapItem = nullptr;

    QImage qImg;

    cv::Mat rgbImg;
    cv::Mat rgbaImg;

    if (cvImage.channels() == 1) {
        qImg = QImage(
            (const unsigned char *)(cvImage.data),
            cvImage.cols,
            cvImage.rows,
            cvImage.step,
            QImage::Format_Grayscale8
            );
    }
    else if (cvImage.channels() == 3) {
        cv::cvtColor(cvImage, rgbImg, cv::COLOR_BGR2RGB);
        qImg = QImage(
            (const unsigned char *)(rgbImg.data),
            rgbImg.cols,
            rgbImg.rows,
            rgbImg.step,
            QImage::Format_RGB888
            );
    }
    else if (cvImage.channels() == 4) {
        cv::cvtColor(cvImage, rgbaImg, cv::COLOR_BGRA2RGBA);
        qImg = QImage(
            (const unsigned char *)(rgbaImg.data),
            rgbaImg.cols,
            rgbaImg.rows,
            rgbaImg.step,
            QImage::Format_RGBA8888
            );
    }

    pixmapItem = scene->addPixmap(QPixmap::fromImage(qImg.copy()));
    ui->graphicsView->setSceneRect(pixmapItem->boundingRect());

    QTimer::singleShot(10, this, [=]() {
        if (pixmapItem) {
            ui->graphicsView->fitInView(pixmapItem, Qt::KeepAspectRatio);
        }
    });
}


void MainWindow::onListWidgetCurrentItemChanged(QListWidgetItem *current, QListWidgetItem *previous)//选择列表图片
{
    Q_UNUSED(previous);
    if (current) {
        displayImage(current->text()); // text() 存储的就是图像的绝对路径
    }
}

// ==================== 持久化：加载配置 ====================
void MainWindow::loadSettings()
{
    QString configPath = QCoreApplication::applicationDirPath();
    QString jsonPath = configPath + "/imagelist.json";
    QString iniPath = configPath + "/settings.ini";

    // 1. 读取 JSON 恢复列表
    QFile jsonFile(jsonPath);
    if (jsonFile.open(QIODevice::ReadOnly)) {
        QJsonDocument doc = QJsonDocument::fromJson(jsonFile.readAll());
        QJsonArray arr = doc.array();

        for (int i = 0; i < arr.size(); ++i) {
            m_imagePaths.append(arr[i].toString());
        }

        jsonFile.close();
    } else {
        // 如果是第一次启动没有 JSON，自动扫描默认图片文件夹
        QDir dir("C:/qtdevelop/20260701/20260701/pictures");

        if (dir.exists()) {
            QStringList filters;
            filters << "*.jpg" << "*.jpeg" << "*.bmp" << "*.png" << "*.gif";
            dir.setNameFilters(filters);

            QFileInfoList fileList = dir.entryInfoList(QDir::Files | QDir::NoSymLinks);

            for (const QFileInfo &fileInfo : fileList) {
                m_imagePaths.append(fileInfo.absoluteFilePath());
            }
        } else {
            qDebug() << "图片目录不存在，请检查路径！";
        }
    }

    // 用数据源填充列表
    ui->listWidget->addItems(m_imagePaths);

    // 2. 读取 INI 恢复上次选中的项
    QSettings settings(iniPath, QSettings::IniFormat);
    QString lastSelected = settings.value("LastSelectedImage", "").toString();

    int rowToSelect = -1;

    int lastIndex = m_imagePaths.indexOf(lastSelected);
    if (lastIndex != -1) {
        rowToSelect = lastIndex;
    } else if (ui->listWidget->count() > 0) {
        rowToSelect = 0;
    }

    if (rowToSelect != -1) {
        ui->listWidget->setCurrentRow(rowToSelect);
        ui->listWidget->setFocus();

        QListWidgetItem *item = ui->listWidget->item(rowToSelect);
        if (item) {
            displayImage(item->text());
        }
    }
}

// ==================== 持久化：保存配置 ====================
void MainWindow::saveSettings()
{
    QString configPath = QCoreApplication::applicationDirPath();

    // 1. 保存列表到 JSON
    QJsonArray arr;
    // 【关键步骤】遍历数据源
    for (const QString &path : m_imagePaths) {
        arr.append(path);
    }
    QJsonDocument doc(arr);
    QFile jsonFile(configPath + "/imagelist.json");
    if (jsonFile.open(QIODevice::WriteOnly)) {
        jsonFile.write(doc.toJson());
        jsonFile.close();
    }

    // 2. 保存当前选中项到 INI
    QSettings settings(configPath + "/settings.ini", QSettings::IniFormat);
    if (ui->listWidget->currentItem()) {
        settings.setValue("LastSelectedImage", ui->listWidget->currentItem()->text());
    }
}

// ==================== 事件拦截 ====================
void MainWindow::closeEvent(QCloseEvent *event)
{
    saveSettings(); // 窗口关闭前保存
    QMainWindow::closeEvent(event);
}

void MainWindow::resizeEvent(QResizeEvent *event)
{
    // 保证拖拽改变窗口大小时，图像依然保持 FitInView
    if (pixmapItem) {
        ui->graphicsView->fitInView(pixmapItem, Qt::KeepAspectRatio);
    }
    QMainWindow::resizeEvent(event);
}


// --- 新增：事件过滤器的实现 ---
bool MainWindow::eventFilter(QObject *watched, QEvent *event)
{
    // ==================== 处理 listWidget：只允许左键单击加载图片 ====================
    if (watched == ui->listWidget->viewport()) {

        if (event->type() == QEvent::MouseButtonPress) {
            QMouseEvent *mouseEvent = static_cast<QMouseEvent *>(event);

            if (mouseEvent->button() == Qt::LeftButton) {
                m_leftPressedItem = ui->listWidget->itemAt(mouseEvent->pos());
                m_leftPressedPos = mouseEvent->pos();
            }

            return false;
        }

        if (event->type() == QEvent::MouseMove) {
            QMouseEvent *mouseEvent = static_cast<QMouseEvent *>(event);

            if (m_leftPressedItem) {
                int moveDistance = (mouseEvent->pos() - m_leftPressedPos).manhattanLength();

                // 如果鼠标移动距离超过系统拖拽阈值，认为不是单击，而是拖动
                if (moveDistance > QApplication::startDragDistance()) {
                    m_leftPressedItem = nullptr;
                }
            }

            return false;
        }

        if (event->type() == QEvent::MouseButtonRelease) {
            QMouseEvent *mouseEvent = static_cast<QMouseEvent *>(event);

            if (mouseEvent->button() == Qt::LeftButton) {
                QListWidgetItem *releaseItem = ui->listWidget->itemAt(mouseEvent->pos());

                int moveDistance = (mouseEvent->pos() - m_leftPressedPos).manhattanLength();

                bool isClick =
                    m_leftPressedItem &&
                    releaseItem &&
                    m_leftPressedItem == releaseItem &&
                    moveDistance <= QApplication::startDragDistance();

                bool hasModifier =
                    mouseEvent->modifiers() & (Qt::ControlModifier | Qt::ShiftModifier);

                // 普通左键单击才显示图片
                // Ctrl / Shift 多选时不触发图片切换
                if (isClick && !hasModifier) {
                    ui->listWidget->setCurrentItem(releaseItem);
                    displayImage(releaseItem->text());
                }

                m_leftPressedItem = nullptr;
            }

            return false;
        }
    }

    // ==================== 处理 graphicsView：滚轮缩放 ====================
    if (watched == ui->graphicsView->viewport() || watched == ui->graphicsView) {
        if (event->type() == QEvent::Wheel) {
            QWheelEvent *wheelEvent = static_cast<QWheelEvent *>(event);

            double scaleFactor = 1.15;

            if (wheelEvent->angleDelta().y() > 0) {
                ui->graphicsView->scale(scaleFactor, scaleFactor);
            } else {
                ui->graphicsView->scale(1.0 / scaleFactor, 1.0 / scaleFactor);
            }

            return true;
        }
    }

    return QMainWindow::eventFilter(watched, event);
}
// --------------------------------
// ==================== 槽函数：右键菜单 ====================
// ==================== 槽函数：右键菜单 ====================
void MainWindow::onListWidgetCustomContextMenuRequested(const QPoint &pos)
{
    QListWidgetItem *item = ui->listWidget->itemAt(pos);

    QMenu menu(this);

    QAction *removeCurrentAction = nullptr;
    QAction *removeSelectedAction = nullptr;
    QAction *saveAction = nullptr;
    QAction *addFilesAction = nullptr;

    QList<QListWidgetItem *> selectedItems = ui->listWidget->selectedItems();

    if (item) {
        // 如果右键点击的 item 不在当前选中集合中，则先选中它
        // 这样右键单个未选中的项时，符合用户习惯：操作当前右键项
        if (!item->isSelected()) {
            ui->listWidget->clearSelection();
            item->setSelected(true);
            ui->listWidget->setCurrentItem(item);
            selectedItems = ui->listWidget->selectedItems();
        }

        if (selectedItems.count() > 1) {
            removeSelectedAction = menu.addAction(
                QString("移除选中图片 (%1 张)").arg(selectedItems.count())
                );
        } else {
            removeCurrentAction = menu.addAction("移除图片");
        }
    } else {
        saveAction = menu.addAction("保存当前图片到目录...");
        addFilesAction = menu.addAction("添加图片文件...");
    }

    QAction *selectedAction = menu.exec(ui->listWidget->viewport()->mapToGlobal(pos));

    if (!selectedAction) {
        return;
    }

    if (selectedAction == removeCurrentAction || selectedAction == removeSelectedAction) {
        deleteSelectedImages();
    } else if (selectedAction == saveAction) {
        onSaveCurrentImageToDir();
    } else if (selectedAction == addFilesAction) {
        onAddImageFiles();
    }
}
// ==================== 槽函数：选择目录添加图片 ====================
void MainWindow::onBtnAddDirClicked()
{
    QString dirPath = QFileDialog::getExistingDirectory(
        this, "选择图片目录", QCoreApplication::applicationDirPath()
        );
    if (dirPath.isEmpty()) return;

    QDir dir(dirPath);
    QStringList filters;
    filters << "*.jpg" << "*.jpeg" << "*.png" << "*.bmp" << "*.gif";
    dir.setNameFilters(filters);
    QFileInfoList fileList = dir.entryInfoList(QDir::Files | QDir::NoSymLinks);

    int addedCount = 0;
    for (const QFileInfo &fileInfo : fileList) {
        QString filePath = fileInfo.absoluteFilePath();
        // 【关键步骤】检查数据源中是否已存在
        if (!m_imagePaths.contains(filePath)) {
            m_imagePaths.append(filePath);
            addedCount++;
        }
    }
    
    if (addedCount > 0) {
        int firstNewRow = m_imagePaths.count() - addedCount;
        refreshListWidget(firstNewRow);
        qDebug() << "成功添加" << addedCount << "张图片";
    } else {
        qDebug() << "该目录下的图片已全部在列表中";
    }
}
// ==================== 槽函数：保存当前图片到指定目录 ====================
void MainWindow::onSaveCurrentImageToDir()
{
    // 如果没有图片在显示，直接返回
    if (cvImage.empty()) {
        qDebug() << "当前没有图片可保存";
        return;
    }

    // 弹出目录选择对话框
    QString dirPath = QFileDialog::getExistingDirectory(
        this,
        "选择保存目录",
        QCoreApplication::applicationDirPath()
        );

    if (dirPath.isEmpty()) return;  // 用户点了取消

    // 生成文件名（可以用时间戳避免重名）
    QString fileName = "image_" + QDateTime::currentDateTime().toString("yyyyMMdd_hhmmss") + ".png";
    QString savePath = dirPath + "/" + fileName;

    // 使用 OpenCV 保存图片
    bool success = cv::imwrite(savePath.toStdString(), cvImage);

    if (success) {
        qDebug() << "图片已保存到：" << savePath;
        // 可选：弹出提示框
        QMessageBox::information(this, "保存成功", "图片已保存到：\n" + savePath);
    } else {
        qDebug() << "图片保存失败！";
        QMessageBox::warning(this, "保存失败", "图片保存失败，请检查目录权限。");
    }
}
// ==================== 槽函数：从任意目录选择图片文件添加 ====================
void MainWindow::onAddImageFiles()
{
    QStringList filePaths = QFileDialog::getOpenFileNames(
        this, "选择图片文件", QCoreApplication::applicationDirPath(),
        "图片文件 (*.jpg *.jpeg *.png *.bmp *.gif)"
        );
    if (filePaths.isEmpty()) return;

    int addedCount = 0;
    for (const QString &filePath : filePaths) {
        // 【关键步骤】检查数据源中是否已存在
        if (!m_imagePaths.contains(filePath)) {
            m_imagePaths.append(filePath);
            addedCount++;
        }
    }

    if (addedCount > 0) {
        int firstNewRow = m_imagePaths.count() - addedCount;
        refreshListWidget(firstNewRow);
        appendLog(QString("[Image] 成功添加 %1 张图片").arg(addedCount));
    } else {
        appendLog("[Image] 该目录下的图片已全部在列表中");
    }
}
void MainWindow::refreshListWidget(int rowToSelect)
{
    ui->listWidget->clear();
    ui->listWidget->addItems(m_imagePaths);

    if (m_imagePaths.isEmpty()) {
        scene->clear();
        pixmapItem = nullptr;
        cvImage.release();
        return;
    }

    if (rowToSelect < 0) {
        rowToSelect = 0;
    }

    if (rowToSelect >= m_imagePaths.count()) {
        rowToSelect = m_imagePaths.count() - 1;
    }

    ui->listWidget->setCurrentRow(rowToSelect);
    ui->listWidget->setFocus();

    QListWidgetItem *item = ui->listWidget->item(rowToSelect);
    if (item) {
        displayImage(item->text());
    }
}
void MainWindow::deleteSelectedImages()
{
    QList<QListWidgetItem *> selectedItems = ui->listWidget->selectedItems();

    if (selectedItems.isEmpty()) {
        return;
    }

    // 记录删除前正在 graphicsView 中显示的图片
    QString displayedPathBeforeDelete = m_currentImagePath;

    // 记录被删除项中最靠前的行号，用于当前显示图片也被删除时选择附近图片
    int firstSelectedRow = ui->listWidget->row(selectedItems.first());

    for (QListWidgetItem *item : selectedItems) {
        if (!item) continue;

        int row = ui->listWidget->row(item);
        if (row >= 0 && row < firstSelectedRow) {
            firstSelectedRow = row;
        }
    }

    // 收集需要删除的路径
    QStringList pathsToRemove;

    for (QListWidgetItem *item : selectedItems) {
        if (item) {
            pathsToRemove.append(item->text());
        }
    }

    if (pathsToRemove.isEmpty()) {
        return;
    }

    // 从数据源中删除
    for (const QString &path : pathsToRemove) {
        m_imagePaths.removeAll(path);
    }

    // 重新刷新列表，但先不要调用 displayImage
    ui->listWidget->clear();
    ui->listWidget->addItems(m_imagePaths);

    // 如果列表已经空了，清空显示
    if (m_imagePaths.isEmpty()) {
        scene->clear();
        pixmapItem = nullptr;
        cvImage.release();
        m_currentImagePath.clear();
        return;
    }

    // 情况 1：删除的不是当前正在显示的图片
    // 那么继续显示原来的图片，并且在列表中重新选中它
    int displayedIndex = m_imagePaths.indexOf(displayedPathBeforeDelete);

    if (displayedIndex != -1) {
        ui->listWidget->setCurrentRow(displayedIndex);
        ui->listWidget->item(displayedIndex)->setSelected(true);

        // 注意：这里不需要重新 displayImage
        // 因为 graphicsView 里面本来就已经显示着这张图
        // 如果你希望重新加载一次，也可以打开下面这句：
        // displayImage(displayedPathBeforeDelete);

        return;
    }

    // 情况 2：当前正在显示的图片也被删除了
    // 那么选择删除位置附近的一张图片显示
    int newRow = firstSelectedRow;

    if (newRow >= m_imagePaths.count()) {
        newRow = m_imagePaths.count() - 1;
    }

    if (newRow < 0) {
        newRow = 0;
    }

    ui->listWidget->setCurrentRow(newRow);
    ui->listWidget->item(newRow)->setSelected(true);

    displayImage(m_imagePaths[newRow]);
}
void MainWindow::initCommunication()
{
    m_tcpClient = new TcpClient(this);
    m_tcpServer = new TcpServer(this);
    m_udpComm = new UdpComm(this);
    m_serialComm = new SerialComm(this);
    m_modbusClient = new ModbusClient(this);
    m_modbusServer = new ModbusServer(this);
    m_modbusRtuClient = new ModbusRtuClient(this);

    initCommunicationSignals();

    appendLog("通讯模块初始化完成");
}
void MainWindow::initCommunicationSignals()
{               //ModbusRtuClient
    connect(m_modbusRtuClient, &ModbusRtuClient::opened,
            this,
            [=]() {
                appendLog("[Modbus RTU Client] opened");

                ui->btnModbusRtuOpen->setEnabled(false);
                ui->btnModbusRtuClose->setEnabled(true);
                ui->btnModbusRtuReadHolding->setEnabled(true);
                ui->btnModbusRtuWriteSingle->setEnabled(true);
                ui->btnModbusRtuWriteMultiple->setEnabled(true);

                ui->comboBoxModbusRtuPort->setEnabled(false);
                ui->comboBoxModbusRtuBaudRate->setEnabled(false);
                ui->comboBoxModbusRtuDataBits->setEnabled(false);
                ui->comboBoxModbusRtuStopBits->setEnabled(false);
                ui->comboBoxModbusRtuParity->setEnabled(false);
            });

    connect(m_modbusRtuClient, &ModbusRtuClient::closed,
            this,
            [=]() {
                appendLog("[Modbus RTU Client] closed");

                ui->btnModbusRtuOpen->setEnabled(true);
                ui->btnModbusRtuClose->setEnabled(false);
                ui->btnModbusRtuReadHolding->setEnabled(false);
                ui->btnModbusRtuWriteSingle->setEnabled(false);
                ui->btnModbusRtuWriteMultiple->setEnabled(false);

                ui->comboBoxModbusRtuPort->setEnabled(true);
                ui->comboBoxModbusRtuBaudRate->setEnabled(true);
                ui->comboBoxModbusRtuDataBits->setEnabled(true);
                ui->comboBoxModbusRtuStopBits->setEnabled(true);
                ui->comboBoxModbusRtuParity->setEnabled(true);
            });

    connect(m_modbusRtuClient, &ModbusRtuClient::logMessage,
            this,
            [=](const QString &msg) {
                appendLog(msg);
            });

    connect(m_modbusRtuClient, &ModbusRtuClient::errorOccurred,
            this,
            [=](const QString &error) {
                appendLog(QString("[Modbus RTU Client Error] %1").arg(error));
            });

    connect(m_modbusRtuClient, &ModbusRtuClient::holdingRegistersRead,
            this,
            [=](quint8 slaveId, quint16 startAddress, QVector<quint16> values) {
                appendLog(QString("[Modbus RTU Client] Read Holding OK. slave=%1, start=%2, count=%3")
                              .arg(slaveId)
                              .arg(startAddress)
                              .arg(values.size()));

                for (int i = 0; i < values.size(); ++i) {
                    appendLog(QString("  RTU HR[%1] = %2")
                                  .arg(startAddress + i)
                                  .arg(values[i]));
                }
            });

    connect(m_modbusRtuClient, &ModbusRtuClient::writeFinished,
            this,
            [=](quint8 slaveId, quint8 functionCode, quint16 startAddress, quint16 count) {
                appendLog(QString("[Modbus RTU Client] Write OK. slave=%1, func=0x%2, start=%3, count=%4")
                              .arg(slaveId)
                              .arg(functionCode, 2, 16, QChar('0'))
                              .arg(startAddress)
                              .arg(count)
                              .toUpper());
            });
    //Modbus TCP Server
    connect(m_modbusServer, &ModbusServer::holdingRegisterChanged,
            this,
            [=](int address, quint16 value) {
                ui->lineEditModbusRegAddr->setText(QString::number(address));
                ui->lineEditModbusRegValue->setText(QString::number(value));
            });
    // ==================== Modbus TCP Client ====================
    connect(m_modbusClient, &ModbusClient::logMessage,
            this,
            [=](const QString &msg) {
                appendLog(msg);
            });
    connect(m_modbusClient, &ModbusClient::connected,
            this,
            [=]() {
                appendLog("[Modbus TCP Client] connected");
                ui->btnModbusClientConnect->setEnabled(false);
                ui->btnModbusClientDisconnect->setEnabled(true);
                ui->btnModbusClientReadHolding->setEnabled(true);
                ui->btnModbusClientWriteSingle->setEnabled(true);
                ui->btnModbusClientWriteMultiple->setEnabled(true);
                ui->lineEditModbusClientIp->setEnabled(false);
                ui->lineEditModbusClientPort->setEnabled(false);
            });

    connect(m_modbusClient, &ModbusClient::disconnected,
            this,
            [=]() {
                appendLog("[Modbus TCP Client] disconnected");

                ui->btnModbusClientConnect->setEnabled(true);
                ui->btnModbusClientDisconnect->setEnabled(false);
                ui->btnModbusClientReadHolding->setEnabled(false);
                ui->btnModbusClientWriteSingle->setEnabled(false);
                ui->btnModbusClientWriteMultiple->setEnabled(false);

                ui->lineEditModbusClientIp->setEnabled(true);
                ui->lineEditModbusClientPort->setEnabled(true);
            });

    connect(m_modbusClient, &ModbusClient::errorOccurred,
            this,
            [=](const QString &error) {
                appendLog(QString("[Modbus TCP Client Error] %1").arg(error));
            });

    connect(m_modbusClient, &ModbusClient::holdingRegistersRead,
            this,
            [=](int startAddress, QVector<quint16> values) {
                appendLog(QString("[Modbus TCP Client] Read Holding Registers OK. start=%1, count=%2")
                              .arg(startAddress)
                              .arg(values.size()));

                for (int i = 0; i < values.size(); ++i) {
                    appendLog(QString("  HR[%1] = %2")
                                  .arg(startAddress + i)
                                  .arg(values[i]));
                }
            });

    connect(m_modbusClient, &ModbusClient::writeFinished,
            this,
            [=](const QString &message) {
                appendLog(QString("[Modbus TCP Client] %1").arg(message));
            });
    // ==================== Serial COM ====================
    connect(m_serialComm, &SerialComm::opened,
            this,
            [=]() {
                appendLog("[Serial] opened");

                ui->btnSerialOpen->setEnabled(false);
                ui->btnSerialClose->setEnabled(true);
                ui->btnSerialSend->setEnabled(true);

                ui->comboBoxSerialPort->setEnabled(false);
                ui->comboBoxSerialBaudRate->setEnabled(false);
                ui->comboBoxSerialDataBits->setEnabled(false);
                ui->comboBoxSerialStopBits->setEnabled(false);
                ui->comboBoxSerialParity->setEnabled(false);
            });

    connect(m_serialComm, &SerialComm::closed,
            this,
            [=]() {
                appendLog("[Serial] closed");

                ui->btnSerialOpen->setEnabled(true);
                ui->btnSerialClose->setEnabled(false);
                ui->btnSerialSend->setEnabled(false);

                ui->comboBoxSerialPort->setEnabled(true);
                ui->comboBoxSerialBaudRate->setEnabled(true);
                ui->comboBoxSerialDataBits->setEnabled(true);
                ui->comboBoxSerialStopBits->setEnabled(true);
                ui->comboBoxSerialParity->setEnabled(true);
            });

    connect(m_serialComm, &SerialComm::dataReceived,
            this,
            [=](const QByteArray &data) {
                appendLog(QString("[Serial Recv HEX] %1")
                              .arg(QString::fromLatin1(data.toHex(' ').toUpper())));

                appendLog(QString("[Serial Recv UTF8] %1")
                              .arg(QString::fromUtf8(data)));
            });

    connect(m_serialComm, &SerialComm::errorOccurred,
            this,
            [=](const QString &error) {
                appendLog(QString("[Serial Error] %1").arg(error));
            });
    // ==================== TCP Client ====================
    connect(m_tcpClient, &TcpClient::connected,
            this,
            [=]() {
                appendLog("[TCP Client] connected");
                ui->btnTcpClientConnect->setEnabled(false);
                ui->btnTcpClientDisconnect->setEnabled(true);
                ui->btnTcpClientSend->setEnabled(true);
                ui->lineEditTcpClientIp->setEnabled(false);
                ui->lineEditTcpClientPort->setEnabled(false);
            });
    connect(m_tcpClient, &TcpClient::disconnected,
            this,
            [=]() {
                appendLog("[TCP Client] disconnected");

                // 断开连接时清零接收次数
                m_tcpClientRxCount = 0;
                ui->labelTcpClientRxCount->setText("TCP接收次数：0");

                ui->btnTcpClientConnect->setEnabled(true);
                ui->btnTcpClientDisconnect->setEnabled(false);
                ui->btnTcpClientSend->setEnabled(false);
                ui->lineEditTcpClientIp->setEnabled(true);
                ui->lineEditTcpClientPort->setEnabled(true);
            });
    connect(m_tcpClient, &TcpClient::dataReceived,
            this,
            [=](const QByteArray &data) {
                if (data.isEmpty()) {
                    return;
                }

                // TCP 接收次数 +1
                m_tcpClientRxCount++;

                // 更新界面
                ui->labelTcpClientRxCount->setText(
                    QString("TCP接收次数：%1").arg(m_tcpClientRxCount)
                    );

                appendLog(QString("[TCP Client Recv HEX] %1")
                              .arg(QString::fromLatin1(data.toHex(' ').toUpper())));

                appendLog(QString("[TCP Client Recv UTF8] %1")
                              .arg(QString::fromUtf8(data)));
            });
    connect(m_tcpClient, &TcpClient::errorOccurred,
            this,
            [=](const QString &error) {
                appendLog(QString("[TCP Client Error] %1").arg(error));
            });

    connect(m_tcpServer, &TcpServer::clientConnected,
            this,
            [=](const QString &peer) {
                appendLog(QString("[TCP Server] client connected: %1").arg(peer));
            });

    connect(m_tcpServer, &TcpServer::clientDisconnected,
            this,
            [=](const QString &peer) {
                appendLog(QString("[TCP Server] client disconnected: %1").arg(peer));
            });

    connect(m_tcpServer, &TcpServer::dataReceived,
            this,
            [=](const QString &peer, const QByteArray &data) {
                appendLog(QString("[TCP Server Recv From] %1").arg(peer));

                appendLog(QString("[TCP Server Recv HEX] %1")
                              .arg(QString::fromLatin1(data.toHex(' ').toUpper())));

                appendLog(QString("[TCP Server Recv UTF8] %1")
                              .arg(QString::fromUtf8(data)));
            });

    connect(m_tcpServer, &TcpServer::errorOccurred,
            this,
            [=](const QString &error) {
                appendLog(QString("[TCP Server Error] %1").arg(error));
            });

    connect(m_udpComm, &UdpComm::dataReceived,
            this,
            [=](const QString &ip, quint16 port, const QByteArray &data) {
                if (data.isEmpty()) {
                    return;
                }

                // UDP 接收次数 +1
                m_udpRxCount++;

                // 更新界面
                ui->labelUdpRxCount->setText(
                    QString("UDP接收次数：%1").arg(m_udpRxCount)
                    );

                appendLog(QString("[UDP Recv From] %1:%2").arg(ip).arg(port));

                appendLog(QString("[UDP Recv HEX] %1")
                              .arg(QString::fromLatin1(data.toHex(' ').toUpper())));

                appendLog(QString("[UDP Recv UTF8] %1")
                              .arg(QString::fromUtf8(data)));
            });

    connect(m_udpComm, &UdpComm::errorOccurred,
            this,
            [=](const QString &error) {
                appendLog(QString("[UDP Error] %1").arg(error));
            });

    connect(m_modbusServer, &ModbusServer::errorOccurred,
            this,
            [=](const QString &error) {
                appendLog(QString("[Modbus TCP Server Error] %1").arg(error));
            });
}

void MainWindow::appendLog(const QString &text)
{
    QString msg = QDateTime::currentDateTime().toString("hh:mm:ss.zzz ")
    + text;

    qDebug().noquote() << msg;

    if (ui->textEditLog) {
        ui->textEditLog->append(msg);
    }
}
void MainWindow::on_btnTcpServerStart_clicked()
{
    bool okPort = false;
    quint16 port = ui->lineEditTcpServerPort->text().trimmed().toUShort(&okPort);

    if (!okPort || port == 0) {
        appendLog("[TCP Server] 端口无效");
        return;
    }

    bool ok = m_tcpServer->start(port);

    if (ok) {
        appendLog(QString("[TCP Server] started at port %1").arg(port));

        ui->btnTcpServerStart->setEnabled(false);
        ui->btnTcpServerStop->setEnabled(true);
        ui->lineEditTcpServerPort->setEnabled(false);
    } else {
        appendLog(QString("[TCP Server] start failed at port %1").arg(port));

        ui->btnTcpServerStart->setEnabled(true);
        ui->btnTcpServerStop->setEnabled(false);
        ui->lineEditTcpServerPort->setEnabled(true);
    }
}
void MainWindow::on_btnTcpServerStop_clicked()
{
    m_tcpServer->stop();
    appendLog("[TCP Server] stopped");

    ui->btnTcpServerStart->setEnabled(true);
    ui->btnTcpServerStop->setEnabled(false);
    ui->lineEditTcpServerPort->setEnabled(true);
}
void MainWindow::on_btnTcpServerSend_clicked()
{
    QString text = ui->textEditTcpServerSend->toPlainText();

    if (text.isEmpty()) {
        appendLog("[TCP Server] 发送内容为空");
        return;
    }

    QByteArray data;

    if (ui->checkBoxTcpServerSendHex->isChecked()) {
        bool ok = false;
        data = hexStringToByteArray(text, &ok);

        if (!ok) {
            appendLog("[TCP Server] HEX 格式错误");
            appendLog("[TCP Server] 示例：01 03 00 00 00 02");
            return;
        }

        appendLog(QString("[TCP Server Send HEX] %1")
                      .arg(QString::fromLatin1(data.toHex(' ').toUpper())));
    } else {
        data = text.toUtf8();

        appendLog(QString("[TCP Server Send UTF8] %1").arg(text));
        appendLog(QString("[TCP Server Send HEX] %1")
                      .arg(QString::fromLatin1(data.toHex(' ').toUpper())));
    }

    qint64 len = m_tcpServer->sendDataToAll(data);

    appendLog(QString("[TCP Server Send] bytes = %1").arg(len));
}
void MainWindow::on_btnUdpBind_clicked()
{
    bool okPort = false;
    quint16 port = ui->lineEditUdpLocalPort->text().trimmed().toUShort(&okPort);

    if (!okPort || port == 0) {
        appendLog("[UDP] 本地端口无效");
        return;
    }

    bool ok = m_udpComm->bindPort(port);

    if (ok) {
        appendLog(QString("[UDP] bind local port success: %1").arg(port));

        ui->btnUdpBind->setEnabled(false);
        ui->btnUdpClose->setEnabled(true);
        ui->lineEditUdpLocalPort->setEnabled(false);
    } else {
        appendLog(QString("[UDP] bind local port failed: %1").arg(port));

        ui->btnUdpBind->setEnabled(true);
        ui->btnUdpClose->setEnabled(false);
        ui->lineEditUdpLocalPort->setEnabled(true);
    }
}
void MainWindow::on_btnUdpClose_clicked()
{
    m_udpComm->close();
    appendLog("[UDP] closed");

    m_udpRxCount = 0;
    ui->labelUdpRxCount->setText("UDP接收次数：0");

    ui->btnUdpBind->setEnabled(true);
    ui->btnUdpClose->setEnabled(false);
    ui->lineEditUdpLocalPort->setEnabled(true);
}
void MainWindow::on_btnUdpSend_clicked()
{
    QString ip = ui->lineEditUdpTargetIp->text().trimmed();

    bool okPort = false;
    quint16 port = ui->lineEditUdpTargetPort->text().trimmed().toUShort(&okPort);

    QString text = ui->textEditUdpSend->toPlainText();

    if (ip.isEmpty()) {
        appendLog("[UDP] 目标 IP 为空");
        return;
    }

    if (!okPort || port == 0) {
        appendLog("[UDP] 目标端口无效");
        return;
    }

    if (text.isEmpty()) {
        appendLog("[UDP] 发送内容为空");
        return;
    }

    QByteArray data;

    if (ui->checkBoxUdpSendHex->isChecked()) {
        bool ok = false;
        data = hexStringToByteArray(text, &ok);

        if (!ok) {
            appendLog("[UDP] HEX 格式错误");
            appendLog("[UDP] 示例：01 03 00 00 00 02");
            return;
        }

        appendLog(QString("[UDP Send HEX] %1")
                      .arg(QString::fromLatin1(data.toHex(' ').toUpper())));
    } else {
        data = text.toUtf8();

        appendLog(QString("[UDP Send UTF8] %1").arg(text));
        appendLog(QString("[UDP Send HEX] %1")
                      .arg(QString::fromLatin1(data.toHex(' ').toUpper())));
    }

    qint64 len = m_udpComm->sendData(ip, port, data);

    appendLog(QString("[UDP Send] to %1:%2, bytes = %3")
                  .arg(ip)
                  .arg(port)
                  .arg(len));
}
void MainWindow::on_btnModbusServerStart_clicked()
{
    int port = ui->lineEditModbusServerPort->text().trimmed().toInt();
    int serverAddress = ui->lineEditModbusServerId->text().trimmed().toInt();

    if (port <= 0) {
        appendLog("[Modbus TCP Server] 端口无效");
        return;
    }

    if (serverAddress <= 0) {
        appendLog("[Modbus TCP Server] 站号无效");
        return;
    }

    bool ok = m_modbusServer->startTcp(port, serverAddress);

    if (ok) {
        appendLog(QString("[Modbus TCP Server] started. port = %1 serverAddress = %2")
                      .arg(port)
                      .arg(serverAddress));

        m_modbusServer->setHoldingRegister(0, 100);
        m_modbusServer->setHoldingRegister(1, 200);
        m_modbusServer->setHoldingRegister(2, 300);

        appendLog("[Modbus TCP Server] init HR[0]=100, HR[1]=200, HR[2]=300");

        ui->btnModbusServerStart->setEnabled(false);
        ui->btnModbusServerStop->setEnabled(true);
        ui->lineEditModbusServerPort->setEnabled(false);
        ui->lineEditModbusServerId->setEnabled(false);
    } else {
        appendLog("[Modbus TCP Server] start failed");

        ui->btnModbusServerStart->setEnabled(true);
        ui->btnModbusServerStop->setEnabled(false);
        ui->lineEditModbusServerPort->setEnabled(true);
        ui->lineEditModbusServerId->setEnabled(true);
    }
}
void MainWindow::on_btnModbusServerStop_clicked()
{
    m_modbusServer->stop();
    appendLog("[Modbus TCP Server] stopped");

    ui->btnModbusServerStart->setEnabled(true);
    ui->btnModbusServerStop->setEnabled(false);
    ui->lineEditModbusServerPort->setEnabled(true);
    ui->lineEditModbusServerId->setEnabled(true);
}
void MainWindow::on_btnModbusSetReg_clicked()
{
    int addr = ui->lineEditModbusRegAddr->text().trimmed().toInt();
    int value = ui->lineEditModbusRegValue->text().trimmed().toInt();

    if (addr < 0) {
        appendLog("[Modbus] 寄存器地址无效");
        return;
    }

    bool ok = m_modbusServer->setHoldingRegister(addr, value);

    if (ok) {
        appendLog(QString("[Modbus] set HR[%1] = %2").arg(addr).arg(value));
    } else {
        appendLog(QString("[Modbus] set HR[%1] failed").arg(addr));
    }
}
QByteArray MainWindow::hexStringToByteArray(const QString &hexText, bool *ok)
{
    if (ok) {
        *ok = false;
    }

    QString text = hexText.trimmed();

    if (text.isEmpty()) {
        return QByteArray();
    }

    // 去掉常见分隔符
    text.remove(' ');
    text.remove('\n');
    text.remove('\r');
    text.remove('\t');
    text.remove(',');
    text.remove(';');

    // 支持 0x01 0x03 这种写法
    text.replace("0x", "", Qt::CaseInsensitive);

    // HEX 字符串长度必须是偶数
    if (text.length() % 2 != 0) {
        return QByteArray();
    }

    // 检查是否都是合法 HEX 字符
    for (const QChar &ch : text) {
        if (!ch.isDigit() &&
            !(ch >= 'a' && ch <= 'f') &&
            !(ch >= 'A' && ch <= 'F')) {
            return QByteArray();
        }
    }

    QByteArray data;

    for (int i = 0; i < text.length(); i += 2) {
        QString byteString = text.mid(i, 2);

        bool convertOk = false;
        char byte = static_cast<char>(byteString.toUInt(&convertOk, 16));

        if (!convertOk) {
            return QByteArray();
        }

        data.append(byte);
    }

    if (ok) {
        *ok = true;
    }

    return data;
}
QString MainWindow::byteArrayToPrintableText(const QByteArray &data)
{
    QString result;

    for (unsigned char ch : data) {
        if (ch >= 0x20 && ch <= 0x7E) {
            result.append(QChar(ch));
        } else {
            result.append('.');
        }
    }

    return result;
}
void MainWindow::on_btnClearLog_clicked()
{
    if (!ui->textEditLog) {
        return;
    }

    ui->textEditLog->clear();

    qDebug() << "当前日志已清空";
}
void MainWindow::on_btnSaveLog_clicked()
{
    if (!ui->textEditLog) {
        return;
    }

    QString logText = ui->textEditLog->toPlainText();

    if (logText.trimmed().isEmpty()) {
        QMessageBox::information(this, "提示", "当前日志为空，无需保存。");
        return;
    }

    QString defaultFileName = "log_" +
                              QDateTime::currentDateTime().toString("yyyyMMdd_hhmmss") +
                              ".txt";

    QString filePath = QFileDialog::getSaveFileName(
        this,
        "保存日志到文件",
        QCoreApplication::applicationDirPath() + "/" + defaultFileName,
        "文本文件 (*.txt);;所有文件 (*.*)"
        );

    if (filePath.isEmpty()) {
        return;
    }

    QFile file(filePath);

    if (!file.open(QIODevice::WriteOnly | QIODevice::Text)) {
        QMessageBox::warning(this, "保存失败", "日志文件打开失败，请检查路径或权限。");
        return;
    }

    QTextStream out(&file);
#if QT_VERSION < QT_VERSION_CHECK(6, 0, 0)
    out.setCodec("UTF-8");
#endif

    out << logText;

    file.close();

    QMessageBox::information(this, "保存成功", "日志已保存到：\n" + filePath);

    appendLog(QString("[Log] 日志已保存到文件：%1").arg(filePath));
}
void MainWindow::on_btnTcpClientConnect_clicked()
{
    QString ip = ui->lineEditTcpClientIp->text().trimmed();

    bool okPort = false;
    quint16 port = ui->lineEditTcpClientPort->text().trimmed().toUShort(&okPort);

    if (ip.isEmpty()) {
        appendLog("[TCP Client] 服务器 IP 为空");
        return;
    }

    if (!okPort || port == 0) {
        appendLog("[TCP Client] 服务器端口无效");
        return;
    }

    appendLog(QString("[TCP Client] connecting to %1:%2 ...")
                  .arg(ip)
                  .arg(port));

    m_tcpClient->connectToServer(ip, port);
}
void MainWindow::on_btnTcpClientDisconnect_clicked()
{
    m_tcpClient->disconnectFromServer();

    appendLog("[TCP Client] disconnect request");
}
void MainWindow::on_btnTcpClientSend_clicked()
{
    QString text = ui->textEditTcpClientSend->toPlainText();

    if (text.isEmpty()) {
        appendLog("[TCP Client] 发送内容为空");
        return;
    }

    QByteArray data;

    if (ui->checkBoxTcpClientSendHex->isChecked()) {
        bool ok = false;
        data = hexStringToByteArray(text, &ok);

        if (!ok) {
            appendLog("[TCP Client] HEX 格式错误");
            appendLog("[TCP Client] 示例：01 03 00 00 00 02");
            return;
        }

        appendLog(QString("[TCP Client Send HEX] %1")
                      .arg(QString::fromLatin1(data.toHex(' ').toUpper())));
    } else {
        data = text.toUtf8();

        appendLog(QString("[TCP Client Send UTF8] %1").arg(text));
        appendLog(QString("[TCP Client Send HEX] %1")
                      .arg(QString::fromLatin1(data.toHex(' ').toUpper())));
    }

    qint64 len = m_tcpClient->sendData(data);

    appendLog(QString("[TCP Client Send] bytes = %1").arg(len));
}
void MainWindow::initSerialUi()
{
    // 波特率
    ui->comboBoxSerialBaudRate->clear();
    ui->comboBoxSerialBaudRate->addItem("9600");
    ui->comboBoxSerialBaudRate->addItem("19200");
    ui->comboBoxSerialBaudRate->addItem("38400");
    ui->comboBoxSerialBaudRate->addItem("57600");
    ui->comboBoxSerialBaudRate->addItem("115200");
    ui->comboBoxSerialBaudRate->setCurrentText("9600");

    // 数据位
    ui->comboBoxSerialDataBits->clear();
    ui->comboBoxSerialDataBits->addItem("5");
    ui->comboBoxSerialDataBits->addItem("6");
    ui->comboBoxSerialDataBits->addItem("7");
    ui->comboBoxSerialDataBits->addItem("8");
    ui->comboBoxSerialDataBits->setCurrentText("8");

    // 停止位
    ui->comboBoxSerialStopBits->clear();
    ui->comboBoxSerialStopBits->addItem("1");
    ui->comboBoxSerialStopBits->addItem("1.5");
    ui->comboBoxSerialStopBits->addItem("2");
    ui->comboBoxSerialStopBits->setCurrentText("1");

    // 校验位
    ui->comboBoxSerialParity->clear();
    ui->comboBoxSerialParity->addItem("None");
    ui->comboBoxSerialParity->addItem("Even");
    ui->comboBoxSerialParity->addItem("Odd");
    ui->comboBoxSerialParity->addItem("Mark");
    ui->comboBoxSerialParity->addItem("Space");
    ui->comboBoxSerialParity->setCurrentText("None");

    refreshSerialPorts();

    ui->btnSerialOpen->setEnabled(true);
    ui->btnSerialClose->setEnabled(false);
    ui->btnSerialSend->setEnabled(false);
}
void MainWindow::refreshSerialPorts()
{
    QString current = ui->comboBoxSerialPort->currentText();

    ui->comboBoxSerialPort->clear();

    const auto ports = QSerialPortInfo::availablePorts();

    for (const QSerialPortInfo &info : ports) {
        ui->comboBoxSerialPort->addItem(info.portName());
    }

    int index = ui->comboBoxSerialPort->findText(current);
    if (index >= 0) {
        ui->comboBoxSerialPort->setCurrentIndex(index);
    }

    appendLog(QString("[Serial] found %1 port(s)").arg(ports.size()));
}
void MainWindow::on_btnSerialRefresh_clicked()
{
    refreshSerialPorts();
}
void MainWindow::on_btnSerialOpen_clicked()
{
    QString portName = ui->comboBoxSerialPort->currentText().trimmed();

    if (portName.isEmpty()) {
        appendLog("[Serial] 串口号为空");
        return;
    }

    bool okBaud = false;
    qint32 baudRate = ui->comboBoxSerialBaudRate->currentText().toInt(&okBaud);

    if (!okBaud || baudRate <= 0) {
        appendLog("[Serial] 波特率无效");
        return;
    }

    QSerialPort::DataBits dataBits = QSerialPort::Data8;
    QString dataBitsText = ui->comboBoxSerialDataBits->currentText();

    if (dataBitsText == "5") {
        dataBits = QSerialPort::Data5;
    } else if (dataBitsText == "6") {
        dataBits = QSerialPort::Data6;
    } else if (dataBitsText == "7") {
        dataBits = QSerialPort::Data7;
    } else {
        dataBits = QSerialPort::Data8;
    }

    QSerialPort::StopBits stopBits = QSerialPort::OneStop;
    QString stopBitsText = ui->comboBoxSerialStopBits->currentText();

    if (stopBitsText == "1") {
        stopBits = QSerialPort::OneStop;
    } else if (stopBitsText == "1.5") {
        stopBits = QSerialPort::OneAndHalfStop;
    } else if (stopBitsText == "2") {
        stopBits = QSerialPort::TwoStop;
    }

    QSerialPort::Parity parity = QSerialPort::NoParity;
    QString parityText = ui->comboBoxSerialParity->currentText();

    if (parityText == "None") {
        parity = QSerialPort::NoParity;
    } else if (parityText == "Even") {
        parity = QSerialPort::EvenParity;
    } else if (parityText == "Odd") {
        parity = QSerialPort::OddParity;
    } else if (parityText == "Mark") {
        parity = QSerialPort::MarkParity;
    } else if (parityText == "Space") {
        parity = QSerialPort::SpaceParity;
    }

    appendLog(QString("[Serial] opening %1, baud=%2, data=%3, stop=%4, parity=%5")
                  .arg(portName)
                  .arg(baudRate)
                  .arg(dataBitsText)
                  .arg(stopBitsText)
                  .arg(parityText));

    bool ret = m_serialComm->open(portName,
                                  baudRate,
                                  dataBits,
                                  parity,
                                  stopBits);

    if (!ret) {
        appendLog("[Serial] open failed");
    }
}
void MainWindow::on_btnSerialClose_clicked()
{
    m_serialComm->close();
}
void MainWindow::on_btnSerialSend_clicked()
{
    QString text = ui->textEditSerialSend->toPlainText();

    if (text.isEmpty()) {
        appendLog("[Serial] 发送内容为空");
        return;
    }

    QByteArray data;

    if (ui->checkBoxSerialSendHex->isChecked()) {
        bool ok = false;
        data = hexStringToByteArray(text, &ok);

        if (!ok) {
            appendLog("[Serial] HEX 格式错误");
            appendLog("[Serial] 示例：01 03 00 00 00 02");
            return;
        }

        appendLog(QString("[Serial Send HEX] %1")
                      .arg(QString::fromLatin1(data.toHex(' ').toUpper())));
    } else {
        data = text.toUtf8();

        appendLog(QString("[Serial Send UTF8] %1").arg(text));
        appendLog(QString("[Serial Send HEX] %1")
                      .arg(QString::fromLatin1(data.toHex(' ').toUpper())));
    }

    qint64 len = m_serialComm->sendData(data);

    appendLog(QString("[Serial Send] bytes = %1").arg(len));
}
void MainWindow::initModbusClientUi()
{
    ui->lineEditModbusClientIp->setText("127.0.0.1");
    ui->lineEditModbusClientPort->setText("1502");

    ui->spinBoxModbusClientUnitId->setRange(1, 247);
    ui->spinBoxModbusClientUnitId->setValue(1);

    ui->spinBoxModbusClientStartAddr->setRange(0, 65535);
    ui->spinBoxModbusClientStartAddr->setValue(0);

    ui->spinBoxModbusClientCount->setRange(1, 125);
    ui->spinBoxModbusClientCount->setValue(10);

    ui->spinBoxModbusClientWriteAddr->setRange(0, 65535);
    ui->spinBoxModbusClientWriteAddr->setValue(0);

    ui->lineEditModbusClientWriteValue->setText("123");

    ui->btnModbusClientConnect->setEnabled(true);
    ui->btnModbusClientDisconnect->setEnabled(false);
    ui->btnModbusClientReadHolding->setEnabled(false);
    ui->btnModbusClientWriteSingle->setEnabled(false);
    ui->btnModbusClientWriteMultiple->setEnabled(false);
}
void MainWindow::on_btnModbusClientConnect_clicked()
{
    if (!m_modbusClient) {
        appendLog("[Modbus TCP Client] client object is null");
        return;
    }

    if (m_modbusClient->isConnected()) {
        appendLog("[Modbus TCP Client] already connected");
        return;
    }

    QString ip = ui->lineEditModbusClientIp->text().trimmed();

    bool okPort = false;
    int port = ui->lineEditModbusClientPort->text().trimmed().toInt(&okPort);

    if (ip.isEmpty()) {
        appendLog("[Modbus TCP Client] IP为空");
        return;
    }

    if (!okPort || port <= 0 || port > 65535) {
        appendLog("[Modbus TCP Client] 端口无效");
        return;
    }

    m_modbusClient->connectToServer(ip, port);
}
void MainWindow::on_btnModbusClientDisconnect_clicked()
{
    m_modbusClient->disconnectFromServer();
}
void MainWindow::on_btnModbusClientReadHolding_clicked()
{
    if (!m_modbusClient || !m_modbusClient->isConnected()) {
        appendLog("[Modbus TCP Client] please connect first");
        return;
    }

    int unitId = ui->spinBoxModbusClientUnitId->value();
    int startAddr = ui->spinBoxModbusClientStartAddr->value();
    int count = ui->spinBoxModbusClientCount->value();

    appendLog(QString("[Modbus TCP Client] Read Holding. unit=%1, start=%2, count=%3")
                  .arg(unitId)
                  .arg(startAddr)
                  .arg(count));

    m_modbusClient->readHoldingRegisters(unitId, startAddr, static_cast<quint16>(count));
}
void MainWindow::on_btnModbusClientWriteSingle_clicked()
{
    int unitId = ui->spinBoxModbusClientUnitId->value();
    int addr = ui->spinBoxModbusClientWriteAddr->value();

    QString valueText = ui->lineEditModbusClientWriteValue->text().trimmed();

    bool ok = false;
    int value = valueText.toInt(&ok);

    if (!ok || value < 0 || value > 65535) {
        appendLog("[Modbus TCP Client] 写入值无效，范围应为 0~65535");
        return;
    }

    appendLog(QString("[Modbus TCP Client] Write Single Holding. unit=%1, addr=%2, value=%3")
                  .arg(unitId)
                  .arg(addr)
                  .arg(value));

    m_modbusClient->writeSingleHoldingRegister(unitId,
                                               addr,
                                               static_cast<quint16>(value));
}
void MainWindow::on_btnModbusClientWriteMultiple_clicked()
{
    int unitId = ui->spinBoxModbusClientUnitId->value();
    int startAddr = ui->spinBoxModbusClientWriteAddr->value();

    QString text = ui->lineEditModbusClientWriteValue->text().trimmed();

    if (text.isEmpty()) {
        appendLog("[Modbus TCP Client] 写入内容为空");
        return;
    }

    text.replace(",", " ");
    QStringList parts = text.split(" ", Qt::SkipEmptyParts);

    QVector<quint16> values;

    for (const QString &part : parts) {
        bool ok = false;
        int value = part.toInt(&ok);

        if (!ok || value < 0 || value > 65535) {
            appendLog(QString("[Modbus TCP Client] 无效写入值：%1").arg(part));
            return;
        }

        values.append(static_cast<quint16>(value));
    }

    if (values.isEmpty()) {
        appendLog("[Modbus TCP Client] 没有有效写入值");
        return;
    }

    appendLog(QString("[Modbus TCP Client] Write Multiple Holding. unit=%1, start=%2, count=%3")
                  .arg(unitId)
                  .arg(startAddr)
                  .arg(values.size()));

    m_modbusClient->writeMultipleHoldingRegisters(unitId,
                                                  startAddr,
                                                  values);
}
QByteArray MainWindow::textToUtf8Bytes(const QString &text)
{
    return text.toUtf8();
}

QString MainWindow::bytesToUtf8Text(const QByteArray &data)
{
    return QString::fromUtf8(data);
}
void MainWindow::initModbusRtuUi()
{
    ui->comboBoxModbusRtuBaudRate->clear();
    ui->comboBoxModbusRtuBaudRate->addItems({"9600", "19200", "38400", "57600", "115200"});
    ui->comboBoxModbusRtuBaudRate->setCurrentText("9600");

    ui->comboBoxModbusRtuDataBits->clear();
    ui->comboBoxModbusRtuDataBits->addItems({"7", "8"});
    ui->comboBoxModbusRtuDataBits->setCurrentText("8");

    ui->comboBoxModbusRtuStopBits->clear();
    ui->comboBoxModbusRtuStopBits->addItems({"1", "2"});
    ui->comboBoxModbusRtuStopBits->setCurrentText("1");

    ui->comboBoxModbusRtuParity->clear();
    ui->comboBoxModbusRtuParity->addItems({"None", "Even", "Odd"});
    ui->comboBoxModbusRtuParity->setCurrentText("None");

    ui->spinBoxModbusRtuSlaveId->setRange(1, 247);
    ui->spinBoxModbusRtuSlaveId->setValue(1);

    ui->spinBoxModbusRtuStartAddr->setRange(0, 65535);
    ui->spinBoxModbusRtuStartAddr->setValue(0);

    ui->spinBoxModbusRtuCount->setRange(1, 125);
    ui->spinBoxModbusRtuCount->setValue(2);

    ui->spinBoxModbusRtuWriteAddr->setRange(0, 65535);
    ui->spinBoxModbusRtuWriteAddr->setValue(0);

    ui->lineEditModbusRtuWriteValue->setText("123");

    refreshModbusRtuPorts();

    ui->btnModbusRtuOpen->setEnabled(true);
    ui->btnModbusRtuClose->setEnabled(false);
    ui->btnModbusRtuReadHolding->setEnabled(false);
    ui->btnModbusRtuWriteSingle->setEnabled(false);
    ui->btnModbusRtuWriteMultiple->setEnabled(false);
}
void MainWindow::refreshModbusRtuPorts()
{
    QString current = ui->comboBoxModbusRtuPort->currentText();

    ui->comboBoxModbusRtuPort->clear();

    const auto ports = QSerialPortInfo::availablePorts();

    for (const QSerialPortInfo &info : ports) {
        ui->comboBoxModbusRtuPort->addItem(info.portName());
    }

    int index = ui->comboBoxModbusRtuPort->findText(current);
    if (index >= 0) {
        ui->comboBoxModbusRtuPort->setCurrentIndex(index);
    }

    appendLog(QString("[Modbus RTU Client] found %1 port(s)").arg(ports.size()));
}
void MainWindow::on_btnModbusRtuRefresh_clicked()
{
    refreshModbusRtuPorts();
}
void MainWindow::on_btnModbusRtuOpen_clicked()
{
    QString portName = ui->comboBoxModbusRtuPort->currentText().trimmed();

    if (portName.isEmpty()) {
        appendLog("[Modbus RTU Client] 串口号为空");
        return;
    }

    bool okBaud = false;
    qint32 baudRate = ui->comboBoxModbusRtuBaudRate->currentText().toInt(&okBaud);

    if (!okBaud || baudRate <= 0) {
        appendLog("[Modbus RTU Client] 波特率无效");
        return;
    }

    QSerialPort::DataBits dataBits =
        getSerialDataBitsFromText(ui->comboBoxModbusRtuDataBits->currentText());

    QSerialPort::StopBits stopBits =
        getSerialStopBitsFromText(ui->comboBoxModbusRtuStopBits->currentText());

    QSerialPort::Parity parity =
        getSerialParityFromText(ui->comboBoxModbusRtuParity->currentText());

    appendLog(QString("[Modbus RTU Client] opening %1, baud=%2, data=%3, stop=%4, parity=%5")
                  .arg(portName)
                  .arg(baudRate)
                  .arg(ui->comboBoxModbusRtuDataBits->currentText())
                  .arg(ui->comboBoxModbusRtuStopBits->currentText())
                  .arg(ui->comboBoxModbusRtuParity->currentText()));

    bool ok = m_modbusRtuClient->open(portName,
                                      baudRate,
                                      dataBits,
                                      parity,
                                      stopBits);

    if (!ok) {
        appendLog("[Modbus RTU Client] open failed");
    }
}
void MainWindow::on_btnModbusRtuClose_clicked()
{
    if (m_modbusRtuClient) {
        m_modbusRtuClient->close();
    }
}
void MainWindow::on_btnModbusRtuReadHolding_clicked()
{
    if (!m_modbusRtuClient || !m_modbusRtuClient->isOpen()) {
        appendLog("[Modbus RTU Client] please open serial first");
        return;
    }

    quint8 slaveId = static_cast<quint8>(ui->spinBoxModbusRtuSlaveId->value());
    quint16 startAddr = static_cast<quint16>(ui->spinBoxModbusRtuStartAddr->value());
    quint16 count = static_cast<quint16>(ui->spinBoxModbusRtuCount->value());

    appendLog(QString("[Modbus RTU Client] Read Holding. slave=%1, start=%2, count=%3")
                  .arg(slaveId)
                  .arg(startAddr)
                  .arg(count));

    m_modbusRtuClient->readHoldingRegisters(slaveId, startAddr, count);
}
void MainWindow::on_btnModbusRtuWriteSingle_clicked()
{
    if (!m_modbusRtuClient || !m_modbusRtuClient->isOpen()) {
        appendLog("[Modbus RTU Client] please open serial first");
        return;
    }

    quint8 slaveId = static_cast<quint8>(ui->spinBoxModbusRtuSlaveId->value());
    quint16 addr = static_cast<quint16>(ui->spinBoxModbusRtuWriteAddr->value());

    QString valueText = ui->lineEditModbusRtuWriteValue->text().trimmed();

    bool ok = false;
    int value = valueText.toInt(&ok);

    if (!ok || value < 0 || value > 65535) {
        appendLog("[Modbus RTU Client] 写入值无效，范围 0~65535");
        return;
    }

    appendLog(QString("[Modbus RTU Client] Write Single. slave=%1, addr=%2, value=%3")
                  .arg(slaveId)
                  .arg(addr)
                  .arg(value));

    m_modbusRtuClient->writeSingleHoldingRegister(slaveId,
                                                  addr,
                                                  static_cast<quint16>(value));
}
void MainWindow::on_btnModbusRtuWriteMultiple_clicked()
{
    if (!m_modbusRtuClient || !m_modbusRtuClient->isOpen()) {
        appendLog("[Modbus RTU Client] please open serial first");
        return;
    }

    quint8 slaveId = static_cast<quint8>(ui->spinBoxModbusRtuSlaveId->value());
    quint16 startAddr = static_cast<quint16>(ui->spinBoxModbusRtuWriteAddr->value());

    QString text = ui->lineEditModbusRtuWriteValue->text().trimmed();

    if (text.isEmpty()) {
        appendLog("[Modbus RTU Client] 写入内容为空");
        return;
    }

    text.replace(",", " ");

    QStringList parts = text.split(" ", Qt::SkipEmptyParts);

    QVector<quint16> values;

    for (const QString &part : parts) {
        bool ok = false;
        int value = part.toInt(&ok);

        if (!ok || value < 0 || value > 65535) {
            appendLog(QString("[Modbus RTU Client] 无效写入值：%1").arg(part));
            return;
        }

        values.append(static_cast<quint16>(value));
    }

    if (values.isEmpty()) {
        appendLog("[Modbus RTU Client] 没有有效写入值");
        return;
    }

    appendLog(QString("[Modbus RTU Client] Write Multiple. slave=%1, start=%2, count=%3")
                  .arg(slaveId)
                  .arg(startAddr)
                  .arg(values.size()));

    m_modbusRtuClient->writeMultipleHoldingRegisters(slaveId,
                                                     startAddr,
                                                     values);
}
QSerialPort::DataBits MainWindow::getSerialDataBitsFromText(const QString &text) const
{
    if (text == "5") {
        return QSerialPort::Data5;
    }

    if (text == "6") {
        return QSerialPort::Data6;
    }

    if (text == "7") {
        return QSerialPort::Data7;
    }

    return QSerialPort::Data8;
}

QSerialPort::StopBits MainWindow::getSerialStopBitsFromText(const QString &text) const
{
    if (text == "1.5") {
        return QSerialPort::OneAndHalfStop;
    }

    if (text == "2") {
        return QSerialPort::TwoStop;
    }

    return QSerialPort::OneStop;
}

QSerialPort::Parity MainWindow::getSerialParityFromText(const QString &text) const
{
    if (text == "Even") {
        return QSerialPort::EvenParity;
    }

    if (text == "Odd") {
        return QSerialPort::OddParity;
    }

    if (text == "Mark") {
        return QSerialPort::MarkParity;
    }

    if (text == "Space") {
        return QSerialPort::SpaceParity;
    }

    return QSerialPort::NoParity;
}

void MainWindow::initModbusRtuSlaveUi()
{
    m_modbusRtuSlaveSerial = new QSerialPort(this);

    m_modbusRtuSlaveFrameTimer = new QTimer(this);
    m_modbusRtuSlaveFrameTimer->setSingleShot(true);
    m_modbusRtuSlaveFrameTimer->setInterval(30);   // RTU 帧间隔，第一版用 30ms 足够

    connect(m_modbusRtuSlaveSerial, &QSerialPort::readyRead,
            this, &MainWindow::onModbusRtuSlaveReadyRead);

    connect(m_modbusRtuSlaveFrameTimer, &QTimer::timeout,
            this, &MainWindow::processModbusRtuSlaveFrame);

    connect(ui->btnModbusRtuSlaveRefreshPort, &QPushButton::clicked,
            this, &MainWindow::refreshModbusRtuSlavePorts);

    connect(ui->btnModbusRtuSlaveOpen, &QPushButton::clicked, this, [=]() {
        QString portName = ui->comboBoxModbusRtuSlavePort->currentText();

        if (portName.isEmpty()) {
            appendLog("[RTU Slave] 串口为空");
            return;
        }

        if (m_modbusRtuSlaveSerial->isOpen()) {
            m_modbusRtuSlaveSerial->close();
        }

        m_modbusRtuSlaveSerial->setPortName(portName);
        m_modbusRtuSlaveSerial->setBaudRate(ui->comboBoxModbusRtuSlaveBaudRate->currentText().toInt());

        int dataBits = ui->comboBoxModbusRtuSlaveDataBits->currentText().toInt();
        if (dataBits == 5) {
            m_modbusRtuSlaveSerial->setDataBits(QSerialPort::Data5);
        } else if (dataBits == 6) {
            m_modbusRtuSlaveSerial->setDataBits(QSerialPort::Data6);
        } else if (dataBits == 7) {
            m_modbusRtuSlaveSerial->setDataBits(QSerialPort::Data7);
        } else {
            m_modbusRtuSlaveSerial->setDataBits(QSerialPort::Data8);
        }

        QString parity = ui->comboBoxModbusRtuSlaveParity->currentText();
        if (parity == "None") {
            m_modbusRtuSlaveSerial->setParity(QSerialPort::NoParity);
        } else if (parity == "Odd") {
            m_modbusRtuSlaveSerial->setParity(QSerialPort::OddParity);
        } else if (parity == "Even") {
            m_modbusRtuSlaveSerial->setParity(QSerialPort::EvenParity);
        } else {
            m_modbusRtuSlaveSerial->setParity(QSerialPort::NoParity);
        }

        QString stopBits = ui->comboBoxModbusRtuSlaveStopBits->currentText();
        if (stopBits == "1") {
            m_modbusRtuSlaveSerial->setStopBits(QSerialPort::OneStop);
        } else if (stopBits == "1.5") {
            m_modbusRtuSlaveSerial->setStopBits(QSerialPort::OneAndHalfStop);
        } else if (stopBits == "2") {
            m_modbusRtuSlaveSerial->setStopBits(QSerialPort::TwoStop);
        } else {
            m_modbusRtuSlaveSerial->setStopBits(QSerialPort::OneStop);
        }

        m_modbusRtuSlaveSerial->setFlowControl(QSerialPort::NoFlowControl);

        if (!m_modbusRtuSlaveSerial->open(QIODevice::ReadWrite)) {
            appendLog("[RTU Slave] 打开串口失败: " + m_modbusRtuSlaveSerial->errorString());
            return;
        }

        m_modbusRtuSlaveRxBuffer.clear();

        setModbusRtuSlaveOpenedState(true);

        appendLog(QString("[RTU Slave] 打开串口成功: %1, %2, Slave ID=%3")
                      .arg(portName)
                      .arg(ui->comboBoxModbusRtuSlaveBaudRate->currentText())
                      .arg(ui->spinBoxModbusRtuSlaveSelfId->value()));
    });

    connect(ui->btnModbusRtuSlaveClose, &QPushButton::clicked, this, [=]() {
        if (m_modbusRtuSlaveSerial->isOpen()) {
            m_modbusRtuSlaveSerial->close();
        }

        m_modbusRtuSlaveRxBuffer.clear();
        setModbusRtuSlaveOpenedState(false);

        appendLog("[RTU Slave] 串口已关闭");
    });

    connect(ui->btnModbusRtuSlaveInitRegisters, &QPushButton::clicked,
            this, &MainWindow::initModbusRtuSlaveRegisters);

    connect(ui->btnModbusRtuSlaveClearRegisters, &QPushButton::clicked, this, [=]() {
        for (int i = 0; i < m_modbusRtuSlaveHoldingRegisters.size(); ++i) {
            m_modbusRtuSlaveHoldingRegisters[i] = 0;
        }

        updateModbusRtuSlaveTable();
        appendLog("[RTU Slave] 保持寄存器已清空");
    });

    connect(ui->tableWidgetModbusRtuSlaveHolding, &QTableWidget::cellChanged,
            this, [=](int row, int column) {
                if (column != 1) {
                    return;
                }

                if (row < 0 || row >= m_modbusRtuSlaveHoldingRegisters.size()) {
                    return;
                }

                bool ok = false;
                int value = ui->tableWidgetModbusRtuSlaveHolding->item(row, column)->text().toInt(&ok);

                if (!ok) {
                    return;
                }

                if (value < 0) {
                    value = 0;
                }

                if (value > 65535) {
                    value = 65535;
                }

                m_modbusRtuSlaveHoldingRegisters[row] = static_cast<quint16>(value);
            });

    ui->comboBoxModbusRtuSlaveBaudRate->addItems({"9600", "19200", "38400", "57600", "115200"});
    ui->comboBoxModbusRtuSlaveBaudRate->setCurrentText("9600");

    ui->comboBoxModbusRtuSlaveDataBits->addItems({"8", "7", "6", "5"});
    ui->comboBoxModbusRtuSlaveDataBits->setCurrentText("8");

    ui->comboBoxModbusRtuSlaveParity->addItems({"None", "Even", "Odd"});
    ui->comboBoxModbusRtuSlaveParity->setCurrentText("None");

    ui->comboBoxModbusRtuSlaveStopBits->addItems({"1", "1.5", "2"});
    ui->comboBoxModbusRtuSlaveStopBits->setCurrentText("1");

    ui->spinBoxModbusRtuSlaveSelfId->setRange(1, 247);
    ui->spinBoxModbusRtuSlaveSelfId->setValue(1);

    ui->spinBoxModbusRtuSlaveRegisterCount->setRange(1, 1000);
    ui->spinBoxModbusRtuSlaveRegisterCount->setValue(20);

    ui->spinBoxModbusRtuSlaveStartAddress->setRange(0, 65535);
    ui->spinBoxModbusRtuSlaveStartAddress->setValue(0);

    ui->tableWidgetModbusRtuSlaveHolding->setColumnCount(2);
    ui->tableWidgetModbusRtuSlaveHolding->setHorizontalHeaderLabels({"地址", "值"});
    ui->tableWidgetModbusRtuSlaveHolding->horizontalHeader()->setStretchLastSection(true);

    refreshModbusRtuSlavePorts();
    initModbusRtuSlaveRegisters();
    setModbusRtuSlaveOpenedState(false);
}
void MainWindow::refreshModbusRtuSlavePorts()
{
    ui->comboBoxModbusRtuSlavePort->clear();

    const auto ports = QSerialPortInfo::availablePorts();
    for (const QSerialPortInfo &info : ports) {
        ui->comboBoxModbusRtuSlavePort->addItem(info.portName());
    }

    appendLog("[RTU Slave] 已刷新串口列表");
}
void MainWindow::initModbusRtuSlaveRegisters()
{
    int count = ui->spinBoxModbusRtuSlaveRegisterCount->value();

    m_modbusRtuSlaveHoldingRegisters.clear();
    m_modbusRtuSlaveHoldingRegisters.resize(count);

    for (int i = 0; i < count; ++i) {
        m_modbusRtuSlaveHoldingRegisters[i] = 0;
    }

    updateModbusRtuSlaveTable();

    appendLog(QString("[RTU Slave] 初始化保持寄存器数量: %1").arg(count));
}
void MainWindow::updateModbusRtuSlaveTable()
{
    ui->tableWidgetModbusRtuSlaveHolding->blockSignals(true);

    int startAddress = ui->spinBoxModbusRtuSlaveStartAddress->value();
    int count = m_modbusRtuSlaveHoldingRegisters.size();

    ui->tableWidgetModbusRtuSlaveHolding->setRowCount(count);

    for (int i = 0; i < count; ++i) {
        int address = startAddress + i;
        quint16 value = m_modbusRtuSlaveHoldingRegisters[i];

        QTableWidgetItem *addrItem = new QTableWidgetItem(QString::number(address));
        addrItem->setFlags(addrItem->flags() & ~Qt::ItemIsEditable);

        QTableWidgetItem *valueItem = new QTableWidgetItem(QString::number(value));

        ui->tableWidgetModbusRtuSlaveHolding->setItem(i, 0, addrItem);
        ui->tableWidgetModbusRtuSlaveHolding->setItem(i, 1, valueItem);
    }

    ui->tableWidgetModbusRtuSlaveHolding->blockSignals(false);
}
void MainWindow::setModbusRtuSlaveOpenedState(bool opened)
{
    ui->btnModbusRtuSlaveOpen->setEnabled(!opened);
    ui->btnModbusRtuSlaveClose->setEnabled(opened);

    ui->comboBoxModbusRtuSlavePort->setEnabled(!opened);
    ui->comboBoxModbusRtuSlaveBaudRate->setEnabled(!opened);
    ui->comboBoxModbusRtuSlaveDataBits->setEnabled(!opened);
    ui->comboBoxModbusRtuSlaveParity->setEnabled(!opened);
    ui->comboBoxModbusRtuSlaveStopBits->setEnabled(!opened);
    ui->spinBoxModbusRtuSlaveSelfId->setEnabled(!opened);
    ui->btnModbusRtuSlaveRefreshPort->setEnabled(!opened);
}
void MainWindow::onModbusRtuSlaveReadyRead()
{
    QByteArray data = m_modbusRtuSlaveSerial->readAll();

    if (data.isEmpty()) {
        return;
    }

    m_modbusRtuSlaveRxBuffer.append(data);

    m_modbusRtuSlaveFrameTimer->start();

    appendLog("[RTU Slave] RX Part: " + byteArrayToHexString(data));
}
void MainWindow::processModbusRtuSlaveFrame()
{
    if (m_modbusRtuSlaveRxBuffer.isEmpty()) {
        return;
    }

    QByteArray frame = m_modbusRtuSlaveRxBuffer;
    m_modbusRtuSlaveRxBuffer.clear();

    appendLog("[RTU Slave] RX Frame: " + byteArrayToHexString(frame));

    if (frame.size() < 4) {
        appendLog("[RTU Slave] 帧长度过短");
        return;
    }

    handleModbusRtuSlaveRequest(frame);
}
quint16 MainWindow::modbusRtuCrc16(const QByteArray &data)
{
    quint16 crc = 0xFFFF;

    for (int i = 0; i < data.size(); ++i) {
        crc ^= static_cast<quint8>(data.at(i));

        for (int j = 0; j < 8; ++j) {
            if (crc & 0x0001) {
                crc >>= 1;
                crc ^= 0xA001;
            } else {
                crc >>= 1;
            }
        }
    }

    return crc;
}
bool MainWindow::checkModbusRtuCrc(const QByteArray &frame)
{
    if (frame.size() < 4) {
        return false;
    }

    QByteArray data = frame.left(frame.size() - 2);

    quint16 calcCrc = modbusRtuCrc16(data);

    quint8 crcLow = static_cast<quint8>(frame.at(frame.size() - 2));
    quint8 crcHigh = static_cast<quint8>(frame.at(frame.size() - 1));

    quint16 recvCrc = static_cast<quint16>(crcLow | (crcHigh << 8));

    return calcCrc == recvCrc;
}
QByteArray MainWindow::appendModbusRtuCrc(const QByteArray &data)
{
    QByteArray frame = data;

    quint16 crc = modbusRtuCrc16(data);

    frame.append(static_cast<char>(crc & 0xFF));
    frame.append(static_cast<char>((crc >> 8) & 0xFF));

    return frame;
}
QString MainWindow::byteArrayToHexString(const QByteArray &data)
{
    QStringList list;

    for (char ch : data) {
        list << QString("%1")
        .arg(static_cast<quint8>(ch), 2, 16, QChar('0'))
            .toUpper();
    }

    return list.join(" ");
}
void MainWindow::handleModbusRtuSlaveRequest(const QByteArray &frame)
{
    if (!checkModbusRtuCrc(frame)) {
        appendLog("[RTU Slave] CRC 校验失败");
        return;
    }

    quint8 requestSlaveId = static_cast<quint8>(frame.at(0));
    quint8 selfSlaveId = static_cast<quint8>(ui->spinBoxModbusRtuSlaveSelfId->value());

    if (requestSlaveId != selfSlaveId) {
        appendLog(QString("[RTU Slave] 站号不匹配，忽略。请求站号=%1，本机站号=%2")
                      .arg(requestSlaveId)
                      .arg(selfSlaveId));
        return;
    }

    quint8 functionCode = static_cast<quint8>(frame.at(1));

    switch (functionCode) {
    case 0x03:
        handleModbusRtuSlaveReadHolding(frame);
        break;

    case 0x06:
        handleModbusRtuSlaveWriteSingleRegister(frame);
        break;

    case 0x10:
        handleModbusRtuSlaveWriteMultipleRegisters(frame);
        break;

    default:
        sendModbusRtuSlaveException(requestSlaveId, functionCode, 0x01);
        break;
    }
}
void MainWindow::handleModbusRtuSlaveReadHolding(const QByteArray &frame)
{
    if (frame.size() != 8) {
        appendLog("[RTU Slave] 03 请求长度错误");
        return;
    }

    quint8 slaveId = static_cast<quint8>(frame.at(0));

    quint16 requestStartAddr =
        (static_cast<quint8>(frame.at(2)) << 8) |
        static_cast<quint8>(frame.at(3));

    quint16 requestCount =
        (static_cast<quint8>(frame.at(4)) << 8) |
        static_cast<quint8>(frame.at(5));

    int localStartAddress = ui->spinBoxModbusRtuSlaveStartAddress->value();

    int startIndex = requestStartAddr - localStartAddress;

    if (requestCount < 1 || requestCount > 125) {
        sendModbusRtuSlaveException(slaveId, 0x03, 0x03);
        return;
    }

    if (startIndex < 0 || startIndex + requestCount > m_modbusRtuSlaveHoldingRegisters.size()) {
        sendModbusRtuSlaveException(slaveId, 0x03, 0x02);
        return;
    }

    QByteArray response;
    response.append(static_cast<char>(slaveId));
    response.append(static_cast<char>(0x03));
    response.append(static_cast<char>(requestCount * 2));

    for (int i = 0; i < requestCount; ++i) {
        quint16 value = m_modbusRtuSlaveHoldingRegisters[startIndex + i];

        response.append(static_cast<char>((value >> 8) & 0xFF));
        response.append(static_cast<char>(value & 0xFF));
    }

    QByteArray sendFrame = appendModbusRtuCrc(response);

    m_modbusRtuSlaveSerial->write(sendFrame);

    appendLog(QString("[RTU Slave] 03 读保持寄存器 addr=%1 count=%2")
                  .arg(requestStartAddr)
                  .arg(requestCount));
    appendLog("[RTU Slave] TX: " + byteArrayToHexString(sendFrame));
}
void MainWindow::handleModbusRtuSlaveWriteSingleRegister(const QByteArray &frame)
{
    if (frame.size() != 8) {
        appendLog("[RTU Slave] 06 请求长度错误");
        return;
    }

    quint8 slaveId = static_cast<quint8>(frame.at(0));

    quint16 requestAddr =
        (static_cast<quint8>(frame.at(2)) << 8) |
        static_cast<quint8>(frame.at(3));

    quint16 value =
        (static_cast<quint8>(frame.at(4)) << 8) |
        static_cast<quint8>(frame.at(5));

    int localStartAddress = ui->spinBoxModbusRtuSlaveStartAddress->value();
    int index = requestAddr - localStartAddress;

    if (index < 0 || index >= m_modbusRtuSlaveHoldingRegisters.size()) {
        sendModbusRtuSlaveException(slaveId, 0x06, 0x02);
        return;
    }

    m_modbusRtuSlaveHoldingRegisters[index] = value;
    updateModbusRtuSlaveTable();

    m_modbusRtuSlaveSerial->write(frame);

    appendLog(QString("[RTU Slave] 06 写单个寄存器 addr=%1 value=%2")
                  .arg(requestAddr)
                  .arg(value));
    appendLog("[RTU Slave] TX: " + byteArrayToHexString(frame));
}
void MainWindow::handleModbusRtuSlaveWriteMultipleRegisters(const QByteArray &frame)
{
    if (frame.size() < 11) {
        appendLog("[RTU Slave] 10 请求长度过短");
        return;
    }

    quint8 slaveId = static_cast<quint8>(frame.at(0));

    quint16 requestStartAddr =
        (static_cast<quint8>(frame.at(2)) << 8) |
        static_cast<quint8>(frame.at(3));

    quint16 requestCount =
        (static_cast<quint8>(frame.at(4)) << 8) |
        static_cast<quint8>(frame.at(5));

    quint8 byteCount = static_cast<quint8>(frame.at(6));

    if (requestCount < 1 || requestCount > 123) {
        sendModbusRtuSlaveException(slaveId, 0x10, 0x03);
        return;
    }

    if (byteCount != requestCount * 2) {
        sendModbusRtuSlaveException(slaveId, 0x10, 0x03);
        return;
    }

    int expectedFrameSize = 7 + byteCount + 2;
    if (frame.size() != expectedFrameSize) {
        appendLog("[RTU Slave] 10 请求长度与字节数不匹配");
        return;
    }

    int localStartAddress = ui->spinBoxModbusRtuSlaveStartAddress->value();
    int startIndex = requestStartAddr - localStartAddress;

    if (startIndex < 0 || startIndex + requestCount > m_modbusRtuSlaveHoldingRegisters.size()) {
        sendModbusRtuSlaveException(slaveId, 0x10, 0x02);
        return;
    }

    for (int i = 0; i < requestCount; ++i) {
        int dataIndex = 7 + i * 2;

        quint16 value =
            (static_cast<quint8>(frame.at(dataIndex)) << 8) |
            static_cast<quint8>(frame.at(dataIndex + 1));

        m_modbusRtuSlaveHoldingRegisters[startIndex + i] = value;
    }

    updateModbusRtuSlaveTable();

    QByteArray response;
    response.append(static_cast<char>(slaveId));
    response.append(static_cast<char>(0x10));
    response.append(static_cast<char>((requestStartAddr >> 8) & 0xFF));
    response.append(static_cast<char>(requestStartAddr & 0xFF));
    response.append(static_cast<char>((requestCount >> 8) & 0xFF));
    response.append(static_cast<char>(requestCount & 0xFF));

    QByteArray sendFrame = appendModbusRtuCrc(response);

    m_modbusRtuSlaveSerial->write(sendFrame);

    appendLog(QString("[RTU Slave] 10 写多个寄存器 addr=%1 count=%2")
                  .arg(requestStartAddr)
                  .arg(requestCount));
    appendLog("[RTU Slave] TX: " + byteArrayToHexString(sendFrame));
}
void MainWindow::sendModbusRtuSlaveException(quint8 slaveId, quint8 functionCode, quint8 exceptionCode)
{
    QByteArray response;

    response.append(static_cast<char>(slaveId));
    response.append(static_cast<char>(functionCode | 0x80));
    response.append(static_cast<char>(exceptionCode));

    QByteArray sendFrame = appendModbusRtuCrc(response);

    m_modbusRtuSlaveSerial->write(sendFrame);

    appendLog(QString("[RTU Slave] 异常响应 func=0x%1 code=0x%2")
                  .arg(functionCode, 2, 16, QChar('0'))
                  .arg(exceptionCode, 2, 16, QChar('0'))
                  .toUpper());

    appendLog("[RTU Slave] TX: " + byteArrayToHexString(sendFrame));
}
