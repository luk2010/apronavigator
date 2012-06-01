/****************************************************************************
** Meta object code from reading C++ file 'adressbar.h'
**
** Created: Mon 14. May 22:36:46 2012
**      by: The Qt Meta Object Compiler version 63 (Qt 4.8.1)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../adressbar.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'adressbar.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 63
#error "This file was generated using the moc from 4.8.1. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_AdressBar[] = {

 // content:
       6,       // revision
       0,       // classname
       0,    0, // classinfo
       2,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: signature, parameters, type, tag, flags
      11,   10,   10,   10, 0x0a,
      28,   24,   10,   10, 0x08,

       0        // eod
};

static const char qt_meta_stringdata_AdressBar[] = {
    "AdressBar\0\0changeIcon()\0url\0"
    "webViewUrlChanged(QUrl)\0"
};

void AdressBar::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        Q_ASSERT(staticMetaObject.cast(_o));
        AdressBar *_t = static_cast<AdressBar *>(_o);
        switch (_id) {
        case 0: _t->changeIcon(); break;
        case 1: _t->webViewUrlChanged((*reinterpret_cast< const QUrl(*)>(_a[1]))); break;
        default: ;
        }
    }
}

const QMetaObjectExtraData AdressBar::staticMetaObjectExtraData = {
    0,  qt_static_metacall 
};

const QMetaObject AdressBar::staticMetaObject = {
    { &QWidget::staticMetaObject, qt_meta_stringdata_AdressBar,
      qt_meta_data_AdressBar, &staticMetaObjectExtraData }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &AdressBar::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *AdressBar::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *AdressBar::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_AdressBar))
        return static_cast<void*>(const_cast< AdressBar*>(this));
    return QWidget::qt_metacast(_clname);
}

int AdressBar::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QWidget::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 2)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 2;
    }
    return _id;
}
QT_END_MOC_NAMESPACE
