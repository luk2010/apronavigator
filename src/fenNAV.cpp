#include "fenNAV.h"
#include "datafile.h"

#include "scriptengine.h"

#define sv settingsLangue->value(
#define vs ).toString()

fenNAV::fenNAV(QWidget *parent) : QMainWindow(parent)
{
    //Mise en place des variables
        historiqueappele = false;
        settings = new QSettings("conf/options.ini",QSettings::IniFormat);
        langue = "conf/"+settings->value("ALL/language","Francais").value<QString>() + ".ini";
        settingsLangue = new QSettings(langue,QSettings::IniFormat);
        page_accueil = "google.com";
        bool javaEnable = settings->value("WEB/javaEnable",true).value<bool>();
        if (javaEnable)
        {
            QWebSettings::globalSettings()->setAttribute(QWebSettings::AutoLoadImages,true);
            QWebSettings::globalSettings()->setAttribute(QWebSettings::JavascriptEnabled,true);
            QWebSettings::globalSettings()->setAttribute(QWebSettings::JavaEnabled,true);
        }
        bool pluginEnable = settings->value("WEB/pluginEnable",true).value<bool>();
        if (pluginEnable)
            QWebSettings::globalSettings()->setAttribute(QWebSettings::PluginsEnabled,true);
        QWebSettings::globalSettings()->setAttribute(QWebSettings::AutoLoadImages,true);
        compactModeEnable = settings->value("WEB/compactMode",true).value<bool>();
        QWebSettings::globalSettings()->setIconDatabasePath(QDir::tempPath());
        QWebSettings::globalSettings()->setAttribute(QWebSettings::DeveloperExtrasEnabled, true);

        ongletTelechargementOuvert = false;
        listeExtension << "exe" << "msi" << "gz" << "deb"
                       << "jpg" << "jpeg" << "ico" << "png"
                       << "rar" << "zip" << "iso"
                       << "torrent"
                       << "mp3" << "mp4" << "mkv" << "ogg" << "avi"
                       << "c" << "h" << "hpp" << "cpp" << "java";

        progressBarInStatusBar = settings->value("WEB/progressBarStatusbar",false).toBool();

        pluginFactory = new AWebPluginFactory(this);
}

fenNAV::~fenNAV()
{
   delete NAV_Onglets;
}

void fenNAV::NAV_ajouterTab(QUrl url)
{
    NAV_ajouterTab(url.toString());
}

void fenNAV::NAV_ajouterTab(QString url)
{
    QWidget *Onglet = new QWidget;
    AProView *pageWeb = new AProView(this);

    pageWeb->page()->setPluginFactory(pluginFactory);

    QVBoxLayout *layout = new QVBoxLayout;
        layout->addWidget(pageWeb);
    Onglet->setLayout(layout);

    int indexNouvelOnglet = NAV_Onglets->addTab(Onglet,"Nouvelle Page");

    if (url.isEmpty())
    {
    NAV_LOAD(QUrl("http://google.fr"),pageWeb);
    }
    else
    {
        if ((url.left(7) != "http://") && (url.left(8) != "https://" ))
        {
            url = "http://"+url;
        }
        NAV_LOAD(QUrl(url),pageWeb);
    }

    connect(pageWeb, SIGNAL(changerTitre(QString,AProView*)), this, SLOT(NAV_changementTitre(QString,AProView*)));
    connect(pageWeb,SIGNAL(changerIcon(QIcon,AProView*)),this,SLOT(changerIcone(QIcon,AProView*)));
    connect(pageWeb, SIGNAL(urlChanged(QUrl)), this, SLOT(NAV_changementUrl(QUrl)));
    connect(pageWeb, SIGNAL(webViewStatusMessage(QString)), this, SLOT(changeStatusBarMessage(QString)));
    connect(pageWeb, SIGNAL(loadProgress(int)), this, SLOT(NAV_progressionTelechargement(int)));

    NAV_Onglets->setCurrentIndex(indexNouvelOnglet);
}

AProView* fenNAV::NAV_AjouterTabNull()
{
    QWidget *Onglet = new QWidget;
    AProView *pageWeb = new AProView(this);

    pageWeb->page()->setPluginFactory(pluginFactory);

    QVBoxLayout *layout = new QVBoxLayout;
        layout->addWidget(pageWeb);
    Onglet->setLayout(layout);

    int indexNouvelOnglet = NAV_Onglets->addTab(Onglet,"Nouvelle Page");

    connect(pageWeb, SIGNAL(changerTitre(QString,AProView*)), this, SLOT(NAV_changementTitre(QString,AProView*)));
    connect(pageWeb,SIGNAL(changerIcon(QIcon,AProView*)),this,SLOT(changerIcone(QIcon,AProView*)));
    connect(pageWeb, SIGNAL(urlChanged(QUrl)), this, SLOT(NAV_changementUrl(QUrl)));
    connect(pageWeb, SIGNAL(webViewStatusMessage(QString)), this, SLOT(changeStatusBarMessage(QString)));
    connect(pageWeb, SIGNAL(loadProgress(int)), this, SLOT(NAV_progressionTelechargement(int)));

    NAV_Onglets->setCurrentIndex(indexNouvelOnglet);

    return pageWeb;
}

