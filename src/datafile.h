#ifndef DATAFILE_H
#define DATAFILE_H

#include <QDomDocument>
#include <QStringList>

class DataFile
{
public:

    enum DataError
    {
        DataError_FileDoNotExist = 0,
        DataError_FileVersionInvalid = 1,
        DataError_BuildVersionInvalid = 2,
        DataError_NodeUnfound = 3,
        DataError_None = 4
    };

public:

    DataFile();
    ~DataFile();

    int getBuild();
    QString getDataBuild();

    QStringList getDataVersionSupported();

    QString getErrorString();
    DataError getError();

    QString getVersionString();

    bool isValid();

    QDomElement getHistorique();
    QDomElement getFavoris();

    void rebuildData();
    void reload();

    void addHistoriqueElement(QDomElement& element);
    void addFavorisElement(QDomElement& element);

    void removeHistoriqueElement(QDomElement& element);
    void removeFavorisElement(QDomElement& element);

    void save();

    QDomDocument& getDocument();

private:
    QDomDocument data;
    DataError currentError;

    QStringList dataVersionSupported;
};

#endif // DATAFILE_H
