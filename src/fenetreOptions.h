#ifndef FENETREOPTIONS_H
#define FENETREOPTIONS_H

#include <QtGUI>
#include <QtWebKit/QtWebKit>
#include <QApplication>
#include "fenNav.h"
#include "ASwitchButton.h"

class fenNAV;
/* Fenetre d'options */
class fenetreOptions : public QWidget
{
    Q_OBJECT

    public :
    fenetreOptions(QString titre,QSettings *settings,fenNAV *parent = 0);
    ~fenetreOptions();

    bool getJavaEnable();
    bool getPluginEnable();

    public slots :

    void chargerGeneral_NAV();
    void chargerAvance_NAV();
    void chargerSecurite_NAV();

    void chargerGeneralAction_NAV();
    void chargerAvanceAction_NAV();
    void chargerSecuriteAction_NAV();

    void changementOptionAuto();
    void getCurrentPage();

    signals :
    void closing();
    void reloadToolBar();
    void changeHome(QString);
    void seeProgressStatusBar(bool);
    void changeTaskBarVisibility(bool);

    protected :
    void showEvent(QShowEvent *event);
    void closeEvent(QCloseEvent *event);

    private :
    void CenterOnScreen();

    QHBoxLayout *layout_principal;
    QVBoxLayout *layout_principal_complet;

    QWidget *layoutPrincipalGeneralWidget_NAV;
    QVBoxLayout *layoutPrincipalGeneral_NAV;

    QWidget *layoutPrincipalAvanceWidget_NAV;
    QVBoxLayout *layoutPrincipalAvance_NAV;

    QWidget *layoutPrincipalSecuriteWidget_NAV;
    QVBoxLayout *layoutPrincipalSecurite_NAV;

    ASwitchButton *checkJavaEnable;
    ASwitchButton *checkPluginEnable;
    ASwitchButton *checkModeEnable;
    ASwitchButton *progressBarStatusBar;
    ASwitchButton *seeTaskBar;

    QComboBox* tabBarPosition;

    QSettings *settingsOption;

    QLineEdit* pageAccueil;

    bool javaEnable,pluginEnable,compactModeEnable;
    unsigned int logiciel;

    fenNAV* up;

    QPushButton* currentPage;
};

class fenetreOptions_Lecteur : public QWidget
{
    Q_OBJECT

    public :
    fenetreOptions_Lecteur(QWidget* parent = 0);
    ~fenetreOptions_Lecteur();

    public slots :
    void modifier_chemin();

    protected :
    void closeEvent(QCloseEvent *event);

    private :
    QLineEdit* dossier_default;
    QPushButton* parcourir;
    QSettings* settings;
};

#endif