void fenNAV::NAV_supprimerTab(int index)
{
    if(NAV_Onglets->count() < 2)
        NAV_chargerPageAccueil();

    NAV_Onglets->removeTab(index);
}

void fenNAV::NAV_precedent_action()
{
    pageActuelle()->back();
}

void fenNAV::NAV_actualiser_action()
{
    pageActuelle()->reload();
}

void fenNAV::NAV_suivant_action()
{
    pageActuelle()->forward();
}

void fenNAV::NAV_stop_action()
{
    pageActuelle()->stop();
}

void fenNAV::NAV_chargerpage_action()
{
    QString adresse = NAV_Adresse->getLineEdit()->text();
    if ((adresse.left(7) != "http://") && (adresse.left(8) != "https://" ))
        {
            adresse = "http://"+adresse;
        }
    NAV_LOAD(QUrl(adresse),pageActuelle());

}

void fenNAV::NAV_ajouterHistoriqueItem(QString url,QString title)
{
    static QString url_precedent = "";
    if (url == url_precedent)
        return;
    else
        url_precedent = url;

    if(url.isEmpty() || title.isEmpty())
        return;

    DataFile dataFile;
    if(!dataFile.isValid())
    {
        QMessageBox::warning(this, "Error", "Le fichier de donnee est corrompue !");
        dataFile.rebuildData();
    }

    QDomElement historiqueElement = dataFile.getHistorique();
    if(historiqueElement.isNull())
    {
        QMessageBox::warning(this, "Error", "Impossible de toruver le noeud \"<historique>\" !");
        return;
    }

    if(historiqueElement.hasChildNodes())
        if(historiqueElement.firstChildElement().attribute(QString("url")) == url)
            return;

    QDomElement item = dataFile.getDocument().createElement(QString("adresse"));
    item.setAttribute("title", title);
    item.setAttribute("url", url);
    dataFile.addHistoriqueElement(item);

    dataFile.save();
}

void fenNAV::NAV_changementTitre(QString titrelong,AProView* view)
{
    QString titrecourt = titrelong;
    if (titrelong.size() > 40)
    {
        titrecourt = titrelong.left(40)+"...";
    }

    int index = -1;
    for (int i = 0; i < NAV_Onglets->count(); i++)
    {
        if (NAV_Onglets->widget(i)->findChild<AProView*>() == view)
            index = i;
    }

    if (index < 0)
        return;

    NAV_Onglets->setTabIcon(index,QIcon("icones/globe.png"));
    NAV_Onglets->setTabText(index,titrecourt);
}

void fenNAV::changerIcone(QIcon ic,AProView* view)
{
    int index = -1;
    for (int i = 0; i < NAV_Onglets->count(); i++)
    {
        if (NAV_Onglets->widget(i)->findChild<AProView*>() == view)
            index = i;
    }

    if (index < 0)
        return;

    NAV_Onglets->setTabIcon(index,ic);
}

void fenNAV::NAV_changementUrl(QUrl url)
{
    NAV_Adresse->getLineEdit()->setText(url.toString());
    NAV_Adresse->setWebView(pageActuelle());
    NAV_Adresse->changeIcon();

    NAV_Adresse->repaint();
}

void fenNAV::NAV_changementOnglet(int index)
{
    NAV_changementUrl(pageActuelle()->url());
}

void fenNAV::NAV_chargerPageAccueil()
{
    NAV_ajouterTab(page_accueil);
}

void fenNAV::NAV_rechercher_pressed()
{
    QString recherche = "http://google.com/search?hl=fr&q="+NAV_searchBar->lineEdit()->text();
    QUrl url_googlerecherche(recherche);
    NAV_LOAD(url_googlerecherche,pageActuelle());
}

void fenNAV::NAV_AfficherHistorique(bool afficher)
{
    if (afficher)
    {
        if (menuNav_Affichage_AfficherHistorique->isChecked())
            NAV_History_action->setChecked(true);
        if (NAV_History_action->isChecked())
            menuNav_Affichage_AfficherHistorique->setChecked(true);

        treeWidget = new QTreeWidget();
        treeWidget->setColumnCount(2);
        treeWidget->setHeaderHidden(true);
        treeWidget->setUniformRowHeights(true);
        treeWidget->setEditTriggers(QTreeWidget::NoEditTriggers);
        treeWidget->setSelectionBehavior(QTreeWidget::SelectRows);
        treeWidget->setColumnWidth(0,200);
        treeWidget->setFrameStyle(QFrame::Panel | QFrame::Plain);
        treeWidget->setRootIsDecorated(false);

        readHistoriqueData(treeWidget);

        NAV_boutonHistorique_vider = new QPushButton("Vider");

        NAV_layout_histo = new QVBoxLayout;
        NAV_layout_histo->addWidget(NAV_boutonHistorique_vider);
        NAV_layout_histo->addWidget(treeWidget);

        NAV_widget_histo = new QWidget;
        NAV_widget_histo->setLayout(NAV_layout_histo);

        NAV_History->setWidget(NAV_widget_histo);
        NAV_History->setVisible(true);

        connect(NAV_boutonHistorique_vider,SIGNAL(pressed()),this,SLOT(NAV_viderHistorique()));
        connect(pageActuelle(),SIGNAL(urlChanged(QUrl)),this,SLOT(NAV_MAJHistorique(QUrl)));
        connect(treeWidget,SIGNAL(itemDoubleClicked(QTreeWidgetItem*,int)),this,SLOT(NAV_chargerHistoriqueItem(QTreeWidgetItem*,int)));
    }
    else
    {
        NAV_History->setVisible(false);
        NAV_History_action->setChecked(false);
        menuNav_Affichage_AfficherHistorique->setChecked(false);
    }
}

