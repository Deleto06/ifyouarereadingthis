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
#include <QtWidgets/QGraphicsView>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QListWidget>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPushButton>
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
    QWidget *tab_6;
    QTextEdit *textEditLog;
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
        listWidget = new QListWidget(centralwidget);
        listWidget->setObjectName("listWidget");
        listWidget->setMinimumSize(QSize(350, 350));

        horizontalLayout->addWidget(listWidget);

        btnAddDir = new QPushButton(centralwidget);
        btnAddDir->setObjectName("btnAddDir");

        horizontalLayout->addWidget(btnAddDir);

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
        tab_6 = new QWidget();
        tab_6->setObjectName("tab_6");
        tabWidgetComm->addTab(tab_6, QString());

        horizontalLayout->addWidget(tabWidgetComm);

        textEditLog = new QTextEdit(centralwidget);
        textEditLog->setObjectName("textEditLog");
        textEditLog->setReadOnly(true);

        horizontalLayout->addWidget(textEditLog);

        MainWindow->setCentralWidget(centralwidget);
        menubar = new QMenuBar(MainWindow);
        menubar->setObjectName("menubar");
        menubar->setGeometry(QRect(0, 0, 1011, 20));
        MainWindow->setMenuBar(menubar);
        statusbar = new QStatusBar(MainWindow);
        statusbar->setObjectName("statusbar");
        MainWindow->setStatusBar(statusbar);

        retranslateUi(MainWindow);

        tabWidgetComm->setCurrentIndex(1);


        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QCoreApplication::translate("MainWindow", "MainWindow", nullptr));
        btnAddDir->setText(QCoreApplication::translate("MainWindow", "\351\200\211\346\213\251\346\226\207\344\273\266\345\244\271", nullptr));
        label->setText(QCoreApplication::translate("MainWindow", "\347\253\257\345\217\243\357\274\232", nullptr));
        lineEditTcpServerPort->setText(QCoreApplication::translate("MainWindow", "6000", nullptr));
        btnTcpServerStart->setText(QCoreApplication::translate("MainWindow", "\345\220\257\345\212\250", nullptr));
        btnTcpServerStop->setText(QCoreApplication::translate("MainWindow", "\345\201\234\346\255\242", nullptr));
        label_2->setText(QCoreApplication::translate("MainWindow", "\345\217\221\351\200\201\345\206\205\345\256\271\357\274\232", nullptr));
        checkBoxTcpServerSendHex->setText(QCoreApplication::translate("MainWindow", "HEX\345\217\221\351\200\201", nullptr));
        btnTcpServerSend->setText(QCoreApplication::translate("MainWindow", "\345\217\221\351\200\201\347\273\231\345\205\250\351\203\250\345\256\242\346\210\267\347\253\257", nullptr));
        tabWidgetComm->setTabText(tabWidgetComm->indexOf(tab_3), QCoreApplication::translate("MainWindow", "TCP Server", nullptr));
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
        tabWidgetComm->setTabText(tabWidgetComm->indexOf(tab_6), QCoreApplication::translate("MainWindow", "Serial", nullptr));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
