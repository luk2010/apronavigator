#ifndef FENETRE_PRINCIPALE_H
#define FENETRE_PRINCIPALE_H

#include <QtGUI>
#include <QtWebKit>
#include <QApplication>
#include <iostream>
#include <string>

#include "fmod.h"
#include "fenNAV.h"

#define VERSION "Atlanti's Project v0.06A"

class Fenetre_Princ : public fenNAV
{
    Q_OBJECT

    public :
    Fenetre_Princ();
    Fenetre_Princ(int i);
    Fenetre_Princ(QUrl url);
    ~Fenetre_Princ();

    bool getQuit();

    void gestionSonInit();
    void gestionSonUpdate();
    void gestionSonRelease();

    void ajouterLec();

    void loadPlugins();

    public slots :

    void chargerFenetre(int i);
    void afficherOptionNAV();
    void afficherOptionLecteur();
    void changerLanguage(QAction* action);
    void aboutAPro();
    void aboutACorp();
    void quit();

    void LEC_chargerMusique(QString musique);
    void LEC_chargerMusicFromSearchBar();
    void LEC_ouvrirMusique();
    void LEC_slotPlay();
    void LEC_playpause();
    void LEC_slotStop();
    void LEC_afficherInfo();
    void LEC_changerVolume(int volume);
    void LEC_setMuet(bool muet);
    void LEC_setLoop(bool);
    void LEC_changeMusicPosition();
    void LEC_UpdatePosition();
    void sendQuit();

    signals :
    void quitquit();

    private :
    //Resources Bases



    QSettings *settings;
    QSettings *settingsLangue;

    bool quitter;
    bool mainwindow;
    bool ide,lec,nav;
    bool son_init;
    QString langue;

    //Resources LEC
    FMOD_CHANNEL *chaine_unique;
    FMOD_SOUND *musique_S;
    //Initialisation FMOD
    FMOD_RESULT resultat;
    FMOD_SYSTEM *system;

    QAction *LEC_Play;
    QAction *LEC_Stop;

    QLabel *titre_chanson;
    QLabel *auteur_chanson;
    QLabel *album_chanson;
    QLabel *date_chanson;
    QLabel *time_standard;//< Temps ecoulé
    QLabel *time_apple;//< Temps restant (comme dans itunes pour _apple ;) )

    QToolBar *LECToolBar;

    QSlider *LEC_volume;
    QSlider *LEC_time;

    QAction *LEC_loop;
    QAction *LEC_mute;

    musicSearchLine *searchMusicBar;

    protected :
    void closeEvent(QCloseEvent *);
    void hideEvent(QHideEvent *event);
    void showEvent(QShowEvent *event);

    int volume_dernier;
};

#endif //FENETRE_PRINCIPALE_H
