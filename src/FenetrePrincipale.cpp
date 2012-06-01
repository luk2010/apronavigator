#include "FenetrePrincipale.h"
#include "scriptengine.h"
//#include "AProProject.h"
#define IDE 1001
#define LECTEUR 1002
#define NAVIGATEUR 1003
#define sv settingsLangue->value(
#define vs ).toString()
using namespace std;

Fenetre_Princ::Fenetre_Princ()
{
    // Lors du démarrage du programme, l'utilisateur arrive dans la fenêtre "NAV"
    settings = new QSettings("conf/options.ini",QSettings::IniFormat);
    quitter = false;
    volume_dernier = settings->value("LEC/volume_dernier",50).value<int>();
    langue = "conf/"+settings->value("ALL/language","Francais").value<QString>() + ".ini";
    chargerFenetre(0);

    QScriptValue this_script = ScriptEngine::get()->newQObject(this);
    ScriptEngine::get()->globalObject().setProperty("MainWindow", this_script);
}

Fenetre_Princ::Fenetre_Princ(int i)
{
    chargerFenetre(i);
}

Fenetre_Princ::~Fenetre_Princ()
{
    if (lec)
    gestionSonRelease();
}

void Fenetre_Princ::chargerFenetre(int i)
{
    if (i == 0)
    {
        settingsLangue = new QSettings(langue,QSettings::IniFormat);
        mainwindow = true;
        ide = false;
        lec = false;
        nav = false;
        musique_S = NULL;
        chaine_unique = NULL;

        LECToolBar = new QToolBar(settingsLangue->value("LECToolBar").value<QString>());
        this->addToolBar(Qt::BottomToolBarArea, LECToolBar);
        ajouterLec();

        LECToolBar->setAllowedAreas(Qt::BottomToolBarArea);
        LECToolBar->setMovable(false);

        fenNAV::setupNavigator();

        //Connection de base

        connect(menuFichier_Ouvrir,SIGNAL(triggered()),this, SLOT(LEC_ouvrirMusique()));
        connect(menuFichier_Quitter,SIGNAL(triggered()),this, SLOT(quit()));
        connect(menuAide_AProposQt,SIGNAL(triggered()), qApp, SLOT(aboutQt()));
        connect(menuAide_AProposAPro,SIGNAL(triggered()), this, SLOT(aboutAPro()));
        connect(menuAide_AProposACorp,SIGNAL(triggered()), this, SLOT(aboutACorp()));
        connect(menuOption_configurerNavigateur,SIGNAL(triggered()),this,SLOT(afficherOptionNAV()));
        connect(menuOption_configurerLecteur,SIGNAL(triggered()),this,SLOT(afficherOptionLecteur()));
        connect(languageGroup,SIGNAL(triggered(QAction*)),this,SLOT(changerLanguage(QAction*)));
        connect(this,SIGNAL(quitNOW()),this,SLOT(sendQuit()));
        connect(qApp,SIGNAL(aboutToQuit()),this,SLOT(quit()));
    }
}

void Fenetre_Princ::sendQuit()
{
    emit quitquit();
}

void Fenetre_Princ::aboutAPro()
{
    QMessageBox::information(this,"À propos du projet Atlanti's","Le projet Atlanti's Project Nav 'n' IDE est un navigateur IDE avec lecteur audio FMOD(tm) intégré.<br />Il est la propriété de Atlanti's Corp et est totalement gratuit.");
}

void Fenetre_Princ::aboutACorp()
{
    QMessageBox::information(this,"À propos de la société Atlanti's Corporation","Atlanti's Corporation correspond à la société mère de APro.<br />Tous droits réservés, Atlanti's Corporation 2010.");
}

void Fenetre_Princ::changerLanguage(QAction* action)
{
    if (action == langueAllemand)
    {
        settings->setValue("ALL/language","Anglais");
        QMessageBox::warning(this,"Erreur","La langue allemande n'est pas encore comprise !");
        langueAllemand->setChecked(false);
        if (langue == "conf/Francais.ini")
            langueFrancais->setChecked(true);
        else if (langue == "conf/Anglais.ini")
            langueAnglais->setChecked(true);
    }
    else if (action == langueAnglais)
    {
        settings->setValue("ALL/language","Anglais");
        QMessageBox::warning(this,"Attention","La langue souhaitée ne sera valide qu'après un redémarrage de l'application !");
    }
    else if (action == langueFrancais)
    {
        settings->setValue("ALL/language","Francais");
        QMessageBox::warning(this,"Attention","La langue souhaitée ne sera valide qu'après un redémarrage de l'application !");
    }
    else
        QMessageBox::warning(this,"Erreur","Langue non reconnue !");

}

