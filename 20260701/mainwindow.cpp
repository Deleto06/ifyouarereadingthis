#include "mainwindow.h"
#include "./ui_mainwindow.h"
#include <QWheelEvent>
#include <QDebug>
#include <QScrollBar>
#include <QFile>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    scene = new QGraphicsScene(this);
    ui->graphicsView->setScene(scene);

    ui->graphicsView->setDragMode(QGraphicsView::ScrollHandDrag);
    ui->graphicsView->setTransformationAnchor(QGraphicsView::AnchorUnderMouse);

    ui->graphicsView->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    ui->graphicsView->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);

    ui->graphicsView->installEventFilter(this);
    ui->graphicsView->viewport()->installEventFilter(this);


    QString filePath ="C:/qtdevelop/20260701/20260701/pictures/这是中文路径的图像 (1).jpg";

    QFile file(filePath);
    if (file.open(QIODevice::ReadOnly)) {
        QByteArray fileData = file.readAll();
        file.close();


        std::vector<uchar> buffer(fileData.constData(), fileData.constData() + fileData.size());


        cvImage = cv::imdecode(buffer, cv::IMREAD_COLOR);
    }

    if(!cvImage.empty()) {
        cv::Mat rgbImg;
        cv::cvtColor(cvImage, rgbImg, cv::COLOR_BGR2RGB);

        QImage qImg((const unsigned char*)(rgbImg.data), rgbImg.cols, rgbImg.rows, rgbImg.step, QImage::Format_RGB888);
        pixmapItem = scene->addPixmap(QPixmap::fromImage(qImg.copy()));

        ui->graphicsView->setSceneRect(pixmapItem->boundingRect());
    } else {
        qDebug() << "Failed to load image! Check your file path:" << filePath;
    }
}

bool MainWindow::eventFilter(QObject *watched, QEvent *event)
{
    if ((watched == ui->graphicsView || watched == ui->graphicsView->viewport())
        && event->type() == QEvent::Wheel)
    {
        QWheelEvent *wheelEvent = static_cast<QWheelEvent*>(event);

        double scaleFactor = 1.15;
        if (wheelEvent->angleDelta().y() > 0) {
            ui->graphicsView->scale(scaleFactor, scaleFactor);
        } else {
            ui->graphicsView->scale(1.0 / scaleFactor, 1.0 / scaleFactor);
        }

        return true;
    }

    return QMainWindow::eventFilter(watched, event);
}

MainWindow::~MainWindow()
{
    delete ui;
}