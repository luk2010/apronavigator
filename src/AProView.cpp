#include "AProView.h"
#include "fenNAV.h"

fenTelechargement::fenTelechargement(QWidget* parent,FileInfo& info)
: QWidget(parent)
{
    timer.start();
    listeExtension << "exe" << "msi" << "gz"
                       << "jpg" << "jpeg" << "ico" << "png"
                       << "rar" << "zip" << "iso"
                       << "torrent"
                       << "mp3" << "mp4" << "mkv" << "ogg";
    manager = new QNetworkAccessManager(this);
    infosFichier.info = new QFileInfo(info.url.toString());
    infosFichier.url = info.url;
    if (!listeExtension.contains(infosFichier.info->suffix()))
        if(!erreurExtension())
            close();
    url = infosFichier.url;

    QString titre = "Telechargement de - " + infosFichier.info->fileName();
    setWindowTitle(titre);

    layoutPrincipal = new QVBoxLayout(this);

    QLabel *Infos = new QLabel("Nom du fichier : "+infosFichier.info->fileName());
        layoutPrincipal->addWidget(Infos);
    QLabel *extension = new QLabel("Extension : "+infosFichier.info->suffix());
        layoutPrincipal->addWidget(extension);
    layoutPrincipal->insertStretch(-1,1);
    QHBoxLayout *layoutTaille = new QHBoxLayout;
    QLabel *taille = new QLabel("Taille : ");
        layoutTaille->addWidget(taille);
    size = new QLabel("inconnue");
        layoutTaille->addWidget(size);
    layoutPrincipal->addLayout(layoutTaille);
    QHBoxLayout *layoutVitesse = new QHBoxLayout;
    QLabel *speed = new QLabel("Vitesse : ");
        layoutVitesse->addWidget(speed);
    vitesse = new QLabel("inconnue");
        layoutVitesse->addWidget(vitesse);
    layoutPrincipal->addLayout(layoutVitesse);
    bardeProgression = new QProgressBar;
        layoutPrincipal->addWidget(bardeProgression);
    etape = new QLabel("Téléchargement en cours...");
        layoutPrincipal->addWidget(etape);
    annuler = new QPushButton("Annuler");
        layoutPrincipal->addWidget(annuler);

    recus_old = 0;
    commencerTelechargement();

}

fenTelechargement::~fenTelechargement()
{
    delete reply;
}

void fenTelechargement::commencerTelechargement()
{
    reply = manager->get(QNetworkRequest(url));
    connect(reply,SIGNAL(downloadProgress(qint64, qint64)), this, SLOT(MAJ_telechargement(qint64, qint64)));
    connect(annuler,SIGNAL(pressed()),this,SLOT(Annuler()));
}

void fenTelechargement::MAJ_telechargement(qint64 recus, qint64 total)
{
    if (total != -1)
        bardeProgression->setRange(0,total);
    bardeProgression->setValue(recus);
    recus_old = recus;
    MAJ_vitesse();
    if (recus == total)
        finirEtEcrire();
}

void fenTelechargement::finirEtEcrire()
{
    if (reply->size() == 0)
    {
        QMessageBox::critical(0,"Erreur","Le fichier n'a pu être téléchargé !");
        close();
        return;
    }

    fichier = new QFile(QFileDialog::getSaveFileName(0,"Emplacement du fichier",infosFichier.info->fileName(),"Tous fichiers(*)"));
    if (fichier == NULL)
    {
        close();
        return;
    }

    fichier->open(QIODevice::WriteOnly);
    etape->setText("Ecriture du fichier...");
    fichier->write(reply->readAll());
    fichier->close();
    reply->close();
    infosFichier.finished = true;
    emit telechargementFini(infosFichier);
    close();
}

void fenTelechargement::Annuler()
{
    if (QMessageBox::warning(0,tr("Attention"),tr("Voulez-vous vraiment annuler le téléchargement ?"),QMessageBox::Yes | QMessageBox::No, QMessageBox::No) == QMessageBox::No)
        return;
    etape->setText("Annulation...");
    reply->abort();
    infosFichier.canceled = true;
    emit telechargementAnnule(infosFichier);
    close();
}