void fenNAV::NAV_MAJHistorique(QUrl url)
{
        NAV_layout_histo->removeWidget(treeWidget);

        treeWidget = new QTreeWidget();
        treeWidget->setColumnCount(2);
        treeWidget->setHeaderHidden(true);
        treeWidget->setUniformRowHeights(true);
        treeWidget->setEditTriggers(QTreeWidget::NoEditTriggers);
        treeWidget->setSelectionBehavior(QTreeWidget::SelectRows);
        treeWidget->setColumnWidth(0,200);
        treeWidget->setFrameStyle(QFrame::Panel | QFrame::Plain);
        treeWidget->setRootIsDecorated(false);

        readHistoriqueData(treeWidget);

        NAV_layout_histo->addWidget(treeWidget);
        NAV_widget_histo = new QWidget;
        NAV_widget_histo->setLayout(NAV_layout_histo);

        NAV_History->setWidget(NAV_widget_histo);
        if (menuNav_Affichage_AfficherHistorique->isChecked())
        NAV_History->setVisible(true);

        connect(pageActuelle(),SIGNAL(urlChanged(QUrl)),this,SLOT(NAV_MAJHistorique(QUrl)));
        connect(treeWidget,SIGNAL(itemDoubleClicked(QTreeWidgetItem*,int)),this,SLOT(NAV_chargerHistoriqueItem(QTreeWidgetItem*,int)));
}

void fenNAV::NAV_afficherOption()
{
    OptionsNAV = new fenetreOptions("Options du Navigateur",settings,this);
    OptionsNAV->show();
    connect(OptionsNAV,SIGNAL(reloadToolBar()),this,SLOT(loadToolBarPosition()));
    connect(OptionsNAV,SIGNAL(changeHome(QString)),this,SLOT(changePageAccueil(QString)));
    connect(OptionsNAV,SIGNAL(seeProgressStatusBar(bool)),this,SLOT(seeProgressStatusBar(bool)));
    connect(OptionsNAV,SIGNAL(changeTaskBarVisibility(bool)),Etat_NAV,SLOT(setVisible(bool)));
}

void fenNAV::NAV_chargerHistoriqueItem(QTreeWidgetItem* item, int column)
{
    NAV_ajouterTab(item->text(1));
    NAV_Adresse->getLineEdit()->setText(item->text(1));
    NAV_chargerpage_action();
}

AProView *fenNAV::pageActuelle()
{
   return NAV_Onglets->currentWidget()->findChild<AProView *>();
}

void fenNAV::NAV_LOAD(QUrl url,AProView *pageWeb)
{
    pageWeb->load(url);
    pageWeb->page()->setForwardUnsupportedContent(true);
    connect(pageWeb,SIGNAL(ajouterTab(QUrl)),this,SLOT(NAV_ajouterTab(QUrl)));
}

void fenNAV::NAV_progressionTelechargement(int per)
{
    trierLoading();
}

void fenNAV::NAV_viderHistorique()
{
    DataFile dataFile;
    if(!dataFile.isValid())
    {
        QMessageBox::warning(this, "Error", "Le fichier de donnee est corrompue !");
        dataFile.rebuildData();
        dataFile.save();

        NAV_MAJHistorique();
        return;
    }

    QDomElement historiqueElement = dataFile.getHistorique();
    if(historiqueElement.isNull())
    {
        QMessageBox::warning(this, "Error", "Impossible de toruver le noeud \"<historique>\" !");

        NAV_MAJHistorique();
        return;
    }

    while(historiqueElement.childNodes().count() > 0)
        historiqueElement.removeChild(historiqueElement.firstChild());

    dataFile.save();

    NAV_MAJHistorique();
}

void fenNAV::NAV_ZOOMUP()
{
    pageActuelle()->setZoomFactor(pageActuelle()->zoomFactor()+0.05);
}

void fenNAV::NAV_ZOOMDOWN()
{
    pageActuelle()->setZoomFactor(pageActuelle()->zoomFactor()-0.05);
}

