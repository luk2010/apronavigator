#ifndef APROHOMEPAGE_H
#define APROHOMEPAGE_H

#include <QtGUI>
#include "AProFileForm.h"
#include "AProProject.h"

class AnimatedGroupBox;

class Pixmap : public QGraphicsObject
 {
     Q_OBJECT
 public:
     Pixmap(const QPixmap &pix) : QGraphicsObject(), p(pix)
     {
     }

     ~Pixmap() {}

     void paint(QPainter *painter, const QStyleOptionGraphicsItem *, QWidget *)
     {
         painter->drawPixmap(QPointF(), p);
     }

     QRectF boundingRect() const
     {
         return QRectF( QPointF(0, 0), p.size());
     }

 private:
     QPixmap p;
 };

class AProHomePage : public QScrollArea
{
    Q_OBJECT

    public :
    AProHomePage(const QImage& bg,QWidget* parent = 0);
    ~AProHomePage();

    QWidget* area_widget() { return widget; }

    void paintEvent(QPaintEvent* e);

    public slots :
    void fichier_parcourir();
    void discoverType();
    void createNewFile();
    void createRecentFile();
    //void createRecentProject();

    signals :
    void sendNewFile(AProFileForm*);
    void sendOpenFile(AProFileForm*);
    void openFileRequest();
    void openProjectRequest();

    public slots:
    void sendNewFile_slot(QString _str);
    void sendOpenFileRequest();
    void sendOpenProjectRequest();

    protected :
    bool event(QEvent* e);

    private :
    QWidget* widget;

    QBoxLayout* vLayout;

    QHBoxLayout* hLayout2;
    QHBoxLayout* hLayout;

    QVBoxLayout* vLayout2;
    QVBoxLayout* vLayout3;

    QLabel* label_img2;
    QLabel* label_img;
    QLabel* label_dossier_fichier;
    QLabel* label_type;
    QLabel* label_bar_gauche;
    QLabel* label_bar_droite;

    QPushButton* newFichier;
    QPushButton* newProject;

    QImage m_bg;
    QPixmap m_stretch;

    QLineEdit* fileName;

    QComboBox* type;

    QCheckBox* addToCurrentProject;
    QCheckBox* isheader;

    QSpacerItem* spacerItem;
    QSpacerItem* spacerItem2;

    QMap<QString,AProFileForm> recentFiles;
    QMap<QString,AProProject> recentProject;
};

class AnimatedGroupBox : public QGroupBox
{
    Q_OBJECT

    public :
    AnimatedGroupBox(QString titre,QWidget* parent = 0);
    ~AnimatedGroupBox() {}

    public slots:
    void animate();
    void addVisibleContrainter(AnimatedGroupBox* contrainter) { contraintersList.prepend(contrainter); }
    void cleanLater() { setVisible(false); }

    private :
    bool alreadyAnimated;
    bool parentIsAnAnimatedLayout;
    QList<AnimatedGroupBox*> contraintersList;
};

#endif //APROHOMEPAGE_H