bool fenTelechargement::erreurExtension()
{
    if (QMessageBox::critical(this,"Attention","L'extension du fichier n'est pas reconnue !<br />Voulez-vous tout de même continuer ?",QMessageBox::Yes | QMessageBox::No) == QMessageBox::Yes)
        return true;
    else
        return false;
}

void fenTelechargement::MAJ_vitesse()
{
    double speed = recus_old / timer.elapsed();
    vitesse->setText(QString::number(speed)+" kbs/s");
}

GestionTelechargement* GestionTelechargement::Instance = new GestionTelechargement(0);

GestionTelechargement::GestionTelechargement(QObject *parent) : QObject(parent)
{
    url_old = NULL;
}

GestionTelechargement::~GestionTelechargement()
{
}

void GestionTelechargement::ajouterTelechargement(QUrl url)
{
    FileInfo info;
    info.info = new QFileInfo(url.toString());
    info.url = url;
    info.canceled = false;
    info.finished = false;

    //Verification que le téléchargement n'a pas déjà été effectué !
    if (url_old == info.url)
        return;
    url_old = url;
    fenTelechargement* fentelechargement = new fenTelechargement(0,info);
    connect(fentelechargement,SIGNAL(telechargementFini(FileInfo&)),this,SLOT(telechargementFini(FileInfo&)));
    connect(fentelechargement,SIGNAL(telechargementAnnule(FileInfo&)),this,SLOT(telechargementAnnule(FileInfo&)));
    fentelechargement->show();
}

void GestionTelechargement::afficherTelechargements()
{
    //Mise en place du tableau
    QTableWidget* tableau = new QTableWidget;
        tableau->setColumnCount(2);
        tableau->setColumnWidth(0,200);
        tableau->setColumnWidth(1,200);
        tableau->setEditTriggers(QAbstractItemView::NoEditTriggers);
        tableau->setGridStyle(Qt::NoPen);
        tableau->verticalHeader()->hide();
        tableau->horizontalHeader()->hide();
        tableau->setAlternatingRowColors(true);
        tableau->setSelectionBehavior(QAbstractItemView::SelectRows);
        tableau->setRowCount(downloadFinished.size()+downloadCanceled.size()+2);

    //Mise à jour des éléments
        QListView* view = new QListView;
        view->setAlternatingRowColors(true);
        view->setEditTriggers(QListView::NoEditTriggers);

        unsigned int i = 0;
        //Téléchargements terminés
        QTableWidgetItem* titre1 = new QTableWidgetItem("Téléchargements Terminés");
            titre1->setFlags(Qt::NoItemFlags);
            titre1->setTextColor(Qt::black);
            QFont font;
            font.setBold(true);
            font.setUnderline(true);
            titre1->setData(Qt::FontRole,font);
        tableau->setItem(0,0,titre1);
        QTableWidgetItem* titre1_2 = new QTableWidgetItem("");
            titre1_2->setFlags(Qt::NoItemFlags);
        tableau->setItem(0,1,titre1_2);

        QStringList listName;
        QStringList listPath;
        for (i = 0; i < downloadFinished.size(); i++)
        {
            QTableWidgetItem* newItemNom = new QTableWidgetItem(downloadFinished[i].info->baseName());
            tableau->setItem(i+1,0,newItemNom);

            QTableWidgetItem* newItemItem = new QTableWidgetItem(downloadFinished[i].info->path());
            tableau->setItem(i+1,1,newItemItem);
        }

        //Téléchargements annulés
        QTableWidgetItem* titre2 = new QTableWidgetItem("Téléchargements Annulés");
            titre2->setFlags(Qt::NoItemFlags);
            titre2->setTextColor(Qt::black);
            titre2->setData(Qt::FontRole,font);
        tableau->setItem(i+1,0,titre2);
        QTableWidgetItem* titre2_2 = new QTableWidgetItem("");
            titre2_2->setFlags(Qt::NoItemFlags);
        tableau->setItem(i+1,1,titre2_2);

        for (unsigned int j = 0; j < downloadCanceled.size(); j++)
        {
            QTableWidgetItem* newItemNom = new QTableWidgetItem(downloadCanceled[j].info->baseName());
            tableau->setItem(i+2+j,0,newItemNom);

            QTableWidgetItem* newItemItem = new QTableWidgetItem(downloadCanceled[j].info->path());
            tableau->setItem(i+2+j,1,newItemItem);
        }


    //Mise en place du cadre
    QVBoxLayout* layoutVertical = new QVBoxLayout;
    layoutVertical->addWidget(tableau);
    QHBoxLayout* layoutHorizontal = new QHBoxLayout;
    layoutHorizontal->addLayout(layoutVertical);
    QWidget* fenetrePrincipale = new QWidget(0);
    fenetrePrincipale->setLayout(layoutHorizontal);
    fenetrePrincipale->setWindowTitle("Historique des téléchargements");
    fenetrePrincipale->setMinimumWidth(450);
    fenetrePrincipale->show();
}

