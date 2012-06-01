/****************************************************************************
** Meta object code from reading C++ file 'AProSearchLine.h'
**
** Created: Mon 14. May 22:36:25 2012
**      by: The Qt Meta Object Compiler version 63 (Qt 4.8.1)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../AProSearchLine.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'AProSearchLine.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 63
#error "This file was generated using the moc from 4.8.1. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_GSuggest[] = {

 // content:
       6,       // revision
       0,       // classname
       0,    0, // classinfo
       4,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: signature, parameters, type, tag, flags
      10,    9,    9,    9, 0x0a,
      27,    9,    9,    9, 0x0a,
      44,    9,    9,    9, 0x0a,
      64,   58,    9,    9, 0x0a,

       0        // eod
};

static const char qt_meta_stringdata_GSuggest[] = {
    "GSuggest\0\0doneCompletion()\0preventSuggest()\0"
    "autoSuggest()\0reply\0"
    "handleNetworkData(QNetworkReply*)\0"
};

void GSuggest::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        Q_ASSERT(staticMetaObject.cast(_o));
        GSuggest *_t = static_cast<GSuggest *>(_o);
        switch (_id) {
        case 0: _t->doneCompletion(); break;
        case 1: _t->preventSuggest(); break;
        case 2: _t->autoSuggest(); break;
        case 3: _t->handleNetworkData((*reinterpret_cast< QNetworkReply*(*)>(_a[1]))); break;
        default: ;
        }
    }
}

const QMetaObjectExtraData GSuggest::staticMetaObjectExtraData = {
    0,  qt_static_metacall 
};

const QMetaObject GSuggest::staticMetaObject = {
    { &QObject::staticMetaObject, qt_meta_stringdata_GSuggest,
      qt_meta_data_GSuggest, &staticMetaObjectExtraData }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &GSuggest::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *GSuggest::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *GSuggest::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_GSuggest))
        return static_cast<void*>(const_cast< GSuggest*>(this));
    return QObject::qt_metacast(_clname);
}

int GSuggest::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QObject::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 4)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 4;
    }
    return _id;
}
static const uint qt_meta_data_clearButton[] = {

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
      18,   13,   12,   12, 0x0a,
      45,   39,   12,   12, 0x0a,

       0        // eod
};

static const char qt_meta_stringdata_clearButton[] = {
    "clearButton\0\0text\0textChanged(QString)\0"
    "color\0setColor(QColor)\0"
};

void clearButton::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        Q_ASSERT(staticMetaObject.cast(_o));
        clearButton *_t = static_cast<clearButton *>(_o);
        switch (_id) {
        case 0: _t->textChanged((*reinterpret_cast< const QString(*)>(_a[1]))); break;
        case 1: _t->setColor((*reinterpret_cast< const QColor(*)>(_a[1]))); break;
        default: ;
        }
    }
}

const QMetaObjectExtraData clearButton::staticMetaObjectExtraData = {
    0,  qt_static_metacall 
};

const QMetaObject clearButton::staticMetaObject = {
    { &QAbstractButton::staticMetaObject, qt_meta_stringdata_clearButton,
      qt_meta_data_clearButton, &staticMetaObjectExtraData }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &clearButton::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *clearButton::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *clearButton::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_clearButton))
        return static_cast<void*>(const_cast< clearButton*>(this));
    return QAbstractButton::qt_metacast(_clname);
}

int clearButton::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QAbstractButton::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 2)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 2;
    }
    return _id;
}
static const uint qt_meta_data_searchLine[] = {

 // content:
       6,       // revision
       0,       // classname
       0,    0, // classinfo
       1,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       1,       // signalCount

 // signals: signature, parameters, type, tag, flags
      17,   12,   11,   11, 0x05,

       0        // eod
};

static const char qt_meta_stringdata_searchLine[] = {
    "searchLine\0\0text\0textChanged(QString)\0"
};

void searchLine::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        Q_ASSERT(staticMetaObject.cast(_o));
        searchLine *_t = static_cast<searchLine *>(_o);
        switch (_id) {
        case 0: _t->textChanged((*reinterpret_cast< const QString(*)>(_a[1]))); break;
        default: ;
        }
    }
}

const QMetaObjectExtraData searchLine::staticMetaObjectExtraData = {
    0,  qt_static_metacall 
};

const QMetaObject searchLine::staticMetaObject = {
    { &QWidget::staticMetaObject, qt_meta_stringdata_searchLine,
      qt_meta_data_searchLine, &staticMetaObjectExtraData }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &searchLine::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *searchLine::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *searchLine::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_searchLine))
        return static_cast<void*>(const_cast< searchLine*>(this));
    return QWidget::qt_metacast(_clname);
}

int searchLine::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
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

// SIGNAL 0
void searchLine::textChanged(const QString & _t1)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}
static const uint qt_meta_data_MusicSearcher[] = {

 // content:
       6,       // revision
       0,       // classname
       0,    0, // classinfo
       2,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       1,       // signalCount

 // signals: signature, parameters, type, tag, flags
      15,   14,   14,   14, 0x05,

 // slots: signature, parameters, type, tag, flags
      29,   14,   14,   14, 0x0a,

       0        // eod
};

static const char qt_meta_stringdata_MusicSearcher[] = {
    "MusicSearcher\0\0popupFilled()\0search()\0"
};

void MusicSearcher::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        Q_ASSERT(staticMetaObject.cast(_o));
        MusicSearcher *_t = static_cast<MusicSearcher *>(_o);
        switch (_id) {
        case 0: _t->popupFilled(); break;
        case 1: _t->search(); break;
        default: ;
        }
    }
    Q_UNUSED(_a);
}

const QMetaObjectExtraData MusicSearcher::staticMetaObjectExtraData = {
    0,  qt_static_metacall 
};

const QMetaObject MusicSearcher::staticMetaObject = {
    { &QObject::staticMetaObject, qt_meta_stringdata_MusicSearcher,
      qt_meta_data_MusicSearcher, &staticMetaObjectExtraData }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &MusicSearcher::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *MusicSearcher::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *MusicSearcher::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_MusicSearcher))
        return static_cast<void*>(const_cast< MusicSearcher*>(this));
    return QObject::qt_metacast(_clname);
}

int MusicSearcher::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QObject::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 2)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 2;
    }
    return _id;
}

// SIGNAL 0
void MusicSearcher::popupFilled()
{
    QMetaObject::activate(this, &staticMetaObject, 0, 0);
}
static const uint qt_meta_data_autoSearchSuggest[] = {

 // content:
       6,       // revision
       0,       // classname
       0,    0, // classinfo
       5,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       1,       // signalCount

 // signals: signature, parameters, type, tag, flags
      19,   18,   18,   18, 0x05,

 // slots: signature, parameters, type, tag, flags
      35,   18,   18,   18, 0x0a,
      56,   49,   44,   18, 0x0a,
      86,   18,   18,   18, 0x0a,
     103,   18,   18,   18, 0x0a,

       0        // eod
};

static const char qt_meta_stringdata_autoSearchSuggest[] = {
    "autoSearchSuggest\0\0lancerMusique()\0"
    "search()\0bool\0obj,ev\0eventFilter(QObject*,QEvent*)\0"
    "doneCompletion()\0showPopup()\0"
};

void autoSearchSuggest::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        Q_ASSERT(staticMetaObject.cast(_o));
        autoSearchSuggest *_t = static_cast<autoSearchSuggest *>(_o);
        switch (_id) {
        case 0: _t->lancerMusique(); break;
        case 1: _t->search(); break;
        case 2: { bool _r = _t->eventFilter((*reinterpret_cast< QObject*(*)>(_a[1])),(*reinterpret_cast< QEvent*(*)>(_a[2])));
            if (_a[0]) *reinterpret_cast< bool*>(_a[0]) = _r; }  break;
        case 3: _t->doneCompletion(); break;
        case 4: _t->showPopup(); break;
        default: ;
        }
    }
}

const QMetaObjectExtraData autoSearchSuggest::staticMetaObjectExtraData = {
    0,  qt_static_metacall 
};

const QMetaObject autoSearchSuggest::staticMetaObject = {
    { &QObject::staticMetaObject, qt_meta_stringdata_autoSearchSuggest,
      qt_meta_data_autoSearchSuggest, &staticMetaObjectExtraData }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &autoSearchSuggest::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *autoSearchSuggest::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *autoSearchSuggest::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_autoSearchSuggest))
        return static_cast<void*>(const_cast< autoSearchSuggest*>(this));
    return QObject::qt_metacast(_clname);
}

int autoSearchSuggest::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QObject::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 5)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 5;
    }
    return _id;
}

// SIGNAL 0
void autoSearchSuggest::lancerMusique()
{
    QMetaObject::activate(this, &staticMetaObject, 0, 0);
}
static const uint qt_meta_data_musicSearchLine[] = {

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
      17,   16,   16,   16, 0x0a,

       0        // eod
};

static const char qt_meta_stringdata_musicSearchLine[] = {
    "musicSearchLine\0\0returnPressed_emit()\0"
};

void musicSearchLine::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        Q_ASSERT(staticMetaObject.cast(_o));
        musicSearchLine *_t = static_cast<musicSearchLine *>(_o);
        switch (_id) {
        case 0: _t->returnPressed_emit(); break;
        default: ;
        }
    }
    Q_UNUSED(_a);
}

const QMetaObjectExtraData musicSearchLine::staticMetaObjectExtraData = {
    0,  qt_static_metacall 
};

const QMetaObject musicSearchLine::staticMetaObject = {
    { &QLineEdit::staticMetaObject, qt_meta_stringdata_musicSearchLine,
      qt_meta_data_musicSearchLine, &staticMetaObjectExtraData }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &musicSearchLine::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *musicSearchLine::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *musicSearchLine::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_musicSearchLine))
        return static_cast<void*>(const_cast< musicSearchLine*>(this));
    return QLineEdit::qt_metacast(_clname);
}

int musicSearchLine::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QLineEdit::qt_metacall(_c, _id, _a);
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
