#include "fenIDE.h"
#define sv settingsLangue->value(
#define vs ).toString()

fenIDE::fenIDE(QWidget *parent) : QMainWindow(parent)
{
        init();
        createLexers();
        createActions();
        createMenu();
        createToolBar();
        createTabBar();
        createDocks();
        createStatusBar();

        seeHomePage();
        MAJ_menuIDE(-1);
}

fenIDE::~fenIDE()
{
    delete IDE_Tab;
}

void fenIDE::init()
{
    settings = new QSettings("conf/options.ini",QSettings::IniFormat);
    langue = "conf/"+settings->value("ALL/language","Francais").value<QString>() + ".ini";
    settingsLangue = new QSettings(langue,QSettings::IniFormat);

    projetOuvert = false;
    numero_Fichier_IDE = 0;
    activatedProject = NULL;
}

void fenIDE::createActions()
{
    //Fichier
    menuIDE_Fichier_EmptyFile = new QAction(tr("Fichier vide"),this);
    menuIDE_Fichier_GroupedFile = new QAction(tr("Fichier CPP/C avec header"),this);
    menuIDE_Fichier_Project = new QAction(tr("Nouveau projet"),this);
    menuIDE_Fichier_Ouvrir = new QAction(QIcon("icones/ouvrir.png"),tr("Ouvrir..."),this);
    menuIDE_Fichier_OuvrirProjet = new QAction(QIcon("icones/Atlanti.ico"),tr("Ouvrir un projet..."),this);
    menuIDE_Fichier_Enregistrer = new QAction(QIcon("icones/save.png"),sv"menuIDE_Fichier_Enregistrer"vs,this);
    menuIDE_Fichier_EnregistrerSous = new QAction(QIcon("icones/save.png"),sv"menuIDE_Fichier_EnregistrerSous"vs,this);
    saveCurrentProject = new QAction(QIcon("icones/save.png"),tr("Sauver le projet courant"),this);
    menuIDE_Fichier_ToutEnregistrer = new QAction(QIcon("icones/saveAll.png"),tr("Tout Enregistrer"),this);

    //Options
    QActionGroup *IDE_parserGroup = new QActionGroup(this);
        menuIDE_Options_Parser_CPP = IDE_parserGroup->addAction(settingsLangue->value("menuIDE_Options_Parser_CPP").toString());
            menuIDE_Options_Parser_CPP->setCheckable(true);
        menuIDE_Options_Parser_HTML = IDE_parserGroup->addAction(settingsLangue->value("menuIDE_Options_Parser_HTML").toString());
            menuIDE_Options_Parser_HTML->setCheckable(true);
        menuIDE_Options_Parser_PHP = IDE_parserGroup->addAction(settingsLangue->value("menuIDE_Options_Parser_PHP").toString());
            menuIDE_Options_Parser_PHP->setCheckable(true);
        menuIDE_Options_Parser_XML = IDE_parserGroup->addAction(settingsLangue->value("menuIDE_Options_Parser_XML").toString());
            menuIDE_Options_Parser_XML->setCheckable(true);
        menuIDE_Options_Parser_JAVA = IDE_parserGroup->addAction(settingsLangue->value("menuIDE_Options_Parser_JAVA").toString());
            menuIDE_Options_Parser_JAVA->setCheckable(true);
        menuIDE_Options_Parser_NULL = IDE_parserGroup->addAction("Aucun Parser");
            menuIDE_Options_Parser_NULL->setCheckable(true);

     menuIDE_Options_ZoomIn = new QAction(QIcon("icones/viewmag+.png"),sv"menuIDE_Options_ZoomIn"vs,this);
     menuIDE_Options_ZoomOut = new QAction(QIcon("icones/viewmag-.png"),sv"menuIDE_Options_ZoomOut"vs,this);
     reinitZoom = new QAction(tr("Réinitialiser le niveau de zoom"),this);

     connect(IDE_parserGroup,SIGNAL(triggered(QAction *)),this,SLOT(changerParser(QAction *)));
     connect(menuIDE_Fichier_EmptyFile,SIGNAL(triggered()),this,SLOT(nouveauFichierVide()));
     connect(menuIDE_Fichier_GroupedFile,SIGNAL(triggered()),this,SLOT(nouveauGroup()));
     connect(menuIDE_Fichier_Project,SIGNAL(triggered()),this,SLOT(nouveauProjet()));
     connect(menuIDE_Options_ZoomIn,SIGNAL(triggered()),this,SLOT(zoom_in()));
     connect(menuIDE_Options_ZoomOut,SIGNAL(triggered()),this,SLOT(zoom_out()));
     connect(reinitZoom,SIGNAL(triggered()),this,SLOT(resetZoom()));
     connect(menuIDE_Fichier_EnregistrerSous,SIGNAL(triggered()),this,SLOT(saveFileSous()));
     connect(menuIDE_Fichier_Enregistrer,SIGNAL(triggered()),this,SLOT(saveFile()));
     connect(menuIDE_Fichier_ToutEnregistrer,SIGNAL(triggered()),this,SLOT(saveAllFiles()));
     connect(menuIDE_Fichier_Ouvrir,SIGNAL(triggered()),this,SLOT(openFile()));
     connect(menuIDE_Fichier_OuvrirProjet,SIGNAL(triggered()),this,SLOT(openProject()));
     connect(saveCurrentProject,SIGNAL(triggered()),this,SLOT(saveProject()));
}

