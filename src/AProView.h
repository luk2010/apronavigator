#ifndef APROVIEW_H
#define APROVIEW_H

#include <QtGUI>
#include <QtWebKit>
#include <iostream>
#include <vector>
#include <algorithm>
#include "AProFile.h"

struct FileInfo
{
    QFileInfo *info;
    QUrl url;
    bool canceled;
    bool finished;
};

class fenTelechargement : public QWidget
{
    Q_OBJECT

    signals :
    void telechargementFini(FileInfo&);
    void telechargementAnnule(FileInfo&);

    public :
    //Constructeur
    fenTelechargement(QWidget* parent,FileInfo& info);
    //Destructeur
    ~fenTelechargement();

    bool erreurExtension();

    public slots:

    void commencerTelechargement();
    void MAJ_telechargement(qint64,qint64);
    void finirEtEcrire();
    void Annuler();
    void MAJ_vitesse();

    private :

    QNetworkAccessManager *manager;
    QNetworkReply *reply;
    QUrl url;

    QProgressBar *bardeProgression;
    FileInfo infosFichier;
    QVBoxLayout *layoutPrincipal;

    QLabel *size;
    QLabel *etape;
    QLabel *vitesse;

    QList<QString> listeExtension;
    QFile *fichier;
    qint64 recus_old;

    QPushButton* annuler;

    QTime timer;
};

class GestionTelechargement : public QObject
{
    Q_OBJECT

    public :

    //Constructeur
    GestionTelechargement(QObject *parent = 0);
    //Destructeur
    ~GestionTelechargement();

    static GestionTelechargement* getInstance() { return Instance; }

    public slots :
    void ajouterTelechargement(QUrl url);
    void afficherTelechargements();
    void telechargementFini(FileInfo&);
    void telechargementAnnule(FileInfo&);

    private :

    typedef std::vector<FileInfo> downloadV;
    downloadV downloadFinished;
    downloadV downloadCanceled;

    static GestionTelechargement* Instance;
    QUrl url_old;
};

#define getGT GestionTelechargement::getInstance()

class fenNAV;
class AProView : public QWebView
{
    Q_OBJECT

    public :
    //Constructeur
    AProView(fenNAV *parent);
    //Destructeur
    ~AProView();

    QWebPage* page();

    bool loadStart() { return mloadStarte; }
    int loadingStatus() { return loadStatus; }
    int progress() { return loadStatus; }

    public slots:
    void pretelechargement();
    void pretelechargement(QNetworkReply *reply);
    void ajouterPage();
    void envoiChangerTitre(QString titre);
    void sendIconChanged();
    void loadingStarted();
    void setLoadingStatus(int pourcent) { loadStatus = pourcent; }
    void loadingFinished(bool);
    void linkHovered(QString Url,QString Title,QString Content);
    void showInspector();
    void downloadElement(QUrl url);

    signals:
    void ajouterTab(QUrl);
    void changerTitre(QString,AProView*);
    void changerIcon(QIcon,AProView*);
    void webViewStatusMessage(QString);

    protected :
    void contextMenuEvent(QContextMenuEvent *event);
    QWebView* createWindow(QWebPage::WebWindowType type);

    private :
    fenNAV* navigator;
    QWebPage* m_page;
    QWebInspector* inspector;

    QUrl urlUtilise;
    QUrl urlImgUtilise;
    QUrl url_old;

    int loadStatus;
    bool mloadStarte;
};

#endif //APROVIEW_H
