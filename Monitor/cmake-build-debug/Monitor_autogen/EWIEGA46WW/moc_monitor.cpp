/****************************************************************************
** Meta object code from reading C++ file 'monitor.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.15.2)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include <memory>
#include "../../../monitor.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'monitor.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.15.2. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_Monitor_t {
    QByteArrayData data[18];
    char stringdata0[232];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_Monitor_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_Monitor_t qt_meta_stringdata_Monitor = {
    {
QT_MOC_LITERAL(0, 0, 7), // "Monitor"
QT_MOC_LITERAL(1, 8, 11), // "btn_connect"
QT_MOC_LITERAL(2, 20, 0), // ""
QT_MOC_LITERAL(3, 21, 12), // "DataReceived"
QT_MOC_LITERAL(4, 34, 10), // "COMChanged"
QT_MOC_LITERAL(5, 45, 13), // "SourceChanged"
QT_MOC_LITERAL(6, 59, 8), // "SetChart"
QT_MOC_LITERAL(7, 68, 11), // "AddObserver"
QT_MOC_LITERAL(8, 80, 13), // "DeleteObserve"
QT_MOC_LITERAL(9, 94, 15), // "CheckBoxChanged"
QT_MOC_LITERAL(10, 110, 5), // "About"
QT_MOC_LITERAL(11, 116, 12), // "SaveSettings"
QT_MOC_LITERAL(12, 129, 12), // "LoadSettings"
QT_MOC_LITERAL(13, 142, 12), // "GenerateShot"
QT_MOC_LITERAL(14, 155, 14), // "RuleCheck_Name"
QT_MOC_LITERAL(15, 170, 14), // "deleteSeedSlot"
QT_MOC_LITERAL(16, 185, 42), // "on_ObservedList_customContext..."
QT_MOC_LITERAL(17, 228, 3) // "pos"

    },
    "Monitor\0btn_connect\0\0DataReceived\0"
    "COMChanged\0SourceChanged\0SetChart\0"
    "AddObserver\0DeleteObserve\0CheckBoxChanged\0"
    "About\0SaveSettings\0LoadSettings\0"
    "GenerateShot\0RuleCheck_Name\0deleteSeedSlot\0"
    "on_ObservedList_customContextMenuRequested\0"
    "pos"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_Monitor[] = {

 // content:
       8,       // revision
       0,       // classname
       0,    0, // classinfo
      15,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: name, argc, parameters, tag, flags
       1,    0,   89,    2, 0x0a /* Public */,
       3,    0,   90,    2, 0x0a /* Public */,
       4,    1,   91,    2, 0x0a /* Public */,
       5,    1,   94,    2, 0x0a /* Public */,
       6,    0,   97,    2, 0x0a /* Public */,
       7,    0,   98,    2, 0x0a /* Public */,
       8,    0,   99,    2, 0x0a /* Public */,
       9,    1,  100,    2, 0x0a /* Public */,
      10,    0,  103,    2, 0x0a /* Public */,
      11,    0,  104,    2, 0x0a /* Public */,
      12,    0,  105,    2, 0x0a /* Public */,
      13,    0,  106,    2, 0x0a /* Public */,
      14,    1,  107,    2, 0x0a /* Public */,
      15,    0,  110,    2, 0x0a /* Public */,
      16,    1,  111,    2, 0x08 /* Private */,

 // slots: parameters
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, QMetaType::Int,    2,
    QMetaType::Void, QMetaType::Int,    2,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, QMetaType::Int,    2,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Bool, QMetaType::QString,    2,
    QMetaType::Void,
    QMetaType::Void, QMetaType::QPoint,   17,

       0        // eod
};

void Monitor::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<Monitor *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->btn_connect(); break;
        case 1: _t->DataReceived(); break;
        case 2: _t->COMChanged((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 3: _t->SourceChanged((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 4: _t->SetChart(); break;
        case 5: _t->AddObserver(); break;
        case 6: _t->DeleteObserve(); break;
        case 7: _t->CheckBoxChanged((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 8: _t->About(); break;
        case 9: _t->SaveSettings(); break;
        case 10: _t->LoadSettings(); break;
        case 11: _t->GenerateShot(); break;
        case 12: { bool _r = _t->RuleCheck_Name((*reinterpret_cast< const QString(*)>(_a[1])));
            if (_a[0]) *reinterpret_cast< bool*>(_a[0]) = std::move(_r); }  break;
        case 13: _t->deleteSeedSlot(); break;
        case 14: _t->on_ObservedList_customContextMenuRequested((*reinterpret_cast< const QPoint(*)>(_a[1]))); break;
        default: ;
        }
    }
}

QT_INIT_METAOBJECT const QMetaObject Monitor::staticMetaObject = { {
    QMetaObject::SuperData::link<QMainWindow::staticMetaObject>(),
    qt_meta_stringdata_Monitor.data,
    qt_meta_data_Monitor,
    qt_static_metacall,
    nullptr,
    nullptr
} };


const QMetaObject *Monitor::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *Monitor::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_Monitor.stringdata0))
        return static_cast<void*>(this);
    return QMainWindow::qt_metacast(_clname);
}

int Monitor::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QMainWindow::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 15)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 15;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 15)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 15;
    }
    return _id;
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
