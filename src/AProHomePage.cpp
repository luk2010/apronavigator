#include "AProHomePage.h"
#include "clickablelabel.h"

AProHomePage::AProHomePage(const QImage& bg,QWidget* parent)
 : QScrollArea(0),m_bg(bg)
{
    widget = new QWidget(this);
        setWidget(widget);
        setWidgetResizable(true);
        setBackgroundRole(QPalette::Light);

    vLayout = new QVBoxLayout;
        widget->setLayout(vLayout);

    hLayout2 = new QHBoxLayout;
        vLayout->addLayout(hLayout2);
        hLayout2->addStretch();

    QPixmap img2("images/logoACorp.png");
    label_img2 = new QLabel;
        label_img2->setPixmap(img2);
        hLayout2->addWidget(label_img2);
    QPixmap img("images/ATexte.jpg","JPG");
    label_img = new QLabel;
        label_img->setPixmap(img.scaled(QSize(width()*0.8,height()/2),Qt::IgnoreAspectRatio,Qt::SmoothTransformation));
        hLayout2->addWidget(label_img);
        hLayout2->addStretch();

    hLayout = new QHBoxLayout;
        vLayout->addLayout(hLayout);

    newFichier = new QPushButton("Nouveau Fichier");
        newFichier->setMaximumWidth(200);
        newFichier->setMinimumWidth(200);
    newProject = new QPushButton("Nouveau Projet");
        newProject->setMaximumWidth(200);
        newProject->setMinimumWidth(200);
    hLayout->addStretch();
    hLayout->addWidget(newFichier);
    hLayout->addItem(new QSpacerItem(20,0));
    hLayout->addWidget(newProject);
    hLayout->addStretch();

    QHBoxLayout* invisibleLayout = new QHBoxLayout;
    vLayout->addLayout(invisibleLayout);
    invisibleLayout->addStretch();

    //Nouveau fichier
    AnimatedGroupBox* newGroupBox = new AnimatedGroupBox("Nouveau Fichier");
    invisibleLayout->addWidget(newGroupBox);
    newGroupBox->setVisible(false);
    QVBoxLayout* layoutGroupBox = new QVBoxLayout;
    newGroupBox->setLayout(layoutGroupBox);
    newGroupBox->setMaximumWidth(250);
    layoutGroupBox->setAlignment(Qt::AlignLeft);
        //Item
    QHBoxLayout* hLayout3 = new QHBoxLayout;
        layoutGroupBox->addLayout(hLayout3);
        hLayout3->addWidget(new QLabel("Nom du fichier : "));
    fileName = new QLineEdit;
        fileName->setObjectName("fileName");
        fileName->setMaximumWidth(150);
        hLayout3->addWidget(fileName);
    QPushButton* parcourir = new QPushButton("...");
        parcourir->setMaximumWidth(20);
        hLayout3->addWidget(parcourir);
    QHBoxLayout* hLayout6 = new QHBoxLayout;
        layoutGroupBox->addLayout(hLayout6);
        hLayout6->setAlignment(Qt::AlignLeft);
        hLayout6->addWidget(new QLabel("Dossier : "));
    label_dossier_fichier = new QLabel("Aucun sélectionné !");
        hLayout6->addWidget(label_dossier_fichier);
    QHBoxLayout* hLayout4 = new QHBoxLayout;
        hLayout4->setAlignment(Qt::AlignLeft);
        layoutGroupBox->addLayout(hLayout4);
        hLayout4->addWidget(new QLabel("Type : "));
    type = new QComboBox;
        type->setMaximumWidth(100);
        hLayout4->addWidget(type);
        type->addItem("C++");
        type->addItem("C");
        type->insertSeparator(2);
        type->addItem("Java");
        type->insertSeparator(4);
        type->addItem("Html");
        type->addItem("PHP");
        type->insertSeparator(7);
        type->addItem("XML");
        type->insertSeparator(9);
        type->addItem("Autres");
    layoutGroupBox->addItem(new QSpacerItem(0,20));
    addToCurrentProject = new QCheckBox("Ajouter au projet courant");
        addToCurrentProject->setChecked(false);
        layoutGroupBox->addWidget(addToCurrentProject);
    isheader = new QCheckBox("Header");
        isheader->setChecked(false);
        layoutGroupBox->addWidget(isheader);
    QHBoxLayout* hLayout7 = new QHBoxLayout;
        layoutGroupBox->addLayout(hLayout7);
    QPushButton* creerFichier = new QPushButton("Créer");
        creerFichier->setMaximumWidth(100);
        hLayout7->addWidget(creerFichier);
    hLayout7->addWidget(new QLabel("Type : "));
    label_type = new QLabel("Aucun sélectionné !");
        hLayout7->addWidget(label_type);
    hLayout7->addStretch();

    //Nouveau Projet
    AnimatedGroupBox* newGroupBox2 = new AnimatedGroupBox("Nouveau Projet");
        newGroupBox2->addVisibleContrainter(newGroupBox);
        newGroupBox->addVisibleContrainter(newGroupBox2);
    invisibleLayout->addWidget(newGroupBox2);
    newGroupBox2->setVisible(false);
    invisibleLayout->addStretch();
    QVBoxLayout* layoutGroupBox2 = new QVBoxLayout;
    newGroupBox2->setLayout(layoutGroupBox2);
    newGroupBox2->setMinimumWidth(250);
    newGroupBox2->setMaximumWidth(250);
        //Item
    QHBoxLayout* hLayout8 = new QHBoxLayout;
        layoutGroupBox2->addLayout(hLayout8);
    hLayout8->addWidget(new QLabel("Nom du Projet : "));
    QLineEdit* lineEdit_ProjectName = new QLineEdit();
        hLayout8->addWidget(lineEdit_ProjectName);
    QPushButton* parcourir_project = new QPushButton("...");
        parcourir_project->setMaximumWidth(20);
        hLayout8->addWidget(parcourir_project);
    QHBoxLayout* hLayout9 = new QHBoxLayout;
        layoutGroupBox2->addLayout(hLayout9);
    hLayout9->addWidget(new QLabel("Dossier : "));
    QLabel* label_dossier_projet = new QLabel("Aucun sélectionné !");
        hLayout9->addWidget(label_dossier_projet);

    //Bouton ouvrir
    QHBoxLayout* hLayout5 = new QHBoxLayout;
    hLayout5->addStretch();
    vLayout->addLayout(hLayout5);
    QPushButton* ouvrirFichier = new QPushButton("Ouvrir un fichier...");
        ouvrirFichier->setMaximumWidth(200);
        ouvrirFichier->setMinimumWidth(150);
        hLayout5->addWidget(ouvrirFichier);
        hLayout5->addItem(new QSpacerItem(20,0));
    QPushButton* ouvrirProjet = new QPushButton("Ouvrir un projet...");
        ouvrirProjet->setMaximumWidth(200);
        ouvrirProjet->setMinimumWidth(150);
        hLayout5->addWidget(ouvrirProjet);
        hLayout5->addStretch();

    vLayout->addItem(new QSpacerItem(0,35));

    //Fichiers récents
    QPixmap pix_fichiersrecents("images/fichiers_recents.png");
    QPixmap pix_projetsrecents("images/projets_recents.png");
    QPixmap pix_bar("images/bar_menu.png");

    QHBoxLayout* hLayout11 = new QHBoxLayout;
        vLayout->addLayout(hLayout11);
        hLayout11->addStretch();
    QLabel* label_fichiersrecents = new QLabel;
        label_fichiersrecents->setPixmap(pix_fichiersrecents.scaled(150,30,Qt::IgnoreAspectRatio,Qt::SmoothTransformation));
        hLayout11->addWidget(label_fichiersrecents);
    hLayout11->addItem(new QSpacerItem(22,0));
    QLabel* label_projetsrecents = new QLabel;
        label_projetsrecents->setPixmap(pix_projetsrecents.scaled(150,30,Qt::IgnoreAspectRatio,Qt::SmoothTransformation));
        hLayout11->addWidget(label_projetsrecents);
    hLayout11->addStretch();
    pix_bar = pix_bar.scaled(QSize(300,10),Qt::IgnoreAspectRatio,Qt::SmoothTransformation);
    QHBoxLayout* hLayout10 = new QHBoxLayout;
        hLayout10->addStretch();
        vLayout->addLayout(hLayout10);
    label_bar_gauche = new QLabel;
        label_bar_gauche->setPixmap(pix_bar);
        hLayout10->addWidget(label_bar_gauche);
        hLayout10->addItem(new QSpacerItem(22,0));
    label_bar_droite = new QLabel;
        label_bar_droite->setPixmap(pix_bar);
        hLayout10->addWidget(label_bar_droite);
        hLayout10->addStretch();
    QHBoxLayout* hLayout12 = new QHBoxLayout;
        vLayout->addLayout(hLayout12);
        hLayout12->addStretch();
    QGridLayout* gridLayout = new QGridLayout;
        gridLayout->setColumnMinimumWidth(1,300);
        gridLayout->setColumnMinimumWidth(2,22);
        gridLayout->setColumnMinimumWidth(3,300);
        hLayout12->addLayout(gridLayout);
        hLayout12->addStretch();
    vLayout2 = new QVBoxLayout;
        gridLayout->addLayout(vLayout2,1,1,Qt::AlignRight);
    vLayout3 = new QVBoxLayout;
        gridLayout->addLayout(vLayout3,1,3,Qt::AlignLeft);
    createRecentFile(); //vLayout2
    //createRecentProject(); //vLayout3

    vLayout->addStretch();
    setStyle(new QPlastiqueStyle());

    connect(newFichier,SIGNAL(pressed()),newGroupBox,SLOT(animate()));
    connect(newProject,SIGNAL(pressed()),newGroupBox2,SLOT(animate()));
    connect(parcourir,SIGNAL(pressed()),this,SLOT(fichier_parcourir()));
    connect(type,SIGNAL(activated(int)),this,SLOT(discoverType()));
    connect(isheader,SIGNAL(stateChanged(int)),this,SLOT(discoverType()));
    connect(creerFichier,SIGNAL(pressed()),this,SLOT(createNewFile()));
    connect(ouvrirFichier,SIGNAL(pressed()),this,SLOT(sendOpenFileRequest()));
    connect(ouvrirProjet,SIGNAL(pressed()),this,SLOT(sendOpenProjectRequest()));
}

