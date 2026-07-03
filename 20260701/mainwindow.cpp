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
    ui->listWidget->viewport()->installEventFilter(this);

    // connect连接信号和槽。 连接列表切换信号 (鼠标点击和上下键都会触发这个信号)
    connect(ui->listWidget, &QListWidget::currentItemChanged,
            this, &MainWindow::onListWidgetCurrentItemChanged);

    ui->listWidget->setContextMenuPolicy(Qt::CustomContextMenu);
    connect(ui->listWidget, &QListWidget::customContextMenuRequested,
            this, &MainWindow::onListWidgetCustomContextMenuRequested);

    connect(ui->btnAddDir, &QPushButton::clicked,
            this, &MainWindow::onBtnAddDirClicked);
    // 3. 加载上次保存的状态
    loadSettings();
}

MainWindow::~MainWindow()
{
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

    scene->clear();
    pixmapItem = nullptr;

    QImage qImg;

    cv::Mat rgbImg;
    cv::Mat rgbaImg;


    if (cvImage.channels() == 1) {
        qImg = QImage((const unsigned char*)(cvImage.data), cvImage.cols, cvImage.rows, cvImage.step, QImage::Format_Grayscale8);
    }
    else if (cvImage.channels() == 3) {
        cv::cvtColor(cvImage, rgbImg, cv::COLOR_BGR2RGB);
        qImg = QImage((const unsigned char*)(rgbImg.data), rgbImg.cols, rgbImg.rows, rgbImg.step, QImage::Format_RGB888);
    }
    else if (cvImage.channels() == 4) {
        cv::cvtColor(cvImage, rgbaImg, cv::COLOR_BGRA2RGBA);
        qImg = QImage((const unsigned char*)(rgbaImg.data), rgbaImg.cols, rgbaImg.rows, rgbaImg.step, QImage::Format_RGBA8888);
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
            filters << "*.jpg" << "*.bmp" << "*.png";
            dir.setNameFilters(filters);
            QFileInfoList fileList = dir.entryInfoList(QDir::Files | QDir::NoSymLinks);
            for (const QFileInfo &fileInfo : fileList) {
                m_imagePaths.append(fileInfo.absoluteFilePath());
            }
        } else {
            qDebug() << "图片目录不存在，请检查路径！";
        }
    }

    // 【关键步骤】用数据源一次性填充界面
    ui->listWidget->addItems(m_imagePaths);

    // 2. 读取 INI 恢复上次选中的项
    QSettings settings(iniPath, QSettings::IniFormat);
    QString lastSelected = settings.value("LastSelectedImage", "").toString();

    // 在数据源 m_imagePaths 中查找上次选中的图片索引
    int lastIndex = m_imagePaths.indexOf(lastSelected);
    if (lastIndex != -1) {
        ui->listWidget->setCurrentRow(lastIndex);
        ui->listWidget->setFocus();
    } else if (ui->listWidget->count() > 0) {
        ui->listWidget->setCurrentRow(0);
        ui->listWidget->setFocus();
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

// mainwindow.cpp

// --- 新增：事件过滤器的实现 ---
bool MainWindow::eventFilter(QObject *watched, QEvent *event)
{
    // --- 原有逻辑：处理 ListWidget 右键 ---
    if (watched == ui->listWidget->viewport()) {
        if (event->type() == QEvent::MouseButtonPress) {
            QMouseEvent *mouseEvent = static_cast<QMouseEvent*>(event);
            if (mouseEvent->button() == Qt::RightButton) {
                // ... 你的右键菜单代码 ...
                return true;
            }
        }
    }

    // --- 新增逻辑：处理 GraphicsView 滚轮缩放 ---
    if (watched == ui->graphicsView->viewport()) { // 注意：通常是 viewport
        if (event->type() == QEvent::Wheel) {
            QWheelEvent *wheelEvent = static_cast<QWheelEvent *>(event);

            // 获取当前的缩放比例
            double scaleFactor = 1.15; // 每次滚动的缩放系数

            // 判断滚轮方向：向上滚放大，向下滚缩小
            if (wheelEvent->angleDelta().y() > 0) {
                ui->graphicsView->scale(scaleFactor, scaleFactor);
            } else {
                ui->graphicsView->scale(1.0 / scaleFactor, 1.0 / scaleFactor);
            }

            return true; // 事件已处理，不再传递
        }
    }

    // 其他事件全部放行
    return QMainWindow::eventFilter(watched, event);
}
// --------------------------------
// ==================== 槽函数：右键菜单 ====================
// ==================== 槽函数：右键菜单 ====================
void MainWindow::onListWidgetCustomContextMenuRequested(const QPoint &pos)
{
    // 1. 获取被右键点击的项
    QListWidgetItem *item = ui->listWidget->itemAt(pos);

    // 2. 如果点在空白处，执行原有逻辑
    if (!item) {
        QMenu menu(this);
        QAction *saveAction = menu.addAction("保存当前图片到目录...");
        QAction *addFilesAction = menu.addAction("添加图片文件...");
        QAction *selected = menu.exec(ui->listWidget->viewport()->mapToGlobal(pos));

        if (selected == saveAction) {
            onSaveCurrentImageToDir();
        } else if (selected == addFilesAction) {
            onAddImageFiles();
        }
        return; // 处理完空白处逻辑后直接返回
    }

    // 3. 如果点在某个列表项上
    // 【关键步骤】获取该项在数据源中的索引
    int itemRow = ui->listWidget->row(item);

    QMenu menu(this);
    QAction *removeAction = menu.addAction("移除图片");
    QAction *selected = menu.exec(ui->listWidget->viewport()->mapToGlobal(pos));

    if (selected == removeAction) {
        // 【关键步骤】操作数据源
        m_imagePaths.removeAt(itemRow);

        // 【关键步骤】清空并重新填充界面
        ui->listWidget->clear();
        ui->listWidget->addItems(m_imagePaths);

        // 【关键步骤】根据新数据源恢复选中状态
        // 逻辑：尽量保持删除前的视觉位置不变
        if (!m_imagePaths.isEmpty()) {
            int newRow = qMin(itemRow, m_imagePaths.count() - 1);
            ui->listWidget->setCurrentRow(newRow);
        } else {
            scene->clear();
            pixmapItem = nullptr;
        }
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
        // 【关键步骤】清空并重新填充界面
        ui->listWidget->clear();
        ui->listWidget->addItems(m_imagePaths);
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
        // 【关键步骤】清空并重新填充界面
        ui->listWidget->clear();
        ui->listWidget->addItems(m_imagePaths);
        qDebug() << "成功添加" << addedCount << "张图片";
    } else {
        qDebug() << "所选图片已全部在列表中";
    }
}