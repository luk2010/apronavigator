#include "fenetreOptions.h"

fenetreOptions::fenetreOptions(QString titre,QSettings *settings,fenNAV *parent)
 : QWidget(0)
{
    up = parent;
    settingsOption = new QSettings("conf/options.ini",QSettings::IniFormat);
    javaEnable = false;
    pluginEnable = false;

    setWindowTitle(titre);
    setMinimumWidth(400);
    setMaximumWidth(400);

    //Layout pour les options
    layout_principal = new QHBoxLayout;
    layout_principal->setMargin(0);
    layout_principal->setSpacing(0);
    setLayout(layout_principal);

    QGroupBox *groupedeslisteview = new QGroupBox(tr(""));
    QVBoxLayout *vboxlayout = new QVBoxLayout;

    QPixmap imgGeneral("icones/pref_general.png");
    QPixmap imgAvance("icones/pref_avance.png");
    QPixmap imgSecurite("icones/pref_securite.png");

    QPushButton* boutonGeneral_NAV = new QPushButton;
        boutonGeneral_NAV->setFlat(true);
        boutonGeneral_NAV->setIcon(imgGeneral);
        boutonGeneral_NAV->setIconSize(imgGeneral.size());
    QPushButton* boutonAvance_NAV = new QPushButton;
        boutonAvance_NAV->setFlat(true);
        boutonAvance_NAV->setIcon(imgAvance);
        boutonAvance_NAV->setIconSize(imgAvance.size());
    QPushButton* boutonSecurite_NAV = new QPushButton;
        boutonSecurite_NAV->setFlat(true);
        boutonSecurite_NAV->setIcon(imgSecurite);
        boutonSecurite_NAV->setIconSize(imgSecurite.size());

    vboxlayout->addWidget(boutonGeneral_NAV);
    vboxlayout->addWidget(boutonAvance_NAV);
    vboxlayout->addWidget(boutonSecurite_NAV);
    groupedeslisteview->setLayout(vboxlayout);
    groupedeslisteview->setMaximumWidth(100);

    layoutPrincipalAvanceWidget_NAV = new QWidget(this);
    layoutPrincipalGeneralWidget_NAV = new QWidget;
    layoutPrincipalSecuriteWidget_NAV = new QWidget;

    chargerGeneral_NAV();
    chargerAvance_NAV();
    chargerSecurite_NAV();

    layout_principal->addWidget(groupedeslisteview);
    layout_principal->addWidget(layoutPrincipalGeneralWidget_NAV);
    layout_principal->addWidget(layoutPrincipalAvanceWidget_NAV);
    layout_principal->addWidget(layoutPrincipalSecuriteWidget_NAV);

    layoutPrincipalGeneralWidget_NAV->setVisible(true);
    layoutPrincipalAvanceWidget_NAV->setVisible(false);
    layoutPrincipalSecuriteWidget_NAV->setVisible(false);

    connect(boutonGeneral_NAV,SIGNAL(pressed()),this,SLOT(chargerGeneralAction_NAV()));
    connect(boutonAvance_NAV,SIGNAL(pressed()),this,SLOT(chargerAvanceAction_NAV()));
    connect(boutonSecurite_NAV,SIGNAL(pressed()),this,SLOT(chargerSecuriteAction_NAV()));
}

fenetreOptions::~fenetreOptions()
{
}

void fenetreOptions::showEvent(QShowEvent *event)
{
   Q_UNUSED(event);
   CenterOnScreen();
}

void fenetreOptions::CenterOnScreen()
{
    QDesktopWidget screen;
    QRect screenGeom = screen.screenGeometry(this);
    int screenCenterX = screenGeom.center().x();
    int screenCenterY = screenGeom.center().y();
    move(screenCenterX - width()/2,screenCenterY- width()/2);
}