void fenIDE::createMenu()
{
    menuBar()->setStyle(new QCleanlooksStyle());
    menuIDE_Fichier = menuBar()->addMenu(sv"menuIDE_Fichier"vs);
        menuIDE_Fichier_Nouveau = menuIDE_Fichier->addMenu(sv"menuIDE_Fichier_Nouveau"vs);
            menuIDE_Fichier_Nouveau->addAction(menuIDE_Fichier_EmptyFile);
            menuIDE_Fichier_Nouveau->addAction(menuIDE_Fichier_GroupedFile);
            menuIDE_Fichier_Nouveau->addSeparator();
            menuIDE_Fichier_Nouveau->addAction(menuIDE_Fichier_Project);
        menuIDE_Fichier->addSeparator();
        menuIDE_Fichier->addAction(menuIDE_Fichier_Ouvrir);
        menuIDE_Fichier->addAction(menuIDE_Fichier_OuvrirProjet);
        menuIDE_Fichier->addSeparator();
        menuIDE_Fichier->addAction(menuIDE_Fichier_Enregistrer);
        menuIDE_Fichier->addAction(menuIDE_Fichier_EnregistrerSous);
        menuIDE_Fichier->addAction(saveCurrentProject);
        menuIDE_Fichier->addAction(menuIDE_Fichier_ToutEnregistrer);
    menuIDE_Options = menuBar()->addMenu(sv"menuIDE_Options"vs);
        menuIDE_Options_Parser = menuIDE_Options->addMenu(settingsLangue->value("menuIDE_Option_Parser").toString());
            menuIDE_Options_Parser->addAction(menuIDE_Options_Parser_CPP);
            menuIDE_Options_Parser->addAction(menuIDE_Options_Parser_HTML);
            menuIDE_Options_Parser->addAction(menuIDE_Options_Parser_PHP);
            menuIDE_Options_Parser->addAction(menuIDE_Options_Parser_XML);
            menuIDE_Options_Parser->addAction(menuIDE_Options_Parser_JAVA);
            menuIDE_Options_Parser->addAction(menuIDE_Options_Parser_NULL);
        menuIDE_Options->addSeparator();
        menuIDE_Options->addAction(menuIDE_Options_ZoomIn);
        menuIDE_Options->addAction(menuIDE_Options_ZoomOut);
        menuIDE_Options->addAction(reinitZoom);
}

void fenIDE::createToolBar()
{
    IDEToolBar = addToolBar(sv"IDEToolBar"vs);
        IDEToolBar->addAction(menuIDE_Options_ZoomOut);
        IDEToolBar->addAction(menuIDE_Options_ZoomIn);
    IDEToolBar->addSeparator();
    IDEToolBar->addAction(menuIDE_Fichier_Enregistrer);
    IDEToolBar->addAction(menuIDE_Fichier_ToutEnregistrer);
}

void fenIDE::createLexers()
{
    lexerCpp = new QsciLexerCPP;
    lexerHTML = new QsciLexerHTML;
    lexerJava = new QsciLexerJava;
    lexerXML = new QsciLexerXML;
}

void fenIDE::createTabBar()
{
    IDE_Tab = new ATabWidget;
    setCentralWidget(IDE_Tab);
    IDE_Tab->setTabsClosable(true);
    IDE_Tab->tabBar()->setMovable(true);
    IDE_Tab->tabBar()->setShape(QTabBar::RoundedNorth);
    IDE_Tab->tabBar()->setDrawBase(false);

    connect(IDE_Tab,SIGNAL(tabCloseRequested(int)),this,SLOT(supprimerTab(int)));
    connect(IDE_Tab,SIGNAL(currentChanged(int)),this,SLOT(MAJ_menuIDE(int)));
    connect(IDE_Tab->tabBar(),SIGNAL(tabMoved(int,int)),this,SLOT(reloadTab(int,int)));
}

void fenIDE::createDocks()
{
    IDE_Dock_Outils = new QDockWidget(sv"IDE_Dock_Outils"vs,this);
    IDE_Dock_Outils->setAllowedAreas(Qt::LeftDockWidgetArea|Qt::RightDockWidgetArea);
    addDockWidget(Qt::LeftDockWidgetArea,IDE_Dock_Outils);
        contenu_IDE_Dock_Outils = new QWidget;
        contenu_IDE_Dock_Outils->setMinimumWidth(200);
        IDE_Dock_Outils->setWidget(contenu_IDE_Dock_Outils);
    QVBoxLayout* newLayout = new QVBoxLayout;
        contenu_IDE_Dock_Outils->setLayout(newLayout);

    treeWidget = new treeWidgetWRC;
        treeWidget->setHeaderHidden(true);
        treeWidget->setAnimated(true);
        treeWidget->setMouseTracking(true);
        newLayout->addWidget(treeWidget);

    connect(treeWidget,SIGNAL(itemRClicked(QTreeWidgetItem*,int,QPoint)),this,SLOT(itemContextMenuEvent(QTreeWidgetItem*,int,QPoint)));
    connect(treeWidget,SIGNAL(itemDoubleClicked(QTreeWidgetItem *, int )),this,SLOT(openProjectItem(QTreeWidgetItem*,int)));
}

