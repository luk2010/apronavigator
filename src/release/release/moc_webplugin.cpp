/****************************************************************************
** Meta object code from reading C++ file 'webplugin.h'
**
** Created: Wed 16. May 15:59:35 2012
**      by: The Qt Meta Object Compiler version 63 (Qt 4.8.1)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../webplugin.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'webplugin.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 63
#error "This file was generated using the moc from 4.8.1. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_WebPlugin[] = {

 // content:
       6,       // revision
       0,       // classname
       0,    0, // classinfo
       7,   14, // methods
       3,   49, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: signature, parameters, type, tag, flags
      62,   20,   11,   10, 0x0a,
     115,   10,  107,   10, 0x0a,
     131,  125,   10,   10, 0x0a,
     148,   10,  107,   10, 0x0a,
     178,  165,   10,   10, 0x0a,
     216,   10,  202,   10, 0x0a,
     238,  229,   10,   10, 0x0a,

 // properties: name, type, flags
     264,  107, 0x0a095103,
     269,  107, 0x0a095103,
     281,  202, 0x0009510b,

       0        // eod
};

static const char qt_meta_stringdata_WebPlugin[] = {
    "WebPlugin\0\0QObject*\0"
    "mimeType,url,argumentNames,argumentValues\0"
    "create(QString,QUrl,QStringList,QStringList)\0"
    "QString\0getName()\0_name\0setName(QString)\0"
    "getDescription()\0_description\0"
    "setDescription(QString)\0QList<Plugin>\0"
    "getPlugins()\0_plugins\0setPlugins(QList<Plugin>)\0"
    "name\0description\0plugins\0"
};

void WebPlugin::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        Q_ASSERT(staticMetaObject.cast(_o));
        WebPlugin *_t = static_cast<WebPlugin *>(_o);
        switch (_id) {
        case 0: { QObject* _r = _t->create((*reinterpret_cast< const QString(*)>(_a[1])),(*reinterpret_cast< const QUrl(*)>(_a[2])),(*reinterpret_cast< const QStringList(*)>(_a[3])),(*reinterpret_cast< const QStringList(*)>(_a[4])));
            if (_a[0]) *reinterpret_cast< QObject**>(_a[0]) = _r; }  break;
        case 1: { QString _r = _t->getName();
            if (_a[0]) *reinterpret_cast< QString*>(_a[0]) = _r; }  break;
        case 2: _t->setName((*reinterpret_cast< const QString(*)>(_a[1]))); break;
        case 3: { QString _r = _t->getDescription();
            if (_a[0]) *reinterpret_cast< QString*>(_a[0]) = _r; }  break;
        case 4: _t->setDescription((*reinterpret_cast< const QString(*)>(_a[1]))); break;
        case 5: { QList<Plugin> _r = _t->getPlugins();
            if (_a[0]) *reinterpret_cast< QList<Plugin>*>(_a[0]) = _r; }  break;
        case 6: _t->setPlugins((*reinterpret_cast< const QList<Plugin>(*)>(_a[1]))); break;
        default: ;
        }
    }
}

const QMetaObjectExtraData WebPlugin::staticMetaObjectExtraData = {
    0,  qt_static_metacall 
};

const QMetaObject WebPlugin::staticMetaObject = {
    { &QObject::staticMetaObject, qt_meta_stringdata_WebPlugin,
      qt_meta_data_WebPlugin, &staticMetaObjectExtraData }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &WebPlugin::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *WebPlugin::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *WebPlugin::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_WebPlugin))
        return static_cast<void*>(const_cast< WebPlugin*>(this));
    return QObject::qt_metacast(_clname);
}

int WebPlugin::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QObject::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 7)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 7;
    }
#ifndef QT_NO_PROPERTIES
      else if (_c == QMetaObject::ReadProperty) {
        void *_v = _a[0];
        switch (_id) {
        case 0: *reinterpret_cast< QString*>(_v) = getName(); break;
        case 1: *reinterpret_cast< QString*>(_v) = getDescription(); break;
        case 2: *reinterpret_cast< QList<Plugin>*>(_v) = getPlugins(); break;
        }
        _id -= 3;
    } else if (_c == QMetaObject::WriteProperty) {
        void *_v = _a[0];
        switch (_id) {
        case 0: setName(*reinterpret_cast< QString*>(_v)); break;
        case 1: setDescription(*reinterpret_cast< QString*>(_v)); break;
        case 2: setPlugins(*reinterpret_cast< QList<Plugin>*>(_v)); break;
        }
        _id -= 3;
    } else if (_c == QMetaObject::ResetProperty) {
        _id -= 3;
    } else if (_c == QMetaObject::QueryPropertyDesignable) {
        _id -= 3;
    } else if (_c == QMetaObject::QueryPropertyScriptable) {
        _id -= 3;
    } else if (_c == QMetaObject::QueryPropertyStored) {
        _id -= 3;
    } else if (_c == QMetaObject::QueryPropertyEditable) {
        _id -= 3;
    } else if (_c == QMetaObject::QueryPropertyUser) {
        _id -= 3;
    }
#endif // QT_NO_PROPERTIES
    return _id;
}
QT_END_MOC_NAMESPACE
