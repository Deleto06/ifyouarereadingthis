/****************************************************************************
** Meta object code from reading C++ file 'modbusrtuclient.h'
**
** Created by: The Qt Meta Object Compiler version 69 (Qt 6.11.1)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../../../comm/modbusrtuclient.h"
#include <QtCore/qmetatype.h>
#include <QtCore/QList>

#include <QtCore/qtmochelpers.h>

#include <memory>


#include <QtCore/qxptype_traits.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'modbusrtuclient.h' doesn't include <QObject>."
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
struct qt_meta_tag_ZN15ModbusRtuClientE_t {};
} // unnamed namespace

template <> constexpr inline auto ModbusRtuClient::qt_create_metaobjectdata<qt_meta_tag_ZN15ModbusRtuClientE_t>()
{
    namespace QMC = QtMocConstants;
    QtMocHelpers::StringRefStorage qt_stringData {
        "ModbusRtuClient",
        "opened",
        "",
        "closed",
        "errorOccurred",
        "error",
        "logMessage",
        "message",
        "rawDataSent",
        "data",
        "rawDataReceived",
        "holdingRegistersRead",
        "slaveId",
        "startAddress",
        "QList<quint16>",
        "values",
        "writeFinished",
        "functionCode",
        "count",
        "onReadyRead",
        "onFrameTimeout"
    };

    QtMocHelpers::UintData qt_methods {
        // Signal 'opened'
        QtMocHelpers::SignalData<void()>(1, 2, QMC::AccessPublic, QMetaType::Void),
        // Signal 'closed'
        QtMocHelpers::SignalData<void()>(3, 2, QMC::AccessPublic, QMetaType::Void),
        // Signal 'errorOccurred'
        QtMocHelpers::SignalData<void(const QString &)>(4, 2, QMC::AccessPublic, QMetaType::Void, {{
            { QMetaType::QString, 5 },
        }}),
        // Signal 'logMessage'
        QtMocHelpers::SignalData<void(const QString &)>(6, 2, QMC::AccessPublic, QMetaType::Void, {{
            { QMetaType::QString, 7 },
        }}),
        // Signal 'rawDataSent'
        QtMocHelpers::SignalData<void(const QByteArray &)>(8, 2, QMC::AccessPublic, QMetaType::Void, {{
            { QMetaType::QByteArray, 9 },
        }}),
        // Signal 'rawDataReceived'
        QtMocHelpers::SignalData<void(const QByteArray &)>(10, 2, QMC::AccessPublic, QMetaType::Void, {{
            { QMetaType::QByteArray, 9 },
        }}),
        // Signal 'holdingRegistersRead'
        QtMocHelpers::SignalData<void(quint8, quint16, QVector<quint16>)>(11, 2, QMC::AccessPublic, QMetaType::Void, {{
            { QMetaType::UChar, 12 }, { QMetaType::UShort, 13 }, { 0x80000000 | 14, 15 },
        }}),
        // Signal 'writeFinished'
        QtMocHelpers::SignalData<void(quint8, quint8, quint16, quint16)>(16, 2, QMC::AccessPublic, QMetaType::Void, {{
            { QMetaType::UChar, 12 }, { QMetaType::UChar, 17 }, { QMetaType::UShort, 13 }, { QMetaType::UShort, 18 },
        }}),
        // Slot 'onReadyRead'
        QtMocHelpers::SlotData<void()>(19, 2, QMC::AccessPrivate, QMetaType::Void),
        // Slot 'onFrameTimeout'
        QtMocHelpers::SlotData<void()>(20, 2, QMC::AccessPrivate, QMetaType::Void),
    };
    QtMocHelpers::UintData qt_properties {
    };
    QtMocHelpers::UintData qt_enums {
    };
    return QtMocHelpers::metaObjectData<ModbusRtuClient, qt_meta_tag_ZN15ModbusRtuClientE_t>(QMC::MetaObjectFlag{}, qt_stringData,
            qt_methods, qt_properties, qt_enums);
}
Q_CONSTINIT const QMetaObject ModbusRtuClient::staticMetaObject = { {
    QMetaObject::SuperData::link<QObject::staticMetaObject>(),
    qt_staticMetaObjectStaticContent<qt_meta_tag_ZN15ModbusRtuClientE_t>.stringdata,
    qt_staticMetaObjectStaticContent<qt_meta_tag_ZN15ModbusRtuClientE_t>.data,
    qt_static_metacall,
    nullptr,
    qt_staticMetaObjectRelocatingContent<qt_meta_tag_ZN15ModbusRtuClientE_t>.metaTypes,
    nullptr
} };

void ModbusRtuClient::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    auto *_t = static_cast<ModbusRtuClient *>(_o);
    if (_c == QMetaObject::InvokeMetaMethod) {
        switch (_id) {
        case 0: _t->opened(); break;
        case 1: _t->closed(); break;
        case 2: _t->errorOccurred((*reinterpret_cast<std::add_pointer_t<QString>>(_a[1]))); break;
        case 3: _t->logMessage((*reinterpret_cast<std::add_pointer_t<QString>>(_a[1]))); break;
        case 4: _t->rawDataSent((*reinterpret_cast<std::add_pointer_t<QByteArray>>(_a[1]))); break;
        case 5: _t->rawDataReceived((*reinterpret_cast<std::add_pointer_t<QByteArray>>(_a[1]))); break;
        case 6: _t->holdingRegistersRead((*reinterpret_cast<std::add_pointer_t<quint8>>(_a[1])),(*reinterpret_cast<std::add_pointer_t<quint16>>(_a[2])),(*reinterpret_cast<std::add_pointer_t<QList<quint16>>>(_a[3]))); break;
        case 7: _t->writeFinished((*reinterpret_cast<std::add_pointer_t<quint8>>(_a[1])),(*reinterpret_cast<std::add_pointer_t<quint8>>(_a[2])),(*reinterpret_cast<std::add_pointer_t<quint16>>(_a[3])),(*reinterpret_cast<std::add_pointer_t<quint16>>(_a[4]))); break;
        case 8: _t->onReadyRead(); break;
        case 9: _t->onFrameTimeout(); break;
        default: ;
        }
    }
    if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        switch (_id) {
        default: *reinterpret_cast<QMetaType *>(_a[0]) = QMetaType(); break;
        case 6:
            switch (*reinterpret_cast<int*>(_a[1])) {
            default: *reinterpret_cast<QMetaType *>(_a[0]) = QMetaType(); break;
            case 2:
                *reinterpret_cast<QMetaType *>(_a[0]) = QMetaType::fromType< QList<quint16> >(); break;
            }
            break;
        }
    }
    if (_c == QMetaObject::IndexOfMethod) {
        if (QtMocHelpers::indexOfMethod<void (ModbusRtuClient::*)()>(_a, &ModbusRtuClient::opened, 0))
            return;
        if (QtMocHelpers::indexOfMethod<void (ModbusRtuClient::*)()>(_a, &ModbusRtuClient::closed, 1))
            return;
        if (QtMocHelpers::indexOfMethod<void (ModbusRtuClient::*)(const QString & )>(_a, &ModbusRtuClient::errorOccurred, 2))
            return;
        if (QtMocHelpers::indexOfMethod<void (ModbusRtuClient::*)(const QString & )>(_a, &ModbusRtuClient::logMessage, 3))
            return;
        if (QtMocHelpers::indexOfMethod<void (ModbusRtuClient::*)(const QByteArray & )>(_a, &ModbusRtuClient::rawDataSent, 4))
            return;
        if (QtMocHelpers::indexOfMethod<void (ModbusRtuClient::*)(const QByteArray & )>(_a, &ModbusRtuClient::rawDataReceived, 5))
            return;
        if (QtMocHelpers::indexOfMethod<void (ModbusRtuClient::*)(quint8 , quint16 , QVector<quint16> )>(_a, &ModbusRtuClient::holdingRegistersRead, 6))
            return;
        if (QtMocHelpers::indexOfMethod<void (ModbusRtuClient::*)(quint8 , quint8 , quint16 , quint16 )>(_a, &ModbusRtuClient::writeFinished, 7))
            return;
    }
}

const QMetaObject *ModbusRtuClient::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *ModbusRtuClient::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_staticMetaObjectStaticContent<qt_meta_tag_ZN15ModbusRtuClientE_t>.strings))
        return static_cast<void*>(this);
    return QObject::qt_metacast(_clname);
}

int ModbusRtuClient::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QObject::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 10)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 10;
    }
    if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 10)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 10;
    }
    return _id;
}

// SIGNAL 0
void ModbusRtuClient::opened()
{
    QMetaObject::activate(this, &staticMetaObject, 0, nullptr);
}

// SIGNAL 1
void ModbusRtuClient::closed()
{
    QMetaObject::activate(this, &staticMetaObject, 1, nullptr);
}

// SIGNAL 2
void ModbusRtuClient::errorOccurred(const QString & _t1)
{
    QMetaObject::activate<void>(this, &staticMetaObject, 2, nullptr, _t1);
}

// SIGNAL 3
void ModbusRtuClient::logMessage(const QString & _t1)
{
    QMetaObject::activate<void>(this, &staticMetaObject, 3, nullptr, _t1);
}

// SIGNAL 4
void ModbusRtuClient::rawDataSent(const QByteArray & _t1)
{
    QMetaObject::activate<void>(this, &staticMetaObject, 4, nullptr, _t1);
}

// SIGNAL 5
void ModbusRtuClient::rawDataReceived(const QByteArray & _t1)
{
    QMetaObject::activate<void>(this, &staticMetaObject, 5, nullptr, _t1);
}

// SIGNAL 6
void ModbusRtuClient::holdingRegistersRead(quint8 _t1, quint16 _t2, QVector<quint16> _t3)
{
    QMetaObject::activate<void>(this, &staticMetaObject, 6, nullptr, _t1, _t2, _t3);
}

// SIGNAL 7
void ModbusRtuClient::writeFinished(quint8 _t1, quint8 _t2, quint16 _t3, quint16 _t4)
{
    QMetaObject::activate<void>(this, &staticMetaObject, 7, nullptr, _t1, _t2, _t3, _t4);
}
QT_WARNING_POP