void fenIDE::createStatusBar()
{
    Etat_IDE = statusBar();
    label_readWriteIndic = new QLabel(sv"Etat_IDE_addPermanentWidget"vs);
        Etat_IDE->addPermanentWidget(label_readWriteIndic);
}

void fenIDE::nouveauFichierVide()
{
    numero_Fichier_IDE++;
    QString Texte = "";
    if (!projetOuvert)
        Texte = "Nouveau_Fichier" + QString::number(numero_Fichier_IDE) + ".cpp";
    else
    {
        if (QMessageBox::question(this,"Appartenance au projet", QString("Voulez-vous ajouter votre fichier au projet %1 en cours ?").arg(activatedProject->text(0)),QMessageBox::Yes | QMessageBox::No) == QMessageBox::Yes)
        {
            addNewFileToProject(false);
            return;
        }
        else
            Texte = "Nouveau_Fichier" + QString::number(numero_Fichier_IDE) + ".cpp";
    }
            documentIDE *scintilla = new documentIDE;
            scintilla->setMarginLineNumbers(1,true);
            scintilla->setMarginWidth(1,50);
            scintilla->setLexer(lexerCpp);
            scintilla->setAutoIndent(true);
            scintilla->setIndentationGuides(true);
            scintilla->setIndentationsUseTabs(true);
            scintilla->setAutoCompletionSource(QsciScintilla::AcsAll);
            scintilla->setAutoCompletionReplaceWord(true);
            scintilla->setAutoCompletionThreshold(2);
            scintilla->setCaretWidth(2);
            scintilla->setFolding(QsciScintilla::CircledTreeFoldStyle,3);
            scintilla->setBraceMatching(QsciScintilla::SloppyBraceMatch);
            scintilla->setUtf8(true);
            scintilla->zoomIn(2);
            scintilla->setSaved(false);
            scintilla->setModified(false);
            scintilla->setWrapMode(QsciScintilla::WrapWord);
    scintilla->setTab(IDE_Tab->addTab(scintilla,QIcon("icones/warning.png"),(Texte)));

    IDE_Tab->setCurrentIndex(scintilla->wichTab());

    MAJ_menuIDE(-1);

    connect(scintilla,SIGNAL(unsaved(int)),this,SLOT(unsavedTab(int)));
}

void fenIDE::closeProject(QTreeWidgetItem* item)
{
    if (item == NULL)
    {
        item = tempItem;
        if (item == NULL)
            return;
    }

    if (item->text(2) != "projectItem")
        return;

    for (int i = 0; i < IDE_Tab->count();)
    {
        documentIDE* doc = scintillaAt(i);
        if (doc != NULL)
        {
            if (doc->beliveToProject() == item)
                supprimerTab(i);
        }
        else
            i++;
    }
    projects[item].saveProject();
    treeWidget->invisibleRootItem()->removeChild(item);
    projects.erase(projects.find(item));
}

void fenIDE::addNewFileToProject(bool __temp)
{
    QTreeWidgetItem* project;
    if (__temp)
        project = tempItem;
    else
        project = activatedProject;

    if (project == NULL)
        return;
    else if (project->text(2) != "projectItem")
        return;

    QString name = QFileDialog::getSaveFileName(0,"Sauver le fichier",project->text(1),"Tous (*)");
    if (name == "")
        return;

            documentIDE *scintilla = new documentIDE;
            scintilla->setMarginLineNumbers(1,true);
            scintilla->setMarginWidth(1,50);
            scintilla->setLexer(lexerCpp);
            scintilla->setAutoIndent(true);
            scintilla->setIndentationGuides(true);
            scintilla->setIndentationsUseTabs(true);
            scintilla->setAutoCompletionSource(QsciScintilla::AcsAll);
            scintilla->setAutoCompletionReplaceWord(true);
            scintilla->setAutoCompletionThreshold(2);
            scintilla->setCaretWidth(2);
            scintilla->setFolding(QsciScintilla::CircledTreeFoldStyle,3);
            scintilla->setBraceMatching(QsciScintilla::SloppyBraceMatch);
            scintilla->setUtf8(true);
            scintilla->zoomIn(2);
            scintilla->setSaved(false);
            scintilla->setModified(false);
            scintilla->setProjectBeliving(project);
            scintilla->setFile(name);
            scintilla->setWrapMode(QsciScintilla::WrapWord);
    scintilla->setTab(IDE_Tab->addTab(scintilla,QIcon("icones/warning.png"),QFileInfo(name).fileName()));
    IDE_Tab->setCurrentIndex(scintilla->wichTab());

    MAJ_menuIDE(-1);

    QFile file(name);
    file.open(QIODevice::WriteOnly | QIODevice::Truncate);
    file.close();
    projects[project].addFile(QFileInfo(name).fileName());
    projects[project].saveProject();
    reloadProject(project);

    connect(scintilla,SIGNAL(unsaved(int)),this,SLOT(unsavedTab(int)));
}

void fenIDE::nouveauGroup()
{
}

void fenIDE::nouveauProjet()
{
}

