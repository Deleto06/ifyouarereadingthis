/****************************************************************************
** Meta object code from reading C++ file 'mainwindow.h'
**
** Created by: The Qt Meta Object Compiler version 69 (Qt 6.11.1)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../../../mainwindow.h"
#include <QtCore/qmetatype.h>

#include <QtCore/qtmochelpers.h>

#include <memory>


#include <QtCore/qxptype_traits.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'mainwindow.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 69
#error "This file was generated using the moc from 6.11.1. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

#ifndef Q_CONSTINIT
#define Q_CONSTINIT
#endif

QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
QT_WARNING_DISABLE_GCC("-Wuseless-cast")
namespace {
struct qt_meta_tag_ZN10MainWindowE_t {};
} // unnamed namespace

template <> constexpr inline auto MainWindow::qt_create_metaobjectdata<qt_meta_tag_ZN10MainWindowE_t>()
{
    namespace QMC = QtMocConstants;
    QtMocHelpers::StringRefStorage qt_stringData {
        "MainWindow",
        "onListWidgetCurrentItemChanged",
        "",
        "QListWidgetItem*",
        "current",
        "previous",
        "onListWidgetCustomContextMenuRequested",
        "QPoint",
        "pos",
        "onBtnAddDirClicked",
        "onSaveCurrentImageToDir",
        "onAddImageFiles",
        "on_btnTcpServerStart_clicked",
        "on_btnTcpServerStop_clicked",
        "on_btnTcpServerSend_clicked",
        "on_btnTcpClientConnect_clicked",
        "on_btnTcpClientDisconnect_clicked",
        "on_btnTcpClientSend_clicked",
        "on_btnUdpBind_clicked",
        "on_btnUdpClose_clicked",
        "on_btnUdpSend_clicked",
        "on_btnModbusServerStart_clicked",
        "on_btnModbusServerStop_clicked",
        "on_btnModbusSetReg_clicked",
        "on_btnModbusClientConnect_clicked",
        "on_btnModbusClientDisconnect_clicked",
        "on_btnModbusClientReadHolding_clicked",
        "on_btnModbusClientWriteSingle_clicked",
        "on_btnModbusClientWriteMultiple_clicked",
        "on_btnSerialRefresh_clicked",
        "on_btnSerialOpen_clicked",
        "on_btnSerialClose_clicked",
        "on_btnSerialSend_clicked",
        "on_btnClearLog_clicked",
        "on_btnSaveLog_clicked",
        "on_btnModbusRtuOpen_clicked",
        "on_btnModbusRtuClose_clicked",
        "on_btnModbusRtuReadHolding_clicked",
        "on_btnModbusRtuWriteSingle_clicked",
        "on_btnModbusRtuWriteMultiple_clicked",
        "on_btnModbusRtuRefresh_clicked"
    };

    QtMocHelpers::UintData qt_methods {
        // Slot 'onListWidgetCurrentItemChanged'
        QtMocHelpers::SlotData<void(QListWidgetItem *, QListWidgetItem *)>(1, 2, QMC::AccessPrivate, QMetaType::Void, {{
            { 0x80000000 | 3, 4 }, { 0x80000000 | 3, 5 },
        }}),
        // Slot 'onListWidgetCustomContextMenuRequested'
        QtMocHelpers::SlotData<void(const QPoint &)>(6, 2, QMC::AccessPrivate, QMetaType::Void, {{
            { 0x80000000 | 7, 8 },
        }}),
        // Slot 'onBtnAddDirClicked'
        QtMocHelpers::SlotData<void()>(9, 2, QMC::AccessPrivate, QMetaType::Void),
        // Slot 'onSaveCurrentImageToDir'
        QtMocHelpers::SlotData<void()>(10, 2, QMC::AccessPrivate, QMetaType::Void),
        // Slot 'onAddImageFiles'
        QtMocHelpers::SlotData<void()>(11, 2, QMC::AccessPrivate, QMetaType::Void),
        // Slot 'on_btnTcpServerStart_clicked'
        QtMocHelpers::SlotData<void()>(12, 2, QMC::AccessPrivate, QMetaType::Void),
        // Slot 'on_btnTcpServerStop_clicked'
        QtMocHelpers::SlotData<void()>(13, 2, QMC::AccessPrivate, QMetaType::Void),
        // Slot 'on_btnTcpServerSend_clicked'
        QtMocHelpers::SlotData<void()>(14, 2, QMC::AccessPrivate, QMetaType::Void),
        // Slot 'on_btnTcpClientConnect_clicked'
        QtMocHelpers::SlotData<void()>(15, 2, QMC::AccessPrivate, QMetaType::Void),
        // Slot 'on_btnTcpClientDisconnect_clicked'
        QtMocHelpers::SlotData<void()>(16, 2, QMC::AccessPrivate, QMetaType::Void),
        // Slot 'on_btnTcpClientSend_clicked'
        QtMocHelpers::SlotData<void()>(17, 2, QMC::AccessPrivate, QMetaType::Void),
        // Slot 'on_btnUdpBind_clicked'
        QtMocHelpers::SlotData<void()>(18, 2, QMC::AccessPrivate, QMetaType::Void),
        // Slot 'on_btnUdpClose_clicked'
        QtMocHelpers::SlotData<void()>(19, 2, QMC::AccessPrivate, QMetaType::Void),
        // Slot 'on_btnUdpSend_clicked'
        QtMocHelpers::SlotData<void()>(20, 2, QMC::AccessPrivate, QMetaType::Void),
        // Slot 'on_btnModbusServerStart_clicked'
        QtMocHelpers::SlotData<void()>(21, 2, QMC::AccessPrivate, QMetaType::Void),
        // Slot 'on_btnModbusServerStop_clicked'
        QtMocHelpers::SlotData<void()>(22, 2, QMC::AccessPrivate, QMetaType::Void),
        // Slot 'on_btnModbusSetReg_clicked'
        QtMocHelpers::SlotData<void()>(23, 2, QMC::AccessPrivate, QMetaType::Void),
        // Slot 'on_btnModbusClientConnect_clicked'
        QtMocHelpers::SlotData<void()>(24, 2, QMC::AccessPrivate, QMetaType::Void),
        // Slot 'on_btnModbusClientDisconnect_clicked'
        QtMocHelpers::SlotData<void()>(25, 2, QMC::AccessPrivate, QMetaType::Void),
        // Slot 'on_btnModbusClientReadHolding_clicked'
        QtMocHelpers::SlotData<void()>(26, 2, QMC::AccessPrivate, QMetaType::Void),
        // Slot 'on_btnModbusClientWriteSingle_clicked'
        QtMocHelpers::SlotData<void()>(27, 2, QMC::AccessPrivate, QMetaType::Void),
        // Slot 'on_btnModbusClientWriteMultiple_clicked'
        QtMocHelpers::SlotData<void()>(28, 2, QMC::AccessPrivate, QMetaType::Void),
        // Slot 'on_btnSerialRefresh_clicked'
        QtMocHelpers::SlotData<void()>(29, 2, QMC::AccessPrivate, QMetaType::Void),
        // Slot 'on_btnSerialOpen_clicked'
        QtMocHelpers::SlotData<void()>(30, 2, QMC::AccessPrivate, QMetaType::Void),
        // Slot 'on_btnSerialClose_clicked'
        QtMocHelpers::SlotData<void()>(31, 2, QMC::AccessPrivate, QMetaType::Void),
        // Slot 'on_btnSerialSend_clicked'
        QtMocHelpers::SlotData<void()>(32, 2, QMC::AccessPrivate, QMetaType::Void),
        // Slot 'on_btnClearLog_clicked'
        QtMocHelpers::SlotData<void()>(33, 2, QMC::AccessPrivate, QMetaType::Void),
        // Slot 'on_btnSaveLog_clicked'
        QtMocHelpers::SlotData<void()>(34, 2, QMC::AccessPrivate, QMetaType::Void),
        // Slot 'on_btnModbusRtuOpen_clicked'
        QtMocHelpers::SlotData<void()>(35, 2, QMC::AccessPrivate, QMetaType::Void),
        // Slot 'on_btnModbusRtuClose_clicked'
        QtMocHelpers::SlotData<void()>(36, 2, QMC::AccessPrivate, QMetaType::Void),
        // Slot 'on_btnModbusRtuReadHolding_clicked'
        QtMocHelpers::SlotData<void()>(37, 2, QMC::AccessPrivate, QMetaType::Void),
        // Slot 'on_btnModbusRtuWriteSingle_clicked'
        QtMocHelpers::SlotData<void()>(38, 2, QMC::AccessPrivate, QMetaType::Void),
        // Slot 'on_btnModbusRtuWriteMultiple_clicked'
        QtMocHelpers::SlotData<void()>(39, 2, QMC::AccessPrivate, QMetaType::Void),
        // Slot 'on_btnModbusRtuRefresh_clicked'
        QtMocHelpers::SlotData<void()>(40, 2, QMC::AccessPrivate, QMetaType::Void),
    };
    QtMocHelpers::UintData qt_properties {
    };
    QtMocHelpers::UintData qt_enums {
    };
    return QtMocHelpers::metaObjectData<MainWindow, qt_meta_tag_ZN10MainWindowE_t>(QMC::MetaObjectFlag{}, qt_stringData,
            qt_methods, qt_properties, qt_enums);
}
Q_CONSTINIT const QMetaObject MainWindow::staticMetaObject = { {
    QMetaObject::SuperData::link<QMainWindow::staticMetaObject>(),
    qt_staticMetaObjectStaticContent<qt_meta_tag_ZN10MainWindowE_t>.stringdata,
    qt_staticMetaObjectStaticContent<qt_meta_tag_ZN10MainWindowE_t>.data,
    qt_static_metacall,
    nullptr,
    qt_staticMetaObjectRelocatingContent<qt_meta_tag_ZN10MainWindowE_t>.metaTypes,
    nullptr
} };

void MainWindow::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    auto *_t = static_cast<MainWindow *>(_o);
    if (_c == QMetaObject::InvokeMetaMethod) {
        switch (_id) {
        case 0: _t->onListWidgetCurrentItemChanged((*reinterpret_cast<std::add_pointer_t<QListWidgetItem*>>(_a[1])),(*reinterpret_cast<std::add_pointer_t<QListWidgetItem*>>(_a[2]))); break;
        case 1: _t->onListWidgetCustomContextMenuRequested((*reinterpret_cast<std::add_pointer_t<QPoint>>(_a[1]))); break;
        case 2: _t->onBtnAddDirClicked(); break;
        case 3: _t->onSaveCurrentImageToDir(); break;
        case 4: _t->onAddImageFiles(); break;
        case 5: _t->on_btnTcpServerStart_clicked(); break;
        case 6: _t->on_btnTcpServerStop_clicked(); break;
        case 7: _t->on_btnTcpServerSend_clicked(); break;
        case 8: _t->on_btnTcpClientConnect_clicked(); break;
        case 9: _t->on_btnTcpClientDisconnect_clicked(); break;
        case 10: _t->on_btnTcpClientSend_clicked(); break;
        case 11: _t->on_btnUdpBind_clicked(); break;
        case 12: _t->on_btnUdpClose_clicked(); break;
        case 13: _t->on_btnUdpSend_clicked(); break;
        case 14: _t->on_btnModbusServerStart_clicked(); break;
        case 15: _t->on_btnModbusServerStop_clicked(); break;
        case 16: _t->on_btnModbusSetReg_clicked(); break;
        case 17: _t->on_btnModbusClientConnect_clicked(); break;
        case 18: _t->on_btnModbusClientDisconnect_clicked(); break;
        case 19: _t->on_btnModbusClientReadHolding_clicked(); break;
        case 20: _t->on_btnModbusClientWriteSingle_clicked(); break;
        case 21: _t->on_btnModbusClientWriteMultiple_clicked(); break;
        case 22: _t->on_btnSerialRefresh_clicked(); break;
        case 23: _t->on_btnSerialOpen_clicked(); break;
        case 24: _t->on_btnSerialClose_clicked(); break;
        case 25: _t->on_btnSerialSend_clicked(); break;
        case 26: _t->on_btnClearLog_clicked(); break;
        case 27: _t->on_btnSaveLog_clicked(); break;
        case 28: _t->on_btnModbusRtuOpen_clicked(); break;
        case 29: _t->on_btnModbusRtuClose_clicked(); break;
        case 30: _t->on_btnModbusRtuReadHolding_clicked(); break;
        case 31: _t->on_btnModbusRtuWriteSingle_clicked(); break;
        case 32: _t->on_btnModbusRtuWriteMultiple_clicked(); break;
        case 33: _t->on_btnModbusRtuRefresh_clicked(); break;
        default: ;
        }
    }
}

const QMetaObject *MainWindow::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *MainWindow::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_staticMetaObjectStaticContent<qt_meta_tag_ZN10MainWindowE_t>.strings))
        return static_cast<void*>(this);
    return QMainWindow::qt_metacast(_clname);
}

int MainWindow::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QMainWindow::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 34)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 34;
    }
    if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 34)
            *reinterpret_cast<QMetaType *>(_a[0]) = QMetaType();
        _id -= 34;
    }
    return _id;
}
QT_WARNING_POP
