/****************************************************************************
** Meta object code from reading C++ file 'AProView.h'
**
** Created: Mon 14. May 22:36:28 2012
**      by: The Qt Meta Object Compiler version 63 (Qt 4.8.1)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../AProView.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'AProView.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 63
#error "This file was generated using the moc from 4.8.1. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_fenTelechargement[] = {

 // content:
       6,       // revision
       0,       // classname
       0,    0, // classinfo
       7,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       2,       // signalCount

 // signals: signature, parameters, type, tag, flags
      19,   18,   18,   18, 0x05,
      49,   18,   18,   18, 0x05,

 // slots: signature, parameters, type, tag, flags
      81,   18,   18,   18, 0x0a,
     109,  107,   18,   18, 0x0a,
     143,   18,   18,   18, 0x0a,
     159,   18,   18,   18, 0x0a,
     169,   18,   18,   18, 0x0a,

       0        // eod
};

static const char qt_meta_stringdata_fenTelechargement[] = {
    "fenTelechargement\0\0telechargementFini(FileInfo&)\0"
    "telechargementAnnule(FileInfo&)\0"
    "commencerTelechargement()\0,\0"
    "MAJ_telechargement(qint64,qint64)\0"
    "finirEtEcrire()\0Annuler()\0MAJ_vitesse()\0"
};

void fenTelechargement::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        Q_ASSERT(staticMetaObject.cast(_o));
        fenTelechargement *_t = static_cast<fenTelechargement *>(_o);
        switch (_id) {
        case 0: _t->telechargementFini((*reinterpret_cast< FileInfo(*)>(_a[1]))); break;
        case 1: _t->telechargementAnnule((*reinterpret_cast< FileInfo(*)>(_a[1]))); break;
        case 2: _t->commencerTelechargement(); break;
        case 3: _t->MAJ_telechargement((*reinterpret_cast< qint64(*)>(_a[1])),(*reinterpret_cast< qint64(*)>(_a[2]))); break;
        case 4: _t->finirEtEcrire(); break;
        case 5: _t->Annuler(); break;
        case 6: _t->MAJ_vitesse(); break;
        default: ;
        }
    }
}

const QMetaObjectExtraData fenTelechargement::staticMetaObjectExtraData = {
    0,  qt_static_metacall 
};

const QMetaObject fenTelechargement::staticMetaObject = {
    { &QWidget::staticMetaObject, qt_meta_stringdata_fenTelechargement,
      qt_meta_data_fenTelechargement, &staticMetaObjectExtraData }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &fenTelechargement::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *fenTelechargement::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *fenTelechargement::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_fenTelechargement))
        return static_cast<void*>(const_cast< fenTelechargement*>(this));
    return QWidget::qt_metacast(_clname);
}

int fenTelechargement::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QWidget::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 7)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 7;
    }
    return _id;
}

// SIGNAL 0
void fenTelechargement::telechargementFini(FileInfo & _t1)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}

// SIGNAL 1
void fenTelechargement::telechargementAnnule(FileInfo & _t1)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 1, _a);
}
static const uint qt_meta_data_GestionTelechargement[] = {

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
      27,   23,   22,   22, 0x0a,
      55,   22,   22,   22, 0x0a,
      81,   22,   22,   22, 0x0a,
     111,   22,   22,   22, 0x0a,

       0        // eod
};

static const char qt_meta_stringdata_GestionTelechargement[] = {
    "GestionTelechargement\0\0url\0"
    "ajouterTelechargement(QUrl)\0"
    "afficherTelechargements()\0"
    "telechargementFini(FileInfo&)\0"
    "telechargementAnnule(FileInfo&)\0"
};

void GestionTelechargement::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        Q_ASSERT(staticMetaObject.cast(_o));
        GestionTelechargement *_t = static_cast<GestionTelechargement *>(_o);
        switch (_id) {
        case 0: _t->ajouterTelechargement((*reinterpret_cast< QUrl(*)>(_a[1]))); break;
        case 1: _t->afficherTelechargements(); break;
        case 2: _t->telechargementFini((*reinterpret_cast< FileInfo(*)>(_a[1]))); break;
        case 3: _t->telechargementAnnule((*reinterpret_cast< FileInfo(*)>(_a[1]))); break;
        default: ;
        }
    }
}

const QMetaObjectExtraData GestionTelechargement::staticMetaObjectExtraData = {
    0,  qt_static_metacall 
};

const QMetaObject GestionTelechargement::staticMetaObject = {
    { &QObject::staticMetaObject, qt_meta_stringdata_GestionTelechargement,
      qt_meta_data_GestionTelechargement, &staticMetaObjectExtraData }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &GestionTelechargement::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *GestionTelechargement::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *GestionTelechargement::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_GestionTelechargement))
        return static_cast<void*>(const_cast< GestionTelechargement*>(this));
    return QObject::qt_metacast(_clname);
}

int GestionTelechargement::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
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
static const uint qt_meta_data_AProView[] = {

 // content:
       6,       // revision
       0,       // classname
       0,    0, // classinfo
      15,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       4,       // signalCount

 // signals: signature, parameters, type, tag, flags
      10,    9,    9,    9, 0x05,
      29,   27,    9,    9, 0x05,
      61,   27,    9,    9, 0x05,
      90,    9,    9,    9, 0x05,

 // slots: signature, parameters, type, tag, flags
     120,    9,    9,    9, 0x0a,
     146,  140,    9,    9, 0x0a,
     180,    9,    9,    9, 0x0a,
     200,  194,    9,    9, 0x0a,
     227,    9,    9,    9, 0x0a,
     245,    9,    9,    9, 0x0a,
     271,  262,    9,    9, 0x0a,
     293,    9,    9,    9, 0x0a,
     333,  315,    9,    9, 0x0a,
     370,    9,    9,    9, 0x0a,
     390,  386,    9,    9, 0x0a,

       0        // eod
};

static const char qt_meta_stringdata_AProView[] = {
    "AProView\0\0ajouterTab(QUrl)\0,\0"
    "changerTitre(QString,AProView*)\0"
    "changerIcon(QIcon,AProView*)\0"
    "webViewStatusMessage(QString)\0"
    "pretelechargement()\0reply\0"
    "pretelechargement(QNetworkReply*)\0"
    "ajouterPage()\0titre\0envoiChangerTitre(QString)\0"
    "sendIconChanged()\0loadingStarted()\0"
    "pourcent\0setLoadingStatus(int)\0"
    "loadingFinished(bool)\0Url,Title,Content\0"
    "linkHovered(QString,QString,QString)\0"
    "showInspector()\0url\0downloadElement(QUrl)\0"
};

void AProView::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        Q_ASSERT(staticMetaObject.cast(_o));
        AProView *_t = static_cast<AProView *>(_o);
        switch (_id) {
        case 0: _t->ajouterTab((*reinterpret_cast< QUrl(*)>(_a[1]))); break;
        case 1: _t->changerTitre((*reinterpret_cast< QString(*)>(_a[1])),(*reinterpret_cast< AProView*(*)>(_a[2]))); break;
        case 2: _t->changerIcon((*reinterpret_cast< QIcon(*)>(_a[1])),(*reinterpret_cast< AProView*(*)>(_a[2]))); break;
        case 3: _t->webViewStatusMessage((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 4: _t->pretelechargement(); break;
        case 5: _t->pretelechargement((*reinterpret_cast< QNetworkReply*(*)>(_a[1]))); break;
        case 6: _t->ajouterPage(); break;
        case 7: _t->envoiChangerTitre((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 8: _t->sendIconChanged(); break;
        case 9: _t->loadingStarted(); break;
        case 10: _t->setLoadingStatus((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 11: _t->loadingFinished((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 12: _t->linkHovered((*reinterpret_cast< QString(*)>(_a[1])),(*reinterpret_cast< QString(*)>(_a[2])),(*reinterpret_cast< QString(*)>(_a[3]))); break;
        case 13: _t->showInspector(); break;
        case 14: _t->downloadElement((*reinterpret_cast< QUrl(*)>(_a[1]))); break;
        default: ;
        }
    }
}

const QMetaObjectExtraData AProView::staticMetaObjectExtraData = {
    0,  qt_static_metacall 
};

const QMetaObject AProView::staticMetaObject = {
    { &QWebView::staticMetaObject, qt_meta_stringdata_AProView,
      qt_meta_data_AProView, &staticMetaObjectExtraData }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &AProView::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *AProView::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *AProView::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_AProView))
        return static_cast<void*>(const_cast< AProView*>(this));
    return QWebView::qt_metacast(_clname);
}

int AProView::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QWebView::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 15)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 15;
    }
    return _id;
}

// SIGNAL 0
void AProView::ajouterTab(QUrl _t1)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}

// SIGNAL 1
void AProView::changerTitre(QString _t1, AProView * _t2)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)), const_cast<void*>(reinterpret_cast<const void*>(&_t2)) };
    QMetaObject::activate(this, &staticMetaObject, 1, _a);
}

// SIGNAL 2
void AProView::changerIcon(QIcon _t1, AProView * _t2)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)), const_cast<void*>(reinterpret_cast<const void*>(&_t2)) };
    QMetaObject::activate(this, &staticMetaObject, 2, _a);
}

// SIGNAL 3
void AProView::webViewStatusMessage(QString _t1)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 3, _a);
}
QT_END_MOC_NAMESPACE
