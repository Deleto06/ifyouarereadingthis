/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 6.11.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QCheckBox>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QGraphicsView>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QListWidget>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QScrollArea>
#include <QtWidgets/QSpinBox>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QTabWidget>
#include <QtWidgets/QTableWidget>
#include <QtWidgets/QTextEdit>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QWidget *centralwidget;
    QHBoxLayout *horizontalLayout;
    QGroupBox *groupBox;
    QVBoxLayout *verticalLayout_4;
    QListWidget *listWidget;
    QPushButton *btnAddDir;
    QGraphicsView *graphicsView;
    QTabWidget *tabWidgetComm;
    QWidget *tab_3;
    QVBoxLayout *verticalLayout;
    QLabel *label;
    QLineEdit *lineEditTcpServerPort;
    QPushButton *btnTcpServerStart;
    QPushButton *btnTcpServerStop;
    QLabel *label_2;
    QTextEdit *textEditTcpServerSend;
    QCheckBox *checkBoxTcpServerSendHex;
    QPushButton *btnTcpServerSend;
    QWidget *tab;
    QVBoxLayout *verticalLayout_6;
    QLabel *label_10;
    QLineEdit *lineEditTcpClientIp;
    QLabel *label_12;
    QLineEdit *lineEditTcpClientPort;
    QPushButton *btnTcpClientConnect;
    QPushButton *btnTcpClientDisconnect;
    QLabel *label_13;
    QTextEdit *textEditTcpClientSend;
    QCheckBox *checkBoxTcpClientSendHex;
    QLabel *labelTcpClientRxCount;
    QPushButton *btnClearTcpClientRxCount;
    QPushButton *btnTcpClientSend;
    QWidget *tab_4;
    QVBoxLayout *verticalLayout_2;
    QLabel *label_3;
    QLineEdit *lineEditUdpLocalPort;
    QPushButton *btnUdpBind;
    QPushButton *btnUdpClose;
    QLabel *label_4;
    QLineEdit *lineEditUdpTargetIp;
    QLabel *label_5;
    QLineEdit *lineEditUdpTargetPort;
    QLabel *label_6;
    QTextEdit *textEditUdpSend;
    QCheckBox *checkBoxUdpSendHex;
    QLabel *labelUdpRxCount;
    QPushButton *btnClearUdpRxCount;
    QPushButton *btnUdpSend;
    QWidget *tab_5;
    QVBoxLayout *verticalLayout_3;
    QHBoxLayout *horizontalLayout_2;
    QLabel *label_7;
    QLineEdit *lineEditModbusServerPort;
    QHBoxLayout *horizontalLayout_3;
    QLabel *label_8;
    QLineEdit *lineEditModbusServerId;
    QPushButton *btnModbusServerStop;
    QPushButton *btnModbusServerStart;
    QLabel *label_9;
    QLineEdit *lineEditModbusRegAddr;
    QLabel *label_11;
    QLineEdit *lineEditModbusRegValue;
    QPushButton *btnModbusSetReg;
    QWidget *tab_2;
    QVBoxLayout *verticalLayout_11;
    QHBoxLayout *horizontalLayout_10;
    QLabel *label_20;
    QLineEdit *lineEditModbusClientIp;
    QHBoxLayout *horizontalLayout_11;
    QLabel *label_21;
    QLineEdit *lineEditModbusClientPort;
    QHBoxLayout *horizontalLayout_12;
    QLabel *label_22;
    QSpinBox *spinBoxModbusClientUnitId;
    QHBoxLayout *horizontalLayout_17;
    QPushButton *btnModbusClientConnect;
    QPushButton *btnModbusClientDisconnect;
    QHBoxLayout *horizontalLayout_13;
    QLabel *label_23;
    QSpinBox *spinBoxModbusClientStartAddr;
    QHBoxLayout *horizontalLayout_14;
    QLabel *label_24;
    QSpinBox *spinBoxModbusClientCount;
    QPushButton *btnModbusClientReadHolding;
    QHBoxLayout *horizontalLayout_15;
    QLabel *label_32;
    QSpinBox *spinBoxModbusClientWriteAddr;
    QVBoxLayout *verticalLayout_10;
    QLabel *label_34;
    QLineEdit *lineEditModbusClientWriteValue;
    QLabel *label_25;
    QPushButton *btnModbusClientWriteSingle;
    QPushButton *btnModbusClientWriteMultiple;
    QWidget *tab_6;
    QVBoxLayout *verticalLayout_9;
    QHBoxLayout *horizontalLayout_8;
    QLabel *label_14;
    QComboBox *comboBoxSerialPort;
    QHBoxLayout *horizontalLayout_7;
    QLabel *label_15;
    QComboBox *comboBoxSerialBaudRate;
    QHBoxLayout *horizontalLayout_6;
    QLabel *label_17;
    QComboBox *comboBoxSerialDataBits;
    QHBoxLayout *horizontalLayout_5;
    QLabel *label_16;
    QComboBox *comboBoxSerialStopBits;
    QHBoxLayout *horizontalLayout_4;
    QLabel *label_18;
    QComboBox *comboBoxSerialParity;
    QHBoxLayout *horizontalLayout_9;
    QPushButton *btnSerialOpen;
    QPushButton *btnSerialClose;
    QPushButton *btnSerialRefresh;
    QLabel *label_19;
    QTextEdit *textEditSerialSend;
    QCheckBox *checkBoxSerialSendHex;
    QPushButton *btnSerialSend;
    QWidget *tab_7;
    QGroupBox *groupBox_3;
    QLabel *label_33;
    QLabel *label_35;
    QSpinBox *spinBoxModbusRtuStartAddr;
    QSpinBox *spinBoxModbusRtuCount;
    QPushButton *btnModbusRtuReadHolding;
    QGroupBox *groupBox_4;
    QLabel *label_36;
    QSpinBox *spinBoxModbusRtuWriteAddr;
    QLabel *label_37;
    QLineEdit *lineEditModbusRtuWriteValue;
    QPushButton *btnModbusRtuWriteSingle;
    QPushButton *btnModbusRtuWriteMultiple;
    QGroupBox *groupBox_5;
    QLabel *label_26;
    QLabel *label_27;
    QLabel *label_28;
    QLabel *label_29;
    QLabel *label_30;
    QLabel *label_31;
    QComboBox *comboBoxModbusRtuPort;
    QComboBox *comboBoxModbusRtuBaudRate;
    QComboBox *comboBoxModbusRtuDataBits;
    QComboBox *comboBoxModbusRtuStopBits;
    QComboBox *comboBoxModbusRtuParity;
    QSpinBox *spinBoxModbusRtuSlaveId;
    QPushButton *btnModbusRtuOpen;
    QPushButton *btnModbusRtuClose;
    QPushButton *btnModbusRtuRefresh;
    QWidget *tab_8;
    QScrollArea *scrollArea;
    QWidget *scrollAreaWidgetContents;
    QGroupBox *groupBox_6;
    QPushButton *btnModbusRtuSlaveOpen;
    QPushButton *btnModbusRtuSlaveClose;
    QWidget *horizontalLayoutWidget;
    QHBoxLayout *horizontalLayout_16;
    QLabel *label_38;
    QComboBox *comboBoxModbusRtuSlavePort;
    QPushButton *btnModbusRtuSlaveRefreshPort;
    QWidget *horizontalLayoutWidget_2;
    QHBoxLayout *horizontalLayout_18;
    QLabel *label_39;
    QComboBox *comboBoxModbusRtuSlaveBaudRate;
    QWidget *horizontalLayoutWidget_3;
    QHBoxLayout *horizontalLayout_19;
    QLabel *label_40;
    QComboBox *comboBoxModbusRtuSlaveDataBits;
    QWidget *horizontalLayoutWidget_4;
    QHBoxLayout *horizontalLayout_20;
    QLabel *label_42;
    QComboBox *comboBoxModbusRtuSlaveParity;
    QWidget *horizontalLayoutWidget_5;
    QHBoxLayout *horizontalLayout_21;
    QLabel *label_41;
    QComboBox *comboBoxModbusRtuSlaveStopBits;
    QWidget *horizontalLayoutWidget_8;
    QHBoxLayout *horizontalLayout_24;
    QLabel *label_43;
    QSpinBox *spinBoxModbusRtuSlaveSelfId;
    QGroupBox *groupBox_7;
    QPushButton *btnModbusRtuSlaveInitRegisters;
    QPushButton *btnModbusRtuSlaveClearRegisters;
    QWidget *horizontalLayoutWidget_6;
    QHBoxLayout *horizontalLayout_22;
    QLabel *label_44;
    QSpinBox *spinBoxModbusRtuSlaveRegisterCount;
    QWidget *horizontalLayoutWidget_7;
    QHBoxLayout *horizontalLayout_23;
    QLabel *label_45;
    QSpinBox *spinBoxModbusRtuSlaveStartAddress;
    QTableWidget *tableWidgetModbusRtuSlaveHolding;
    QGroupBox *groupBox_2;
    QVBoxLayout *verticalLayout_5;
    QTextEdit *textEditLog;
    QPushButton *btnSaveLog;
    QPushButton *btnClearLog;
    QMenuBar *menubar;
    QStatusBar *statusbar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName("MainWindow");
        MainWindow->resize(1011, 600);
        centralwidget = new QWidget(MainWindow);
        centralwidget->setObjectName("centralwidget");
        horizontalLayout = new QHBoxLayout(centralwidget);
        horizontalLayout->setObjectName("horizontalLayout");
        groupBox = new QGroupBox(centralwidget);
        groupBox->setObjectName("groupBox");
        verticalLayout_4 = new QVBoxLayout(groupBox);
        verticalLayout_4->setObjectName("verticalLayout_4");
        listWidget = new QListWidget(groupBox);
        listWidget->setObjectName("listWidget");
        listWidget->setMinimumSize(QSize(200, 0));

        verticalLayout_4->addWidget(listWidget);

        btnAddDir = new QPushButton(groupBox);
        btnAddDir->setObjectName("btnAddDir");

        verticalLayout_4->addWidget(btnAddDir);


        horizontalLayout->addWidget(groupBox);

        graphicsView = new QGraphicsView(centralwidget);
        graphicsView->setObjectName("graphicsView");

        horizontalLayout->addWidget(graphicsView);

        tabWidgetComm = new QTabWidget(centralwidget);
        tabWidgetComm->setObjectName("tabWidgetComm");
        tab_3 = new QWidget();
        tab_3->setObjectName("tab_3");
        verticalLayout = new QVBoxLayout(tab_3);
        verticalLayout->setObjectName("verticalLayout");
        label = new QLabel(tab_3);
        label->setObjectName("label");

        verticalLayout->addWidget(label);

        lineEditTcpServerPort = new QLineEdit(tab_3);
        lineEditTcpServerPort->setObjectName("lineEditTcpServerPort");

        verticalLayout->addWidget(lineEditTcpServerPort);

        btnTcpServerStart = new QPushButton(tab_3);
        btnTcpServerStart->setObjectName("btnTcpServerStart");

        verticalLayout->addWidget(btnTcpServerStart);

        btnTcpServerStop = new QPushButton(tab_3);
        btnTcpServerStop->setObjectName("btnTcpServerStop");

        verticalLayout->addWidget(btnTcpServerStop);

        label_2 = new QLabel(tab_3);
        label_2->setObjectName("label_2");

        verticalLayout->addWidget(label_2);

        textEditTcpServerSend = new QTextEdit(tab_3);
        textEditTcpServerSend->setObjectName("textEditTcpServerSend");

        verticalLayout->addWidget(textEditTcpServerSend);

        checkBoxTcpServerSendHex = new QCheckBox(tab_3);
        checkBoxTcpServerSendHex->setObjectName("checkBoxTcpServerSendHex");

        verticalLayout->addWidget(checkBoxTcpServerSendHex);

        btnTcpServerSend = new QPushButton(tab_3);
        btnTcpServerSend->setObjectName("btnTcpServerSend");

        verticalLayout->addWidget(btnTcpServerSend);

        tabWidgetComm->addTab(tab_3, QString());
        tab = new QWidget();
        tab->setObjectName("tab");
        verticalLayout_6 = new QVBoxLayout(tab);
        verticalLayout_6->setObjectName("verticalLayout_6");
        label_10 = new QLabel(tab);
        label_10->setObjectName("label_10");

        verticalLayout_6->addWidget(label_10);

        lineEditTcpClientIp = new QLineEdit(tab);
        lineEditTcpClientIp->setObjectName("lineEditTcpClientIp");

        verticalLayout_6->addWidget(lineEditTcpClientIp);

        label_12 = new QLabel(tab);
        label_12->setObjectName("label_12");

        verticalLayout_6->addWidget(label_12);

        lineEditTcpClientPort = new QLineEdit(tab);
        lineEditTcpClientPort->setObjectName("lineEditTcpClientPort");

        verticalLayout_6->addWidget(lineEditTcpClientPort);

        btnTcpClientConnect = new QPushButton(tab);
        btnTcpClientConnect->setObjectName("btnTcpClientConnect");

        verticalLayout_6->addWidget(btnTcpClientConnect);

        btnTcpClientDisconnect = new QPushButton(tab);
        btnTcpClientDisconnect->setObjectName("btnTcpClientDisconnect");

        verticalLayout_6->addWidget(btnTcpClientDisconnect);

        label_13 = new QLabel(tab);
        label_13->setObjectName("label_13");

        verticalLayout_6->addWidget(label_13);

        textEditTcpClientSend = new QTextEdit(tab);
        textEditTcpClientSend->setObjectName("textEditTcpClientSend");

        verticalLayout_6->addWidget(textEditTcpClientSend);

        checkBoxTcpClientSendHex = new QCheckBox(tab);
        checkBoxTcpClientSendHex->setObjectName("checkBoxTcpClientSendHex");

        verticalLayout_6->addWidget(checkBoxTcpClientSendHex);

        labelTcpClientRxCount = new QLabel(tab);
        labelTcpClientRxCount->setObjectName("labelTcpClientRxCount");

        verticalLayout_6->addWidget(labelTcpClientRxCount);

        btnClearTcpClientRxCount = new QPushButton(tab);
        btnClearTcpClientRxCount->setObjectName("btnClearTcpClientRxCount");

        verticalLayout_6->addWidget(btnClearTcpClientRxCount);

        btnTcpClientSend = new QPushButton(tab);
        btnTcpClientSend->setObjectName("btnTcpClientSend");

        verticalLayout_6->addWidget(btnTcpClientSend);

        tabWidgetComm->addTab(tab, QString());
        tab_4 = new QWidget();
        tab_4->setObjectName("tab_4");
        verticalLayout_2 = new QVBoxLayout(tab_4);
        verticalLayout_2->setObjectName("verticalLayout_2");
        label_3 = new QLabel(tab_4);
        label_3->setObjectName("label_3");

        verticalLayout_2->addWidget(label_3);

        lineEditUdpLocalPort = new QLineEdit(tab_4);
        lineEditUdpLocalPort->setObjectName("lineEditUdpLocalPort");

        verticalLayout_2->addWidget(lineEditUdpLocalPort);

        btnUdpBind = new QPushButton(tab_4);
        btnUdpBind->setObjectName("btnUdpBind");

        verticalLayout_2->addWidget(btnUdpBind);

        btnUdpClose = new QPushButton(tab_4);
        btnUdpClose->setObjectName("btnUdpClose");

        verticalLayout_2->addWidget(btnUdpClose);

        label_4 = new QLabel(tab_4);
        label_4->setObjectName("label_4");

        verticalLayout_2->addWidget(label_4);

        lineEditUdpTargetIp = new QLineEdit(tab_4);
        lineEditUdpTargetIp->setObjectName("lineEditUdpTargetIp");

        verticalLayout_2->addWidget(lineEditUdpTargetIp);

        label_5 = new QLabel(tab_4);
        label_5->setObjectName("label_5");

        verticalLayout_2->addWidget(label_5);

        lineEditUdpTargetPort = new QLineEdit(tab_4);
        lineEditUdpTargetPort->setObjectName("lineEditUdpTargetPort");

        verticalLayout_2->addWidget(lineEditUdpTargetPort);

        label_6 = new QLabel(tab_4);
        label_6->setObjectName("label_6");

        verticalLayout_2->addWidget(label_6);

        textEditUdpSend = new QTextEdit(tab_4);
        textEditUdpSend->setObjectName("textEditUdpSend");

        verticalLayout_2->addWidget(textEditUdpSend);

        checkBoxUdpSendHex = new QCheckBox(tab_4);
        checkBoxUdpSendHex->setObjectName("checkBoxUdpSendHex");

        verticalLayout_2->addWidget(checkBoxUdpSendHex);

        labelUdpRxCount = new QLabel(tab_4);
        labelUdpRxCount->setObjectName("labelUdpRxCount");

        verticalLayout_2->addWidget(labelUdpRxCount);

        btnClearUdpRxCount = new QPushButton(tab_4);
        btnClearUdpRxCount->setObjectName("btnClearUdpRxCount");

        verticalLayout_2->addWidget(btnClearUdpRxCount);

        btnUdpSend = new QPushButton(tab_4);
        btnUdpSend->setObjectName("btnUdpSend");

        verticalLayout_2->addWidget(btnUdpSend);

        tabWidgetComm->addTab(tab_4, QString());
        tab_5 = new QWidget();
        tab_5->setObjectName("tab_5");
        verticalLayout_3 = new QVBoxLayout(tab_5);
        verticalLayout_3->setObjectName("verticalLayout_3");
        horizontalLayout_2 = new QHBoxLayout();
        horizontalLayout_2->setObjectName("horizontalLayout_2");
        label_7 = new QLabel(tab_5);
        label_7->setObjectName("label_7");

        horizontalLayout_2->addWidget(label_7);

        lineEditModbusServerPort = new QLineEdit(tab_5);
        lineEditModbusServerPort->setObjectName("lineEditModbusServerPort");

        horizontalLayout_2->addWidget(lineEditModbusServerPort);


        verticalLayout_3->addLayout(horizontalLayout_2);

        horizontalLayout_3 = new QHBoxLayout();
        horizontalLayout_3->setObjectName("horizontalLayout_3");
        label_8 = new QLabel(tab_5);
        label_8->setObjectName("label_8");

        horizontalLayout_3->addWidget(label_8);

        lineEditModbusServerId = new QLineEdit(tab_5);
        lineEditModbusServerId->setObjectName("lineEditModbusServerId");

        horizontalLayout_3->addWidget(lineEditModbusServerId);


        verticalLayout_3->addLayout(horizontalLayout_3);

        btnModbusServerStop = new QPushButton(tab_5);
        btnModbusServerStop->setObjectName("btnModbusServerStop");

        verticalLayout_3->addWidget(btnModbusServerStop);

        btnModbusServerStart = new QPushButton(tab_5);
        btnModbusServerStart->setObjectName("btnModbusServerStart");

        verticalLayout_3->addWidget(btnModbusServerStart);

        label_9 = new QLabel(tab_5);
        label_9->setObjectName("label_9");

        verticalLayout_3->addWidget(label_9);

        lineEditModbusRegAddr = new QLineEdit(tab_5);
        lineEditModbusRegAddr->setObjectName("lineEditModbusRegAddr");

        verticalLayout_3->addWidget(lineEditModbusRegAddr);

        label_11 = new QLabel(tab_5);
        label_11->setObjectName("label_11");

        verticalLayout_3->addWidget(label_11);

        lineEditModbusRegValue = new QLineEdit(tab_5);
        lineEditModbusRegValue->setObjectName("lineEditModbusRegValue");

        verticalLayout_3->addWidget(lineEditModbusRegValue);

        btnModbusSetReg = new QPushButton(tab_5);
        btnModbusSetReg->setObjectName("btnModbusSetReg");

        verticalLayout_3->addWidget(btnModbusSetReg);

        tabWidgetComm->addTab(tab_5, QString());
        tab_2 = new QWidget();
        tab_2->setObjectName("tab_2");
        verticalLayout_11 = new QVBoxLayout(tab_2);
        verticalLayout_11->setObjectName("verticalLayout_11");
        horizontalLayout_10 = new QHBoxLayout();
        horizontalLayout_10->setObjectName("horizontalLayout_10");
        label_20 = new QLabel(tab_2);
        label_20->setObjectName("label_20");

        horizontalLayout_10->addWidget(label_20);

        lineEditModbusClientIp = new QLineEdit(tab_2);
        lineEditModbusClientIp->setObjectName("lineEditModbusClientIp");

        horizontalLayout_10->addWidget(lineEditModbusClientIp);


        verticalLayout_11->addLayout(horizontalLayout_10);

        horizontalLayout_11 = new QHBoxLayout();
        horizontalLayout_11->setObjectName("horizontalLayout_11");
        label_21 = new QLabel(tab_2);
        label_21->setObjectName("label_21");

        horizontalLayout_11->addWidget(label_21);

        lineEditModbusClientPort = new QLineEdit(tab_2);
        lineEditModbusClientPort->setObjectName("lineEditModbusClientPort");

        horizontalLayout_11->addWidget(lineEditModbusClientPort);


        verticalLayout_11->addLayout(horizontalLayout_11);

        horizontalLayout_12 = new QHBoxLayout();
        horizontalLayout_12->setObjectName("horizontalLayout_12");
        label_22 = new QLabel(tab_2);
        label_22->setObjectName("label_22");

        horizontalLayout_12->addWidget(label_22);

        spinBoxModbusClientUnitId = new QSpinBox(tab_2);
        spinBoxModbusClientUnitId->setObjectName("spinBoxModbusClientUnitId");
        spinBoxModbusClientUnitId->setValue(1);

        horizontalLayout_12->addWidget(spinBoxModbusClientUnitId);


        verticalLayout_11->addLayout(horizontalLayout_12);

        horizontalLayout_17 = new QHBoxLayout();
        horizontalLayout_17->setObjectName("horizontalLayout_17");
        btnModbusClientConnect = new QPushButton(tab_2);
        btnModbusClientConnect->setObjectName("btnModbusClientConnect");

        horizontalLayout_17->addWidget(btnModbusClientConnect);

        btnModbusClientDisconnect = new QPushButton(tab_2);
        btnModbusClientDisconnect->setObjectName("btnModbusClientDisconnect");

        horizontalLayout_17->addWidget(btnModbusClientDisconnect);


        verticalLayout_11->addLayout(horizontalLayout_17);

        horizontalLayout_13 = new QHBoxLayout();
        horizontalLayout_13->setObjectName("horizontalLayout_13");
        label_23 = new QLabel(tab_2);
        label_23->setObjectName("label_23");

        horizontalLayout_13->addWidget(label_23);

        spinBoxModbusClientStartAddr = new QSpinBox(tab_2);
        spinBoxModbusClientStartAddr->setObjectName("spinBoxModbusClientStartAddr");

        horizontalLayout_13->addWidget(spinBoxModbusClientStartAddr);


        verticalLayout_11->addLayout(horizontalLayout_13);

        horizontalLayout_14 = new QHBoxLayout();
        horizontalLayout_14->setObjectName("horizontalLayout_14");
        label_24 = new QLabel(tab_2);
        label_24->setObjectName("label_24");

        horizontalLayout_14->addWidget(label_24);

        spinBoxModbusClientCount = new QSpinBox(tab_2);
        spinBoxModbusClientCount->setObjectName("spinBoxModbusClientCount");
        spinBoxModbusClientCount->setValue(10);

        horizontalLayout_14->addWidget(spinBoxModbusClientCount);


        verticalLayout_11->addLayout(horizontalLayout_14);

        btnModbusClientReadHolding = new QPushButton(tab_2);
        btnModbusClientReadHolding->setObjectName("btnModbusClientReadHolding");

        verticalLayout_11->addWidget(btnModbusClientReadHolding);

        horizontalLayout_15 = new QHBoxLayout();
        horizontalLayout_15->setObjectName("horizontalLayout_15");
        label_32 = new QLabel(tab_2);
        label_32->setObjectName("label_32");

        horizontalLayout_15->addWidget(label_32);

        spinBoxModbusClientWriteAddr = new QSpinBox(tab_2);
        spinBoxModbusClientWriteAddr->setObjectName("spinBoxModbusClientWriteAddr");

        horizontalLayout_15->addWidget(spinBoxModbusClientWriteAddr);


        verticalLayout_11->addLayout(horizontalLayout_15);

        verticalLayout_10 = new QVBoxLayout();
        verticalLayout_10->setObjectName("verticalLayout_10");
        label_34 = new QLabel(tab_2);
        label_34->setObjectName("label_34");

        verticalLayout_10->addWidget(label_34);

        lineEditModbusClientWriteValue = new QLineEdit(tab_2);
        lineEditModbusClientWriteValue->setObjectName("lineEditModbusClientWriteValue");

        verticalLayout_10->addWidget(lineEditModbusClientWriteValue);

        label_25 = new QLabel(tab_2);
        label_25->setObjectName("label_25");

        verticalLayout_10->addWidget(label_25);


        verticalLayout_11->addLayout(verticalLayout_10);

        btnModbusClientWriteSingle = new QPushButton(tab_2);
        btnModbusClientWriteSingle->setObjectName("btnModbusClientWriteSingle");

        verticalLayout_11->addWidget(btnModbusClientWriteSingle);

        btnModbusClientWriteMultiple = new QPushButton(tab_2);
        btnModbusClientWriteMultiple->setObjectName("btnModbusClientWriteMultiple");

        verticalLayout_11->addWidget(btnModbusClientWriteMultiple);

        tabWidgetComm->addTab(tab_2, QString());
        tab_6 = new QWidget();
        tab_6->setObjectName("tab_6");
        verticalLayout_9 = new QVBoxLayout(tab_6);
        verticalLayout_9->setObjectName("verticalLayout_9");
        horizontalLayout_8 = new QHBoxLayout();
        horizontalLayout_8->setObjectName("horizontalLayout_8");
        label_14 = new QLabel(tab_6);
        label_14->setObjectName("label_14");

        horizontalLayout_8->addWidget(label_14);

        comboBoxSerialPort = new QComboBox(tab_6);
        comboBoxSerialPort->setObjectName("comboBoxSerialPort");

        horizontalLayout_8->addWidget(comboBoxSerialPort);


        verticalLayout_9->addLayout(horizontalLayout_8);

        horizontalLayout_7 = new QHBoxLayout();
        horizontalLayout_7->setObjectName("horizontalLayout_7");
        label_15 = new QLabel(tab_6);
        label_15->setObjectName("label_15");

        horizontalLayout_7->addWidget(label_15);

        comboBoxSerialBaudRate = new QComboBox(tab_6);
        comboBoxSerialBaudRate->setObjectName("comboBoxSerialBaudRate");

        horizontalLayout_7->addWidget(comboBoxSerialBaudRate);


        verticalLayout_9->addLayout(horizontalLayout_7);

        horizontalLayout_6 = new QHBoxLayout();
        horizontalLayout_6->setObjectName("horizontalLayout_6");
        label_17 = new QLabel(tab_6);
        label_17->setObjectName("label_17");

        horizontalLayout_6->addWidget(label_17);

        comboBoxSerialDataBits = new QComboBox(tab_6);
        comboBoxSerialDataBits->setObjectName("comboBoxSerialDataBits");

        horizontalLayout_6->addWidget(comboBoxSerialDataBits);


        verticalLayout_9->addLayout(horizontalLayout_6);

        horizontalLayout_5 = new QHBoxLayout();
        horizontalLayout_5->setObjectName("horizontalLayout_5");
        label_16 = new QLabel(tab_6);
        label_16->setObjectName("label_16");

        horizontalLayout_5->addWidget(label_16);

        comboBoxSerialStopBits = new QComboBox(tab_6);
        comboBoxSerialStopBits->setObjectName("comboBoxSerialStopBits");

        horizontalLayout_5->addWidget(comboBoxSerialStopBits);


        verticalLayout_9->addLayout(horizontalLayout_5);

        horizontalLayout_4 = new QHBoxLayout();
        horizontalLayout_4->setObjectName("horizontalLayout_4");
        label_18 = new QLabel(tab_6);
        label_18->setObjectName("label_18");

        horizontalLayout_4->addWidget(label_18);

        comboBoxSerialParity = new QComboBox(tab_6);
        comboBoxSerialParity->setObjectName("comboBoxSerialParity");

        horizontalLayout_4->addWidget(comboBoxSerialParity);


        verticalLayout_9->addLayout(horizontalLayout_4);

        horizontalLayout_9 = new QHBoxLayout();
        horizontalLayout_9->setObjectName("horizontalLayout_9");
        btnSerialOpen = new QPushButton(tab_6);
        btnSerialOpen->setObjectName("btnSerialOpen");

        horizontalLayout_9->addWidget(btnSerialOpen);

        btnSerialClose = new QPushButton(tab_6);
        btnSerialClose->setObjectName("btnSerialClose");

        horizontalLayout_9->addWidget(btnSerialClose);


        verticalLayout_9->addLayout(horizontalLayout_9);

        btnSerialRefresh = new QPushButton(tab_6);
        btnSerialRefresh->setObjectName("btnSerialRefresh");

        verticalLayout_9->addWidget(btnSerialRefresh);

        label_19 = new QLabel(tab_6);
        label_19->setObjectName("label_19");

        verticalLayout_9->addWidget(label_19);

        textEditSerialSend = new QTextEdit(tab_6);
        textEditSerialSend->setObjectName("textEditSerialSend");

        verticalLayout_9->addWidget(textEditSerialSend);

        checkBoxSerialSendHex = new QCheckBox(tab_6);
        checkBoxSerialSendHex->setObjectName("checkBoxSerialSendHex");

        verticalLayout_9->addWidget(checkBoxSerialSendHex);

        btnSerialSend = new QPushButton(tab_6);
        btnSerialSend->setObjectName("btnSerialSend");

        verticalLayout_9->addWidget(btnSerialSend);

        tabWidgetComm->addTab(tab_6, QString());
        tab_7 = new QWidget();
        tab_7->setObjectName("tab_7");
        groupBox_3 = new QGroupBox(tab_7);
        groupBox_3->setObjectName("groupBox_3");
        groupBox_3->setGeometry(QRect(10, 270, 231, 111));
        label_33 = new QLabel(groupBox_3);
        label_33->setObjectName("label_33");
        label_33->setGeometry(QRect(20, 20, 71, 20));
        label_35 = new QLabel(groupBox_3);
        label_35->setObjectName("label_35");
        label_35->setGeometry(QRect(20, 60, 53, 15));
        spinBoxModbusRtuStartAddr = new QSpinBox(groupBox_3);
        spinBoxModbusRtuStartAddr->setObjectName("spinBoxModbusRtuStartAddr");
        spinBoxModbusRtuStartAddr->setGeometry(QRect(70, 20, 101, 24));
        spinBoxModbusRtuCount = new QSpinBox(groupBox_3);
        spinBoxModbusRtuCount->setObjectName("spinBoxModbusRtuCount");
        spinBoxModbusRtuCount->setGeometry(QRect(70, 50, 101, 24));
        spinBoxModbusRtuCount->setValue(2);
        btnModbusRtuReadHolding = new QPushButton(groupBox_3);
        btnModbusRtuReadHolding->setObjectName("btnModbusRtuReadHolding");
        btnModbusRtuReadHolding->setEnabled(false);
        btnModbusRtuReadHolding->setGeometry(QRect(20, 80, 111, 23));
        groupBox_4 = new QGroupBox(tab_7);
        groupBox_4->setObjectName("groupBox_4");
        groupBox_4->setGeometry(QRect(10, 390, 231, 111));
        label_36 = new QLabel(groupBox_4);
        label_36->setObjectName("label_36");
        label_36->setGeometry(QRect(20, 20, 53, 15));
        spinBoxModbusRtuWriteAddr = new QSpinBox(groupBox_4);
        spinBoxModbusRtuWriteAddr->setObjectName("spinBoxModbusRtuWriteAddr");
        spinBoxModbusRtuWriteAddr->setGeometry(QRect(70, 20, 101, 24));
        label_37 = new QLabel(groupBox_4);
        label_37->setObjectName("label_37");
        label_37->setGeometry(QRect(30, 50, 41, 16));
        lineEditModbusRtuWriteValue = new QLineEdit(groupBox_4);
        lineEditModbusRtuWriteValue->setObjectName("lineEditModbusRtuWriteValue");
        lineEditModbusRtuWriteValue->setGeometry(QRect(70, 50, 113, 23));
        btnModbusRtuWriteSingle = new QPushButton(groupBox_4);
        btnModbusRtuWriteSingle->setObjectName("btnModbusRtuWriteSingle");
        btnModbusRtuWriteSingle->setEnabled(false);
        btnModbusRtuWriteSingle->setGeometry(QRect(10, 80, 101, 23));
        btnModbusRtuWriteMultiple = new QPushButton(groupBox_4);
        btnModbusRtuWriteMultiple->setObjectName("btnModbusRtuWriteMultiple");
        btnModbusRtuWriteMultiple->setEnabled(false);
        btnModbusRtuWriteMultiple->setGeometry(QRect(120, 80, 101, 23));
        groupBox_5 = new QGroupBox(tab_7);
        groupBox_5->setObjectName("groupBox_5");
        groupBox_5->setGeometry(QRect(10, 10, 231, 241));
        label_26 = new QLabel(groupBox_5);
        label_26->setObjectName("label_26");
        label_26->setGeometry(QRect(10, 30, 53, 15));
        label_27 = new QLabel(groupBox_5);
        label_27->setObjectName("label_27");
        label_27->setGeometry(QRect(10, 60, 53, 15));
        label_28 = new QLabel(groupBox_5);
        label_28->setObjectName("label_28");
        label_28->setGeometry(QRect(10, 90, 53, 15));
        label_29 = new QLabel(groupBox_5);
        label_29->setObjectName("label_29");
        label_29->setGeometry(QRect(10, 120, 53, 15));
        label_30 = new QLabel(groupBox_5);
        label_30->setObjectName("label_30");
        label_30->setGeometry(QRect(10, 150, 53, 15));
        label_31 = new QLabel(groupBox_5);
        label_31->setObjectName("label_31");
        label_31->setGeometry(QRect(20, 180, 53, 15));
        comboBoxModbusRtuPort = new QComboBox(groupBox_5);
        comboBoxModbusRtuPort->setObjectName("comboBoxModbusRtuPort");
        comboBoxModbusRtuPort->setGeometry(QRect(50, 30, 91, 23));
        comboBoxModbusRtuBaudRate = new QComboBox(groupBox_5);
        comboBoxModbusRtuBaudRate->setObjectName("comboBoxModbusRtuBaudRate");
        comboBoxModbusRtuBaudRate->setGeometry(QRect(50, 60, 91, 23));
        comboBoxModbusRtuDataBits = new QComboBox(groupBox_5);
        comboBoxModbusRtuDataBits->setObjectName("comboBoxModbusRtuDataBits");
        comboBoxModbusRtuDataBits->setGeometry(QRect(50, 90, 91, 23));
        comboBoxModbusRtuStopBits = new QComboBox(groupBox_5);
        comboBoxModbusRtuStopBits->setObjectName("comboBoxModbusRtuStopBits");
        comboBoxModbusRtuStopBits->setGeometry(QRect(50, 120, 91, 23));
        comboBoxModbusRtuParity = new QComboBox(groupBox_5);
        comboBoxModbusRtuParity->setObjectName("comboBoxModbusRtuParity");
        comboBoxModbusRtuParity->setGeometry(QRect(50, 150, 91, 23));
        spinBoxModbusRtuSlaveId = new QSpinBox(groupBox_5);
        spinBoxModbusRtuSlaveId->setObjectName("spinBoxModbusRtuSlaveId");
        spinBoxModbusRtuSlaveId->setGeometry(QRect(70, 180, 101, 24));
        spinBoxModbusRtuSlaveId->setValue(1);
        btnModbusRtuOpen = new QPushButton(groupBox_5);
        btnModbusRtuOpen->setObjectName("btnModbusRtuOpen");
        btnModbusRtuOpen->setGeometry(QRect(10, 210, 80, 23));
        btnModbusRtuClose = new QPushButton(groupBox_5);
        btnModbusRtuClose->setObjectName("btnModbusRtuClose");
        btnModbusRtuClose->setGeometry(QRect(100, 210, 80, 23));
        btnModbusRtuRefresh = new QPushButton(groupBox_5);
        btnModbusRtuRefresh->setObjectName("btnModbusRtuRefresh");
        btnModbusRtuRefresh->setGeometry(QRect(170, 30, 41, 23));
        tabWidgetComm->addTab(tab_7, QString());
        tab_8 = new QWidget();
        tab_8->setObjectName("tab_8");
        scrollArea = new QScrollArea(tab_8);
        scrollArea->setObjectName("scrollArea");
        scrollArea->setGeometry(QRect(0, 0, 251, 511));
        scrollArea->setWidgetResizable(true);
        scrollAreaWidgetContents = new QWidget();
        scrollAreaWidgetContents->setObjectName("scrollAreaWidgetContents");
        scrollAreaWidgetContents->setGeometry(QRect(0, 0, 249, 509));
        groupBox_6 = new QGroupBox(scrollAreaWidgetContents);
        groupBox_6->setObjectName("groupBox_6");
        groupBox_6->setGeometry(QRect(10, 10, 231, 241));
        btnModbusRtuSlaveOpen = new QPushButton(groupBox_6);
        btnModbusRtuSlaveOpen->setObjectName("btnModbusRtuSlaveOpen");
        btnModbusRtuSlaveOpen->setGeometry(QRect(10, 210, 80, 23));
        btnModbusRtuSlaveClose = new QPushButton(groupBox_6);
        btnModbusRtuSlaveClose->setObjectName("btnModbusRtuSlaveClose");
        btnModbusRtuSlaveClose->setGeometry(QRect(100, 210, 80, 23));
        horizontalLayoutWidget = new QWidget(groupBox_6);
        horizontalLayoutWidget->setObjectName("horizontalLayoutWidget");
        horizontalLayoutWidget->setGeometry(QRect(10, 20, 221, 31));
        horizontalLayout_16 = new QHBoxLayout(horizontalLayoutWidget);
        horizontalLayout_16->setObjectName("horizontalLayout_16");
        horizontalLayout_16->setContentsMargins(0, 0, 0, 0);
        label_38 = new QLabel(horizontalLayoutWidget);
        label_38->setObjectName("label_38");

        horizontalLayout_16->addWidget(label_38);

        comboBoxModbusRtuSlavePort = new QComboBox(horizontalLayoutWidget);
        comboBoxModbusRtuSlavePort->setObjectName("comboBoxModbusRtuSlavePort");

        horizontalLayout_16->addWidget(comboBoxModbusRtuSlavePort);

        btnModbusRtuSlaveRefreshPort = new QPushButton(horizontalLayoutWidget);
        btnModbusRtuSlaveRefreshPort->setObjectName("btnModbusRtuSlaveRefreshPort");

        horizontalLayout_16->addWidget(btnModbusRtuSlaveRefreshPort);

        horizontalLayoutWidget_2 = new QWidget(groupBox_6);
        horizontalLayoutWidget_2->setObjectName("horizontalLayoutWidget_2");
        horizontalLayoutWidget_2->setGeometry(QRect(10, 50, 131, 31));
        horizontalLayout_18 = new QHBoxLayout(horizontalLayoutWidget_2);
        horizontalLayout_18->setObjectName("horizontalLayout_18");
        horizontalLayout_18->setContentsMargins(0, 0, 0, 0);
        label_39 = new QLabel(horizontalLayoutWidget_2);
        label_39->setObjectName("label_39");

        horizontalLayout_18->addWidget(label_39);

        comboBoxModbusRtuSlaveBaudRate = new QComboBox(horizontalLayoutWidget_2);
        comboBoxModbusRtuSlaveBaudRate->setObjectName("comboBoxModbusRtuSlaveBaudRate");

        horizontalLayout_18->addWidget(comboBoxModbusRtuSlaveBaudRate);

        horizontalLayoutWidget_3 = new QWidget(groupBox_6);
        horizontalLayoutWidget_3->setObjectName("horizontalLayoutWidget_3");
        horizontalLayoutWidget_3->setGeometry(QRect(10, 80, 131, 31));
        horizontalLayout_19 = new QHBoxLayout(horizontalLayoutWidget_3);
        horizontalLayout_19->setObjectName("horizontalLayout_19");
        horizontalLayout_19->setContentsMargins(0, 0, 0, 0);
        label_40 = new QLabel(horizontalLayoutWidget_3);
        label_40->setObjectName("label_40");

        horizontalLayout_19->addWidget(label_40);

        comboBoxModbusRtuSlaveDataBits = new QComboBox(horizontalLayoutWidget_3);
        comboBoxModbusRtuSlaveDataBits->setObjectName("comboBoxModbusRtuSlaveDataBits");

        horizontalLayout_19->addWidget(comboBoxModbusRtuSlaveDataBits);

        horizontalLayoutWidget_4 = new QWidget(groupBox_6);
        horizontalLayoutWidget_4->setObjectName("horizontalLayoutWidget_4");
        horizontalLayoutWidget_4->setGeometry(QRect(10, 110, 131, 31));
        horizontalLayout_20 = new QHBoxLayout(horizontalLayoutWidget_4);
        horizontalLayout_20->setObjectName("horizontalLayout_20");
        horizontalLayout_20->setContentsMargins(0, 0, 0, 0);
        label_42 = new QLabel(horizontalLayoutWidget_4);
        label_42->setObjectName("label_42");

        horizontalLayout_20->addWidget(label_42);

        comboBoxModbusRtuSlaveParity = new QComboBox(horizontalLayoutWidget_4);
        comboBoxModbusRtuSlaveParity->setObjectName("comboBoxModbusRtuSlaveParity");

        horizontalLayout_20->addWidget(comboBoxModbusRtuSlaveParity);

        horizontalLayoutWidget_5 = new QWidget(groupBox_6);
        horizontalLayoutWidget_5->setObjectName("horizontalLayoutWidget_5");
        horizontalLayoutWidget_5->setGeometry(QRect(10, 140, 131, 31));
        horizontalLayout_21 = new QHBoxLayout(horizontalLayoutWidget_5);
        horizontalLayout_21->setObjectName("horizontalLayout_21");
        horizontalLayout_21->setContentsMargins(0, 0, 0, 0);
        label_41 = new QLabel(horizontalLayoutWidget_5);
        label_41->setObjectName("label_41");

        horizontalLayout_21->addWidget(label_41);

        comboBoxModbusRtuSlaveStopBits = new QComboBox(horizontalLayoutWidget_5);
        comboBoxModbusRtuSlaveStopBits->setObjectName("comboBoxModbusRtuSlaveStopBits");

        horizontalLayout_21->addWidget(comboBoxModbusRtuSlaveStopBits);

        horizontalLayoutWidget_8 = new QWidget(groupBox_6);
        horizontalLayoutWidget_8->setObjectName("horizontalLayoutWidget_8");
        horizontalLayoutWidget_8->setGeometry(QRect(10, 170, 131, 31));
        horizontalLayout_24 = new QHBoxLayout(horizontalLayoutWidget_8);
        horizontalLayout_24->setObjectName("horizontalLayout_24");
        horizontalLayout_24->setContentsMargins(0, 0, 0, 0);
        label_43 = new QLabel(horizontalLayoutWidget_8);
        label_43->setObjectName("label_43");

        horizontalLayout_24->addWidget(label_43);

        spinBoxModbusRtuSlaveSelfId = new QSpinBox(horizontalLayoutWidget_8);
        spinBoxModbusRtuSlaveSelfId->setObjectName("spinBoxModbusRtuSlaveSelfId");
        spinBoxModbusRtuSlaveSelfId->setValue(1);

        horizontalLayout_24->addWidget(spinBoxModbusRtuSlaveSelfId);

        groupBox_7 = new QGroupBox(scrollAreaWidgetContents);
        groupBox_7->setObjectName("groupBox_7");
        groupBox_7->setGeometry(QRect(10, 260, 231, 111));
        btnModbusRtuSlaveInitRegisters = new QPushButton(groupBox_7);
        btnModbusRtuSlaveInitRegisters->setObjectName("btnModbusRtuSlaveInitRegisters");
        btnModbusRtuSlaveInitRegisters->setGeometry(QRect(10, 80, 101, 23));
        btnModbusRtuSlaveClearRegisters = new QPushButton(groupBox_7);
        btnModbusRtuSlaveClearRegisters->setObjectName("btnModbusRtuSlaveClearRegisters");
        btnModbusRtuSlaveClearRegisters->setGeometry(QRect(110, 80, 101, 23));
        horizontalLayoutWidget_6 = new QWidget(groupBox_7);
        horizontalLayoutWidget_6->setObjectName("horizontalLayoutWidget_6");
        horizontalLayoutWidget_6->setGeometry(QRect(40, 20, 160, 31));
        horizontalLayout_22 = new QHBoxLayout(horizontalLayoutWidget_6);
        horizontalLayout_22->setObjectName("horizontalLayout_22");
        horizontalLayout_22->setContentsMargins(0, 0, 0, 0);
        label_44 = new QLabel(horizontalLayoutWidget_6);
        label_44->setObjectName("label_44");

        horizontalLayout_22->addWidget(label_44);

        spinBoxModbusRtuSlaveRegisterCount = new QSpinBox(horizontalLayoutWidget_6);
        spinBoxModbusRtuSlaveRegisterCount->setObjectName("spinBoxModbusRtuSlaveRegisterCount");
        spinBoxModbusRtuSlaveRegisterCount->setValue(20);

        horizontalLayout_22->addWidget(spinBoxModbusRtuSlaveRegisterCount);

        horizontalLayoutWidget_7 = new QWidget(groupBox_7);
        horizontalLayoutWidget_7->setObjectName("horizontalLayoutWidget_7");
        horizontalLayoutWidget_7->setGeometry(QRect(40, 50, 160, 31));
        horizontalLayout_23 = new QHBoxLayout(horizontalLayoutWidget_7);
        horizontalLayout_23->setObjectName("horizontalLayout_23");
        horizontalLayout_23->setContentsMargins(0, 0, 0, 0);
        label_45 = new QLabel(horizontalLayoutWidget_7);
        label_45->setObjectName("label_45");

        horizontalLayout_23->addWidget(label_45);

        spinBoxModbusRtuSlaveStartAddress = new QSpinBox(horizontalLayoutWidget_7);
        spinBoxModbusRtuSlaveStartAddress->setObjectName("spinBoxModbusRtuSlaveStartAddress");

        horizontalLayout_23->addWidget(spinBoxModbusRtuSlaveStartAddress);

        tableWidgetModbusRtuSlaveHolding = new QTableWidget(scrollAreaWidgetContents);
        tableWidgetModbusRtuSlaveHolding->setObjectName("tableWidgetModbusRtuSlaveHolding");
        tableWidgetModbusRtuSlaveHolding->setGeometry(QRect(0, 390, 241, 111));
        scrollArea->setWidget(scrollAreaWidgetContents);
        tabWidgetComm->addTab(tab_8, QString());

        horizontalLayout->addWidget(tabWidgetComm);

        groupBox_2 = new QGroupBox(centralwidget);
        groupBox_2->setObjectName("groupBox_2");
        verticalLayout_5 = new QVBoxLayout(groupBox_2);
        verticalLayout_5->setObjectName("verticalLayout_5");
        textEditLog = new QTextEdit(groupBox_2);
        textEditLog->setObjectName("textEditLog");
        textEditLog->setMinimumSize(QSize(200, 0));
        textEditLog->setReadOnly(true);

        verticalLayout_5->addWidget(textEditLog);

        btnSaveLog = new QPushButton(groupBox_2);
        btnSaveLog->setObjectName("btnSaveLog");

        verticalLayout_5->addWidget(btnSaveLog);

        btnClearLog = new QPushButton(groupBox_2);
        btnClearLog->setObjectName("btnClearLog");

        verticalLayout_5->addWidget(btnClearLog);


        horizontalLayout->addWidget(groupBox_2);

        MainWindow->setCentralWidget(centralwidget);
        menubar = new QMenuBar(MainWindow);
        menubar->setObjectName("menubar");
        menubar->setGeometry(QRect(0, 0, 1011, 20));
        MainWindow->setMenuBar(menubar);
        statusbar = new QStatusBar(MainWindow);
        statusbar->setObjectName("statusbar");
        MainWindow->setStatusBar(statusbar);

        retranslateUi(MainWindow);

        tabWidgetComm->setCurrentIndex(2);


        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QCoreApplication::translate("MainWindow", "MainWindow", nullptr));
        groupBox->setTitle(QCoreApplication::translate("MainWindow", "\351\200\211\346\213\251\345\233\276\347\211\207", nullptr));
        btnAddDir->setText(QCoreApplication::translate("MainWindow", "\351\200\211\346\213\251\346\226\207\344\273\266\345\244\271", nullptr));
        label->setText(QCoreApplication::translate("MainWindow", "\347\253\257\345\217\243\357\274\232", nullptr));
        lineEditTcpServerPort->setText(QCoreApplication::translate("MainWindow", "6000", nullptr));
        btnTcpServerStart->setText(QCoreApplication::translate("MainWindow", "\345\220\257\345\212\250", nullptr));
        btnTcpServerStop->setText(QCoreApplication::translate("MainWindow", "\345\201\234\346\255\242", nullptr));
        label_2->setText(QCoreApplication::translate("MainWindow", "\345\217\221\351\200\201\345\206\205\345\256\271\357\274\232", nullptr));
        checkBoxTcpServerSendHex->setText(QCoreApplication::translate("MainWindow", "HEX\345\217\221\351\200\201", nullptr));
        btnTcpServerSend->setText(QCoreApplication::translate("MainWindow", "\345\217\221\351\200\201\347\273\231\345\205\250\351\203\250\345\256\242\346\210\267\347\253\257", nullptr));
        tabWidgetComm->setTabText(tabWidgetComm->indexOf(tab_3), QCoreApplication::translate("MainWindow", "TCP Server", nullptr));
        label_10->setText(QCoreApplication::translate("MainWindow", "\346\234\215\345\212\241\345\231\250IP\357\274\232", nullptr));
        label_12->setText(QCoreApplication::translate("MainWindow", "\346\234\215\345\212\241\345\231\250\347\253\257\345\217\243\357\274\232", nullptr));
        btnTcpClientConnect->setText(QCoreApplication::translate("MainWindow", "\350\277\236\346\216\245", nullptr));
        btnTcpClientDisconnect->setText(QCoreApplication::translate("MainWindow", "\346\226\255\345\274\200", nullptr));
        label_13->setText(QCoreApplication::translate("MainWindow", "\345\217\221\351\200\201\345\206\205\345\256\271\357\274\232", nullptr));
        checkBoxTcpClientSendHex->setText(QCoreApplication::translate("MainWindow", "HEX\345\217\221\351\200\201", nullptr));
        labelTcpClientRxCount->setText(QCoreApplication::translate("MainWindow", "TCP\346\216\245\346\224\266\346\254\241\346\225\260\357\274\2320", nullptr));
        btnClearTcpClientRxCount->setText(QCoreApplication::translate("MainWindow", "\346\270\205\351\233\266", nullptr));
        btnTcpClientSend->setText(QCoreApplication::translate("MainWindow", "\345\217\221\351\200\201", nullptr));
        tabWidgetComm->setTabText(tabWidgetComm->indexOf(tab), QCoreApplication::translate("MainWindow", "TCP Client", nullptr));
        label_3->setText(QCoreApplication::translate("MainWindow", "\346\234\254\345\234\260\347\253\257\345\217\243\357\274\232", nullptr));
        lineEditUdpLocalPort->setText(QCoreApplication::translate("MainWindow", "7000", nullptr));
        btnUdpBind->setText(QCoreApplication::translate("MainWindow", "\347\273\221\345\256\232", nullptr));
        btnUdpClose->setText(QCoreApplication::translate("MainWindow", "\345\205\263\351\227\255", nullptr));
        label_4->setText(QCoreApplication::translate("MainWindow", "\347\233\256\346\240\207IP\357\274\232", nullptr));
        lineEditUdpTargetIp->setText(QCoreApplication::translate("MainWindow", "127.0.0.1", nullptr));
        label_5->setText(QCoreApplication::translate("MainWindow", "\347\233\256\346\240\207\347\253\257\345\217\243\357\274\232", nullptr));
        lineEditUdpTargetPort->setText(QCoreApplication::translate("MainWindow", "6000", nullptr));
        label_6->setText(QCoreApplication::translate("MainWindow", "\345\217\221\351\200\201\345\206\205\345\256\271:", nullptr));
        checkBoxUdpSendHex->setText(QCoreApplication::translate("MainWindow", "HEX\345\217\221\351\200\201", nullptr));
        labelUdpRxCount->setText(QCoreApplication::translate("MainWindow", "UDP\346\216\245\346\224\266\346\254\241\346\225\260\357\274\2320", nullptr));
        btnClearUdpRxCount->setText(QCoreApplication::translate("MainWindow", "\346\270\205\351\233\266", nullptr));
        btnUdpSend->setText(QCoreApplication::translate("MainWindow", "UDP\345\217\221\351\200\201", nullptr));
        tabWidgetComm->setTabText(tabWidgetComm->indexOf(tab_4), QCoreApplication::translate("MainWindow", "UDP", nullptr));
        label_7->setText(QCoreApplication::translate("MainWindow", "\347\253\257\345\217\243\357\274\232", nullptr));
        lineEditModbusServerPort->setText(QCoreApplication::translate("MainWindow", "1502", nullptr));
        label_8->setText(QCoreApplication::translate("MainWindow", "\347\253\231\345\217\267\357\274\232", nullptr));
        lineEditModbusServerId->setText(QCoreApplication::translate("MainWindow", "1", nullptr));
        btnModbusServerStop->setText(QCoreApplication::translate("MainWindow", "\345\201\234\346\255\242", nullptr));
        btnModbusServerStart->setText(QCoreApplication::translate("MainWindow", "\345\220\257\345\212\250", nullptr));
        label_9->setText(QCoreApplication::translate("MainWindow", "\345\257\204\345\255\230\345\231\250\345\234\260\345\235\200\357\274\232", nullptr));
        lineEditModbusRegAddr->setText(QCoreApplication::translate("MainWindow", "0", nullptr));
        label_11->setText(QCoreApplication::translate("MainWindow", "\345\257\204\345\255\230\345\231\250\345\200\274\357\274\232", nullptr));
        lineEditModbusRegValue->setText(QCoreApplication::translate("MainWindow", "100", nullptr));
        btnModbusSetReg->setText(QCoreApplication::translate("MainWindow", "\350\256\276\347\275\256\345\257\204\345\255\230\345\231\250", nullptr));
        tabWidgetComm->setTabText(tabWidgetComm->indexOf(tab_5), QCoreApplication::translate("MainWindow", "Modbus TCP Server", nullptr));
        label_20->setText(QCoreApplication::translate("MainWindow", "\347\233\256\346\240\207IP\357\274\232 ", nullptr));
        lineEditModbusClientIp->setText(QCoreApplication::translate("MainWindow", "127.0.0.1", nullptr));
        label_21->setText(QCoreApplication::translate("MainWindow", "\347\233\256\346\240\207\347\253\257\345\217\243\357\274\232", nullptr));
        lineEditModbusClientPort->setText(QCoreApplication::translate("MainWindow", "1502", nullptr));
        label_22->setText(QCoreApplication::translate("MainWindow", "Unit ID(Slave ID\357\274\214\347\253\231\345\217\267):", nullptr));
        btnModbusClientConnect->setText(QCoreApplication::translate("MainWindow", "\350\277\236\346\216\245", nullptr));
        btnModbusClientDisconnect->setText(QCoreApplication::translate("MainWindow", "\346\226\255\345\274\200", nullptr));
        label_23->setText(QCoreApplication::translate("MainWindow", "\350\265\267\345\247\213\345\234\260\345\235\200:", nullptr));
        label_24->setText(QCoreApplication::translate("MainWindow", "\350\257\273\345\217\226\344\277\235\346\214\201\345\257\204\345\255\230\345\231\250\346\225\260\351\207\217:", nullptr));
        btnModbusClientReadHolding->setText(QCoreApplication::translate("MainWindow", "\350\257\273\344\277\235\346\214\201\345\257\204\345\255\230\345\231\250", nullptr));
        label_32->setText(QCoreApplication::translate("MainWindow", "\345\206\231\345\205\245\350\265\267\345\247\213\345\234\260\345\235\200:", nullptr));
        label_34->setText(QCoreApplication::translate("MainWindow", "\345\206\231\345\205\245\344\277\235\346\214\201\345\257\204\345\255\230\345\231\250\347\232\204\345\200\274:", nullptr));
        lineEditModbusClientWriteValue->setText(QCoreApplication::translate("MainWindow", "123", nullptr));
        label_25->setText(QCoreApplication::translate("MainWindow", "\345\206\231\345\205\245\345\244\232\344\270\252\347\244\272\344\276\213\357\274\23210,20,30 \346\210\22610 20 30", nullptr));
        btnModbusClientWriteSingle->setText(QCoreApplication::translate("MainWindow", "\345\206\231\345\215\225\344\270\252\345\257\204\345\255\230\345\231\250", nullptr));
        btnModbusClientWriteMultiple->setText(QCoreApplication::translate("MainWindow", "\345\206\231\345\244\232\344\270\252\345\257\204\345\255\230\345\231\250", nullptr));
        tabWidgetComm->setTabText(tabWidgetComm->indexOf(tab_2), QCoreApplication::translate("MainWindow", "Modbus TCP Client", nullptr));
        label_14->setText(QCoreApplication::translate("MainWindow", "\344\270\262\345\217\243\345\217\267", nullptr));
        label_15->setText(QCoreApplication::translate("MainWindow", "\346\263\242\347\211\271\347\216\207", nullptr));
        label_17->setText(QCoreApplication::translate("MainWindow", "\346\225\260\346\215\256\344\275\215", nullptr));
        label_16->setText(QCoreApplication::translate("MainWindow", "\345\201\234\346\255\242\344\275\215", nullptr));
        label_18->setText(QCoreApplication::translate("MainWindow", "\346\240\241\351\252\214\344\275\215", nullptr));
        btnSerialOpen->setText(QCoreApplication::translate("MainWindow", "\346\211\223\345\274\200\344\270\262\345\217\243", nullptr));
        btnSerialClose->setText(QCoreApplication::translate("MainWindow", "\345\205\263\351\227\255\344\270\262\345\217\243", nullptr));
        btnSerialRefresh->setText(QCoreApplication::translate("MainWindow", "\345\210\267\346\226\260\344\270\262\345\217\243\345\210\227\350\241\250", nullptr));
        label_19->setText(QCoreApplication::translate("MainWindow", "\345\217\221\351\200\201\345\206\205\345\256\271\357\274\232", nullptr));
        checkBoxSerialSendHex->setText(QCoreApplication::translate("MainWindow", "HEX \345\217\221\351\200\201", nullptr));
        btnSerialSend->setText(QCoreApplication::translate("MainWindow", "\345\217\221\351\200\201", nullptr));
        tabWidgetComm->setTabText(tabWidgetComm->indexOf(tab_6), QCoreApplication::translate("MainWindow", "COM/RS232", nullptr));
        groupBox_3->setTitle(QCoreApplication::translate("MainWindow", "\350\257\273\344\277\235\346\214\201\345\257\204\345\255\230\345\231\250 03", nullptr));
        label_33->setText(QCoreApplication::translate("MainWindow", "\350\265\267\345\247\213\345\234\260\345\235\200", nullptr));
        label_35->setText(QCoreApplication::translate("MainWindow", "\350\257\273\345\217\226\346\225\260\351\207\217", nullptr));
        btnModbusRtuReadHolding->setText(QCoreApplication::translate("MainWindow", "\350\257\273\344\277\235\346\214\201\345\257\204\345\255\230\345\231\250", nullptr));
        groupBox_4->setTitle(QCoreApplication::translate("MainWindow", "\345\206\231\344\277\235\346\214\201\345\257\204\345\255\230\345\231\250 06 / 10", nullptr));
        label_36->setText(QCoreApplication::translate("MainWindow", "\345\206\231\345\205\245\345\234\260\345\235\200", nullptr));
        label_37->setText(QCoreApplication::translate("MainWindow", "\345\206\231\345\205\245\345\200\274", nullptr));
        lineEditModbusRtuWriteValue->setText(QCoreApplication::translate("MainWindow", "123", nullptr));
        btnModbusRtuWriteSingle->setText(QCoreApplication::translate("MainWindow", "\345\206\231\345\215\225\344\270\252\345\257\204\345\255\230\345\231\250", nullptr));
        btnModbusRtuWriteMultiple->setText(QCoreApplication::translate("MainWindow", "\345\206\231\345\244\232\344\270\252\345\257\204\345\255\230\345\231\250", nullptr));
        groupBox_5->setTitle(QCoreApplication::translate("MainWindow", "\350\256\276\347\275\256\344\270\262\345\217\243\345\217\202\346\225\260", nullptr));
        label_26->setText(QCoreApplication::translate("MainWindow", "\344\270\262\345\217\243\345\217\267 ", nullptr));
        label_27->setText(QCoreApplication::translate("MainWindow", "\346\263\242\347\211\271\347\216\207", nullptr));
        label_28->setText(QCoreApplication::translate("MainWindow", "\346\225\260\346\215\256\344\275\215", nullptr));
        label_29->setText(QCoreApplication::translate("MainWindow", "\345\201\234\346\255\242\344\275\215", nullptr));
        label_30->setText(QCoreApplication::translate("MainWindow", "\346\240\241\351\252\214\344\275\215", nullptr));
        label_31->setText(QCoreApplication::translate("MainWindow", "\344\273\216\347\253\231\345\234\260\345\235\200", nullptr));
        btnModbusRtuOpen->setText(QCoreApplication::translate("MainWindow", "\346\211\223\345\274\200\344\270\262\345\217\243", nullptr));
        btnModbusRtuClose->setText(QCoreApplication::translate("MainWindow", "\345\205\263\351\227\255\344\270\262\345\217\243", nullptr));
        btnModbusRtuRefresh->setText(QCoreApplication::translate("MainWindow", "\345\210\267\346\226\260", nullptr));
        tabWidgetComm->setTabText(tabWidgetComm->indexOf(tab_7), QCoreApplication::translate("MainWindow", "Modbus RTU Master", nullptr));
        groupBox_6->setTitle(QCoreApplication::translate("MainWindow", "\350\256\276\347\275\256\344\270\262\345\217\243\345\217\202\346\225\260", nullptr));
        btnModbusRtuSlaveOpen->setText(QCoreApplication::translate("MainWindow", "\346\211\223\345\274\200\344\270\262\345\217\243", nullptr));
        btnModbusRtuSlaveClose->setText(QCoreApplication::translate("MainWindow", "\345\205\263\351\227\255\344\270\262\345\217\243", nullptr));
        label_38->setText(QCoreApplication::translate("MainWindow", "\344\270\262\345\217\243\345\217\267 ", nullptr));
        btnModbusRtuSlaveRefreshPort->setText(QCoreApplication::translate("MainWindow", "\345\210\267\346\226\260", nullptr));
        label_39->setText(QCoreApplication::translate("MainWindow", "\346\263\242\347\211\271\347\216\207", nullptr));
        label_40->setText(QCoreApplication::translate("MainWindow", "\346\225\260\346\215\256\344\275\215", nullptr));
        label_42->setText(QCoreApplication::translate("MainWindow", "\346\240\241\351\252\214\344\275\215", nullptr));
        label_41->setText(QCoreApplication::translate("MainWindow", "\345\201\234\346\255\242\344\275\215", nullptr));
        label_43->setText(QCoreApplication::translate("MainWindow", "\344\273\216\347\253\231\345\234\260\345\235\200", nullptr));
        groupBox_7->setTitle(QCoreApplication::translate("MainWindow", "\345\257\204\345\255\230\345\231\250\351\205\215\347\275\256", nullptr));
        btnModbusRtuSlaveInitRegisters->setText(QCoreApplication::translate("MainWindow", "\345\210\235\345\247\213\345\214\226\345\257\204\345\255\230\345\231\250", nullptr));
        btnModbusRtuSlaveClearRegisters->setText(QCoreApplication::translate("MainWindow", "\346\270\205\347\251\272\345\257\204\345\255\230\345\231\250", nullptr));
        label_44->setText(QCoreApplication::translate("MainWindow", "\344\277\235\346\214\201\345\257\204\345\255\230\345\231\250\346\225\260\351\207\217", nullptr));
        label_45->setText(QCoreApplication::translate("MainWindow", "\350\265\267\345\247\213\345\234\260\345\235\200", nullptr));
        tabWidgetComm->setTabText(tabWidgetComm->indexOf(tab_8), QCoreApplication::translate("MainWindow", "Modbus RTU Slave ", nullptr));
        groupBox_2->setTitle(QCoreApplication::translate("MainWindow", "\346\227\245\345\277\227", nullptr));
        btnSaveLog->setText(QCoreApplication::translate("MainWindow", "\344\277\235\345\255\230\346\227\245\345\277\227\345\210\260...", nullptr));
        btnClearLog->setText(QCoreApplication::translate("MainWindow", "\346\270\205\347\251\272\346\227\245\345\277\227", nullptr));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