void fenIDE::supprimerTab(int index)
{
    documentIDE* docdoc = scintillaAt(index);
    if (docdoc == NULL)
    {
        supprimerNormalTab(index);
        return;
    }

    if (!docdoc->isSaved())
    {
        if(QMessageBox::warning(0,"Attention",QString("Le fichier %1 a été modifié et n'as pas été sauvegardé ! Voulez-vous le faire maintenant ?").arg(IDE_Tab->widget(index)->findChild<documentIDE*>()->getFile()->fileName()),QMessageBox::Yes|QMessageBox::No)==QMessageBox::Yes)
            saveFile(index);
    }
    if (IDE_Tab->count() != 1)
    {
        IDE_Tab->removeTab(index);
        for (int i = 0; i < IDE_Tab->count(); i++)
        {
            documentIDE* doc = scintillaAt(i);
            if (doc != NULL)
                doc->setTab(i);
        }
    }
    else
    {
        seeHomePage();
        IDE_Tab->removeTab(index);
    }
}

void fenIDE::supprimerNormalTab(int index)
{
    if (IDE_Tab->count() != 1)
    {
        IDE_Tab->removeTab(index);
        for (int i = 0; i < IDE_Tab->count(); i++)
        {
            documentIDE* doc = scintillaAt(i);
            if (doc != NULL)
                doc->setTab(i);
        }
    }
    else
    {
        seeHomePage();
        IDE_Tab->removeTab(index);
    }
}

void fenIDE::changerParser(QAction *action)
{
    documentIDE* doc = scintillaActuel();
    if (doc == NULL)
        return;

    if (menuIDE_Options_Parser_CPP->isChecked())
    {
        scintillaActuel()->setLexer(lexerCpp);
        Etat_IDE->showMessage(QString("Parser : Cpp"),20000);
    }
    else if (menuIDE_Options_Parser_HTML->isChecked())
    {
        scintillaActuel()->setLexer(lexerHTML);
        Etat_IDE->showMessage(QString("Parser : HTML"),20000);
    }
    else if (menuIDE_Options_Parser_PHP->isChecked())
    {
        QMessageBox::critical(NULL,"Attention","Le parseur pour PHP est en cours de construction !<br />Veuillez attendre d'autres mises à jour...");
    }
    else if (menuIDE_Options_Parser_XML->isChecked())
    {
        scintillaActuel()->setLexer(lexerXML);
        Etat_IDE->showMessage(QString("Parser : XML"),20000);
    }
    else if (menuIDE_Options_Parser_JAVA->isChecked())
    {
        scintillaActuel()->setLexer(lexerJava);
        Etat_IDE->showMessage(QString("Parser : Java(simple)"),20000);
    }
    else
    {
        scintillaActuel()->setLexer(0);
        Etat_IDE->showMessage(QString("Aucun Parser"),20000);
    }
}

documentIDE *fenIDE::scintillaActuel()
{
    return castTo<QWidget, documentIDE>(IDE_Tab->currentWidget());
}

documentIDE* fenIDE::scintillaAt(int index)
{
    return castTo<QWidget, documentIDE>(IDE_Tab->widget(index));
}

void fenIDE::MAJ_menuIDE(int index)
{
    QsciScintilla *sciScintillaActuel = NULL;
    if (index > 0)
        sciScintillaActuel = scintillaAt(index);
    else
        sciScintillaActuel = scintillaActuel();

    if (sciScintillaActuel == NULL)
    {
        menuIDE_Options_Parser->setEnabled(false);
        menuIDE_Options_ZoomIn->setEnabled(false);
        menuIDE_Options_ZoomOut->setEnabled(false);
        reinitZoom->setEnabled(false);
        return;
    }

    menuIDE_Options_Parser->setEnabled(true);
    menuIDE_Options_ZoomIn->setEnabled(true);
    menuIDE_Options_ZoomOut->setEnabled(true);
    reinitZoom->setEnabled(true);

    if (sciScintillaActuel->lexer() == lexerCpp)
    {
        menuIDE_Options_Parser_CPP->setChecked(true);
    }
    else if (sciScintillaActuel->lexer() == lexerHTML)
    {
        menuIDE_Options_Parser_HTML->setChecked(true);
    }
    else if (sciScintillaActuel->lexer() == lexerJava)
    {
        menuIDE_Options_Parser_JAVA->setChecked(true);
    }
    else if (sciScintillaActuel->lexer() == lexerXML)
    {
        menuIDE_Options_Parser_XML->setChecked(true);
    }
    else
    {
        menuIDE_Options_Parser_NULL->setChecked(true);
    }
}

void fenIDE::zoom_in()
{
    if (scintillaActuel() != NULL)
        scintillaActuel()->zoomIn();
}

void fenIDE::zoom_out()
{
    if (scintillaActuel() != NULL)
        scintillaActuel()->zoomOut();
}

void fenIDE::resetZoom()
{
    if (scintillaActuel() != NULL)
        scintillaActuel()->zoomTo(2);
}

void fenIDE::unsavedTab(int tab)
{
    IDE_Tab->setTabIcon(tab,QIcon("icones/warning.png"));
}