AProHomePage::~AProHomePage()
{
}

void AProHomePage::createRecentFile()
{
    QFile file("data.xml");
    if(!file.open(QIODevice::ReadOnly))
    {
        QMessageBox::warning(0,"Erreur","Impossible de trouver le fichier data.xml !");
        return;
    }

    QDomDocument doc("recentFiles");
    if(!doc.setContent(&file))
    {
        QMessageBox::warning(0,"Erreur","Erreur interne");
        return;
    }

    file.close();

    QDomElement root = doc.documentElement();
    if(root.tagName() != "data")
    {
        QMessageBox::warning(0,"Erreur","Fichier data.xml corrompu.");
        return;
    }

    QDomNode n = root.firstChild();
    while(!n.isNull())
    {
        QDomElement element = n.toElement();
        if(element.tagName() == "IDE")
        {
            QDomElement el2 = element.firstChildElement();
            while(!el2.isNull())
            {
                if(el2.tagName() == "recentFiles")
                {
                    QDomElement recFile = el2.firstChildElement();
                    while(!recFile.isNull())
                    {
                        QFileInfo info(recFile.attribute("src"));
                        ClickableLabel* label = new ClickableLabel(info.fileName(),info.absoluteFilePath());
                        connect(label,SIGNAL(clicked(QString)),this,SLOT(sendNewFile_slot(QString)));
                        vLayout2->addWidget(label);
                        recFile = recFile.nextSiblingElement();
                    }
                }

                el2 = el2.nextSiblingElement();
            }
        }

        n = n.nextSibling();
    }
}

