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


    //connect(ui->listWidget, &QListWidget::currentItemChanged,
     //       this, &MainWindow::onListWidgetCurrentItemChanged);

    ui->listWidget->setContextMenuPolicy(Qt::CustomContextMenu);
    connect(ui->listWidget, &QListWidget::customContextMenuRequested,
            this, &MainWindow::onListWidgetCustomContextMenuRequested);

    connect(ui->btnAddDir, &QPushButton::clicked,
            this, &MainWindow::onBtnAddDirClicked);
    connect(ui->btnClearLog, &QPushButton::clicked,
            this, &MainWindow::on_btnClearLog_clicked);
    connect(ui->btnSaveLog, &QPushButton::clicked,
            this, &MainWindow::on_btnSaveLog_clicked);
   // connect(ui->btnSerialRefresh, &QPushButton::clicked,
   //         this, &MainWindow::on_btnSerialRefresh_clicked);

   // connect(ui->btnSerialOpen, &QPushButton::clicked,
   //         this, &MainWindow::on_btnSerialOpen_clicked);

   // connect(ui->btnSerialClose, &QPushButton::clicked,
    //        this, &MainWindow::on_btnSerialClose_clicked);

   // connect(ui->btnSerialSend, &QPushButton::clicked,
   //         this, &MainWindow::on_btnSerialSend_clicked);
    // 3. 加载上次保存的状态
    loadSettings();
    // 4. 初始化通讯模块
    initUiState();
    initCommunication();
    initSerialUi();
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
        m_modbusClient->disconnectDevice();
    }

    if (m_modbusServer) {
        m_modbusServer->stop();
    }

    delete ui;
}

void MainWindow::initUiState()
{
    // TCP Client
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

    initCommunicationSignals();

    appendLog("通讯模块初始化完成");
}
void MainWindow::initCommunicationSignals()
{
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

                appendLog(QString("[Serial Recv ASCII] %1")
                              .arg(byteArrayToPrintableText(data)));
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
                ui->btnTcpClientConnect->setEnabled(true);
                ui->btnTcpClientDisconnect->setEnabled(false);
                ui->btnTcpClientSend->setEnabled(false);
                ui->lineEditTcpClientIp->setEnabled(true);
                ui->lineEditTcpClientPort->setEnabled(true);
            });
    connect(m_tcpClient, &TcpClient::dataReceived,
            this,
            [=](const QByteArray &data) {
                appendLog(QString("[TCP Client Recv HEX] %1")
                              .arg(QString::fromLatin1(data.toHex(' ').toUpper())));
                appendLog(QString("[TCP Client Recv ASCII] %1")
                              .arg(byteArrayToPrintableText(data)));
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

                appendLog(QString("[TCP Server Recv ASCII] %1")
                              .arg(byteArrayToPrintableText(data)));
            });

    connect(m_tcpServer, &TcpServer::errorOccurred,
            this,
            [=](const QString &error) {
                appendLog(QString("[TCP Server Error] %1").arg(error));
            });

    connect(m_udpComm, &UdpComm::dataReceived,
            this,
            [=](const QString &ip, quint16 port, const QByteArray &data) {
                appendLog(QString("[UDP Recv From] %1:%2").arg(ip).arg(port));

                appendLog(QString("[UDP Recv HEX] %1")
                              .arg(QString::fromLatin1(data.toHex(' ').toUpper())));

                appendLog(QString("[UDP Recv ASCII] %1")
                              .arg(byteArrayToPrintableText(data)));
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
    QString text = ui->textEditTcpServerSend->toPlainText().trimmed();

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
        data = text.toLocal8Bit();

        appendLog(QString("[TCP Server Send TEXT] %1").arg(text));
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

    ui->btnUdpBind->setEnabled(true);
    ui->btnUdpClose->setEnabled(false);
    ui->lineEditUdpLocalPort->setEnabled(true);
}
void MainWindow::on_btnUdpSend_clicked()
{
    QString ip = ui->lineEditUdpTargetIp->text().trimmed();

    bool okPort = false;
    quint16 port = ui->lineEditUdpTargetPort->text().trimmed().toUShort(&okPort);

    QString text = ui->textEditUdpSend->toPlainText().trimmed();

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
        data = text.toLocal8Bit();

        appendLog(QString("[UDP Send TEXT] %1").arg(text));
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
    QString text = ui->textEditTcpClientSend->toPlainText().trimmed();

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
        data = text.toLocal8Bit();

        appendLog(QString("[TCP Client Send TEXT] %1").arg(text));
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
    QString text = ui->textEditSerialSend->toPlainText().trimmed();

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
        data = text.toLocal8Bit();

        appendLog(QString("[Serial Send TEXT] %1").arg(text));
    }

    qint64 len = m_serialComm->sendData(data);

    appendLog(QString("[Serial Send] bytes = %1").arg(len));
}