void fenIDE::saveFileSous(int index)
{
    if (index == 0)
        index = IDE_Tab->currentIndex();

    QFile file(QFileDialog::getSaveFileName(0,tr("Enregistrer sous..."),QDir::home().absolutePath(),tr("Tout (*)")));
    if (!file.open(QIODevice::ReadWrite))
        return;
    documentIDE* document = (documentIDE*)IDE_Tab->widget(index);
    if (document == NULL)
        return;

    file.write(document->text().toUtf8());
    file.close();
    document->setSaved(true);
    IDE_Tab->setTabIcon(index,QIcon("icones/valid.png"));
    IDE_Tab->setTabText(index,QFileInfo(file).fileName());

    document->setFile(QFileInfo(file));
}

void fenIDE::saveFile()
{
    documentIDE* document = scintillaActuel();
    if (document == NULL)
        return;

    QFile file(document->getFile()->absoluteFilePath());
    if (!file.open(QIODevice::ReadWrite|QIODevice::Truncate))
    {
        if(!file.exists())
        {
            saveFileSous();
            return;
        }
        else
            return;
    }

    file.write(document->text().toUtf8());
    file.close();
    document->setSaved(true);
    IDE_Tab->setTabIcon(IDE_Tab->currentIndex(),QIcon("icones/valid.png"));
    IDE_Tab->setTabText(IDE_Tab->currentIndex(),QFileInfo(file).fileName());
}

void fenIDE::saveFile(int index)
{
    documentIDE* document = scintillaAt(index);
    if (document == NULL)
        return;

    QFile file(document->getFile()->absoluteFilePath());
    if (!file.open(QIODevice::ReadWrite|QIODevice::Truncate))
    {
        if(!file.exists())
        {
            saveFileSous(index);
            return;
        }
        else
            return;
    }

    file.write(document->text().toUtf8());
    file.close();
    document->setSaved(true);
    IDE_Tab->setTabIcon(index,QIcon("icones/valid.png"));
    IDE_Tab->setTabText(index,QFileInfo(file).fileName());
}

void fenIDE::saveAllFiles()
{
    for (int i = 0; i < IDE_Tab->count(); i++)
        saveFile(i);
}

void fenIDE::openFile()
{
    QString FileName = QFileDialog::getOpenFileName(0,"Ouvrir...",QDir::home().absolutePath(),"Tous fichiers (*)");
    if (FileName == "")
        return;

    return openFile(FileName,lexerCpp);
}

void fenIDE::openFile(QString fileName,QsciLexer* lexer)
{
            documentIDE *scintilla = new documentIDE;
            scintilla->setMarginLineNumbers(1,true);
            scintilla->setMarginWidth(1,50);
            scintilla->setLexer(lexer);
            scintilla->setAutoIndent(true);
            scintilla->setIndentationGuides(true);
            scintilla->setIndentationsUseTabs(true);
            scintilla->setAutoCompletionSource(QsciScintilla::AcsAll);
            scintilla->setAutoCompletionReplaceWord(true);
            scintilla->setAutoCompletionThreshold(2);
            scintilla->setCaretWidth(2);
            scintilla->setFolding(QsciScintilla::CircledTreeFoldStyle,3);
            scintilla->setBraceMatching(QsciScintilla::SloppyBraceMatch);
            scintilla->setUtf8(true);
            scintilla->zoomIn(2);
            scintilla->setModified(false);
            scintilla->setWrapMode(QsciScintilla::WrapWord);
            QFile file(fileName);
            file.open(QIODevice::ReadOnly);
            scintilla->read(&file);
            file.close();
            scintilla->setFile(fileName);
            scintilla->setSaved(true);
    scintilla->setTab(IDE_Tab->addTab(scintilla,QIcon("icones/valid.png"),QFileInfo(fileName).fileName()));

    IDE_Tab->setCurrentIndex(scintilla->wichTab());

    MAJ_menuIDE(-1);

    connect(scintilla,SIGNAL(unsaved(int)),this,SLOT(unsavedTab(int)));
}

void fenIDE::openFile(AProFileForm* form)
{
    documentIDE *scintilla = new documentIDE;
    scintilla->setMarginLineNumbers(1,true);
    scintilla->setMarginWidth(1,50);
    if (form->fileType() == AProFileForm::Cpp || form->fileType() == AProFileForm::C)
        scintilla->setLexer(lexerCpp);
    scintilla->setAutoIndent(true);
    scintilla->setIndentationGuides(true);
    scintilla->setIndentationsUseTabs(true);
            scintilla->setAutoCompletionSource(QsciScintilla::AcsAll);
            scintilla->setAutoCompletionReplaceWord(true);
            scintilla->setAutoCompletionThreshold(2);
            scintilla->setCaretWidth(2);
            scintilla->setFolding(QsciScintilla::CircledTreeFoldStyle,3);
            scintilla->setBraceMatching(QsciScintilla::SloppyBraceMatch);
            scintilla->setUtf8(true);
            scintilla->zoomIn(2);
            scintilla->setModified(false);
            if (form->hasToBeHadToCurProj())
                scintilla->setProjectBeliving(activatedProject);
            scintilla->setWrapMode(QsciScintilla::WrapWord);
            QFile file(form->fileInfo().absoluteFilePath());
            file.open(QIODevice::ReadOnly);
            scintilla->read(&file);
            file.close();
            scintilla->setFile(form->fileInfo().absoluteFilePath());
            scintilla->setSaved(true);
    scintilla->setTab(IDE_Tab->addTab(scintilla,QIcon("icones/valid.png"),form->fileInfo().fileName()));

    IDE_Tab->setCurrentIndex(scintilla->wichTab());

    MAJ_menuIDE(-1);

    connect(scintilla,SIGNAL(unsaved(int)),this,SLOT(unsavedTab(int)));
}