void Fenetre_Princ::quit()
{
    quitter = true;
    //Sous_Fenetre_IDE_widget->event(new QCloseEvent());
    sendQuit();
}

void Fenetre_Princ::closeEvent(QCloseEvent *)
{
    quit();
}

bool Fenetre_Princ::getQuit()
{
    return quitter;
}

void Fenetre_Princ::afficherOptionNAV()
{
    this->NAV_afficherOption();
}

void Fenetre_Princ::gestionSonInit()
{
    resultat = FMOD_System_Create(&system);
    resultat = FMOD_System_Init(system,100,FMOD_INIT_NORMAL,0);
    son_init = true;
}

void Fenetre_Princ::gestionSonUpdate()
{
    FMOD_System_Update(system);
}

void Fenetre_Princ::gestionSonRelease()
{
    FMOD_System_Release(system);
}

void Fenetre_Princ::LEC_ouvrirMusique()
{
    QString fichier = QFileDialog::getOpenFileName(this,"Ouvrir...","/home","Musique (*.mp3 *.wmv *.ogg *.mp2 *.flac);;Fichiers musicaux (*.mid *.midi);;Tous les fichiers (*)");
    QFileInfo infofichier(fichier);
    if (!infofichier.exists())
        return;
    else if (infofichier.suffix()=="")
        return;
    else if (infofichier.isDir())
        return;

    if (fichier == 0 || fichier == NULL)
        return;
    LEC_chargerMusique(fichier);
    LEC_Play->setText("Pause");
    LEC_Play->setIcon(QIcon("icones/player_pause.png"));
    LEC_afficherInfo();
}

void Fenetre_Princ::LEC_chargerMusique(QString musique)
{
    const char *musique_c = musique.toStdString().c_str();
    resultat = FMOD_System_CreateStream(system,musique_c,FMOD_DEFAULT,0,&musique_S);
    resultat = FMOD_System_PlaySound(system,FMOD_CHANNEL_REUSE,musique_S,false,&chaine_unique);
    LEC_changerVolume(LEC_volume->value());
    LEC_setLoop(LEC_loop->isChecked());
    LEC_setMuet(LEC_mute->isChecked());
}

void Fenetre_Princ::LEC_slotPlay()
{
    FMOD_SOUND *son_jouer_peutetre;
    FMOD_Channel_GetCurrentSound(chaine_unique,&son_jouer_peutetre);
    if ((son_jouer_peutetre != NULL) && (chaine_unique != NULL))
    {
        LEC_playpause();
    }
    else
    {
        LEC_ouvrirMusique();
    }
}

void Fenetre_Princ::LEC_playpause()
{
    FMOD_BOOL paused;
    FMOD_Channel_GetPaused(chaine_unique,&paused);
    if (paused)
    {
        FMOD_Channel_SetPaused(chaine_unique,false);
        LEC_Play->setText("Pause");
        LEC_Play->setIcon(QIcon("icones/player_pause.png"));
    }
    if (!paused)
    {
        FMOD_Channel_SetPaused(chaine_unique,true);
        LEC_Play->setText("Jouer");
        LEC_Play->setIcon(QIcon("icones/player_play.png"));
    }
}

void Fenetre_Princ::LEC_slotStop()
{
    FMOD_Channel_Stop(chaine_unique);
    LEC_Play->setText("Jouer");
    LEC_Play->setIcon(QIcon("icones/player_play.png"));
    LEC_afficherInfo();
}

void Fenetre_Princ::LEC_afficherInfo()
{
    FMOD_SOUND *son_jouer;
    FMOD_Channel_GetCurrentSound(chaine_unique,&son_jouer);
    if (son_jouer == NULL || son_jouer == 0)
    {
        titre_chanson->setText("Aucun Titre !");
        auteur_chanson->setText("Aucun auteur !");
        album_chanson->setText("Aucun album !");
        return;
    }
    FMOD_TAG tag;
    tag.type = FMOD_TAGTYPE_ID3V2;
    resultat = FMOD_Sound_GetTag(son_jouer,"TIT2",0,&tag);
    if (tag.datalen < 50)
    {
        QString str((char*)tag.data);
        if (tag.datalen > 15)
        {
            str.resize(12);
            str += "...";
        }

        titre_chanson->setText(str);
    }
    else
    {
        titre_chanson->setText("Titre Inconnu");
    }
    FMOD_TAG tag_auteur;
    resultat = FMOD_Sound_GetTag(son_jouer,"ARTIST",0,&tag_auteur);
    if (tag_auteur.datalen < 25)
    {
        QString str((char*)tag_auteur.data);
        if (tag_auteur.datalen > 15)
        {
            str.resize(12);
            str += "...";
        }

        auteur_chanson->setText(str);
    }
    else
    {
        auteur_chanson->setText("Auteur inconnu");
    }

    FMOD_TAG tag_album;
    tag_album.type = FMOD_TAGTYPE_ID3V2;
    resultat = FMOD_Sound_GetTag(son_jouer,"TALB",0,&tag_album);
    if (tag_album.datalen < 50)
    {
        QString str((char*)tag_album.data);
        if (tag_album.datalen > 15)
        {
            str.resize(12);
            str += "...";
        }

        album_chanson->setText(str);
    }
    else
    {
        album_chanson->setText("Album inconnu");
    }


}