void fenetreOptions::chargerGeneral_NAV()
{
    layoutPrincipalGeneral_NAV = new QVBoxLayout;

    QGroupBox* groupBox = new QGroupBox("Propriétés Générales");

    checkJavaEnable = new ASwitchButton("Activation de Java");
        checkJavaEnable->setChecked(settingsOption->value("WEB/javaEnable").toBool());
    checkPluginEnable = new ASwitchButton("Activation des Plug-ins (Adobe Flash, etc...)");
        checkPluginEnable->setChecked(settingsOption->value("WEB/pluginEnable").toBool());
    checkModeEnable = new ASwitchButton("Mode Compact ( 1 seul téléchargement )");
        checkModeEnable->setChecked(settingsOption->value("WEB/compactMode").toBool());

    QLabel* label_pageacceuil = new QLabel(tr("Page d'acceuil : "));
    pageAccueil = new QLineEdit(settingsOption->value("WEB/pageAccueil","http://google.com").toString());
    currentPage = new QPushButton("Page Actuelle");
        connect(currentPage,SIGNAL(pressed()),this,SLOT(getCurrentPage()));
    QHBoxLayout* hlayout2 = new QHBoxLayout;
        hlayout2->addWidget(label_pageacceuil);
        hlayout2->addWidget(pageAccueil);
        hlayout2->addWidget(currentPage);

    tabBarPosition = new QComboBox;
        tabBarPosition->addItem(tr("Haut"),Qt::DisplayRole);
        tabBarPosition->addItem(tr("Bas"),Qt::DisplayRole);
        tabBarPosition->addItem(tr("Gauche"),Qt::DisplayRole);
        tabBarPosition->addItem(tr("Droite"),Qt::DisplayRole);
        tabBarPosition->setCurrentIndex(settingsOption->value("WEB/tabBarPosition").toInt());
    QLabel* titre_tabBarPosition = new QLabel("Position de la barre d'outils : ");
    QHBoxLayout* hlayout = new QHBoxLayout();
        hlayout->addWidget(titre_tabBarPosition);
        hlayout->addWidget(tabBarPosition);

    QVBoxLayout* vBox = new QVBoxLayout;
        vBox->addWidget(checkJavaEnable);
        vBox->addWidget(checkPluginEnable);
        vBox->addWidget(checkModeEnable);
        vBox->addStretch(1);
        vBox->addLayout(hlayout2);
        vBox->addLayout(hlayout);
    groupBox->setLayout(vBox);

    layoutPrincipalGeneral_NAV->addWidget(groupBox);
    layoutPrincipalGeneralWidget_NAV->setLayout(layoutPrincipalGeneral_NAV);
}

void fenetreOptions::chargerAvance_NAV()
{
    layoutPrincipalAvance_NAV = new QVBoxLayout;
        QGroupBox* design = new QGroupBox("Design");
            layoutPrincipalAvance_NAV->addWidget(design);
            QVBoxLayout* layout = new QVBoxLayout;
            design->setLayout(layout);
        progressBarStatusBar = new ASwitchButton("Afficher la barre de chargement des pages");
            progressBarStatusBar->setChecked(settingsOption->value("WEB/progressBarStatusbar",true).toBool());
            layout->addWidget(progressBarStatusBar);
        seeTaskBar = new ASwitchButton("Afficher la barre de statut");
            seeTaskBar->setChecked(settingsOption->value("WEB/StatusBarVisible",true).toBool());
            layout->addWidget(seeTaskBar);

    layoutPrincipalAvanceWidget_NAV->setLayout(layoutPrincipalAvance_NAV);
}

void fenetreOptions::chargerSecurite_NAV()
{
    layoutPrincipalSecurite_NAV = new QVBoxLayout;
        QLabel *titre = new QLabel("Sécurité");
        layoutPrincipalSecurite_NAV->addWidget(titre);

    layoutPrincipalSecuriteWidget_NAV->setLayout(layoutPrincipalSecurite_NAV);
}

void fenetreOptions::chargerGeneralAction_NAV()
{
    layoutPrincipalGeneralWidget_NAV->setVisible(true);
    layoutPrincipalAvanceWidget_NAV->setVisible(false);
    layoutPrincipalSecuriteWidget_NAV->setVisible(false);
}

void fenetreOptions::chargerAvanceAction_NAV()
{
    layoutPrincipalGeneralWidget_NAV->setVisible(false);
    layoutPrincipalAvanceWidget_NAV->setVisible(true);
    layoutPrincipalSecuriteWidget_NAV->setVisible(false);
}

