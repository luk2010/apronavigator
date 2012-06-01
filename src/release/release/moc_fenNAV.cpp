/****************************************************************************
** Meta object code from reading C++ file 'fenNAV.h'
**
** Created: Fri 1. Jun 18:53:01 2012
**      by: The Qt Meta Object Compiler version 63 (Qt 4.8.1)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../fenNAV.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'fenNAV.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 63
#error "This file was generated using the moc from 4.8.1. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_AFavoris[] = {

 // content:
       6,       // revision
       0,       // classname
       0,    0, // classinfo
       7,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       1,       // signalCount

 // signals: signature, parameters, type, tag, flags
      10,    9,    9,    9, 0x05,

 // slots: signature, parameters, type, tag, flags
      25,    9,    9,    9, 0x0a,
      62,    9,   41,    9, 0x0a,
      76,    9,    9,    9, 0x0a,
     112,   95,    9,    9, 0x0a,
     166,    9,    9,    9, 0x0a,
     179,    9,    9,    9, 0x0a,

       0        // eod
};

static const char qt_meta_stringdata_AFavoris[] = {
    "AFavoris\0\0reloadTabBar()\0deleteFavoris()\0"
    "QList<FavoriElement>\0loadFavoris()\0"
    "createNewFavoris()\0current,previous\0"
    "changeSelectedItem(QTreeWidgetItem*,QTreeWidgetItem*)\0"
    "createList()\0confirmNewFav()\0"
};

void AFavoris::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        Q_ASSERT(staticMetaObject.cast(_o));
        AFavoris *_t = static_cast<AFavoris *>(_o);
        switch (_id) {
        case 0: _t->reloadTabBar(); break;
        case 1: _t->deleteFavoris(); break;
        case 2: { QList<FavoriElement> _r = _t->loadFavoris();
            if (_a[0]) *reinterpret_cast< QList<FavoriElement>*>(_a[0]) = _r; }  break;
        case 3: _t->createNewFavoris(); break;
        case 4: _t->changeSelectedItem((*reinterpret_cast< QTreeWidgetItem*(*)>(_a[1])),(*reinterpret_cast< QTreeWidgetItem*(*)>(_a[2]))); break;
        case 5: _t->createList(); break;
        case 6: _t->confirmNewFav(); break;
        default: ;
        }
    }
}

const QMetaObjectExtraData AFavoris::staticMetaObjectExtraData = {
    0,  qt_static_metacall 
};

const QMetaObject AFavoris::staticMetaObject = {
    { &QWidget::staticMetaObject, qt_meta_stringdata_AFavoris,
      qt_meta_data_AFavoris, &staticMetaObjectExtraData }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &AFavoris::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *AFavoris::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *AFavoris::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_AFavoris))
        return static_cast<void*>(const_cast< AFavoris*>(this));
    return QWidget::qt_metacast(_clname);
}

int AFavoris::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
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
void AFavoris::reloadTabBar()
{
    QMetaObject::activate(this, &staticMetaObject, 0, 0);
}
static const uint qt_meta_data_fenNAV[] = {

 // content:
       6,       // revision
       0,       // classname
       0,    0, // classinfo
      63,   14, // methods
      17,  329, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       2,       // signalCount

 // signals: signature, parameters, type, tag, flags
       8,    7,    7,    7, 0x05,
      20,   18,    7,    7, 0x05,

 // slots: signature, parameters, type, tag, flags
      51,   47,    7,    7, 0x0a,
      75,    7,    7,    7, 0x2a,
      92,   47,    7,    7, 0x0a,
     123,    7,  113,    7, 0x0a,
     150,  144,    7,    7, 0x0a,
     172,    7,    7,    7, 0x0a,
     195,    7,    7,    7, 0x0a,
     216,    7,    7,    7, 0x0a,
     234,    7,    7,    7, 0x0a,
     258,    7,    7,    7, 0x0a,
     298,  283,    7,    7, 0x0a,
     337,   47,    7,    7, 0x0a,
     361,  144,    7,    7, 0x0a,
     387,    7,    7,    7, 0x0a,
     412,    7,    7,    7, 0x0a,
     446,  437,    7,    7, 0x0a,
     485,  475,    7,    7, 0x0a,
     528,   47,    7,    7, 0x0a,
     552,    7,    7,    7, 0x2a,
     572,    7,    7,    7, 0x0a,
     605,  593,    7,    7, 0x0a,
     653,    7,    7,    7, 0x0a,
     675,    7,    7,    7, 0x0a,
     710,    7,    7,    7, 0x0a,
     723,    7,    7,    7, 0x0a,
     738,    7,    7,    7, 0x0a,
     758,    7,    7,    7, 0x0a,
     779,    7,    7,    7, 0x0a,
     804,    7,    7,    7, 0x0a,
     838,  826,    7,    7, 0x0a,
     873,  865,    7,    7, 0x0a,
     907,  903,    7,    7, 0x0a,
     934,    7,    7,    7, 0x0a,
     949,    7,    7,    7, 0x0a,
     968,    7,    7,    7, 0x0a,
     990,  986,    7,    7, 0x0a,
    1029,    7,    7,    7, 0x0a,
    1052, 1048,    7,    7, 0x0a,
    1084,    7,    7,    7, 0x0a,
    1108,    7,    7,    7, 0x0a,
    1137, 1132,    7,    7, 0x0a,
    1182, 1175,    7,    7, 0x0a,
    1209,    7,  113,    7, 0x0a,
    1236, 1224,    7,    7, 0x0a,
    1268,    7, 1261,    7, 0x0a,
    1282,    7, 1261,    7, 0x0a,
    1299,    7, 1261,    7, 0x0a,
    1315,    7, 1261,    7, 0x0a,
    1341,    7, 1329,    7, 0x0a,
    1372,    7, 1356,    7, 0x0a,
    1401,    7, 1392,    7, 0x0a,
    1421,    7, 1392,    7, 0x0a,
    1440,    7, 1392,    7, 0x0a,
    1458,    7, 1392,    7, 0x0a,
    1474,    7, 1392,    7, 0x0a,
    1490,    7, 1392,    7, 0x0a,
    1506,    7, 1392,    7, 0x0a,
    1525,    7, 1392,    7, 0x0a,
    1556,    7, 1548,    7, 0x0a,
    1593,    7, 1574,    7, 0x0a,
    1630,    7, 1612,    7, 0x0a,

 // properties: name, type, flags
    1643, 1261, 0x00095009,
    1652, 1261, 0x00095009,
    1664, 1261, 0x00095009,
    1675, 1261, 0x00095009,
    1684, 1356, 0x00095009,
    1699, 1392, 0x00095009,
    1714, 1392, 0x00095009,
    1728, 1392, 0x00095009,
    1741, 1392, 0x00095009,
    1752, 1392, 0x00095009,
    1763, 1392, 0x00095009,
    1774, 1392, 0x00095009,
    1788, 1392, 0x00095009,
    1806, 1548, 0x00095009,
    1819, 1329, 0x00095009,
    1829, 1574, 0x00095009,
    1843, 1612, 0x00095009,

       0        // eod
};

static const char qt_meta_stringdata_fenNAV[] = {
    "fenNAV\0\0quitNOW()\0,\0favSignal(QString,QString)\0"
    "url\0NAV_ajouterTab(QString)\0"
    "NAV_ajouterTab()\0NAV_ajouterTab(QUrl)\0"
    "AProView*\0NAV_AjouterTabNull()\0index\0"
    "NAV_supprimerTab(int)\0NAV_precedent_action()\0"
    "NAV_suivant_action()\0NAV_stop_action()\0"
    "NAV_actualiser_action()\0"
    "NAV_chargerpage_action()\0titrelong,view\0"
    "NAV_changementTitre(QString,AProView*)\0"
    "NAV_changementUrl(QUrl)\0"
    "NAV_changementOnglet(int)\0"
    "NAV_chargerPageAccueil()\0"
    "NAV_rechercher_pressed()\0afficher\0"
    "NAV_AfficherHistorique(bool)\0url,title\0"
    "NAV_ajouterHistoriqueItem(QString,QString)\0"
    "NAV_MAJHistorique(QUrl)\0NAV_MAJHistorique()\0"
    "NAV_afficherOption()\0item,column\0"
    "NAV_chargerHistoriqueItem(QTreeWidgetItem*,int)\0"
    "NAV_viderHistorique()\0"
    "NAV_progressionTelechargement(int)\0"
    "NAV_ZOOMUP()\0NAV_ZOOMDOWN()\0"
    "afficherDownloads()\0afficherLesFavoris()\0"
    "afficherFenetreFavoris()\0loadToolBarPosition()\0"
    "newHomePage\0changePageAccueil(QString)\0"
    "ic,view\0changerIcone(QIcon,AProView*)\0"
    "see\0seeProgressStatusBar(bool)\0"
    "trierLoading()\0toggleFullscreen()\0"
    "addFavorisPopup()\0n,u\0"
    "activateStaticSlotFav(QString,QString)\0"
    "emitCustomSignal()\0msg\0"
    "changeStatusBarMessage(QString)\0"
    "extractVideosFromPage()\0extractMusicsFromPage()\0"
    "item\0addDownloadFromItem(QListWidgetItem*)\0"
    "plugin\0registerPlugin(AProPlugin)\0"
    "pageActuelle()\0url,pageWeb\0"
    "NAV_LOAD(QUrl,AProView*)\0QMenu*\0"
    "getFileMenu()\0getDisplayMenu()\0"
    "getOptionMenu()\0getHelpMenu()\0QStatusBar*\0"
    "getStatusBar()\0QList<QAction*>\0"
    "getToolBarActions()\0QAction*\0"
    "getPreviousAction()\0getForwardAction()\0"
    "getReloadAction()\0getStopAction()\0"
    "getHomeAction()\0getLoadAction()\0"
    "getHistoryAction()\0getFavoriteAddAction()\0"
    "QMovie*\0getLoadingMovie()\0AWebPluginFactory*\0"
    "getPluginFactory()\0QList<AProPlugin>\0"
    "getPlugins()\0fileMenu\0displayMenu\0"
    "optionMenu\0helpMenu\0toolBarActions\0"
    "previousAction\0forwardAction\0reloadAction\0"
    "stopAction\0homeAction\0loadAction\0"
    "historyAction\0favoriteAddAction\0"
    "loadingMovie\0statusBar\0pluginFactory\0"
    "plugins\0"
};

void fenNAV::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        Q_ASSERT(staticMetaObject.cast(_o));
        fenNAV *_t = static_cast<fenNAV *>(_o);
        switch (_id) {
        case 0: _t->quitNOW(); break;
        case 1: _t->favSignal((*reinterpret_cast< const QString(*)>(_a[1])),(*reinterpret_cast< const QString(*)>(_a[2]))); break;
        case 2: _t->NAV_ajouterTab((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 3: _t->NAV_ajouterTab(); break;
        case 4: _t->NAV_ajouterTab((*reinterpret_cast< QUrl(*)>(_a[1]))); break;
        case 5: { AProView* _r = _t->NAV_AjouterTabNull();
            if (_a[0]) *reinterpret_cast< AProView**>(_a[0]) = _r; }  break;
        case 6: _t->NAV_supprimerTab((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 7: _t->NAV_precedent_action(); break;
        case 8: _t->NAV_suivant_action(); break;
        case 9: _t->NAV_stop_action(); break;
        case 10: _t->NAV_actualiser_action(); break;
        case 11: _t->NAV_chargerpage_action(); break;
        case 12: _t->NAV_changementTitre((*reinterpret_cast< QString(*)>(_a[1])),(*reinterpret_cast< AProView*(*)>(_a[2]))); break;
        case 13: _t->NAV_changementUrl((*reinterpret_cast< QUrl(*)>(_a[1]))); break;
        case 14: _t->NAV_changementOnglet((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 15: _t->NAV_chargerPageAccueil(); break;
        case 16: _t->NAV_rechercher_pressed(); break;
        case 17: _t->NAV_AfficherHistorique((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 18: _t->NAV_ajouterHistoriqueItem((*reinterpret_cast< QString(*)>(_a[1])),(*reinterpret_cast< QString(*)>(_a[2]))); break;
        case 19: _t->NAV_MAJHistorique((*reinterpret_cast< QUrl(*)>(_a[1]))); break;
        case 20: _t->NAV_MAJHistorique(); break;
        case 21: _t->NAV_afficherOption(); break;
        case 22: _t->NAV_chargerHistoriqueItem((*reinterpret_cast< QTreeWidgetItem*(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2]))); break;
        case 23: _t->NAV_viderHistorique(); break;
        case 24: _t->NAV_progressionTelechargement((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 25: _t->NAV_ZOOMUP(); break;
        case 26: _t->NAV_ZOOMDOWN(); break;
        case 27: _t->afficherDownloads(); break;
        case 28: _t->afficherLesFavoris(); break;
        case 29: _t->afficherFenetreFavoris(); break;
        case 30: _t->loadToolBarPosition(); break;
        case 31: _t->changePageAccueil((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 32: _t->changerIcone((*reinterpret_cast< QIcon(*)>(_a[1])),(*reinterpret_cast< AProView*(*)>(_a[2]))); break;
        case 33: _t->seeProgressStatusBar((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 34: _t->trierLoading(); break;
        case 35: _t->toggleFullscreen(); break;
        case 36: _t->addFavorisPopup(); break;
        case 37: _t->activateStaticSlotFav((*reinterpret_cast< const QString(*)>(_a[1])),(*reinterpret_cast< const QString(*)>(_a[2]))); break;
        case 38: _t->emitCustomSignal(); break;
        case 39: _t->changeStatusBarMessage((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 40: _t->extractVideosFromPage(); break;
        case 41: _t->extractMusicsFromPage(); break;
        case 42: _t->addDownloadFromItem((*reinterpret_cast< QListWidgetItem*(*)>(_a[1]))); break;
        case 43: _t->registerPlugin((*reinterpret_cast< AProPlugin(*)>(_a[1]))); break;
        case 44: { AProView* _r = _t->pageActuelle();
            if (_a[0]) *reinterpret_cast< AProView**>(_a[0]) = _r; }  break;
        case 45: _t->NAV_LOAD((*reinterpret_cast< QUrl(*)>(_a[1])),(*reinterpret_cast< AProView*(*)>(_a[2]))); break;
        case 46: { QMenu* _r = _t->getFileMenu();
            if (_a[0]) *reinterpret_cast< QMenu**>(_a[0]) = _r; }  break;
        case 47: { QMenu* _r = _t->getDisplayMenu();
            if (_a[0]) *reinterpret_cast< QMenu**>(_a[0]) = _r; }  break;
        case 48: { QMenu* _r = _t->getOptionMenu();
            if (_a[0]) *reinterpret_cast< QMenu**>(_a[0]) = _r; }  break;
        case 49: { QMenu* _r = _t->getHelpMenu();
            if (_a[0]) *reinterpret_cast< QMenu**>(_a[0]) = _r; }  break;
        case 50: { QStatusBar* _r = _t->getStatusBar();
            if (_a[0]) *reinterpret_cast< QStatusBar**>(_a[0]) = _r; }  break;
        case 51: { QList<QAction*> _r = _t->getToolBarActions();
            if (_a[0]) *reinterpret_cast< QList<QAction*>*>(_a[0]) = _r; }  break;
        case 52: { QAction* _r = _t->getPreviousAction();
            if (_a[0]) *reinterpret_cast< QAction**>(_a[0]) = _r; }  break;
        case 53: { QAction* _r = _t->getForwardAction();
            if (_a[0]) *reinterpret_cast< QAction**>(_a[0]) = _r; }  break;
        case 54: { QAction* _r = _t->getReloadAction();
            if (_a[0]) *reinterpret_cast< QAction**>(_a[0]) = _r; }  break;
        case 55: { QAction* _r = _t->getStopAction();
            if (_a[0]) *reinterpret_cast< QAction**>(_a[0]) = _r; }  break;
        case 56: { QAction* _r = _t->getHomeAction();
            if (_a[0]) *reinterpret_cast< QAction**>(_a[0]) = _r; }  break;
        case 57: { QAction* _r = _t->getLoadAction();
            if (_a[0]) *reinterpret_cast< QAction**>(_a[0]) = _r; }  break;
        case 58: { QAction* _r = _t->getHistoryAction();
            if (_a[0]) *reinterpret_cast< QAction**>(_a[0]) = _r; }  break;
        case 59: { QAction* _r = _t->getFavoriteAddAction();
            if (_a[0]) *reinterpret_cast< QAction**>(_a[0]) = _r; }  break;
        case 60: { QMovie* _r = _t->getLoadingMovie();
            if (_a[0]) *reinterpret_cast< QMovie**>(_a[0]) = _r; }  break;
        case 61: { AWebPluginFactory* _r = _t->getPluginFactory();
            if (_a[0]) *reinterpret_cast< AWebPluginFactory**>(_a[0]) = _r; }  break;
        case 62: { QList<AProPlugin> _r = _t->getPlugins();
            if (_a[0]) *reinterpret_cast< QList<AProPlugin>*>(_a[0]) = _r; }  break;
        default: ;
        }
    }
}

const QMetaObjectExtraData fenNAV::staticMetaObjectExtraData = {
    0,  qt_static_metacall 
};

const QMetaObject fenNAV::staticMetaObject = {
    { &QMainWindow::staticMetaObject, qt_meta_stringdata_fenNAV,
      qt_meta_data_fenNAV, &staticMetaObjectExtraData }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &fenNAV::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *fenNAV::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *fenNAV::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_fenNAV))
        return static_cast<void*>(const_cast< fenNAV*>(this));
    return QMainWindow::qt_metacast(_clname);
}

int fenNAV::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QMainWindow::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 63)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 63;
    }
#ifndef QT_NO_PROPERTIES
      else if (_c == QMetaObject::ReadProperty) {
        void *_v = _a[0];
        switch (_id) {
        case 0: *reinterpret_cast< QMenu**>(_v) = getFileMenu(); break;
        case 1: *reinterpret_cast< QMenu**>(_v) = getDisplayMenu(); break;
        case 2: *reinterpret_cast< QMenu**>(_v) = getOptionMenu(); break;
        case 3: *reinterpret_cast< QMenu**>(_v) = getHelpMenu(); break;
        case 4: *reinterpret_cast< QList<QAction*>*>(_v) = getToolBarActions(); break;
        case 5: *reinterpret_cast< QAction**>(_v) = getPreviousAction(); break;
        case 6: *reinterpret_cast< QAction**>(_v) = getForwardAction(); break;
        case 7: *reinterpret_cast< QAction**>(_v) = getReloadAction(); break;
        case 8: *reinterpret_cast< QAction**>(_v) = getStopAction(); break;
        case 9: *reinterpret_cast< QAction**>(_v) = getHomeAction(); break;
        case 10: *reinterpret_cast< QAction**>(_v) = getLoadAction(); break;
        case 11: *reinterpret_cast< QAction**>(_v) = getHistoryAction(); break;
        case 12: *reinterpret_cast< QAction**>(_v) = getFavoriteAddAction(); break;
        case 13: *reinterpret_cast< QMovie**>(_v) = getLoadingMovie(); break;
        case 14: *reinterpret_cast< QStatusBar**>(_v) = getStatusBar(); break;
        case 15: *reinterpret_cast< AWebPluginFactory**>(_v) = getPluginFactory(); break;
        case 16: *reinterpret_cast< QList<AProPlugin>*>(_v) = getPlugins(); break;
        }
        _id -= 17;
    } else if (_c == QMetaObject::WriteProperty) {
        _id -= 17;
    } else if (_c == QMetaObject::ResetProperty) {
        _id -= 17;
    } else if (_c == QMetaObject::QueryPropertyDesignable) {
        _id -= 17;
    } else if (_c == QMetaObject::QueryPropertyScriptable) {
        _id -= 17;
    } else if (_c == QMetaObject::QueryPropertyStored) {
        _id -= 17;
    } else if (_c == QMetaObject::QueryPropertyEditable) {
        _id -= 17;
    } else if (_c == QMetaObject::QueryPropertyUser) {
        _id -= 17;
    }
#endif // QT_NO_PROPERTIES
    return _id;
}

// SIGNAL 0
void fenNAV::quitNOW()
{
    QMetaObject::activate(this, &staticMetaObject, 0, 0);
}

// SIGNAL 1
void fenNAV::favSignal(const QString & _t1, const QString & _t2)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)), const_cast<void*>(reinterpret_cast<const void*>(&_t2)) };
    QMetaObject::activate(this, &staticMetaObject, 1, _a);
}
static const uint qt_meta_data_FavButton[] = {

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
      11,   10,   10,   10, 0x05,

 // slots: signature, parameters, type, tag, flags
      32,   10,   10,   10, 0x0a,

       0        // eod
};

static const char qt_meta_stringdata_FavButton[] = {
    "FavButton\0\0customClick(QString)\0"
    "emitCustomClick()\0"
};

void FavButton::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        Q_ASSERT(staticMetaObject.cast(_o));
        FavButton *_t = static_cast<FavButton *>(_o);
        switch (_id) {
        case 0: _t->customClick((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 1: _t->emitCustomClick(); break;
        default: ;
        }
    }
}

const QMetaObjectExtraData FavButton::staticMetaObjectExtraData = {
    0,  qt_static_metacall 
};

const QMetaObject FavButton::staticMetaObject = {
    { &QAction::staticMetaObject, qt_meta_stringdata_FavButton,
      qt_meta_data_FavButton, &staticMetaObjectExtraData }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &FavButton::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *FavButton::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *FavButton::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_FavButton))
        return static_cast<void*>(const_cast< FavButton*>(this));
    return QAction::qt_metacast(_clname);
}

int FavButton::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QAction::qt_metacall(_c, _id, _a);
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
void FavButton::customClick(QString _t1)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}
QT_END_MOC_NAMESPACE
