/****************************************************************************
** Meta object code from reading C++ file 'FenetrePrincipale.h'
**
** Created: Fri 1. Jun 18:52:58 2012
**      by: The Qt Meta Object Compiler version 63 (Qt 4.8.1)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../FenetrePrincipale.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'FenetrePrincipale.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 63
#error "This file was generated using the moc from 4.8.1. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_Fenetre_Princ[] = {

 // content:
       6,       // revision
       0,       // classname
       0,    0, // classinfo
      21,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       1,       // signalCount

 // signals: signature, parameters, type, tag, flags
      15,   14,   14,   14, 0x05,

 // slots: signature, parameters, type, tag, flags
      28,   26,   14,   14, 0x0a,
      48,   14,   14,   14, 0x0a,
      68,   14,   14,   14, 0x0a,
      99,   92,   14,   14, 0x0a,
     125,   14,   14,   14, 0x0a,
     137,   14,   14,   14, 0x0a,
     150,   14,   14,   14, 0x0a,
     165,  157,   14,   14, 0x0a,
     193,   14,   14,   14, 0x0a,
     225,   14,   14,   14, 0x0a,
     245,   14,   14,   14, 0x0a,
     260,   14,   14,   14, 0x0a,
     276,   14,   14,   14, 0x0a,
     291,   14,   14,   14, 0x0a,
     317,  310,   14,   14, 0x0a,
     345,  340,   14,   14, 0x0a,
     363,   14,   14,   14, 0x0a,
     381,   14,   14,   14, 0x0a,
     407,   14,   14,   14, 0x0a,
     428,   14,   14,   14, 0x0a,

       0        // eod
};

static const char qt_meta_stringdata_Fenetre_Princ[] = {
    "Fenetre_Princ\0\0quitquit()\0i\0"
    "chargerFenetre(int)\0afficherOptionNAV()\0"
    "afficherOptionLecteur()\0action\0"
    "changerLanguage(QAction*)\0aboutAPro()\0"
    "aboutACorp()\0quit()\0musique\0"
    "LEC_chargerMusique(QString)\0"
    "LEC_chargerMusicFromSearchBar()\0"
    "LEC_ouvrirMusique()\0LEC_slotPlay()\0"
    "LEC_playpause()\0LEC_slotStop()\0"
    "LEC_afficherInfo()\0volume\0"
    "LEC_changerVolume(int)\0muet\0"
    "LEC_setMuet(bool)\0LEC_setLoop(bool)\0"
    "LEC_changeMusicPosition()\0"
    "LEC_UpdatePosition()\0sendQuit()\0"
};

void Fenetre_Princ::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        Q_ASSERT(staticMetaObject.cast(_o));
        Fenetre_Princ *_t = static_cast<Fenetre_Princ *>(_o);
        switch (_id) {
        case 0: _t->quitquit(); break;
        case 1: _t->chargerFenetre((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 2: _t->afficherOptionNAV(); break;
        case 3: _t->afficherOptionLecteur(); break;
        case 4: _t->changerLanguage((*reinterpret_cast< QAction*(*)>(_a[1]))); break;
        case 5: _t->aboutAPro(); break;
        case 6: _t->aboutACorp(); break;
        case 7: _t->quit(); break;
        case 8: _t->LEC_chargerMusique((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 9: _t->LEC_chargerMusicFromSearchBar(); break;
        case 10: _t->LEC_ouvrirMusique(); break;
        case 11: _t->LEC_slotPlay(); break;
        case 12: _t->LEC_playpause(); break;
        case 13: _t->LEC_slotStop(); break;
        case 14: _t->LEC_afficherInfo(); break;
        case 15: _t->LEC_changerVolume((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 16: _t->LEC_setMuet((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 17: _t->LEC_setLoop((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 18: _t->LEC_changeMusicPosition(); break;
        case 19: _t->LEC_UpdatePosition(); break;
        case 20: _t->sendQuit(); break;
        default: ;
        }
    }
}

const QMetaObjectExtraData Fenetre_Princ::staticMetaObjectExtraData = {
    0,  qt_static_metacall 
};

const QMetaObject Fenetre_Princ::staticMetaObject = {
    { &fenNAV::staticMetaObject, qt_meta_stringdata_Fenetre_Princ,
      qt_meta_data_Fenetre_Princ, &staticMetaObjectExtraData }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &Fenetre_Princ::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *Fenetre_Princ::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *Fenetre_Princ::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_Fenetre_Princ))
        return static_cast<void*>(const_cast< Fenetre_Princ*>(this));
    return fenNAV::qt_metacast(_clname);
}

int Fenetre_Princ::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = fenNAV::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 21)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 21;
    }
    return _id;
}

// SIGNAL 0
void Fenetre_Princ::quitquit()
{
    QMetaObject::activate(this, &staticMetaObject, 0, 0);
}
QT_END_MOC_NAMESPACE