void fenIDE::closeEvent(QCloseEvent* event)
{
    int countTab = IDE_Tab->count();
    for (int i = 0; i < countTab; i++)
    {
        supprimerTab(0);
    }
}

bool fenIDE::event(QEvent* event)
{
    if (event->type() == 19)
    {
        closeEvent(new QCloseEvent());
        return true;
    }
    else
        return QMainWindow::event(event);
}

void fenIDE::openProject()
{
    QString path = QFileDialog::getOpenFileName(0,tr("Ouverture d'un projet"),QDir::home().absolutePath(),tr("Projets (*.aproject)"));
    if (path == "")
        return;

    AProProject newProject(path);
    newProject.parseFile();
    QDir currentDir(newProject.dir());

    QTreeWidgetItem* root = new QTreeWidgetItem(treeWidget);
    root->setText(0,newProject.getName());
    root->setText(1,newProject.dir());
    root->setText(2,"projectItem");
    root->setData(0,Qt::DecorationRole,QIcon("icones/Atlanti.ico"));
    const QList<QString>* src = newProject.sources();
    if (src->count() > 0)
    {
        QTreeWidgetItem* srcRoot = new QTreeWidgetItem;
        srcRoot->setText(0,"Sources");
        srcRoot->setText(2,"srcItem");
        srcRoot->setData(0,Qt::DecorationRole,QIcon("icones/ouvrir.png"));
        root->addChild(srcRoot);
        filterDirectory(srcRoot,currentDir,src,true);
    }

    src = newProject.headers();
    if (src->count() > 0)
    {
        QTreeWidgetItem* srcRoot = new QTreeWidgetItem;
        srcRoot->setText(0,"Headers");
        srcRoot->setText(2,"srcItem");
        srcRoot->setData(0,Qt::DecorationRole,QIcon("icones/ouvrir.png"));
        root->addChild(srcRoot);
        filterDirectory(srcRoot,currentDir,src,true);
    }

    activateProject(root);
    projects[root] = newProject;
}

bool fenIDE::filterDirectory(QTreeWidgetItem* root,QDir dir,const QList<QString>* liste,bool reinit)
{
    static int totfilesvues;
    if (reinit)
        totfilesvues = 0;

    if (totfilesvues == liste->count())
        return false;

    QFileInfoList list = dir.entryInfoList(QDir::AllDirs|QDir::Files|QDir::NoDotAndDotDot|QDir::NoSymLinks,QDir::DirsFirst);
    int i,j=0;
    for (i = 0; i < list.count(); i++)
    {
        if (!list[i].exists())
            continue;
        else if (list[i].isDir())
        {
            QTreeWidgetItem* newDir = new QTreeWidgetItem;
            newDir->setText(0,list[i].fileName());
            newDir->setData(0,Qt::DecorationRole,QIcon("icones/ouvrir.png"));
            newDir->setText(2,"dirItem");

            if (filterDirectory(newDir,QDir(list[i].absoluteFilePath()),liste))
            {
                root->addChild(newDir);
            }
        }
        else if (list[i].isFile())
        {
            if ((liste->contains(list[i].fileName()))&&(totfilesvues <= liste->count()))
            {
                QTreeWidgetItem* newItem = new QTreeWidgetItem;
                newItem->setText(0,list[i].fileName());
                newItem->setText(2,"fileItem");

                QString suffix = list[i].suffix();
                if (suffix == "c")
                    newItem->setData(0,Qt::DecorationRole,QIcon("icones/source_c.png"));
                else if (suffix == "cpp")
                    newItem->setData(0,Qt::DecorationRole,QIcon("icones/source_cpp.png"));
                else if (suffix == "h")
                    newItem->setData(0,Qt::DecorationRole,QIcon("icones/source_h.png"));

                root->addChild(newItem);
                j++;
                totfilesvues++;
            }
        }
    }

    if(j > 0)
        return true;
    else
        return false;
}

