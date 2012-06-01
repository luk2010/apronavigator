/****************************************************************************
** Meta object code from reading C++ file 'awebpluginfactory.h'
**
** Created: Wed 16. May 16:42:56 2012
**      by: The Qt Meta Object Compiler version 63 (Qt 4.8.1)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../awebpluginfactory.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'awebpluginfactory.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 63
#error "This file was generated using the moc from 4.8.1. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_AWebPluginFactory[] = {

 // content:
       6,       // revision
       0,       // classname
       0,    0, // classinfo
       5,   14, // methods
       1,   39, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: signature, parameters, type, tag, flags
      27,   19,   18,   18, 0x0a,
      56,   19,   18,   18, 0x0a,
     106,   18,   88,   18, 0x0a,
     127,  121,   18,   18, 0x0a,
     192,   18,  159,   18, 0x0a,

 // properties: name, type, flags
     202,   88, 0x0009510b,

       0        // eod
};

static const char qt_meta_stringdata_AWebPluginFactory[] = {
    "AWebPluginFactory\0\0factory\0"
    "addPluginFactory(WebPlugin*)\0"
    "removePluginFactory(WebPlugin*)\0"
    "QList<WebPlugin*>\0getFactories()\0facts\0"
    "setFactories(QList<WebPlugin*>)\0"
    "QList<QWebPluginFactory::Plugin>\0"
    "plugins()\0factories\0"
};

void AWebPluginFactory::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        Q_ASSERT(staticMetaObject.cast(_o));
        AWebPluginFactory *_t = static_cast<AWebPluginFactory *>(_o);
        switch (_id) {
        case 0: _t->addPluginFactory((*reinterpret_cast< WebPlugin*(*)>(_a[1]))); break;
        case 1: _t->removePluginFactory((*reinterpret_cast< WebPlugin*(*)>(_a[1]))); break;
        case 2: { QList<WebPlugin*> _r = _t->getFactories();
            if (_a[0]) *reinterpret_cast< QList<WebPlugin*>*>(_a[0]) = _r; }  break;
        case 3: _t->setFactories((*reinterpret_cast< QList<WebPlugin*>(*)>(_a[1]))); break;
        case 4: { QList<QWebPluginFactory::Plugin> _r = _t->plugins();
            if (_a[0]) *reinterpret_cast< QList<QWebPluginFactory::Plugin>*>(_a[0]) = _r; }  break;
        default: ;
        }
    }
}

const QMetaObjectExtraData AWebPluginFactory::staticMetaObjectExtraData = {
    0,  qt_static_metacall 
};

const QMetaObject AWebPluginFactory::staticMetaObject = {
    { &QWebPluginFactory::staticMetaObject, qt_meta_stringdata_AWebPluginFactory,
      qt_meta_data_AWebPluginFactory, &staticMetaObjectExtraData }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &AWebPluginFactory::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *AWebPluginFactory::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *AWebPluginFactory::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_AWebPluginFactory))
        return static_cast<void*>(const_cast< AWebPluginFactory*>(this));
    return QWebPluginFactory::qt_metacast(_clname);
}

int AWebPluginFactory::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QWebPluginFactory::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 5)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 5;
    }
#ifndef QT_NO_PROPERTIES
      else if (_c == QMetaObject::ReadProperty) {
        void *_v = _a[0];
        switch (_id) {
        case 0: *reinterpret_cast< QList<WebPlugin*>*>(_v) = getFactories(); break;
        }
        _id -= 1;
    } else if (_c == QMetaObject::WriteProperty) {
        void *_v = _a[0];
        switch (_id) {
        case 0: setFactories(*reinterpret_cast< QList<WebPlugin*>*>(_v)); break;
        }
        _id -= 1;
    } else if (_c == QMetaObject::ResetProperty) {
        _id -= 1;
    } else if (_c == QMetaObject::QueryPropertyDesignable) {
        _id -= 1;
    } else if (_c == QMetaObject::QueryPropertyScriptable) {
        _id -= 1;
    } else if (_c == QMetaObject::QueryPropertyStored) {
        _id -= 1;
    } else if (_c == QMetaObject::QueryPropertyEditable) {
        _id -= 1;
    } else if (_c == QMetaObject::QueryPropertyUser) {
        _id -= 1;
    }
#endif // QT_NO_PROPERTIES
    return _id;
}
QT_END_MOC_NAMESPACE