void GestionTelechargement::telechargementFini(FileInfo& info)
{
    downloadFinished.push_back(info);
}

void GestionTelechargement::telechargementAnnule(FileInfo& info)
{
    downloadCanceled.push_back(info);
}

AProView::AProView(fenNAV *parent)
    : QWebView(parent), navigator(parent), m_page(new QWebPage(this)),loadStatus(0),mloadStarte(false)
{
    inspector = new QWebInspector(NULL);
    inspector->setVisible(false);
    inspector->setPage(this->page());

    setPage(m_page);

    connect(this,SIGNAL(titleChanged(QString)),this,SLOT(envoiChangerTitre(QString)));
    connect(this,SIGNAL(iconChanged()),this,SLOT(sendIconChanged()));
    connect(this,SIGNAL(loadStarted()),this,SLOT(loadingStarted()));
    connect(this,SIGNAL(loadProgress(int)),this,SLOT(setLoadingStatus(int)));
    connect(this,SIGNAL(loadFinished(bool)),this,SLOT(loadingFinished(bool)));
    connect(this->page(),SIGNAL(linkHovered(QString,QString,QString)),this,SLOT(linkHovered(QString,QString,QString)));
}

AProView::~AProView()
{
   delete m_page;
   delete inspector;
}

QWebPage* AProView::page()
{
    return m_page;
}

