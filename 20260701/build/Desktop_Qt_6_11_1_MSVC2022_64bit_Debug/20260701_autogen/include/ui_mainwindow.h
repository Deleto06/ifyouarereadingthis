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
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QListWidget>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpinBox>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QTabWidget>
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

        tabWidgetComm->setCurrentIndex(3);


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
        tabWidgetComm->setTabText(tabWidgetComm->indexOf(tab_5), QCoreApplication::translate("MainWindow", "Modbus Server", nullptr));
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
        tabWidgetComm->setTabText(tabWidgetComm->indexOf(tab_2), QCoreApplication::translate("MainWindow", "Modbus Client", nullptr));
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
