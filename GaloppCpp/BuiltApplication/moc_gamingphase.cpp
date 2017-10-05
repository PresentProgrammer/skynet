/****************************************************************************
** Meta object code from reading C++ file 'gamingphase.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.4.0)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../GA_Galopp_kursa_darbs/gamingphase.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'gamingphase.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.4.0. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
struct qt_meta_stringdata_GamingPhase_t {
    QByteArrayData data[12];
    char stringdata[315];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_GamingPhase_t, stringdata) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_GamingPhase_t qt_meta_stringdata_GamingPhase = {
    {
QT_MOC_LITERAL(0, 0, 11), // "GamingPhase"
QT_MOC_LITERAL(1, 12, 40), // "on_player_1_ComboBox_currentI..."
QT_MOC_LITERAL(2, 53, 0), // ""
QT_MOC_LITERAL(3, 54, 5), // "index"
QT_MOC_LITERAL(4, 60, 40), // "on_player_2_ComboBox_currentI..."
QT_MOC_LITERAL(5, 101, 40), // "on_player_3_ComboBox_currentI..."
QT_MOC_LITERAL(6, 142, 30), // "on_player_1_PushButton_clicked"
QT_MOC_LITERAL(7, 173, 30), // "on_player_2_PushButton_clicked"
QT_MOC_LITERAL(8, 204, 30), // "on_player_3_PushButton_clicked"
QT_MOC_LITERAL(9, 235, 21), // "on_backButton_clicked"
QT_MOC_LITERAL(10, 257, 28), // "on_executeGameButton_clicked"
QT_MOC_LITERAL(11, 286, 28) // "on_clearPointsButton_clicked"

    },
    "GamingPhase\0on_player_1_ComboBox_currentIndexChanged\0"
    "\0index\0on_player_2_ComboBox_currentIndexChanged\0"
    "on_player_3_ComboBox_currentIndexChanged\0"
    "on_player_1_PushButton_clicked\0"
    "on_player_2_PushButton_clicked\0"
    "on_player_3_PushButton_clicked\0"
    "on_backButton_clicked\0"
    "on_executeGameButton_clicked\0"
    "on_clearPointsButton_clicked"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_GamingPhase[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
       9,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: name, argc, parameters, tag, flags
       1,    1,   59,    2, 0x08 /* Private */,
       4,    1,   62,    2, 0x08 /* Private */,
       5,    1,   65,    2, 0x08 /* Private */,
       6,    0,   68,    2, 0x08 /* Private */,
       7,    0,   69,    2, 0x08 /* Private */,
       8,    0,   70,    2, 0x08 /* Private */,
       9,    0,   71,    2, 0x08 /* Private */,
      10,    0,   72,    2, 0x08 /* Private */,
      11,    0,   73,    2, 0x08 /* Private */,

 // slots: parameters
    QMetaType::Void, QMetaType::Int,    3,
    QMetaType::Void, QMetaType::Int,    3,
    QMetaType::Void, QMetaType::Int,    3,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,

       0        // eod
};

void GamingPhase::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        GamingPhase *_t = static_cast<GamingPhase *>(_o);
        switch (_id) {
        case 0: _t->on_player_1_ComboBox_currentIndexChanged((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 1: _t->on_player_2_ComboBox_currentIndexChanged((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 2: _t->on_player_3_ComboBox_currentIndexChanged((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 3: _t->on_player_1_PushButton_clicked(); break;
        case 4: _t->on_player_2_PushButton_clicked(); break;
        case 5: _t->on_player_3_PushButton_clicked(); break;
        case 6: _t->on_backButton_clicked(); break;
        case 7: _t->on_executeGameButton_clicked(); break;
        case 8: _t->on_clearPointsButton_clicked(); break;
        default: ;
        }
    }
}

const QMetaObject GamingPhase::staticMetaObject = {
    { &QDialog::staticMetaObject, qt_meta_stringdata_GamingPhase.data,
      qt_meta_data_GamingPhase,  qt_static_metacall, Q_NULLPTR, Q_NULLPTR}
};


const QMetaObject *GamingPhase::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *GamingPhase::qt_metacast(const char *_clname)
{
    if (!_clname) return Q_NULLPTR;
    if (!strcmp(_clname, qt_meta_stringdata_GamingPhase.stringdata))
        return static_cast<void*>(const_cast< GamingPhase*>(this));
    return QDialog::qt_metacast(_clname);
}

int GamingPhase::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QDialog::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 9)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 9;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 9)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 9;
    }
    return _id;
}
QT_END_MOC_NAMESPACE