void AProView::contextMenuEvent(QContextMenuEvent *event)
{
    page()->action(QWebPage::Back)->setText("Précédent");
    page()->action(QWebPage::Forward)->setText("Suivant");
    page()->action(QWebPage::Reload)->setText("Recharger");
    page()->action(QWebPage::Copy)->setText("Copier");
    page()->action(QWebPage::Paste)->setText("Coller");
    page()->action(QWebPage::SelectAll)->setText("Tout sélectionner");
    page()->action(QWebPage::OpenLink)->setText("Ouvrir le lien");
    page()->action(QWebPage::OpenLinkInNewWindow)->setText("Ouvrir le lien dans un nouvel onglet");
    page()->action(QWebPage::CopyLinkToClipboard)->setText("Copier le lien");
    page()->action(QWebPage::DownloadLinkToDisk)->setText("Enregistrer la cible sous...");
    page()->action(QWebPage::OpenImageInNewWindow)->setText("Ouvrir l'image dans un nouvel onglet");
    page()->action(QWebPage::DownloadImageToDisk)->setText("Enregistrer l'image sous...");

    QWebHitTestResult test = page()->mainFrame()->hitTestContent(event->pos());
    QMenu customContextMenu(this);

    customContextMenu.addAction(pageAction(QWebPage::Forward));
    customContextMenu.addAction(pageAction(QWebPage::Back));
    customContextMenu.addAction(pageAction(QWebPage::Reload));
    customContextMenu.addSeparator();
    customContextMenu.addAction(pageAction(QWebPage::Copy));
    customContextMenu.addAction(pageAction(QWebPage::Paste));
    customContextMenu.addAction(pageAction(QWebPage::SelectAll));

    urlUtilise = "";
    urlImgUtilise = "";

    if (!test.linkUrl().isEmpty())
    {
        customContextMenu.addSeparator();
        customContextMenu.addAction(pageAction(QWebPage::OpenLink));
        customContextMenu.addAction(pageAction(QWebPage::OpenLinkInNewWindow));
        customContextMenu.addAction(pageAction(QWebPage::CopyLinkToClipboard));
        customContextMenu.addAction(pageAction(QWebPage::DownloadLinkToDisk));

        urlUtilise = test.linkUrl();
        connect(pageAction(QWebPage::DownloadLinkToDisk),SIGNAL(triggered()),this,SLOT(pretelechargement()));
    }

    if (!test.imageUrl().isEmpty())
    {
        customContextMenu.addSeparator();
        customContextMenu.addAction(pageAction(QWebPage::OpenImageInNewWindow));
        customContextMenu.addAction(pageAction(QWebPage::DownloadImageToDisk));

        urlImgUtilise = test.imageUrl();
        connect(pageAction(QWebPage::OpenImageInNewWindow),SIGNAL(triggered()),this,SLOT(ajouterPage()));
        connect(pageAction(QWebPage::DownloadImageToDisk),SIGNAL(triggered()),this,SLOT(pretelechargement()));
    }
    customContextMenu.addAction(pageAction(QWebPage::InspectElement));
    customContextMenu.exec(event->globalPos());

    connect(pageAction(QWebPage::InspectElement), SIGNAL(triggered()), this, SLOT(showInspector()));
}

void AProView::pretelechargement()
{
    if (!urlUtilise.isEmpty())
        getGT->ajouterTelechargement(urlUtilise);
    if (!urlImgUtilise.isEmpty())
        getGT->ajouterTelechargement(urlImgUtilise);
}

void AProView::pretelechargement(QNetworkReply *reply)
{
    if (!reply->url().isEmpty())
        getGT->ajouterTelechargement(reply->url());
}

void AProView::downloadElement(QUrl url)
{
    if(url.isEmpty() == false)
        getGT->ajouterTelechargement(url);
}

void AProView::ajouterPage()
{
    if (!urlUtilise.isEmpty() && urlUtilise!=url_old)
    {
        url_old = urlUtilise;
        emit ajouterTab(urlUtilise);
    }

    if (!urlImgUtilise.isEmpty() && urlImgUtilise!=url_old)
    {
        url_old = urlImgUtilise;
        emit ajouterTab(urlImgUtilise);
    }
}

void AProView::envoiChangerTitre(QString titre)
{
    emit changerTitre(titre,this);
}

void AProView::sendIconChanged()
{
    emit changerIcon(QWebSettings::iconForUrl(url()),this);
}

void AProView::loadingFinished(bool finish)
{
    mloadStarte = false;
    if (finish)
    {
        loadStatus = 0;
        emit webViewStatusMessage(QString("Aucune Erreur !"));
    }
    else
    {
        loadStatus = -1;
        emit webViewStatusMessage(QString("Une erreur est survenue !"));
    }
}

void AProView::loadingStarted()
{
    mloadStarte = true;
    loadStatus = 0;
    emit webViewStatusMessage(QString("Chargement..."));
}

void AProView::linkHovered(QString Url,QString Title,QString Content)
{
    QString formattedMessage = "";
    if(!Title.isEmpty()) {
        formattedMessage += Title + " : ";
    }
    if(!Url.isEmpty()) {
        formattedMessage += "Lien vers : " + Url;
    }
    emit webViewStatusMessage(formattedMessage);
}

QWebView* AProView::createWindow(QWebPage::WebWindowType type)
{
    return navigator->NAV_AjouterTabNull();
}

void AProView::showInspector()
{
    inspector->show();
}