void fenNAV::setUrl(QUrl url)
{
    urlUtilise = url;
}

void fenNAV::setUrlImg(QUrl img)
{
    urlImgUtilise = img;
}

void fenNAV::afficherDownloads()
{
    getGT->afficherTelechargements();
}

void fenNAV::afficherLesFavoris()
{
    QList<QAction*> listActions = NAVToolBar->actions();
    for (int i = 13; i < listActions.count(); i++)
        NAVToolBar->removeAction(listActions[i]);

    QList <FavoriElement> listeElement = readFavorisData();
    for (int i = 0; i < listeElement.count(); i++)
    {
        FavButton* newButton = new FavButton;
        newButton->setText(listeElement[i].title);
        newButton->setUrl(listeElement[i].url);
        NAVToolBar->addAction(newButton);
        listeFavoris.prepend(newButton);
        connect(newButton,SIGNAL(triggered()),newButton,SLOT(emitCustomClick()));
        connect(newButton,SIGNAL(customClick(QString)),this,SLOT(NAV_ajouterTab(QString)));
    }
}

void fenNAV::afficherFenetreFavoris()
{
    AFavoris* fav = new AFavoris;
    fav->show();

    connect(fav,SIGNAL(reloadTabBar()),this,SLOT(afficherLesFavoris()));
}

void fenNAV::paintEvent(QPaintEvent* event)
{
    NAV_Adresse->setMinimumWidth((NAVToolBar->width())-(NAVToolBar->widgetForAction(NAV_precedent)->width()*11+chargement.width()+NAV_searchBar->width()));
    QMainWindow::paintEvent(event);
}

void fenNAV::loadToolBarPosition()
{
    int tabBarPosition = settings->value("WEB/tabBarPosition").toInt();
    Qt::ToolBarArea toolBarArea = Qt::BottomToolBarArea;
    switch (tabBarPosition)
    {
        case 0 :
        toolBarArea = Qt::TopToolBarArea;
        break;

        case 1 :
        toolBarArea = Qt::BottomToolBarArea;
        break;

        case 2 :
        toolBarArea = Qt::LeftToolBarArea;
        break;

        case 3 :
        toolBarArea = Qt::RightToolBarArea;
        break;
    }
    removeToolBar(NAVToolBar);
    addToolBar(toolBarArea,NAVToolBar);
    NAVToolBar->setVisible(true);
}

void fenNAV::trierLoading()
{
    static int before = 0;
    AProView* currentView = pageActuelle();
    if (currentView->loadingStatus() == before)
        return;

    if (currentView->loadStart())
    {
        switch(currentView->loadingStatus())
        {
            case -1 :
            Etat_NAV->showMessage("Erreur dans la page.",20000);
            break;

            case 0 :
            loading->start();
            NAV_stop->setEnabled(true);

            case 100 :
            loading->stop();
            NAV_stop->setEnabled(false);
        }
        if (currentView->loadingStatus() >= 50)
        NAV_ajouterHistoriqueItem(currentView->url().toString(),currentView->title());
    }
    else
    {
        loading->stop();
        NAV_stop->setEnabled(false);
    }
    before = currentView->loadingStatus();
}

void fenNAV::toggleFullscreen()
{
    if(fullscreen)
    {
        showMaximized();

        thisNormal->setText("Plein Ecran");
    }
    else
    {
        showFullScreen();

        thisNormal->setText("Mode Fenetre");
    }

    fullscreen = !fullscreen;
}

void fenNAV::addFavorisPopup()
{
    QWidget* popup = new QWidget;
    popup->setWindowFlags(Qt::Popup);
    QHBoxLayout* hLayout = new QHBoxLayout;
    popup->setLayout(hLayout);

    lineEdit_popup = new QLineEdit;
    lineEdit_popup->setText(pageActuelle()->title());
    hLayout->addWidget(lineEdit_popup);

    QPushButton* valid = new QPushButton("");
    valid->setIcon(QIcon("icones/valid.png"));
    hLayout->addWidget(valid);

    popup->move(NAVToolBar->widgetForAction(NAV_favorisPlus)->mapToGlobal(QPoint(0,NAVToolBar->widgetForAction(NAV_favorisPlus)->height())));
    popup->show();

    connect(valid,SIGNAL(clicked()),this,SLOT(emitCustomSignal()));
    connect(lineEdit_popup,SIGNAL(returnPressed()),this,SLOT(emitCustomSignal()));
}

void fenNAV::activateStaticSlotFav(const QString &n, const QString &u)
{
    AFavoris::addNewFavoris(n,u);
    afficherLesFavoris();
}

void fenNAV::emitCustomSignal()
{
    emit favSignal(lineEdit_popup->text(),pageActuelle()->url().toString());
}

void fenNAV::changeStatusBarMessage(QString msg)
{
    statusBar()->showMessage(msg);
}