void fenIDE::itemContextMenuEvent(QTreeWidgetItem* item,int column,QPoint pos)
{
    if (!item)
        return;

    tempItem = item;

    if (item->text(2) == "projectItem")
    {
        QMenu projectMenu(this);
        QAction* sauverProjet = projectMenu.addAction("Sauver le projet");

        QAction* activerProjet = projectMenu.addAction("Activer le projet");
        if (activatedProject == item)
            activerProjet->setEnabled(false);
        else
            activerProjet->setEnabled(true);

        QAction* fermerProjet = projectMenu.addAction("Fermer le projet");
        projectMenu.addSeparator();
        QMenu* ajouterUnFichier = projectMenu.addMenu("Ajouter Fichier...");
            QAction* addSource = ajouterUnFichier->addAction("Fichier source");
            QAction* addResource = ajouterUnFichier->addAction("Resource");

        connect(activerProjet,SIGNAL(triggered()),this,SLOT(activateProject()));
        connect(sauverProjet,SIGNAL(triggered()),this,SLOT(saveProject()));
        connect(fermerProjet,SIGNAL(triggered()),this,SLOT(closeProject()));
        projectMenu.exec(pos);
    }
    else if (item->text(2) == "dirItem")
    {
        QMenu dirMenu(this);
        dirMenu.addAction("Ajouter fichier...");
        dirMenu.addAction("Ajouter nouveau fichier");
        dirMenu.exec(pos);
    }
    else if (item->text(2) == "fileItem")
    {
        QMenu srcMenu(this);
        srcMenu.addAction("Ouvrir le fichier");
        srcMenu.addAction("Renommer");
        srcMenu.addSeparator();
        srcMenu.addAction("Supprimer");
        srcMenu.addAction("Soustraire du projet");
        srcMenu.addSeparator();
        srcMenu.addAction("Ajouter les includes liées au fichier");
        srcMenu.exec(pos);
    }
}

void fenIDE::openProjectItem(QTreeWidgetItem* item,int column)
{
    if (item->text(2) != "fileItem")
        return;

    //Trouver le path du fichier :
    QTreeWidgetItem* m_parent = item->parent();
    QString path = item->text(0);
    while (m_parent->text(2) != "projectItem")
    {
        if(m_parent->text(2) != "srcItem")
        {
            path.prepend("/");
            path.prepend(m_parent->text(0));
        }
        m_parent = m_parent->parent();
    }
    path.prepend("/");
    path.prepend(m_parent->text(1));

    QFileInfo info(path);

    AProFileForm* form = new AProFileForm;
    form->setAddToCurrProject(true);
    form->setFile(path);
    form->setFileType(AProFileForm::getFileTypeFromString(info.suffix()));
    form->setIfHeader(AProFileForm::isExtensionHeader(info.suffix()));
    form->setName(info.baseName());
    form->setType(info.suffix());

    return openFile(form);
}

void fenIDE::reloadTab(int from, int to)
{
    for (int i = 0; i < IDE_Tab->count(); i++)
    {
        documentIDE* doc = IDE_Tab->widget(i)->findChild<documentIDE *>();
        if (doc != NULL)
            doc->setTab(i);
    }
}

void fenIDE::seeHomePage()
{
    AProHomePage* homepage = new AProHomePage(QImage(""),this);
    IDE_Tab->addTab(homepage,QIcon("icones/accueilIDE.png"),"Accueil");
    connect(homepage,SIGNAL(sendNewFile(AProFileForm*)),this,SLOT(createNewFile(AProFileForm*)));
    connect(homepage,SIGNAL(sendOpenFile(AProFileForm*)),this,SLOT(openFile(AProFileForm*)));
    connect(homepage,SIGNAL(openFileRequest()),this,SLOT(openFile()));
    connect(homepage,SIGNAL(openProjectRequest()),this,SLOT(openProject()));
}

void fenIDE::activateProject(QTreeWidgetItem* item)
{
    if (item == NULL)
        {
            item = tempItem;
            if (item == NULL)
                return;
        }

    if (item->text(2) != "projectItem")
        return;

    if (activatedProject != NULL)
    {
        QFont font("Arial");
        font.setBold(false);
        activatedProject->setFont(0,font);
    }
    activatedProject = item;
    QFont font("Arial");
    font.setBold(true);
    activatedProject->setFont(0,font);

    projetOuvert = true;
}

void fenIDE::saveProject(QTreeWidgetItem* item)
{
    if (item == NULL)
    {
        item = tempItem;
        if (item == NULL)
        {
            item = activatedProject;
            if (item == NULL)
                return;
        }
    }
    if (item->text(2) != "projectItem")
        return;

    label_readWriteIndic->setText(QString(tr("Sauvegarde du projet %1 en cours...")).arg(item->text(0)));
    projects[item].saveProject();
    label_readWriteIndic->setText(tr("Terminé !"));
}

void fenIDE::reloadProject(QTreeWidgetItem* item)
{
    if (item == NULL)
    {
        item = tempItem;
        if (item == NULL)
        {
            item = activatedProject;
            if (item == NULL)
                return;
        }
    }
    if (item->text(2) != "projectItem")
        return;

    for (int i = 0; i < item->childCount(); )
    {
        QTreeWidgetItem* child = item->child(i);
        item->removeChild(child);
    }
    AProProject* projectToReload = &(projects[item]);
    QDir currentDir(projectToReload->dir());

    const QList<QString>* src = projectToReload->sources();
    if (src->count() > 0)
    {
        QTreeWidgetItem* srcRoot = new QTreeWidgetItem;
        srcRoot->setText(0,"Sources");
        srcRoot->setText(2,"srcItem");
        srcRoot->setData(0,Qt::DecorationRole,QIcon("icones/ouvrir.png"));
        item->addChild(srcRoot);
        filterDirectory(srcRoot,currentDir,src,true);
    }

    src = projectToReload->headers();
    if (src->count() > 0)
    {
        QTreeWidgetItem* srcRoot = new QTreeWidgetItem;
        srcRoot->setText(0,"Headers");
        srcRoot->setText(2,"srcItem");
        srcRoot->setData(0,Qt::DecorationRole,QIcon("icones/ouvrir.png"));
        item->addChild(srcRoot);
        filterDirectory(srcRoot,currentDir,src,true);
    }
}

