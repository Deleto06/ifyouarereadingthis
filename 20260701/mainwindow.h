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
#include <QPoint>
#include "comm/tcpclient.h"
#include "comm/tcpserver.h"
#include "comm/udpcomm.h"
#include "comm/serialcomm.h"
#include "comm/modbusclient.h"
#include "comm/modbusserver.h"
#include "comm/commutils.h"
#include "comm/modbusrtuclient.h"
#include <QSerialPort>
#include <QSerialPortInfo>
#include <QTimer>
#include <QVector>

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
    void on_btnTcpServerStart_clicked();
    void on_btnTcpServerStop_clicked();
    void on_btnTcpServerSend_clicked();

    void on_btnTcpClientConnect_clicked();
    void on_btnTcpClientDisconnect_clicked();
    void on_btnTcpClientSend_clicked();

    void on_btnUdpBind_clicked();
    void on_btnUdpClose_clicked();
    void on_btnUdpSend_clicked();

    void on_btnModbusServerStart_clicked();
    void on_btnModbusServerStop_clicked();
    void on_btnModbusSetReg_clicked();

    void on_btnModbusClientConnect_clicked();
    void on_btnModbusClientDisconnect_clicked();
    void on_btnModbusClientReadHolding_clicked();
    void on_btnModbusClientWriteSingle_clicked();
    void on_btnModbusClientWriteMultiple_clicked();

    void on_btnSerialRefresh_clicked();
    void on_btnSerialOpen_clicked();
    void on_btnSerialClose_clicked();
    void on_btnSerialSend_clicked();

    void on_btnClearLog_clicked();
    void on_btnSaveLog_clicked();

    void on_btnModbusRtuOpen_clicked();
    void on_btnModbusRtuClose_clicked();
    void on_btnModbusRtuReadHolding_clicked();
    void on_btnModbusRtuWriteSingle_clicked();
    void on_btnModbusRtuWriteMultiple_clicked();
    void on_btnModbusRtuRefresh_clicked();
private:
    Ui::MainWindow *ui;
    // ==================== 图像显示相关 ====================
    QGraphicsScene *scene;
    QGraphicsPixmapItem *pixmapItem = nullptr;
    cv::Mat cvImage;
    QStringList m_imagePaths;
    // ==================== 通讯模块相关 ====================
    TcpClient *m_tcpClient = nullptr;
    TcpServer *m_tcpServer = nullptr;
    UdpComm *m_udpComm = nullptr;
    SerialComm *m_serialComm = nullptr;
    ModbusClient *m_modbusClient = nullptr;
    ModbusServer *m_modbusServer = nullptr;
    // 核心功能函数
    ModbusRtuClient *m_modbusRtuClient = nullptr;
    QString byteArrayToPrintableText(const QByteArray &data);
    QListWidgetItem *m_leftPressedItem = nullptr;
    QPoint m_leftPressedPos;
    QString m_currentImagePath;
    QByteArray hexStringToByteArray(const QString &hexText, bool *ok = nullptr);
    QByteArray textToUtf8Bytes(const QString &text);
    QString bytesToUtf8Text(const QByteArray &data);

    QSerialPort::DataBits getSerialDataBitsFromText(const QString &text) const;
    QSerialPort::StopBits getSerialStopBitsFromText(const QString &text) const;
    QSerialPort::Parity getSerialParityFromText(const QString &text) const;

    QSerialPort *m_modbusRtuSlaveSerial = nullptr;
    QByteArray m_modbusRtuSlaveRxBuffer;
    QTimer *m_modbusRtuSlaveFrameTimer = nullptr;
    QVector<quint16> m_modbusRtuSlaveHoldingRegisters;

    quint64 m_tcpClientRxCount = 0;
    quint64 m_udpRxCount = 0;

    bool m_isLeftButtonPressed = false;
    void loadSettings();    // 软件启动时加载配置
    void saveSettings();    // 软件关闭时保存配置
    void displayImage(const QString &filePath); // 自适应显示图像
    void refreshListWidget(int rowToSelect = -1);
    void deleteSelectedImages();
    void initUiState();

    void initCommunication();
    void initCommunicationSignals();

    void testStartTcpServer();
    void testStartUdp();
    void testStartModbusTcpServer();
    void initModbusClientUi();
    void appendLog(const QString &text);
    void initSerialUi();
    void refreshSerialPorts();

    void initModbusRtuUi();
    void initModbusRtuSignals();
    void refreshModbusRtuPorts();

    void initModbusRtuSlaveUi();
    void refreshModbusRtuSlavePorts();
    void initModbusRtuSlaveRegisters();
    void updateModbusRtuSlaveTable();
    void setModbusRtuSlaveOpenedState(bool opened);
    void onModbusRtuSlaveReadyRead();
    void processModbusRtuSlaveFrame();
    quint16 modbusRtuCrc16(const QByteArray &data);
    bool checkModbusRtuCrc(const QByteArray &frame);
    QByteArray appendModbusRtuCrc(const QByteArray &data);
    QString byteArrayToHexString(const QByteArray &data);
    void handleModbusRtuSlaveRequest(const QByteArray &frame);
    void handleModbusRtuSlaveReadHolding(const QByteArray &frame);
    void handleModbusRtuSlaveWriteSingleRegister(const QByteArray &frame);
    void handleModbusRtuSlaveWriteMultipleRegisters(const QByteArray &frame);
    void sendModbusRtuSlaveException(quint8 slaveId, quint8 functionCode, quint8 exceptionCode);


};

#endif // MAINWINDOW_H