void Fenetre_Princ::LEC_changerVolume(int volume)
{
    int volume1 = volume;
    float fvolume = (float)volume1/100;
    FMOD_Channel_SetVolume(chaine_unique,fvolume);
    settings->setValue("LEC/volume_dernier",LEC_volume->value());
}

void Fenetre_Princ::hideEvent(QHideEvent *event)
{
    if (son_init)
    {
    if (titre_chanson != NULL)
        {
            if (titre_chanson->text() != "Aucun titre !")
            {
                if (titre_chanson->text() != "")
                setWindowTitle(titre_chanson->text()+"  |  "+auteur_chanson->text());
            }
        }
    }
}

void Fenetre_Princ::showEvent(QShowEvent *event)
{
    if (son_init)
        setWindowTitle(VERSION);
    event->accept();
}

void Fenetre_Princ::ajouterLec()
{
    gestionSonInit();
    LEC_Play = LECToolBar->addAction(QIcon("icones/player_play.png"),"Jouer");
    LEC_Stop = LECToolBar->addAction(QIcon("icones/player_stop.png"),"Stop");
    LEC_loop = LECToolBar->addAction(QIcon("icones/quick_restart.png"),"En boucle");
        LEC_loop->setCheckable(true);

    QLabel *titre_label = new QLabel(this);
            titre_label->setText("Titre :");
            titre_chanson = new QLabel(this);
            titre_chanson->setText("Aucun titre !");
            titre_chanson->setMaximumWidth(150);
    QLabel *auteur_label = new QLabel(this);
            auteur_label->setText("Auteur :");
            auteur_chanson = new QLabel(this);
            auteur_chanson->setText("Aucun auteur !");
    QLabel *album_label = new QLabel(this);
            album_label->setText("Album :");
            album_chanson = new QLabel(this);
            album_chanson->setText("Aucun album !");
    LEC_volume = new QSlider(Qt::Horizontal,this);
            LEC_volume->setMinimum(0);
            LEC_volume->setMaximum(100);
            LEC_volume->setMaximumWidth(100);
            LEC_volume->setSliderPosition(volume_dernier-1);
    LEC_time = new QSlider(Qt::Horizontal,this);
            LEC_time->setMinimum(0);
            LEC_time->setMaximum(100);
            LEC_time->setMinimumWidth(100);
            LEC_time->setMaximumWidth(100);
            LEC_time->setSliderPosition(0);
    time_apple = new QLabel(this);
        time_apple->setMinimumWidth(40);
        time_apple->setAlignment(Qt::AlignCenter);
        time_apple->setText("- 0:00");
    time_standard = new QLabel(this);
        time_standard->setMinimumWidth(40);
        time_standard->setAlignment(Qt::AlignCenter);
        time_standard->setText("0:00");
    QLabel* label = new QLabel;
        label->setPixmap(QPixmap("icones/recherche_music.png"));
    searchMusicBar = new musicSearchLine(this);
        searchMusicBar->setMaximumWidth(150);
        searchMusicBar->setPlaceholderText("Chercher une musique...");


    LECToolBar->addSeparator();
    LECToolBar->addWidget(titre_label);
    LECToolBar->addWidget(titre_chanson);
    LECToolBar->addSeparator();
    LECToolBar->addWidget(auteur_label);
    LECToolBar->addWidget(auteur_chanson);
    LECToolBar->addSeparator();
    LECToolBar->addWidget(album_label);
    LECToolBar->addWidget(album_chanson);
    LECToolBar->addSeparator();
    LECToolBar->addWidget(LEC_volume);
    LEC_mute = LECToolBar->addAction(QIcon("icones/player_volume.png"),"Muet");
        LEC_mute->setCheckable(true);
    LECToolBar->addSeparator();
    LECToolBar->addWidget(time_standard);
    LECToolBar->addWidget(LEC_time);
    LECToolBar->addWidget(time_apple);
    LECToolBar->addSeparator();
    LECToolBar->addWidget(label);
    LECToolBar->addWidget(searchMusicBar);

    connect(LEC_Play,SIGNAL(triggered()),this,SLOT(LEC_slotPlay()));
    connect(LEC_Stop,SIGNAL(triggered()),this,SLOT(LEC_slotStop()));
    connect(LEC_volume,SIGNAL(valueChanged(int)),this,SLOT(LEC_changerVolume(int)));
    connect(LEC_mute,SIGNAL(toggled(bool)),this,SLOT(LEC_setMuet(bool)));
    connect(LEC_loop,SIGNAL(toggled(bool)),this,SLOT(LEC_setLoop(bool)));
    connect(LEC_time,SIGNAL(sliderReleased()),this,SLOT(LEC_changeMusicPosition()));
    connect(searchMusicBar,SIGNAL(returnPressed()),this,SLOT(LEC_chargerMusicFromSearchBar()));

}

