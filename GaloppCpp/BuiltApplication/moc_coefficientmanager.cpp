/****************************************************************************
** Meta object code from reading C++ file 'coefficientmanager.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.4.0)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../GA_Galopp_kursa_darbs/coefficientmanager.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'coefficientmanager.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.4.0. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
struct qt_meta_stringdata_CoefficientManager_t {
    QByteArrayData data[5];
    char stringdata[119];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_CoefficientManager_t, stringdata) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_CoefficientManager_t qt_meta_stringdata_CoefficientManager = {
    {
QT_MOC_LITERAL(0, 0, 18), // "CoefficientManager"
QT_MOC_LITERAL(1, 19, 42), // "on_readCoeffiecientsFromFileB..."
QT_MOC_LITERAL(2, 62, 0), // ""
QT_MOC_LITERAL(3, 63, 33), // "on_saveCoefficientsButton_cli..."
QT_MOC_LITERAL(4, 97, 21) // "on_backButton_clicked"

    },
    "CoefficientManager\0"
    "on_readCoeffiecientsFromFileButton_clicked\0"
    "\0on_saveCoefficientsButton_clicked\0"
    "on_backButton_clicked"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_CoefficientManager[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
       3,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: name, argc, parameters, tag, flags
       1,    0,   29,    2, 0x08 /* Private */,
       3,    0,   30,    2, 0x08 /* Private */,
       4,    0,   31,    2, 0x08 /* Private */,

 // slots: parameters
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,

       0        // eod
};

void CoefficientManager::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        CoefficientManager *_t = static_cast<CoefficientManager *>(_o);
        switch (_id) {
        case 0: _t->on_readCoeffiecientsFromFileButton_clicked(); break;
        case 1: _t->on_saveCoefficientsButton_clicked(); break;
        case 2: _t->on_backButton_clicked(); break;
        default: ;
        }
    }
    Q_UNUSED(_a);
}

const QMetaObject CoefficientManager::staticMetaObject = {
    { &QDialog::staticMetaObject, qt_meta_stringdata_CoefficientManager.data,
      qt_meta_data_CoefficientManager,  qt_static_metacall, Q_NULLPTR, Q_NULLPTR}
};


const QMetaObject *CoefficientManager::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *CoefficientManager::qt_metacast(const char *_clname)
{
    if (!_clname) return Q_NULLPTR;
    if (!strcmp(_clname, qt_meta_stringdata_CoefficientManager.stringdata))
        return static_cast<void*>(const_cast< CoefficientManager*>(this));
    return QDialog::qt_metacast(_clname);
}

int CoefficientManager::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QDialog::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 3)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 3;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 3)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 3;
    }
    return _id;
}
QT_END_MOC_NAMESPACE
