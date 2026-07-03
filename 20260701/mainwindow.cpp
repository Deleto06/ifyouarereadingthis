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
            ui->listWidget->addItem(arr[i].toString());
        }
        jsonFile.close();
    } else {
        // ================= 【修改这里】 =================
        // 如果是第一次启动没有 JSON，自动扫描你准备好的图片文件夹
        QDir dir("C:/qtdevelop/20260701/20260701/pictures");

        if (dir.exists()) {
            // 设置过滤器，只读取图片文件
            QStringList filters;
            filters << "*.jpg" << "*.bmp" << "*.png";
            dir.setNameFilters(filters);

            QFileInfoList fileList = dir.entryInfoList(QDir::Files | QDir::NoSymLinks);
            for (const QFileInfo &fileInfo : fileList) {
                // 将扫描到的绝对路径添加到列表控件中
                ui->listWidget->addItem(fileInfo.absoluteFilePath());
            }
        } else {
            qDebug() << "图片目录不存在，请检查路径！";
        }
        // ===============================================
    }

    // 2. 读取 INI 恢复上次选中的项
    QSettings settings(iniPath, QSettings::IniFormat);
    QString lastSelected = settings.value("LastSelectedImage", "").toString();

    // 遍历寻找并选中
    if (!lastSelected.isEmpty()) {
        for (int i = 0; i < ui->listWidget->count(); ++i) {
            if (ui->listWidget->item(i)->text() == lastSelected) {
                ui->listWidget->setCurrentRow(i); // 选中，并自动触发图像加载
                 ui->listWidget->setFocus();
                break;
            }
        }
    } else if (ui->listWidget->count() > 0) {
        // 如果没有历史记录（第一次启动），默认选中第一张图
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
    for (int i = 0; i < ui->listWidget->count(); ++i) {
        arr.append(ui->listWidget->item(i)->text());
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

bool MainWindow::eventFilter(QObject *watched, QEvent *event)
{
    if ((watched == ui->graphicsView || watched == ui->graphicsView->viewport())
        && event->type() == QEvent::Wheel)
    {
        QWheelEvent *wheelEvent = static_cast<QWheelEvent*>(event);
        double scaleFactor = 1.15;
        // 增加放大缩小限制，防止无限缩放导致崩溃
        qreal currentScale = ui->graphicsView->transform().m11();

        if (wheelEvent->angleDelta().y() > 0) {
            if (currentScale < 50.0) ui->graphicsView->scale(scaleFactor, scaleFactor);
        } else {
            if (currentScale > 0.02) ui->graphicsView->scale(1.0 / scaleFactor, 1.0 / scaleFactor);
        }
        return true;
    }
    return QMainWindow::eventFilter(watched, event);
}
// ==================== 槽函数：右键菜单 ====================
// ==================== 槽函数：右键菜单 ====================
void MainWindow::onListWidgetCustomContextMenuRequested(const QPoint &pos)
{
    // 获取鼠标位置对应的列表项
    QListWidgetItem *item = ui->listWidget->itemAt(pos);

    if (item) {
        // ============ 点在某个列表项上 ============
        QMenu menu(this);
        QAction *removeAction = menu.addAction("移除图片");

        QAction *selected = menu.exec(ui->listWidget->viewport()->mapToGlobal(pos));
        if (selected == removeAction) {
            int currentRow = ui->listWidget->currentRow();
            delete item;

            if (ui->listWidget->count() > 0) {
                if (currentRow >= ui->listWidget->count()) {
                    ui->listWidget->setCurrentRow(ui->listWidget->count() - 1);
                } else {
                    ui->listWidget->setCurrentRow(currentRow);
                }
            } else {
                scene->clear();
                pixmapItem = nullptr;
            }
        }
    } else {
        // ============ 点在空白处 ============
        QMenu menu(this);
        QAction *saveAction = menu.addAction("保存当前图片到目录...");
        QAction *addFilesAction = menu.addAction("添加图片文件...");  // 【新增】

        QAction *selected = menu.exec(ui->listWidget->viewport()->mapToGlobal(pos));
        if (selected == saveAction) {
            onSaveCurrentImageToDir();
        } else if (selected == addFilesAction) {  // 【新增】
            onAddImageFiles();
        }
    }
}
// ==================== 槽函数：选择目录添加图片 ====================
void MainWindow::onBtnAddDirClicked()
{
    // 弹出目录选择对话框
    QString dirPath = QFileDialog::getExistingDirectory(
        this,
        "选择图片目录",
        QCoreApplication::applicationDirPath()  // 默认打开程序所在目录
        );

    if (dirPath.isEmpty()) return;  // 用户点了取消

    QDir dir(dirPath);
    QStringList filters;
    filters << "*.jpg" << "*.jpeg" << "*.png" << "*.bmp" << "*.gif";
    dir.setNameFilters(filters);

    QFileInfoList fileList = dir.entryInfoList(QDir::Files | QDir::NoSymLinks);

    int addedCount = 0;
    for (const QFileInfo &fileInfo : fileList) {
        QString filePath = fileInfo.absoluteFilePath();
        // 避免重复添加：先检查列表中是否已存在该路径
        bool exists = false;
        for (int i = 0; i < ui->listWidget->count(); ++i) {
            if (ui->listWidget->item(i)->text() == filePath) {
                exists = true;
                break;
            }
        }
        if (!exists) {
            ui->listWidget->addItem(filePath);
            addedCount++;
        }
    }

    // 可选：提示用户添加了多少张
    if (addedCount > 0) {
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
    // 弹出文件选择对话框，支持多选
    QStringList filePaths = QFileDialog::getOpenFileNames(
        this,
        "选择图片文件",
        QCoreApplication::applicationDirPath(),
        "图片文件 (*.jpg *.jpeg *.png *.bmp *.gif)"
        );

    if (filePaths.isEmpty()) return;  // 用户点了取消

    int addedCount = 0;
    for (const QString &filePath : filePaths) {
        // 检查是否已存在
        bool exists = false;
        for (int i = 0; i < ui->listWidget->count(); ++i) {
            if (ui->listWidget->item(i)->text() == filePath) {
                exists = true;
                break;
            }
        }
        if (!exists) {
            ui->listWidget->addItem(filePath);
            addedCount++;
        }
    }

    if (addedCount > 0) {
        qDebug() << "成功添加" << addedCount << "张图片";
    } else {
        qDebug() << "所选图片已全部在列表中";
    }
}