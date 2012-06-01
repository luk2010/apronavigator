#ifndef FENNAV_H
#define FENNAV_H

#include <QtGUI>
#include <QtWebKit>
#include <QDomDocument>
#include <QHash>
#include <QMenu>

#include "ASwitchButton.h"
#include "fenetreOptions.h"
#include "AProSearchLine.h"
#include "AProView.h"
#include "ATabBar.h"
#include "adressbar.h"

#include "awebpluginfactory.h"
#include "aplugin.h"

class AProView;
class FavButton;
class fenetreOptions;

struct HistoriqueElement
{
    QString title;
    QString url;
    QDateTime date;
};
typedef struct HistoriqueElement HistoriqueElement;

struct FavoriElement
{
    QString title;
    QString url;
};
typedef struct FavoriElement FavoriElement;

class AFavoris : public QWidget
{
    Q_OBJECT
public:

    AFavoris(QWidget* parent = 0);
    virtual ~AFavoris() {}

    static void addNewFavoris(const QString& name,const QString& url);

public slots:
    void deleteFavoris();
    QList<FavoriElement> loadFavoris();
    void createNewFavoris();
    void changeSelectedItem(QTreeWidgetItem* current,QTreeWidgetItem* previous);
    void createList();
    void confirmNewFav();

signals:
    void reloadTabBar();

private:
    QTreeWidgetItem* itemSelected;
    QList<FavoriElement> fav;
    QTreeWidget* list;
    QLineEdit* name;
    QLineEdit* url;
    QPushButton* validateFav;
};

class fenNAV : public QMainWindow
{
    Q_OBJECT

    Q_PROPERTY(QMenu* fileMenu READ getFileMenu)
    Q_PROPERTY(QMenu* displayMenu READ getDisplayMenu)
    Q_PROPERTY(QMenu* optionMenu READ getOptionMenu)
    Q_PROPERTY(QMenu* helpMenu READ getHelpMenu)

    Q_PROPERTY(QList<QAction*> toolBarActions READ getToolBarActions)

    Q_PROPERTY(QAction* previousAction READ getPreviousAction)
    Q_PROPERTY(QAction* forwardAction READ getForwardAction)
    Q_PROPERTY(QAction* reloadAction READ getReloadAction)
    Q_PROPERTY(QAction* stopAction READ getStopAction)
    Q_PROPERTY(QAction* homeAction READ getHomeAction)
    Q_PROPERTY(QAction* loadAction READ getLoadAction)
    Q_PROPERTY(QAction* historyAction READ getHistoryAction)
    Q_PROPERTY(QAction* favoriteAddAction READ getFavoriteAddAction)

    Q_PROPERTY(QMovie* loadingMovie READ getLoadingMovie)

    Q_PROPERTY(QStatusBar* statusBar READ getStatusBar)

    Q_PROPERTY(AWebPluginFactory* pluginFactory READ getPluginFactory)

    Q_PROPERTY(QList<AProPlugin> plugins READ getPlugins)

    public :
    //Constructeur
    fenNAV(QWidget *parent = 0);
    //Destructeur
    ~fenNAV();

    void setUrl(QUrl url);
    void setUrlImg(QUrl img);

    public slots :

    //SLOT NAV

    void NAV_ajouterTab(QString url ="");
    void NAV_ajouterTab(QUrl url);
    AProView* NAV_AjouterTabNull();
    void NAV_supprimerTab(int index);
    void NAV_precedent_action();
    void NAV_suivant_action();
    void NAV_stop_action();
    void NAV_actualiser_action();
    void NAV_chargerpage_action();
    void NAV_changementTitre(QString titrelong,AProView* view);
    void NAV_changementUrl(QUrl url);
    void NAV_changementOnglet(int index);
    void NAV_chargerPageAccueil();
    void NAV_rechercher_pressed();
    void NAV_AfficherHistorique(bool afficher);
    void NAV_ajouterHistoriqueItem(QString url,QString title);
    void NAV_MAJHistorique(QUrl url=QString(""));
    void NAV_afficherOption();
    void NAV_chargerHistoriqueItem(QTreeWidgetItem* item, int column);
    void NAV_viderHistorique();
    void NAV_progressionTelechargement(int);
    void NAV_ZOOMUP();
    void NAV_ZOOMDOWN();
    void afficherDownloads();
    void afficherLesFavoris();
    void afficherFenetreFavoris();
    void loadToolBarPosition();
    void changePageAccueil(QString newHomePage) { page_accueil = newHomePage; }
    void changerIcone(QIcon ic,AProView* view);
    void seeProgressStatusBar(bool see) { progressBarInStatusBar = see; }
    void trierLoading();
    void toggleFullscreen();
    void addFavorisPopup();
    void activateStaticSlotFav(const QString& n,const QString& u);
    void emitCustomSignal();
    void changeStatusBarMessage(QString msg);
    void extractVideosFromPage();
    void extractMusicsFromPage();
    void addDownloadFromItem(QListWidgetItem* item);
    void registerPlugin(AProPlugin plugin);