void fenNAV::addNavigationBar()
{
    int tabBarPosition = settings->value("WEB/tabBarPosition").toInt();
    Qt::ToolBarArea toolBarArea = Qt::BottomToolBarArea;
    switch (tabBarPosition)
    {
        case 0 :
        toolBarArea = Qt::TopToolBarArea;
        break;

        case 1 :
        toolBarArea = Qt::BottomToolBarArea;
        break;

        case 2 :
        toolBarArea = Qt::LeftToolBarArea;
        break;

        case 3 :
        toolBarArea = Qt::RightToolBarArea;
        break;
    }

    NAVToolBar = new QToolBar(sv"NAVToolBar"vs);
    addToolBar(toolBarArea,NAVToolBar);
    NAVToolBar->setFloatable(false);
    NAVToolBar->setMovable(false);
        NAV_precedent = NAVToolBar->addAction(QIcon("icones/previous.png"),sv"NAV_precedent"vs);
        NAV_actualiser = NAVToolBar->addAction(QIcon("icones/reload.png"),sv"NAV_actualiser"vs);
        NAV_suivant = NAVToolBar->addAction(QIcon("icones/forward.png"),sv"NAV_suivant"vs);
        NAV_stop = NAVToolBar->addAction(QIcon("icones/stop.png"),sv"NAV_stop"vs);
        NAV_home = NAVToolBar->addAction(QIcon("icones/hibernate.png"),sv"NAV_home"vs);
        NAV_more = new QAction(QIcon("icones/tab_new.png"),sv"NAV_more"vs,0);
        NAV_more->setShortcut(QKeySequence("Ctrl+n"));
        NAV_favorisPlus = NAVToolBar->addAction(QIcon("icones/favoris_plus.png"),"Ajouter aux favoris");
        NAV_Adresse = new AdressBar;
        NAV_Adresse->setSizePolicy(QSizePolicy::Expanding,QSizePolicy::Maximum);
            NAVToolBar->addWidget(NAV_Adresse);
        loading = new QMovie("icones/loading.gif");
        chargement.setMovie(loading);
        NAVToolBar->addWidget(&chargement);
        NAV_chargerPage = NAVToolBar->addAction(QIcon("icones/autostart.png"),sv"NAV_chargerPage"vs);
        NAV_searchBar = new searchLine(NAVToolBar);
            NAV_searchBar->setMaximumWidth(100);
            NAV_searchBar->setMinimumWidth(100);
            NAV_searchBar->lineEdit()->setPlaceholderText("Google...");
            NAVToolBar->addWidget(NAV_searchBar);
        NAV_chercher = NAVToolBar->addAction(QIcon("icones/search.png"),sv"NAV_chercher"vs);
        NAV_History_action = NAVToolBar->addAction(QIcon("icones/history.png"),sv"NAV_History_action"vs);
            NAV_History_action->setCheckable(true);
        NAV_Adresse->setMinimumWidth((NAVToolBar->width())-(NAVToolBar->widgetForAction(NAV_precedent)->width()*9+chargement.width()+NAV_searchBar->width()));
        blankWidget = new QWidget;
        blankWidget->setMinimumWidth(300);
        blankWidget->setSizePolicy(QSizePolicy::Expanding,QSizePolicy::Preferred);
        NAVToolBar->addWidget(blankWidget);
        afficherLesFavoris();

    // Connexions

    connect(NAV_more,SIGNAL(triggered()),this,SLOT(NAV_ajouterTab()));
    connect(NAV_precedent,SIGNAL(triggered()),this,SLOT(NAV_precedent_action()));
    connect(NAV_suivant,SIGNAL(triggered()),this,SLOT(NAV_suivant_action()));
    connect(NAV_actualiser,SIGNAL(triggered()),this,SLOT(NAV_actualiser_action()));
    connect(NAV_stop,SIGNAL(triggered()),this,SLOT(NAV_stop_action()));
    connect(NAV_Adresse->getLineEdit(),SIGNAL(returnPressed()),this,SLOT(NAV_chargerpage_action()));
    connect(NAV_chargerPage,SIGNAL(triggered()),this,SLOT(NAV_chargerpage_action()));
    connect(NAV_home,SIGNAL(triggered()),this,SLOT(NAV_chargerPageAccueil()));
    connect(NAV_searchBar,SIGNAL(returnPressed()),this,SLOT(NAV_rechercher_pressed()));
    connect(NAV_chercher,SIGNAL(triggered()),this,SLOT(NAV_rechercher_pressed()));
    connect(NAV_History_action,SIGNAL(toggled(bool)),this,SLOT(NAV_AfficherHistorique(bool)));
    connect(NAV_favorisPlus,SIGNAL(triggered()),this,SLOT(addFavorisPopup()));
}

