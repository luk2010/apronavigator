#ifndef FENIDE_H
#define FENIDE_H

#include <typeinfo>
#include <QtGUI>

#include <Qsci/qsciscintilla.h>

#include "AProHomePage.h"
#include "AProProject.h"
#include "ATabBar.h"

template<typename T1,typename T2> T2* castTo(T1* p1)
{
    T2* p2 = dynamic_cast<T2*>(p1);
    if(typeid(p2) != typeid(T2*))
        return NULL;
    return p2;
}

class documentIDE;
class treeWidgetWRC;

namespace scintilla
{
class WorkGroupManager
{
public:
    WorkGroupManager();
    ~WorkGroupManager();

    WorkGroup* createGroup();
    void destroyGroup(WorkGroup* group);
    WorkGroup* getDefautGroup();
    WorkGroup* findGroup(documentIDE* doc);

public:
    class WorkGroup
    {
    public:
        WorkGroup(QsciLexer* lexer);
        ~WorkGroup();

        void addDocument(documentIDE* doc);
        void removeDocument(documentIDE* doc);
        void setLexer(QsciLexer* lexer);
        void quitGroup();

    private:
        QList<documentIDE*> docList;
        QsciAPIs* api;

        friend class WorkGroupManager;
    };
    typedef QList<WorkGroup*> WorkGroupList;

private:
    WorkGroupList workGroup;
};
}

class fenIDE : public QMainWindow
{
    Q_OBJECT

    public :
    //Constructeur
    fenIDE(QWidget *parent = 0);
    //Destructeur
    ~fenIDE();

    virtual bool event(QEvent* event);

    //V2
public slots:
    void newFile();
    void newFile(const AProFileForm& f);
    void newProject();
    void newProject(const AProProject& p);
    void openFile();
    void openFile(const AProFileForm& f);
    void openProject();
    void openProject(const AProProject& p);

protected slots:
    documentIDE* createNewScintillaZone();

    //V1
    public slots :

    //SLOT IDE

    void nouveauFichierVide();
    //void nouveauFichier(const AProFileForm& file);
    void nouveauGroup();
    void nouveauProjet();
    void supprimerTab(int index);
    void supprimerNormalTab(int index);
    void changerParser(QAction *action);
    void MAJ_menuIDE(int index);
    void zoom_in();
    void zoom_out();
    void resetZoom();
    void unsavedTab(int tab);
    void saveFileSous(int index = 0);
    void saveFile();
    void saveFile(int);
    void saveAllFiles();
    void openFile();
    void openFile(QString fileName,QsciLexer* lexer);
    void openFile(AProFileForm* form);
    void openProject();
    void itemContextMenuEvent(QTreeWidgetItem* item,int column,QPoint pos);
    bool filterDirectory(QTreeWidgetItem*,QDir,const QList<QString>*,bool reinit = false);
    void openProjectItem(QTreeWidgetItem* item,int column);
    void reloadTab(int,int);
    void seeHomePage();
    void activateProject(QTreeWidgetItem* item = NULL);
    void saveProject(QTreeWidgetItem* item = NULL);
    void closeProject(QTreeWidgetItem* item = NULL);
    void addNewFileToProject(bool __temp = true);
    void reloadProject(QTreeWidgetItem* project = NULL);
    void createNewFile(AProFileForm* form);
    void setParser(AProFileForm::FileType type);

    documentIDE *scintillaActuel();
    documentIDE *scintillaAt(int index);

    QsciLexer* getLexerFromType(Type::FileType type,);
    protected :
    void closeEvent(QCloseEvent* event);
    void init();
    void createActions();
    void createMenu();
    void createToolBar();
    void createLexers();
    void createTabBar();
    void createDocks();
    void createStatusBar();

    private :

    //Resources IDE

    QMenu *menuIDE_Fichier;
    QMenu *menuIDE_Options;
    QMenu *menuIDE_Options_Parser;

    QMenu *menuIDE_Fichier_Nouveau;
    QAction *menuIDE_Fichier_Enregistrer;
    QAction *menuIDE_Fichier_EnregistrerSous;
    QAction* menuIDE_Fichier_OuvrirProjet;
    QAction* saveCurrentProject;
    QAction* reinitZoom;
    QAction *menuIDE_Options_ZoomIn;
    QAction *menuIDE_Options_ZoomOut;
    QAction *menuIDE_Options_Parser_CPP;
    QAction *menuIDE_Options_Parser_HTML;
    QAction *menuIDE_Options_Parser_PHP;
    QAction *menuIDE_Options_Parser_XML;
    QAction *menuIDE_Options_Parser_JAVA;
    QAction *menuIDE_Options_Parser_NULL;
    QAction *menuIDE_Fichier_EmptyFile;
    QAction *menuIDE_Fichier_GroupedFile;
    QAction *menuIDE_Fichier_Project;
    QAction *menuIDE_Fichier_ToutEnregistrer;
    QAction *menuIDE_Fichier_Ouvrir;

    ATabWidget *IDE_Tab;

    QStatusBar *Etat_IDE;
    QLabel* label_readWriteIndic;

    QVBoxLayout *layout_dock_princip;

    QWidget *IDE_Dock_Outils_Widget;
    QWidget *contenu_IDE_Dock_Outils;
    QWidget *groupe_widget;

    QDockWidget *IDE_Dock_Outils;

    QGroupBox *groupe_absolute;

    QCheckBox *Gras;
    QCheckBox *Italique;
    QCheckBox *Souligne;

    QToolBar *IDEToolBar;
    QToolBar *NormalTextToolBar;

    int numero_Fichier_IDE;
    bool projetOuvert;

    QsciLexerCPP *lexerCpp;
    QsciLexerHTML *lexerHTML;
    QsciLexerJava *lexerJava;
    QsciLexerXML *lexerXML;

    QSettings *settings;
    QSettings *settingsLangue;
    QString langue;

    treeWidgetWRC* treeWidget;

    QTreeWidgetItem* activatedProject;
    QTreeWidgetItem* tempItem;
    QMap<QTreeWidgetItem*,AProProject> projects;

    WorkGroupManager* wgManager;
};

class documentIDE : public QsciScintilla
{
    Q_OBJECT

    public :
    documentIDE(QFile fichier = QFile(""));
    ~documentIDE();

    bool isSaved() const { return saved; }
    bool exist() const { return exists; }
    int wichTab() const { return tab; }
    QTreeWidgetItem* beliveToProject() const { return parentProject; }
    const QFileInfo* getFile() const { return &file; }

    public slots :
    void setSaved(bool save) { saved = save; }
    void setTab(int t) { tab = t; }
    void changeSafety();
    void changeModification() { setModified(false); }
    void setFile(QFileInfo fileinf) { file = fileinf; }
    void setProjectBeliving(QTreeWidgetItem* project) { parentProject = project; }

    signals :
    void unsaved(int);

    private :
    bool saved;
    bool exists;
    QTreeWidgetItem* parentProject;
    int tab;
    QTimer* timer;
    QFileInfo file;
};

class treeWidgetWRC : public QTreeWidget
{
    Q_OBJECT

    public :
    treeWidgetWRC(QWidget* parent = 0);
    ~treeWidgetWRC() {}

    signals :
    void itemRClicked(QTreeWidgetItem* itemClicked,int column,QPoint);

    protected :
    void mousePressEvent(QMouseEvent* e);

    private :
    void filterEvent(QMouseEvent* e);
};

#endif //FENIDE_H
