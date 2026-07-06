#include "mainwindow.h"
#include "./ui_mainwindow.h"
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
    // 3. 加载上次保存的状态
    loadSettings();
    // 4. 初始化通讯模块
    initCommunication();
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
        qDebug() << "成功添加" << addedCount << "张图片";
    } else {
        qDebug() << "所选图片已全部在列表中";
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

    qDebug() << "通讯模块初始化完成";

    // 临时测试：先自动启动 TCP Server 和 UDP
    // 注意：确认端口没有被占用
    testStartTcpServer();
    testStartUdp();

    // 临时测试：启动 Modbus TCP Server，方便 Modbus Poll 连接
    testStartModbusTcpServer();
}
void MainWindow::initCommunicationSignals()
{
    // ==================== TCP Client ====================
    connect(m_tcpClient, &TcpClient::connected, this, []() {
        qDebug() << "[TCP Client] connected";
    });

    connect(m_tcpClient, &TcpClient::disconnected, this, []() {
        qDebug() << "[TCP Client] disconnected";
    });

    connect(m_tcpClient, &TcpClient::dataReceived,
            this,
            [](const QByteArray &data) {
                qDebug() << "[TCP Client Recv HEX]" << data.toHex(' ').toUpper();
                qDebug() << "[TCP Client Recv TEXT]" << QString::fromLocal8Bit(data);
            });

    connect(m_tcpClient, &TcpClient::errorOccurred,
            this,
            [](const QString &error) {
                qDebug() << "[TCP Client Error]" << error;
            });

    // ==================== TCP Server ====================
    connect(m_tcpServer, &TcpServer::clientConnected,
            this,
            [](const QString &peer) {
                qDebug() << "[TCP Server] client connected:" << peer;
            });

    connect(m_tcpServer, &TcpServer::clientDisconnected,
            this,
            [](const QString &peer) {
                qDebug() << "[TCP Server] client disconnected:" << peer;
            });

    connect(m_tcpServer, &TcpServer::dataReceived,
            this,
            [=](const QString &peer, const QByteArray &data) {
                qDebug() << "[TCP Server Recv From]" << peer;
                qDebug() << "[TCP Server Recv HEX]" << data.toHex(' ').toUpper();
                qDebug() << "[TCP Server Recv TEXT]" << QString::fromLocal8Bit(data);

                // 收到什么回复什么，方便测试
                m_tcpServer->sendDataToAll(data);
            });

    connect(m_tcpServer, &TcpServer::errorOccurred,
            this,
            [](const QString &error) {
                qDebug() << "[TCP Server Error]" << error;
            });

    // ==================== UDP ====================
    connect(m_udpComm, &UdpComm::dataReceived,
            this,
            [](const QString &ip, quint16 port, const QByteArray &data) {
                qDebug() << "[UDP Recv From]" << ip << port;
                qDebug() << "[UDP Recv HEX]" << data.toHex(' ').toUpper();
                qDebug() << "[UDP Recv TEXT]" << QString::fromLocal8Bit(data);
            });

    connect(m_udpComm, &UdpComm::errorOccurred,
            this,
            [](const QString &error) {
                qDebug() << "[UDP Error]" << error;
            });

    // ==================== Serial ====================
    connect(m_serialComm, &SerialComm::dataReceived,
            this,
            [](const QByteArray &data) {
                qDebug() << "[Serial Recv HEX]" << data.toHex(' ').toUpper();
                qDebug() << "[Serial Recv TEXT]" << QString::fromLocal8Bit(data);
            });

    connect(m_serialComm, &SerialComm::errorOccurred,
            this,
            [](const QString &error) {
                qDebug() << "[Serial Error]" << error;
            });

    connect(m_serialComm, &SerialComm::stateChanged,
            this,
            [](bool opened) {
                qDebug() << "[Serial State]" << opened;
            });
}
void MainWindow::testStartTcpServer()
{
    quint16 port = 6000;

    bool ok = m_tcpServer->start(port);

    if (ok) {
        qDebug() << "[TCP Server] started at port" << port;
    } else {
        qDebug() << "[TCP Server] start failed";
    }
}
void MainWindow::testStartUdp()
{
    quint16 localPort = 7000;

    bool ok = m_udpComm->bindPort(localPort);

    if (ok) {
        qDebug() << "[UDP] bind port success:" << localPort;
    } else {
        qDebug() << "[UDP] bind port failed";
    }
}
void MainWindow::testStartModbusTcpServer()
{
    int port = 1502;
    int serverAddress = 1;

    bool ok = m_modbusServer->startTcp(port, serverAddress);

    if (ok) {
        qDebug() << "[Modbus TCP Server] started. port =" << port
                 << "serverAddress =" << serverAddress;

        m_modbusServer->setHoldingRegister(0, 100);
        m_modbusServer->setHoldingRegister(1, 200);
        m_modbusServer->setHoldingRegister(2, 300);
    } else {
        qDebug() << "[Modbus TCP Server] start failed";
    }
}