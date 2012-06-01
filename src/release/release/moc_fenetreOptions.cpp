/****************************************************************************
** Meta object code from reading C++ file 'fenetreOptions.h'
**
** Created: Fri 1. Jun 18:52:55 2012
**      by: The Qt Meta Object Compiler version 63 (Qt 4.8.1)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../fenetreOptions.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'fenetreOptions.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 63
#error "This file was generated using the moc from 4.8.1. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_fenetreOptions[] = {

 // content:
       6,       // revision
       0,       // classname
       0,    0, // classinfo
      13,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       5,       // signalCount

 // signals: signature, parameters, type, tag, flags
      16,   15,   15,   15, 0x05,
      26,   15,   15,   15, 0x05,
      42,   15,   15,   15, 0x05,
      62,   15,   15,   15, 0x05,
      89,   15,   15,   15, 0x05,

 // slots: signature, parameters, type, tag, flags
     119,   15,   15,   15, 0x0a,
     140,   15,   15,   15, 0x0a,
     160,   15,   15,   15, 0x0a,
     182,   15,   15,   15, 0x0a,
     209,   15,   15,   15, 0x0a,
     235,   15,   15,   15, 0x0a,
     263,   15,   15,   15, 0x0a,
     286,   15,   15,   15, 0x0a,

       0        // eod
};

static const char qt_meta_stringdata_fenetreOptions[] = {
    "fenetreOptions\0\0closing()\0reloadToolBar()\0"
    "changeHome(QString)\0seeProgressStatusBar(bool)\0"
    "changeTaskBarVisibility(bool)\0"
    "chargerGeneral_NAV()\0chargerAvance_NAV()\0"
    "chargerSecurite_NAV()\0chargerGeneralAction_NAV()\0"
    "chargerAvanceAction_NAV()\0"
    "chargerSecuriteAction_NAV()\0"
    "changementOptionAuto()\0getCurrentPage()\0"
};

void fenetreOptions::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        Q_ASSERT(staticMetaObject.cast(_o));
        fenetreOptions *_t = static_cast<fenetreOptions *>(_o);
        switch (_id) {
        case 0: _t->closing(); break;
        case 1: _t->reloadToolBar(); break;
        case 2: _t->changeHome((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 3: _t->seeProgressStatusBar((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 4: _t->changeTaskBarVisibility((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 5: _t->chargerGeneral_NAV(); break;
        case 6: _t->chargerAvance_NAV(); break;
        case 7: _t->chargerSecurite_NAV(); break;
        case 8: _t->chargerGeneralAction_NAV(); break;
        case 9: _t->chargerAvanceAction_NAV(); break;
        case 10: _t->chargerSecuriteAction_NAV(); break;
        case 11: _t->changementOptionAuto(); break;
        case 12: _t->getCurrentPage(); break;
        default: ;
        }
    }
}

const QMetaObjectExtraData fenetreOptions::staticMetaObjectExtraData = {
    0,  qt_static_metacall 
};

const QMetaObject fenetreOptions::staticMetaObject = {
    { &QWidget::staticMetaObject, qt_meta_stringdata_fenetreOptions,
      qt_meta_data_fenetreOptions, &staticMetaObjectExtraData }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &fenetreOptions::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *fenetreOptions::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *fenetreOptions::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_fenetreOptions))
        return static_cast<void*>(const_cast< fenetreOptions*>(this));
    return QWidget::qt_metacast(_clname);
}

int fenetreOptions::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QWidget::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 13)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 13;
    }
    return _id;
}

// SIGNAL 0
void fenetreOptions::closing()
{
    QMetaObject::activate(this, &staticMetaObject, 0, 0);
}

// SIGNAL 1
void fenetreOptions::reloadToolBar()
{
    QMetaObject::activate(this, &staticMetaObject, 1, 0);
}

// SIGNAL 2
void fenetreOptions::changeHome(QString _t1)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 2, _a);
}

// SIGNAL 3
void fenetreOptions::seeProgressStatusBar(bool _t1)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 3, _a);
}

// SIGNAL 4
void fenetreOptions::changeTaskBarVisibility(bool _t1)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 4, _a);
}
static const uint qt_meta_data_fenetreOptions_Lecteur[] = {

 // content:
       6,       // revision
       0,       // classname
       0,    0, // classinfo
       1,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: signature, parameters, type, tag, flags
      24,   23,   23,   23, 0x0a,

       0        // eod
};

static const char qt_meta_stringdata_fenetreOptions_Lecteur[] = {
    "fenetreOptions_Lecteur\0\0modifier_chemin()\0"
};

void fenetreOptions_Lecteur::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        Q_ASSERT(staticMetaObject.cast(_o));
        fenetreOptions_Lecteur *_t = static_cast<fenetreOptions_Lecteur *>(_o);
        switch (_id) {
        case 0: _t->modifier_chemin(); break;
        default: ;
        }
    }
    Q_UNUSED(_a);
}

const QMetaObjectExtraData fenetreOptions_Lecteur::staticMetaObjectExtraData = {
    0,  qt_static_metacall 
};

const QMetaObject fenetreOptions_Lecteur::staticMetaObject = {
    { &QWidget::staticMetaObject, qt_meta_stringdata_fenetreOptions_Lecteur,
      qt_meta_data_fenetreOptions_Lecteur, &staticMetaObjectExtraData }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &fenetreOptions_Lecteur::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *fenetreOptions_Lecteur::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *fenetreOptions_Lecteur::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_fenetreOptions_Lecteur))
        return static_cast<void*>(const_cast< fenetreOptions_Lecteur*>(this));
    return QWidget::qt_metacast(_clname);
}

int fenetreOptions_Lecteur::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QWidget::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 1)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 1;
    }
    return _id;
}
QT_END_MOC_NAMESPACE
