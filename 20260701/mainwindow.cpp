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

    // 2. 连接列表切换信号 (鼠标点击和上下键都会触发这个信号)
    connect(ui->listWidget, &QListWidget::currentItemChanged,
            this, &MainWindow::onListWidgetCurrentItemChanged);

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


    // 把矩阵声明放在 if 外部，保证它们的存活周期撑过 qImg.copy()
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
    // =======================================================
}

// ==================== 槽函数：列表项改变 ====================
void MainWindow::onListWidgetCurrentItemChanged(QListWidgetItem *current, QListWidgetItem *previous)
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