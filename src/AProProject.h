#ifndef APROPROJECT_H
#define APROPROJECT_H

#include <QtGUI>
#include <QDomDocument>

class AProProject : public QObject
{
    Q_OBJECT

    public :
    //Constructeur
    AProProject(QString f = "");
    AProProject(const AProProject& other);

    //Destructeur
    ~AProProject();

    const QList<QString>* sources() const { return &Sources; }
    const QList<QString>* headers() const { return &Headers; }
    const QString& getVersion() const { return version; }
    const QString& getName() const { return name; }
    const QsciLexer* getLexer() const { return lexer; }

    AProProject& operator=(const AProProject& other);

    public slots :

    //Parse le fichier du projet (à son ouverture)
    void parseFile();
    //Sauvegarde le projet
    void saveProject();
    //Ajoute et supprime un fichier au projet
    void addFile(QString f);
    bool deleteFile(QString f);

    QString file() const { return fileName; }
    QString dir() const { return QFileInfo(fileName).absolutePath(); }

    private :

    QString fileName;
    QList<QString> Sources;
    QList<QString> Headers;
    QList<QString> SExtension;
    QList<QString> HExtension;
    QString version;
    QString name;
    QsciLexer* lexer;
};

#endif //APROPROJECT_H