void AProHomePage::paintEvent(QPaintEvent *e)
{
    if (!m_bg.isNull())
    {
        QPainter painter(this);
        if (m_stretch.size() != size())
            m_stretch = QPixmap::fromImage(m_bg.scaled(size(), Qt::IgnoreAspectRatio,
                                                           Qt::SmoothTransformation));
        if (!m_stretch.size().isEmpty())
            painter.drawPixmap(rect(), m_stretch);
    }
    QScrollArea::paintEvent(e);
}

bool AProHomePage::event(QEvent* e)
{
    if (e->type() == QEvent::Paint)
    {
        paintEvent((QPaintEvent*)e);
        return true;
    }
    return QScrollArea::event(e);
}

void AProHomePage::fichier_parcourir()
{
    QString fil = QFileDialog::getSaveFileName(0,"Nom et dossier du fichier",QDir::home().absolutePath(),"Tous fichiers(*)");
    if (fil.isEmpty())
        return;
    QFileInfo info(fil);
    label_dossier_fichier->setText(info.absolutePath());
    fileName->setText(info.baseName());
}

/*void AProHomePage::createRecentFile()
{

}*/

void AProHomePage::discoverType()
{
    QString mtype("");

    if (type->currentText() == "C++")
    {
        if (isheader->isChecked())
            mtype = "hpp";
        else
            mtype = "cpp";
    }
    else if (type->currentText() == "C")
    {
        if (isheader->isChecked())
            mtype = "h";
        else
            mtype = "c";
    }
    else if (type->currentText() == "Java")
    {
        mtype = "java";
    }
    else if (type->currentText() == "Html")
    {
        if (isheader->isChecked())
            mtype = "css";
        else
            mtype = "html";
    }
    else if (type->currentText() == "PHP")
    {
        mtype = "php";
    }
    else if (type->currentText() == "XML")
    {
        mtype = "xml";
    }
    else
    {
        mtype = "Autres";
    }

    label_type->setText(mtype);
}

