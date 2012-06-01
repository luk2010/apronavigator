#include <QFile>
#include <QDate>
#include <QTextStream>

#include "datafile.h"

DataFile::DataFile()
{
    dataVersionSupported << "1.0";
    currentError = DataError_None;

    reload();
}

DataFile::~DataFile()
{
    save();
}

int DataFile::getBuild()
{
    if(currentError == DataError_None)
    {
        if(getDataBuild() == "1.0")
        {
            QDomElement buildElement = data.firstChild().firstChildElement();

            int build = buildElement.text().toInt();
            if(build == 0)
                return -1;

            return build;
        }
        else
        {
            return -1;
        }
    }
    else
    {
        return -1;
    }
}

QString DataFile::getDataBuild()
{
    if(currentError == DataError_None)
    {
        QDomElement dataBuildElement = data.firstChildElement();

        QString build = dataBuildElement.attribute(QString("sys_version"));
        if(!dataVersionSupported.contains(build))
        {
            currentError = DataError_FileVersionInvalid;
        }

        return build;
    }

    return QString("-1");
}

QStringList DataFile::getDataVersionSupported()
{
    return dataVersionSupported;
}

QString DataFile::getErrorString()
{
    switch (currentError)
    {
    case DataError_FileDoNotExist :
        return QString("File does not exist !");

    case DataError_FileVersionInvalid :
        return QString("File Version is invalid !");

    case DataError_BuildVersionInvalid :
        return QString("Build version is invalid !");

    case DataError_NodeUnfound :
        return QString("Node can't be found !");

    case DataError_None :
    default :
        return QString("No error !");
    }
}

DataFile::DataError DataFile::getError()
{
    return currentError;
}

QString DataFile::getVersionString()
{
    if(currentError == DataError_None)
    {
        if(isValid())
        {
            if(getDataBuild() == "1.0")
            {
                QDomElement versionElement = data.firstChild().firstChild().nextSiblingElement();
                return versionElement.text();
            }
        }
    }

    return QString("-1");
}

bool DataFile::isValid()
{
    if(currentError == DataError_None)
    {
        if(dataVersionSupported.contains(getDataBuild()))
        {
            if(getBuild() != -1)
            {
                if(!getHistorique().isNull())
                {
                    if(!getFavoris().isNull())
                    {
                        return true;
                    }
                }
            }
        }
    }

    return false;
}

QDomElement DataFile::getHistorique()
{
    QDomElement historiqueElement = data.firstChild().firstChildElement(QString("historique"));
    if(historiqueElement.isNull())
    {
        currentError = DataError_NodeUnfound;
    }

    return historiqueElement;
}

QDomElement DataFile::getFavoris()
{
    QDomElement favorisElement = data.firstChild().firstChildElement(QString("favoris"));
    if(favorisElement.isNull())
    {
        currentError = DataError_NodeUnfound;
    }

    return favorisElement;
}

void DataFile::rebuildData()
{
    data.clear();

    QDomElement dataNode = data.createElement(QString("data"));
    dataNode.setAttribute(QString("sys_version"), dataVersionSupported.last());
    data.appendChild(dataNode);

    QDomElement buildNode = data.createElement(QString("build"));
    buildNode.appendChild(data.createTextNode(QString("13")));
    dataNode.appendChild(buildNode);

    QDomElement versionNode = data.createElement(QString("version"));
    versionNode.appendChild(data.createTextNode(QString("0.06A")));
    dataNode.appendChild(versionNode);

    dataNode.appendChild(data.createElement(QString("historique")));
    dataNode.appendChild(data.createElement(QString("favoris")));
}

void DataFile::reload()
{
    data.clear();

    QFile dataFile("data.xml");
    dataFile.open(QIODevice::ReadOnly);

    if(!data.setContent(&dataFile) || !isValid())
    {
        rebuildData();
        save();

        currentError = DataError_None;
        return;
    }
}

void DataFile::addHistoriqueElement(QDomElement &element)
{
    if(currentError == DataError_None && !element.isNull())
    {
        QDomElement historiqueElement = getHistorique();

        if(getDataBuild() == "1.0")
        {
            if(element.tagName() == QString("adresse") &&
                    !element.attribute("title").isEmpty() &&
                    !element.attribute("url").isEmpty())
            {
                if(element.attribute("date").isEmpty())
                    element.setAttribute("date", QDate::currentDate().toString());

                historiqueElement.appendChild(element);
            }
        }
    }
}

void DataFile::addFavorisElement(QDomElement &element)
{
    if(currentError == DataError_None && !element.isNull())
    {
        QDomElement favorisElement = getFavoris();

        if(getDataBuild() == "1.0")
        {
            if(element.tagName() == QString("adresse") &&
                    !element.attribute("title").isEmpty() &&
                    !element.attribute("url").isEmpty())
            {
                favorisElement.appendChild(element);
            }
        }
    }
}

void DataFile::removeHistoriqueElement(QDomElement &element)
{
    if(currentError == DataError_None && !element.isNull())
    {
        QDomElement historiqueElement = getHistorique();
        historiqueElement.removeChild(element);
    }
}

void DataFile::removeFavorisElement(QDomElement &element)
{
    if(currentError == DataError_None && !element.isNull())
    {
        QDomElement favorisElement = getFavoris();
        favorisElement.removeChild(element);
    }
}

void DataFile::save()
{
    QFile dataFile("data.xml");
    dataFile.open(QIODevice::ReadWrite | QIODevice::Truncate);

    QTextStream textStream(&dataFile);
    textStream << data.toString();
    dataFile.close();
}

QDomDocument& DataFile::getDocument()
{
    return data;
}

