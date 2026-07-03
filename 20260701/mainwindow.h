#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QGraphicsScene>
#include <QGraphicsPixmapItem>
#include <QEvent>
#include <QCloseEvent>
#include <QListWidgetItem>
#include <opencv2/opencv.hpp>
#include <QResizeEvent>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

protected:
    bool eventFilter(QObject *watched, QEvent *event) override;
    // 拦截窗口关闭事件，用于在退出前保存 JSON 和 INI
    void closeEvent(QCloseEvent *event) override;
    // 窗口大小变化时触发，保证缩放后也能自适应
    void resizeEvent(QResizeEvent *event) override;

private slots:
    // 统一处理鼠标点击和键盘上下键切换图像
    void onListWidgetCurrentItemChanged(QListWidgetItem *current, QListWidgetItem *previous);
    // 右键菜单：移除图片
    void onListWidgetCustomContextMenuRequested(const QPoint &pos);
    // 按钮：选择目录添加图片
    void onBtnAddDirClicked();
    void onSaveCurrentImageToDir();
    void onAddImageFiles();  // 从任意目录选择图片文件添加到列表
private:
    Ui::MainWindow *ui;
    QGraphicsScene *scene;
    QGraphicsPixmapItem *pixmapItem = nullptr;
    cv::Mat cvImage;
    QStringList m_imagePaths;
    // 核心功能函数

    bool m_isLeftButtonPressed = false;
    void loadSettings();    // 软件启动时加载配置
    void saveSettings();    // 软件关闭时保存配置
    void displayImage(const QString &filePath); // 自适应显示图像  
};

#endif // MAINWINDOW_H