void fenetreOptions::chargerSecuriteAction_NAV()
{
    layoutPrincipalGeneralWidget_NAV->setVisible(false);
    layoutPrincipalAvanceWidget_NAV->setVisible(false);
    layoutPrincipalSecuriteWidget_NAV->setVisible(true);
}

void fenetreOptions::closeEvent(QCloseEvent *event)
{
    changementOptionAuto();
    emit closing();
    event->accept();
}

bool fenetreOptions::getJavaEnable()
{
    return javaEnable;
}

bool fenetreOptions::getPluginEnable()
{
    return pluginEnable;
}

void fenetreOptions::changementOptionAuto()
{
    if (checkJavaEnable->isChecked())
    {
        javaEnable = true;
    }
    else
    {
        javaEnable = false;
    }

    if (checkPluginEnable->isChecked())
    {
        pluginEnable = true;
    }
    else
    {
        pluginEnable = false;
    }

    if (checkModeEnable->isChecked())
        compactModeEnable = true;
    else
        compactModeEnable = false;

    settingsOption->setValue("WEB/javaEnable",javaEnable);
    settingsOption->setValue("WEB/pluginEnable",pluginEnable);
    settingsOption->setValue("WEB/compactMode",compactModeEnable);
    settingsOption->setValue("WEB/tabBarPosition",tabBarPosition->currentIndex());
    settingsOption->setValue("WEB/progressBarStatusbar",progressBarStatusBar->isChecked());
    settingsOption->setValue("WEB/pageAccueil",pageAccueil->text());
    settingsOption->setValue("WEB/StatusBarVisible",seeTaskBar->isChecked());

    QWebSettings::globalSettings()->setAttribute(QWebSettings::AutoLoadImages,javaEnable);
    QWebSettings::globalSettings()->setAttribute(QWebSettings::JavascriptEnabled,javaEnable);
    QWebSettings::globalSettings()->setAttribute(QWebSettings::JavaEnabled,javaEnable);
    QWebSettings::globalSettings()->setAttribute(QWebSettings::PluginsEnabled,pluginEnable);

    emit reloadToolBar();
    emit changeHome(pageAccueil->text());
    emit seeProgressStatusBar(progressBarStatusBar->isChecked());
    emit changeTaskBarVisibility(seeTaskBar->isChecked());
}

void fenetreOptions::getCurrentPage()
{
    pageAccueil->setText(up->pageActuelle()->url().toString());
}

///-----Options du lecteur

fenetreOptions_Lecteur::fenetreOptions_Lecteur(QWidget* parent) : QWidget(parent)
{
    settings = new QSettings("conf/options.ini",QSettings::IniFormat);

    QHBoxLayout* hLayout = new QHBoxLayout;
        setLayout(hLayout);

    QGroupBox* groupBox = new QGroupBox(tr("Options du lecteur"));
        hLayout->addWidget(groupBox);

    QVBoxLayout* vLayout = new QVBoxLayout;
        groupBox->setLayout(vLayout);

    QHBoxLayout* hLayout2 = new QHBoxLayout;
        vLayout->addLayout(hLayout2);

    QLabel* titre_dossier_default = new QLabel(tr("Dossier Musiques : "));
        titre_dossier_default->setToolTip(tr("Dossier où sont rangées vos musiques !"));
        hLayout2->addWidget(titre_dossier_default);
    dossier_default = new QLineEdit;
        dossier_default->setText(settings->value("LEC/dossierMusic",QDir::home().absolutePath()).toString());
        dossier_default->setMaximumWidth(150);
        hLayout2->addWidget(dossier_default);
    parcourir = new QPushButton(tr("Parcourir..."));
        hLayout2->addWidget(parcourir);

    connect(parcourir,SIGNAL(pressed()),this,SLOT(modifier_chemin()));
}

fenetreOptions_Lecteur::~fenetreOptions_Lecteur()
{
}

void fenetreOptions_Lecteur::modifier_chemin()
{
    QString directory = QFileDialog::getExistingDirectory(this,"Choisir un dossier",QDir::home().absolutePath(),QFileDialog::ShowDirsOnly);
    dossier_default->setText(directory);
    parcourir->setDown(false);
}

void fenetreOptions_Lecteur::closeEvent(QCloseEvent *event)
{
    settings->setValue("LEC/dossierMusic",dossier_default->text());
}