void fenNAV::addMenuBar()
{
    menuBar()->setStyle(new QCleanlooksStyle());

    menuNav_Fichier = menuBar()->addMenu(sv"menuNav_Fichier"vs);

        menuFichier_Ouvrir = menuNav_Fichier->addAction(QIcon("icones/ouvrir_musique.png"),sv"Ouvrir"vs);
            menuFichier_Ouvrir->setShortcut(tr("Ctrl+o"));

        menuNav_Fichier->addSeparator();

        menuNav_Fichier->addAction(NAV_precedent);
        menuNav_Fichier->addAction(NAV_actualiser);
        menuNav_Fichier->addAction(NAV_suivant);

        menuNav_Fichier->addSeparator();

        QAction* extractVideos = menuNav_Fichier->addAction(tr("Extraire les videos"));
        QAction* extractMusics = menuNav_Fichier->addAction(tr("Extraire les musiques"));

        menuNav_Fichier->addSeparator();

        menuNav_Fichier->addAction(NAV_more);
        menuNav_Fichier_Options = menuNav_Fichier->addAction(QIcon("icones/run.png"),sv"menuNav_Fichier_Options"vs);

        menuNav_Fichier->addSeparator();

        menuFichier_Quitter = menuNav_Fichier->addAction(settingsLangue->value("menuFichier_Quitter").value<QString>());
            menuFichier_Quitter->setIcon(QIcon("icones/quitter.png"));
            menuFichier_Quitter->setShortcut(tr("Ctrl+q"));

    menuNav_Affichage = menuBar()->addMenu(sv"menuNav_Affichage"vs);

        menuNav_Affichage_AfficherHistorique = menuNav_Affichage->addAction(QIcon("icones/history.png"),sv"menuNav_Affichage_AfficherHistorique"vs);
            menuNav_Affichage_AfficherHistorique->setCheckable(true);
            menuNav_Affichage_AfficherHistorique->setShortcut(QString("Ctrl+h"));

        menuNav_Affichage_AfficherDownloads = menuNav_Affichage->addAction(QIcon("icones/histo_down.png"),sv"Historique_téléchargements"vs);
        menuNav_Affichage_AfficherFavoris = menuNav_Affichage->addAction(QIcon("icones/favoris.png"),"Favoris");

        menuNav_Affichage_ZoomUp = menuNav_Affichage->addAction(QIcon("icones/viewmag+.png"),"Zoom +");
            menuNav_Affichage_ZoomUp->setShortcut(QString("Ctrl+d"));

        menuNav_Affichage_ZoomDown = menuNav_Affichage->addAction(QIcon("icones/viewmag-.png"),"Zoom -");
            menuNav_Affichage_ZoomDown->setShortcut(QString("Ctrl+s"));

        menuNav_Affichage->addSeparator();

        thisNormal = menuNav_Affichage->addAction("Plein Ecran");
            thisNormal->setShortcut(QString("F12"));
            fullscreen = false;

        menuOption = menuBar()->addMenu(settingsLangue->value("menuOption").value<QString>());
            QMenu *menuOption_menuLangue = menuOption->addMenu(sv"menuOption_menuLangue"vs);
                langueFrancais = menuOption_menuLangue->addAction(sv"langueFrancais"vs);
                    langueFrancais->setCheckable(true);
                langueAnglais = menuOption_menuLangue->addAction(sv"langueAnglais"vs);
                    langueAnglais->setCheckable(true);
                langueAllemand = menuOption_menuLangue->addAction(sv"langueAllemand"vs);
                    langueAllemand->setCheckable(true);
                languageGroup = new QActionGroup(0);
                    languageGroup->addAction(langueFrancais);
                    languageGroup->addAction(langueAnglais);
                    languageGroup->addAction(langueAllemand);
                if (langue == "conf/Francais.ini")
                    langueFrancais->setChecked(true);
                else if (langue == "conf/Anglais.ini")
                    langueAnglais->setChecked(true);
                else if (langue == "conf/Allemand.ini")
                    langueAllemand->setChecked(true);

            menuOption_configurerLecteur = menuOption->addAction(sv"menuOption_configurerLecteur"vs);
            menuOption_configurerNavigateur = menuOption->addAction(QIcon("icones/web.png"),sv"menuOption_configurerNavigateur"vs);

        menuAide = menuBar()->addMenu(settingsLangue->value("menuAide").value<QString>());
            menuAide_AProposQt = menuAide->addAction(QIcon("icones/qt_about.png"),sv"menuAide_AProposQt"vs);
            menuAide_AProposAPro = menuAide->addAction(sv"menuAide_AProposApro"vs);
            menuAide_AProposACorp = menuAide->addAction("A propos de Atlanti's Corporation");

    connect(menuNav_Affichage_AfficherHistorique,SIGNAL(toggled(bool)),this,SLOT(NAV_AfficherHistorique(bool)));
    connect(menuNav_Fichier_Options,SIGNAL(triggered()),this,SLOT(NAV_afficherOption()));
    connect(menuNav_Affichage_ZoomDown, SIGNAL(triggered()),this,SLOT(NAV_ZOOMDOWN()));
    connect(menuNav_Affichage_ZoomUp, SIGNAL(triggered()), this, SLOT(NAV_ZOOMUP()));
    connect(menuNav_Affichage_AfficherDownloads, SIGNAL(triggered()),this,SLOT(afficherDownloads()));
    connect(thisNormal,SIGNAL(triggered()),this,SLOT(toggleFullscreen()));
    connect(menuNav_Affichage_AfficherFavoris,SIGNAL(triggered()),this,SLOT(afficherFenetreFavoris()));
    connect(extractVideos, SIGNAL(triggered()), this, SLOT(extractVideosFromPage()));
    connect(extractMusics, SIGNAL(triggered()), this, SLOT(extractMusicsFromPage()));
}