void AProHomePage::createNewFile()
{
    if (fileName->text().isEmpty())
        return;
    if (label_dossier_fichier->text().isEmpty())
        return;

    AProFileForm* fileForm = new AProFileForm;
    fileForm->setFile(label_dossier_fichier->text()+QString("/")+fileName->text()+QString(".")+label_type->text());

    if (type->currentText() == "C++")
        fileForm->setFileType(AProFileForm::Cpp);
    else if (type->currentText() == "C")
        fileForm->setFileType(AProFileForm::C);
    else if (type->currentText() == "Java")
        fileForm->setFileType(AProFileForm::Java);
    else if (type->currentText() == "Html")
        fileForm->setFileType(AProFileForm::Html);
    else if (type->currentText() == "PHP")
        fileForm->setFileType(AProFileForm::PHP);
    else if (type->currentText() == "XML")
        fileForm->setFileType(AProFileForm::XML);
    else
        fileForm->setFileType(AProFileForm::Autres);

    emit sendNewFile(fileForm);
}

void AProHomePage::sendNewFile_slot(QString _str)
{
    QFileInfo info(_str);
    AProFileForm* form = new AProFileForm;
    form->setName(info.fileName());
    form->setFile(info.absoluteFilePath());
    form->setFileType(AProFileForm::getFileTypeFromString(info.suffix()));
    form->setType(info.suffix());
    form->setIfHeader(AProFileForm::isExtensionHeader(info.suffix()));

    emit sendOpenFile(form);
}

void AProHomePage::sendOpenFileRequest()
{
    emit openFileRequest();
}

void AProHomePage::sendOpenProjectRequest()
{
    emit openProjectRequest();
}

AnimatedGroupBox::AnimatedGroupBox(QString titre,QWidget* parent)
: QGroupBox(titre,parent)
{
    resize(QSize(width(),0));
    alreadyAnimated = false;
}

void AnimatedGroupBox::animate()
{
    for (int i = 0; i < contraintersList.size(); i++)
    {
        if (contraintersList[i]->isVisible())
            contraintersList[i]->animate();
    }

    if (!alreadyAnimated)
    {
        setVisible(true);
        QPropertyAnimation* animation = new QPropertyAnimation(this,"size");
        animation->setDuration(400);
        animation->setStartValue(QSize(width(),0));
        animation->setEndValue(QSize(width(),height()));
        animation->start();
        alreadyAnimated = true;
    }
    else
    {
        QPropertyAnimation* animation = new QPropertyAnimation(this,"size");
        animation->setDuration(400);
        animation->setStartValue(QSize(width(),height()));
        animation->setEndValue(QSize(width(),0));
        animation->start();
        connect(animation,SIGNAL(finished()),SLOT(cleanLater()));
        alreadyAnimated = false;
    }
}