void Fenetre_Princ::LEC_setMuet(bool muet)
{
    FMOD_Channel_SetMute(chaine_unique,muet);
}

void Fenetre_Princ::LEC_setLoop(bool loop)
{
    if (loop)
        FMOD_Channel_SetMode(chaine_unique,FMOD_LOOP_NORMAL);
    if (!loop)
        FMOD_Channel_SetMode(chaine_unique,FMOD_LOOP_OFF);
}

void Fenetre_Princ::LEC_changeMusicPosition()
{
    unsigned int position = LEC_time->sliderPosition();
    unsigned int music_lenght = 0;//< millisecond
    FMOD_Sound_GetLength(musique_S,&music_lenght,FMOD_TIMEUNIT_MS);
    unsigned int new_position = (music_lenght*position)/100;
    FMOD_Channel_SetPosition(chaine_unique,new_position,FMOD_TIMEUNIT_MS);

    LEC_UpdatePosition();
}

void Fenetre_Princ::LEC_UpdatePosition()
{
    if (musique_S != NULL)
    {
        QString text_avant("");
        QString text_apres("");

        unsigned int lenght = 0;
        unsigned int position = 0;
        unsigned int position_min = 0;
        unsigned int position_sec = 0;

        FMOD_Channel_GetPosition(chaine_unique,&position,FMOD_TIMEUNIT_MS);
        //text_avant
        position_min = (position/1000)/60;
        position_sec = (position - (position_min*1000*60))/1000;
        if (position_sec < 10)
            text_avant = QString::number(position_min) + ":0" + QString::number(position_sec);
        else
            text_avant = QString::number(position_min) + ":" + QString::number(position_sec);
        //text_apres
        FMOD_Sound_GetLength(musique_S,&lenght,FMOD_TIMEUNIT_MS);
        position_min = ((lenght - position)/1000)/60;
        position_sec = (((lenght - position)/1000)-(position_min*60));
        if (position_sec < 10)
            text_apres = "- " + QString::number(position_min) + ":0" + QString::number(position_sec);
        else
            text_apres = "- " + QString::number(position_min) + ":" + QString::number(position_sec);

        time_standard->setText(text_avant);
        time_apple->setText(text_apres);

        if (!LEC_time->isSliderDown())
            LEC_time->setSliderPosition((position*100)/lenght);
    }
}

void Fenetre_Princ::afficherOptionLecteur()
{
    fenetreOptions_Lecteur* optionsLecteur = new fenetreOptions_Lecteur;
    optionsLecteur->show();
}

void Fenetre_Princ::LEC_chargerMusicFromSearchBar()
{
    QString dir = settings->value("LEC/dossierMusic").toString();
    dir += "\\";
    dir += searchMusicBar->text();
    searchMusicBar->setText("");
    LEC_chargerMusique(dir);
    LEC_Play->setText("Pause");
    LEC_Play->setIcon(QIcon("icones/player_pause.png"));
    LEC_afficherInfo();
}

void Fenetre_Princ::loadPlugins()
{
    QString path("plugins/");

    QDir dir(path);
    QFileInfoList list = dir.entryInfoList();

    for(int i = 0; i < list.count(); i++)
    {
        QFileInfo info = list.at(i);
        if(info.suffix() == "qs" || info.suffix() == "js")
        {
            ScriptEngine::get()->pushContext();

            ScriptEngine::loadScript(info.filePath());

            ScriptEngine::get()->popContext();
        }
    }
}