void fenNAV::addOngletsBar()
{
    NAV_Onglets = new ATabWidget;
    setCentralWidget(NAV_Onglets);
    NAV_Onglets->setTabsClosable(true);
    NAV_Onglets->tabBar()->setMovable(true);

    connect(NAV_Onglets,SIGNAL(tabCloseRequested(int)),this,SLOT(NAV_supprimerTab(int)));
    connect(NAV_Onglets, SIGNAL(currentChanged(int)), this, SLOT(NAV_changementOnglet(int)));
}

void fenNAV::addDock()
{
    NAV_History = new QDockWidget(sv"NAV_History"vs,this);
    NAV_History->setAllowedAreas(Qt::LeftDockWidgetArea|Qt::RightDockWidgetArea);
    NAV_History->setFeatures(QDockWidget::DockWidgetMovable|QDockWidget::DockWidgetFloatable);
    addDockWidget(Qt::LeftDockWidgetArea,NAV_History);
    NAV_History->setVisible(false);
}

void fenNAV::addStatusBar()
{
    Etat_NAV = statusBar();
        Etat_NAV->showMessage("Prêt",2000);
        Etat_NAV->setContentsMargins(0,0,10,10);
        progression = new QLabel("Début du chargement",Etat_NAV);
        Etat_NAV->addPermanentWidget(progression);
        progression->setVisible(false);
    barProgressionTelechargement = new QProgressBar(Etat_NAV);
        Etat_NAV->addPermanentWidget(barProgressionTelechargement);
        barProgressionTelechargement->setVisible(false);
}

void fenNAV::setupNavigator()
{
    addNavigationBar();
    addMenuBar();
    addOngletsBar();
    addDock();
    addStatusBar();

    connect(this,SIGNAL(favSignal(QString,QString)),this,SLOT(activateStaticSlotFav(QString,QString)));
    NAV_ajouterTab();
}

void fenNAV::extractVideosFromPage()
{
    AProView* view = pageActuelle();

    if(view != NULL)
    {
        QWebPage* page = view->page();

        if(page != NULL)
        {
            QWebFrame* mainFrame = page->mainFrame();

            if(mainFrame != NULL)
            {
                QListWidget* listWidget = new QListWidget(NULL);
                int videosCount = 0;

                // Test de la balise <embed>
                QWebElementCollection elementCollection = mainFrame->findAllElements(QString("embed"));
                if(elementCollection.count() > 0)
                {
                    foreach(QWebElement element, elementCollection)
                    {
                        QString src = element.attribute("src");

                        if(!src.isEmpty())
                        {
                            if(!src.contains("http://"))
                            {
                                src.prepend(QString("http://") + QString(view->url().authority()) + view->url().path());
                            }

                            QListWidgetItem* item = new QListWidgetItem(listWidget);
                            item->setText(src);

                            listWidget->addItem(item);
                            videosCount++;
                        }
                    }
                }

                // Test de la balise <video> et des enfants <source>
                elementCollection = mainFrame->findAllElements(QString("video"));
                if(elementCollection.count() > 0)
                {
                    foreach(QWebElement element, elementCollection)
                    {
                        QString src = element.attribute("src");
                        if(!src.isEmpty())
                        {
                            if(!src.contains("http://"))
                            {
                                src.prepend(QString("http://") + QString(view->url().authority()) + view->url().path());
                            }

                            QListWidgetItem* item = new QListWidgetItem(listWidget);
                            item->setText(src);

                            listWidget->addItem(item);
                            videosCount++;
                        }
                        else
                        {
                            QWebElementCollection srcCollection = element.findAll(QString("source"));
                            if(srcCollection.count() > 0)
                            {
                                foreach(QWebElement child, srcCollection)
                                {
                                    QString src2 = child.attribute("src");
                                    if(!src2.isEmpty())
                                    {
                                        if(!src2.contains("http://"))
                                        {
                                            src2.prepend(QString("http://") + QString(view->url().authority()) + view->url().path());
                                        }

                                        QListWidgetItem* item = new QListWidgetItem(listWidget);
                                        item->setText(src2);

                                        listWidget->addItem(item);
                                        videosCount++;
                                    }
                                }
                            }
                        }
                    }
                }

                if(videosCount > 0)
                {
                    QMessageBox::information(this, "Cool", QString("Found ") + QString::number(videosCount) + " videos !");

                    listWidget->show();
                    connect(listWidget, SIGNAL(itemDoubleClicked(QListWidgetItem*)), this, SLOT(addDownloadFromItem(QListWidgetItem*)));
                }
                else
                {
                    QMessageBox::warning(this, "Sorry", QString("No videos found in this page !"));
                }

            }
            else
            {
                QMessageBox::warning(this, "Error", "Can't Find Main Frame !");
            }
        }
        else
        {
            QMessageBox::warning(this, "Error", "No Page opened !");
        }
    }
    else
    {
        QMessageBox::warning(this, "Error", "No Page opened !");
    }
}

