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
    QLabel *label_20;
    QLabel *label_21;
    QLabel *label_22;
    QPushButton *btnSerialRefresh_2;
    QPushButton *btnSerialRefresh_3;
    QSpinBox *spinBox;
    QLineEdit *lineEdit;
    QLineEdit *lineEdit_2;
    QSpinBox *spinBox_2;
    QLabel *label_23;
    QLabel *label_24;
    QSpinBox *spinBox_3;
    QLabel *label_32;
    QLabel *label_34;
    QPushButton *btnSerialRefresh_4;
    QPushButton *btnSerialRefresh_5;
    QPushButton *btnSerialRefresh_6;
    QSpinBox *spinBox_4;
    QLineEdit *lineEdit_3;
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
        label_20 = new QLabel(tab_2);
        label_20->setObjectName("label_20");
        label_20->setGeometry(QRect(30, 30, 53, 15));
        label_21 = new QLabel(tab_2);
        label_21->setObjectName("label_21");
        label_21->setGeometry(QRect(12, 50, 61, 20));
        label_22 = new QLabel(tab_2);
        label_22->setObjectName("label_22");
        label_22->setGeometry(QRect(30, 80, 53, 15));
        btnSerialRefresh_2 = new QPushButton(tab_2);
        btnSerialRefresh_2->setObjectName("btnSerialRefresh_2");
        btnSerialRefresh_2->setGeometry(QRect(10, 110, 227, 23));
        btnSerialRefresh_3 = new QPushButton(tab_2);
        btnSerialRefresh_3->setObjectName("btnSerialRefresh_3");
        btnSerialRefresh_3->setGeometry(QRect(10, 130, 227, 23));
        spinBox = new QSpinBox(tab_2);
        spinBox->setObjectName("spinBox");
        spinBox->setGeometry(QRect(80, 80, 42, 24));
        lineEdit = new QLineEdit(tab_2);
        lineEdit->setObjectName("lineEdit");
        lineEdit->setGeometry(QRect(80, 20, 113, 23));
        lineEdit_2 = new QLineEdit(tab_2);
        lineEdit_2->setObjectName("lineEdit_2");
        lineEdit_2->setGeometry(QRect(80, 50, 113, 23));
        spinBox_2 = new QSpinBox(tab_2);
        spinBox_2->setObjectName("spinBox_2");
        spinBox_2->setGeometry(QRect(100, 180, 42, 24));
        label_23 = new QLabel(tab_2);
        label_23->setObjectName("label_23");
        label_23->setGeometry(QRect(40, 180, 53, 15));
        label_24 = new QLabel(tab_2);
        label_24->setObjectName("label_24");
        label_24->setGeometry(QRect(60, 220, 53, 15));
        spinBox_3 = new QSpinBox(tab_2);
        spinBox_3->setObjectName("spinBox_3");
        spinBox_3->setGeometry(QRect(90, 220, 42, 24));
        label_32 = new QLabel(tab_2);
        label_32->setObjectName("label_32");
        label_32->setGeometry(QRect(40, 260, 53, 15));
        label_34 = new QLabel(tab_2);
        label_34->setObjectName("label_34");
        label_34->setGeometry(QRect(80, 340, 53, 15));
        btnSerialRefresh_4 = new QPushButton(tab_2);
        btnSerialRefresh_4->setObjectName("btnSerialRefresh_4");
        btnSerialRefresh_4->setGeometry(QRect(120, 430, 121, 23));
        btnSerialRefresh_5 = new QPushButton(tab_2);
        btnSerialRefresh_5->setObjectName("btnSerialRefresh_5");
        btnSerialRefresh_5->setGeometry(QRect(0, 430, 121, 23));
        btnSerialRefresh_6 = new QPushButton(tab_2);
        btnSerialRefresh_6->setObjectName("btnSerialRefresh_6");
        btnSerialRefresh_6->setGeometry(QRect(60, 380, 121, 23));
        spinBox_4 = new QSpinBox(tab_2);
        spinBox_4->setObjectName("spinBox_4");
        spinBox_4->setGeometry(QRect(100, 260, 42, 24));
        lineEdit_3 = new QLineEdit(tab_2);
        lineEdit_3->setObjectName("lineEdit_3");
        lineEdit_3->setGeometry(QRect(110, 340, 113, 23));
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

        tabWidgetComm->setCurrentIndex(4);


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
        label_21->setText(QCoreApplication::translate("MainWindow", "\347\233\256\346\240\207\347\253\257\345\217\243\357\274\232", nullptr));
        label_22->setText(QCoreApplication::translate("MainWindow", "Unit ID", nullptr));
        btnSerialRefresh_2->setText(QCoreApplication::translate("MainWindow", "\350\277\236\346\216\245", nullptr));
        btnSerialRefresh_3->setText(QCoreApplication::translate("MainWindow", "\346\226\255\345\274\200", nullptr));
        label_23->setText(QCoreApplication::translate("MainWindow", "\350\265\267\345\247\213\345\234\260\345\235\200", nullptr));
        label_24->setText(QCoreApplication::translate("MainWindow", "\346\225\260\351\207\217", nullptr));
        label_32->setText(QCoreApplication::translate("MainWindow", "\345\206\231\345\234\260\345\235\200", nullptr));
        label_34->setText(QCoreApplication::translate("MainWindow", "\345\206\231\345\200\274", nullptr));
        btnSerialRefresh_4->setText(QCoreApplication::translate("MainWindow", "\345\206\231\345\244\232\344\270\252\345\257\204\345\255\230\345\231\250", nullptr));
        btnSerialRefresh_5->setText(QCoreApplication::translate("MainWindow", "\345\206\231\345\215\225\344\270\252\345\257\204\345\255\230\345\231\250", nullptr));
        btnSerialRefresh_6->setText(QCoreApplication::translate("MainWindow", "\350\257\273\344\277\235\346\214\201\345\257\204\345\255\230\345\231\250", nullptr));
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
