#ifndef APROSEARCHLINE_H
#define APROSEARCHLINE_H

#include <QtGUI>
#include <QtWebKit>
#include <QMetaObject>

class GSuggest : public QObject
{
    Q_OBJECT

    public :
    //Constructeur
    GSuggest(QLineEdit *parent = 0);
    ~GSuggest();

    //Filtre les évènements
    bool eventFilter(QObject *obj, QEvent *ev);

    //Affiche les résultats
    void showResult(const QStringList &choices, const QStringList &hits);

    public slots :

    void doneCompletion();
    void preventSuggest();
    void autoSuggest();
    void handleNetworkData(QNetworkReply *reply);

    private :
    QLineEdit *lineEdit;
    QTreeWidget *popup;
    QTimer *timer;
    QNetworkAccessManager networkManager;
};

/*
Un simple bouton rouge avec une croix pour effacer le texte
----
-\/-
-/\-
----
*/
class clearButton : public QAbstractButton
{
    Q_OBJECT

    public :
    clearButton(QWidget *parent = 0);
    void paintEvent(QPaintEvent *event);

    public slots :
    void textChanged(const QString &text);
    void setColor(const QColor &color);

    private :

    QColor m_Color;
};

class searchLine : public QWidget
{
    Q_OBJECT

    signals:
        void textChanged(const QString &text);

    public :
    searchLine(QWidget *parent = 0);

    inline QLineEdit* lineEdit() const { return m_lineEdit; }
    QVariant inputMethodQuery(Qt::InputMethodQuery property) const;

    QSize sizeHint() const;

    protected :
    void focusInEvent(QFocusEvent *event);
    void focusOutEvent(QFocusEvent *event);
    void keyPressEvent(QKeyEvent *event);
    void paintEvent(QPaintEvent *event);
    void resizeEvent(QResizeEvent *event);
    void inputMethodEvent(QInputMethodEvent *e);
    bool event(QEvent *event);
    void updateGeometries();
    void initStyleOption(QStyleOptionFrameV2 *option) const;

    private :
    GSuggest *googSuggestion;
    QLineEdit *m_lineEdit;
    clearButton *ClearButton;
};

class MusicSearcher : public QObject
{
    Q_OBJECT

    QTreeWidget* popup;
    QString query;
    QString dir;

public:
    inline MusicSearcher(QObject* parent, QTreeWidget* _popup, QString _query, QString _dir) : QObject(parent) {
        popup = _popup;
        query = _query;
        dir =  _dir;
    }

    virtual ~MusicSearcher() {
    }

public slots:
    void search() {
        if(!popup) return;

        if (dir == QString(""))
        {
            QMessageBox::warning(0,"Attention","Vous n'avez spécifié aucun dossier de recherche de musique ! Veuillez le préciser dans Options->configurer le lecteur multimédia->parcourir !");
            return;
        }

        if (query == "")
        {
            return;
        }

        QDir directory(dir);
        QDirIterator it(directory,QDirIterator::Subdirectories);

        popup->setUpdatesEnabled(false);
        popup->clear();

        int name = 0;
        while (it.hasNext())
        {
            it.next();
            static QFileInfo info;
            info = it.fileInfo();

            if (info.isDir())
            {
                continue;
            }
            else if ((info.suffix()=="mp3")||(info.suffix()=="ogg")||(info.suffix()=="flac")||(info.suffix()=="mid"))
            {
                if (info.fileName().toLower().contains(query.toLower()))
                {
                    QString filename("");
                    if (info.dir() != directory)
                        filename = directory.relativeFilePath(info.filePath());
                    else
                        filename = info.fileName();

                    QTreeWidgetItem* item = new QTreeWidgetItem(popup);
                    item->setText(0,info.fileName());
                    item->setText(1,filename);
                    name++;
                }
            }
        }

        popup->setCurrentItem(popup->topLevelItem(0));
        popup->resizeColumnToContents(0);
        popup->adjustSize();
        popup->setUpdatesEnabled(true);

        int h = popup->sizeHintForRow(0) * qMin(7,name) + 3;
        popup->resize(popup->width(),h);

        emit popupFilled();
    }

signals:
    void popupFilled();
};

class MusicSearchThread : public QThread
{
protected:
    void run() {
        exec();
    }
};

class musicSearchLine;
class autoSearchSuggest : public QObject
{
    Q_OBJECT

    public :
    autoSearchSuggest(musicSearchLine* parent = 0);
    ~autoSearchSuggest();

    public slots :
    void search();
    bool eventFilter(QObject *obj, QEvent *ev);
    void doneCompletion();
    void showPopup();

    signals :
    void lancerMusique();

    private :
    musicSearchLine* m_lineEdit;
    QTreeWidget* popup;
    QSettings* settings;
    QTimer* timer;
    MusicSearchThread* thread;
    MusicSearcher* searcher;
};

class musicSearchLine : public QLineEdit
{
    Q_OBJECT

    public :
    musicSearchLine(QWidget* parent = 0);
    ~musicSearchLine();

    QMovie* movie_loading;
    QLabel* chargement;

    public slots :
    void returnPressed_emit();

protected:
    //void paintEvent(QPaintEvent *);
    void resizeEvent(QResizeEvent *);

    private :
    autoSearchSuggest* searcher;
};
#endif //APROSEARCHLINE_H