void fenNAV::extractMusicsFromPage()
{
    QMessageBox::information(this, "Sorry", "Extraction of music from video isn't supported yet !");
}

void fenNAV::addDownloadFromItem(QListWidgetItem *item)
{
    pageActuelle()->downloadElement(QUrl(item->text()));
}

void fenNAV::readHistoriqueData(QTreeWidget *tree)
{
    DataFile dataFile;
    if(!dataFile.isValid())
    {
        QMessageBox::warning(this, "Error", "Le fichier de donnee est corrompue !");
        dataFile.rebuildData();
    }

    QDomElement historiqueElement = dataFile.getHistorique();
    if(historiqueElement.isNull())
    {
        QMessageBox::warning(this, "Error", "Impossible de toruver le noeud \"<historique>\" !");
    }

    QDomNodeList nodeList = historiqueElement.elementsByTagName(QString("adresse"));
    for(int i = 0; i < nodeList.count(); i++)
    {
        QDomElement element = nodeList.at(i).toElement();

        QTreeWidgetItem* item = new QTreeWidgetItem();
        item->setText(0, element.attribute("title"));
        item->setText(1, element.attribute("url"));

        tree->insertTopLevelItem(0,item);
    }
}

QList<FavoriElement> fenNAV::readFavorisData()
{
    DataFile dataFile;
    if(!dataFile.isValid())
    {
        QMessageBox::warning(this, "Error", "Le fichier de donnee est corrompue !");
        dataFile.rebuildData();
        dataFile.save();
    }

    QDomElement favorisElement = dataFile.getFavoris();
    if(favorisElement.isNull())
    {
        QMessageBox::warning(this, "Error", "Impossible de toruver le noeud \"<favoris>\" !");
        return QList<FavoriElement>();
    }

    QList <FavoriElement> listeElement;
    listeFavoris.clear();

    QDomElement element = favorisElement.firstChildElement("adresse");
    while (!element.isNull())
    {
        FavoriElement newElement;
        newElement.title = element.attribute("title","");
        newElement.url   = element.attribute("url","");
        listeElement.prepend(newElement);

        element = element.nextSiblingElement("adresse");
    }

    return listeElement;
}

QMenu* fenNAV::getFileMenu()
{
    return menuNav_Fichier;
}

QMenu* fenNAV::getDisplayMenu()
{
    return menuNav_Affichage;
}

QMenu* fenNAV::getOptionMenu()
{
    return menuOption;
}

QMenu* fenNAV::getHelpMenu()
{
    return menuAide;
}

QStatusBar* fenNAV::getStatusBar()
{
    return Etat_NAV;
}

QList<QAction*> fenNAV::getToolBarActions()
{
    QList<QAction*> list;

    list << NAV_precedent
    << NAV_actualiser
    << NAV_suivant
    << NAV_stop
    << NAV_home
    << NAV_chargerPage
    << NAV_more
    << NAV_chercher
    << NAV_History_action
    << NAV_favorisPlus;

    return list;
}

QAction* fenNAV::getPreviousAction()
{
    return NAV_precedent;
}

QAction* fenNAV::getForwardAction()
{
    return NAV_suivant;
}

QAction* fenNAV::getReloadAction()
{
    return NAV_actualiser;
}

QAction* fenNAV::getStopAction()
{
    return NAV_stop;
}

QAction* fenNAV::getHomeAction()
{
    return NAV_home;
}

QAction* fenNAV::getLoadAction()
{
    return NAV_chargerPage;
}

QAction* fenNAV::getHistoryAction()
{
    return NAV_History_action;
}

QAction* fenNAV::getFavoriteAddAction()
{
    return NAV_favorisPlus;
}

QMovie* fenNAV::getLoadingMovie()
{
    return loading;
}

AWebPluginFactory* fenNAV::getPluginFactory()
{
    return pluginFactory;
}

void fenNAV::registerPlugin(AProPlugin plugin)
{
    plugins.append(plugin);
}

QList<AProPlugin> fenNAV::getPlugins()
{
    return plugins;
}

//!------------------------------------------!//
//!------------------------------------------!//
//!------------------------------------------!//
//!------------------------------------------!//
//!--------------- FAVBUTTON ----------------!//
//!------------------------------------------!//
//!------------------------------------------!//
//!------------------------------------------!//
//!------------------------------------------!//

FavButton::FavButton(QObject* parent) : QAction(parent)
{
}

FavButton::~FavButton()
{
}

void FavButton::emitCustomClick()
{
    emit customClick(URL);
}