void fenIDE::createNewFile(AProFileForm* form)
{
            documentIDE *scintilla = new documentIDE;
            scintilla->setMarginLineNumbers(1,true);
            scintilla->setMarginWidth(1,50);
            scintilla->setAutoIndent(true);
            scintilla->setIndentationGuides(true);
            scintilla->setIndentationsUseTabs(true);
            scintilla->setAutoCompletionSource(QsciScintilla::AcsAll);
            scintilla->setAutoCompletionReplaceWord(true);
            scintilla->setAutoCompletionThreshold(2);
            scintilla->setCaretWidth(2);
            scintilla->setFolding(QsciScintilla::CircledTreeFoldStyle,3);
            scintilla->setBraceMatching(QsciScintilla::SloppyBraceMatch);
            scintilla->setUtf8(true);
            scintilla->zoomIn(2);
            scintilla->setSaved(false);
            scintilla->setModified(false);
            scintilla->setFile(form->fileInfo());
            scintilla->setWrapMode(QsciScintilla::WrapWord);
    scintilla->setTab(IDE_Tab->addTab(scintilla,QIcon("icones/warning.png"),form->name()+QString(".")+form->getType()));

    IDE_Tab->setCurrentIndex(scintilla->wichTab());
    setParser(form->fileType());

    MAJ_menuIDE(-1);

    if (form->hasToBeHadToCurProj())
    {
        QFile file(form->fileInfo().absoluteFilePath());
        file.open(QIODevice::WriteOnly | QIODevice::Truncate);
        file.close();
        projects[activatedProject].addFile(form->fileInfo().fileName());
        projects[activatedProject].saveProject();
        reloadProject(activatedProject);
        scintilla->setProjectBeliving(activatedProject);
        IDE_Tab->setTabIcon(scintilla->wichTab(),QIcon("icones/valid.png"));
    }

    connect(scintilla,SIGNAL(unsaved(int)),this,SLOT(unsavedTab(int)));
}

void fenIDE::setParser(AProFileForm::FileType type)
{
    if ((type == AProFileForm::C) || (type == AProFileForm::Cpp))
        changerParser(NULL);
}

QsciLexer* fenIDE::getLexerFromType(Type::FileType type)
{

}

void fenIDE::newFile()
{
    static int magicNumber = 0;
    magicNumber++;
    QString file = "unregistered" + QString::number(magicNumber) + ".cpp";
    newFile(AProFileForm(file,(activatedProject!=NULL)));
}

void fenIDE::newFile(const AProFileForm& f)
{
    documentIDE* doc = createNewScintillaZone();
    doc->setFile(f.getFile());
}

documentIDE* fenIDE::createNewScintillaZone()
{
    documentIDE* doc = new documentIDE;
    doc->setMarginLineNumbers(1,true);
    doc->setMarginWidth(1,50);
    doc->setAutoIndent(true);
    doc->setIndentationGuides(true);
    doc->setIndentationsUseTabs(true);
    doc->setAutoCompletionSource(QsciScintilla::AcsAPIs);
    doc->setAutoCompletionReplaceWord(true);
    doc->setAutoCompletionThreshold(2);
    doc->setCaretWidth(2);
    doc->setFolding(QsciScintilla::CircledTreeFoldStyle,3);
    doc->setBraceMatching(QsciScintilla::SloppyBraceMatch);
    doc->setUtf8(true);
    doc->zoomIn(2);
    doc->setSaved(false);
    doc->setModified(false);
    doc->setWrapMode(QsciScintilla::WrapWord);
    doc->setTab(IDE_Tab->addTab(doc,QIcon("icones/warning.png"),"new_zone"));
    IDE_Tab->setCurrentIndex(doc->wichTab());

    return doc;
}

///-------------------------------------
///-------------------------------------
///-------------------------------------

documentIDE::documentIDE(QFile fichier)
{
    saved = true;
    setProjectBeliving(NULL);
    connect(this,SIGNAL(textChanged()),this,SLOT(changeSafety()));
}

documentIDE::~documentIDE()
{
}

void documentIDE::changeSafety()
{
    timer = new QTimer;
    timer->setSingleShot(true);
    timer->start(2000);
    saved = false;
    emit unsaved(tab);
    connect(timer,SIGNAL(timeout()),this,SLOT(changeModification()));
}

///-------------------------------------
///-------------------------------------
///-------------------------------------

treeWidgetWRC::treeWidgetWRC(QWidget* parent)
 : QTreeWidget(parent)
{

}

void treeWidgetWRC::mousePressEvent(QMouseEvent* e)
{
        filterEvent(e);
}

void treeWidgetWRC::filterEvent(QMouseEvent* e)
{
    if (e->button() == Qt::RightButton)
    {
        QTreeWidgetItem* item = itemAt(e->pos());
        int column = 0;
        emit itemRClicked(item,column,e->globalPos());
    }
    else
        QTreeView::mousePressEvent(e);
}

///-------------------------------------
///-------------------------------------
///-------------------------------------

namespace scintilla
{

}