    AProView *pageActuelle();
    void NAV_LOAD(QUrl url,AProView *pageWeb);

    QMenu* getFileMenu();
    QMenu* getDisplayMenu();
    QMenu* getOptionMenu();
    QMenu* getHelpMenu();

    QStatusBar* getStatusBar();

    QList<QAction*> getToolBarActions();

    QAction* getPreviousAction();
    QAction* getForwardAction();
    QAction* getReloadAction();
    QAction* getStopAction();
    QAction* getHomeAction();
    QAction* getLoadAction();
    QAction* getHistoryAction();
    QAction* getFavoriteAddAction();

    QMovie* getLoadingMovie();

    AWebPluginFactory* getPluginFactory();

    QList<AProPlugin> getPlugins();

    signals :
    void quitNOW();
    void favSignal(const QString&,const QString&);

    protected :
    void paintEvent(QPaintEvent* event);

    void addNavigationBar();
    void addMenuBar();
    void addOngletsBar();
    void addDock();
    void addStatusBar();

    void setupNavigator();

    protected :

    void readHistoriqueData(QTreeWidget* tree);
    QList<FavoriElement> readFavorisData();

    protected :

    //Resources NAV

    QMenu *menuNav_Fichier;
    QMenu *menuNav_Affichage;
    QMenu *menuOption;
    QMenu *menuAide;

    QWidget* blankWidget;

    QAction *NAV_precedent;
    QAction *NAV_actualiser;
    QAction *NAV_suivant;
    QAction *NAV_stop;
    QAction *NAV_home;
    QAction *NAV_chargerPage;
    QAction *NAV_more;
    QAction *NAV_chercher;
    QAction *NAV_History_action;
    QAction *menuNav_Fichier_Options;
    QAction *menuNav_Affichage_AfficherHistorique;
    QAction *menuNav_Affichage_ZoomUp;
    QAction *menuNav_Affichage_ZoomDown;
    QAction *menuNav_Affichage_AfficherDownloads;
    QAction *NAV_favorisPlus;
    QAction* thisNormal;
    QAction* menuNav_Affichage_AfficherFavoris;

    QAction *menuFichier_Ouvrir;
    QAction *menuFichier_Quitter;
    QAction *menuOption_configurerLecteur;
    QAction *menuOption_configurerNavigateur;
    QAction *menuOption_configurerProg;
    QAction *menuAide_AProposQt;
    QAction *menuAide_AProposAPro;
    QAction *menuAide_AProposACorp;
    QActionGroup *languageGroup;
    QAction *langueFrancais;
    QAction *langueAnglais;
    QAction *langueAllemand;

    ATabWidget *NAV_Onglets;

    QStatusBar *Etat_NAV;

    QDockWidget *NAV_History;

    QToolBar *NAVToolBar;

    AdressBar *NAV_Adresse;
    QLineEdit *lineEdit_popup;
    searchLine *NAV_searchBar;

    QLabel *progression;

    QWebHistory *NAV_Historique;

    QVBoxLayout *NAV_layout_histo;
    QMovie* loading;
    QLabel chargement;

    QWidget *NAV_widget_histo;

    QComboBox *choixHistorique;

    QString page_accueil;

    QPushButton *NAV_boutonHistorique_vider;

    int i;
    bool historiqueappele;
    bool ongletTelechargementOuvert;
    bool compactModeEnable;
    bool progressBarInStatusBar;
    bool fullscreen;

    QUrl urlUtilise;
    QUrl urlImgUtilise;

    QProgressBar *barProgressionTelechargement;

    QList<QString> listeExtension;
    QList<FavButton*> listeFavoris;
    QList<AProPlugin> plugins;

    QString langue;
    QSettings *settings;
    QSettings *settingsLangue;

    fenetreOptions *OptionsNAV;
    QTreeWidget* treeWidget;

    AWebPluginFactory* pluginFactory;

};

class FavButton : public QAction
{
    Q_OBJECT

    public :
    FavButton(QObject* parent = 0);
    ~FavButton();

    QString url() const             { return URL; }
    void    setUrl(QString url)     { URL = url; }

    public slots :
    void emitCustomClick();

    signals :
    void customClick(QString);

    private :
    QString URL;
};

#endif //FENNAV_H
