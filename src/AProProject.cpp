#include "AProProject.h"

#define APROJECT_CURRENT_VERSION "1.0"

AProProject::AProProject(QString f)
{
    fileName = f;
    SExtension << "cpp" << "c" << "xml" << "class" << "clss" << "cmd" << "html" << "css" << "php" << "xml" << "asm";
    HExtension << "h" << "hpp" << "INC";
}

AProProject::AProProject(const AProProject& other)
{
    fileName = other.file();
    version = other.getVersion();
    name = other.getName();
    SExtension << "cpp" << "c" << "xml" << "class" << "clss" << "cmd" << "html" << "css" << "php" << "xml" << "asm";
    HExtension << "h" << "hpp" << "INC";

    for (int i = 0; i < other.headers()->count(); i++)
        Headers.prepend((*other.headers())[i]);

    for (int i = 0; i < other.sources()->count(); i++)
        Sources.prepend((*other.sources())[i]);
}

AProProject& AProProject::operator=(const AProProject& other)
{
    fileName = other.file();
    version = other.getVersion();
    name = other.getName();
    SExtension << "cpp" << "c" << "xml" << "class" << "clss" << "cmd" << "html" << "css" << "php" << "xml" << "asm";
    HExtension << "h" << "hpp" << "INC";

    for (int i = 0; i < other.headers()->count(); i++)
        Headers.prepend((*other.headers())[i]);

    for (int i = 0; i < other.sources()->count(); i++)
        Sources.prepend((*other.sources())[i]);
    return *this;
}

AProProject::~AProProject()
{

}

void AProProject::parseFile()
{
    if(fileName.isEmpty())
    {
        QMessageBox::warning(0,"Erreur","Le projet spécifié n'existe pas !");
        return;
    }
    QFile file(fileName);
    if (!file.open(QIODevice::ReadOnly))
    {
        QMessageBox::warning(0,"Erreur","Le projet spécifié n'existe pas !");
        return;
    }
    QDomDocument doc("projet");
    if (!doc.setContent(&file))
        return;

    file.close();

    QDomElement root = doc.documentElement();
    if (root.tagName()!="aproject")
        return;

    version = root.attribute("version","");
    if (version != APROJECT_CURRENT_VERSION)
        return;

    QDomNode n = root.firstChild();
    while(!n.isNull())
    {
        QDomElement e = n.toElement();
        if (!e.isNull())
        {
            if (e.tagName()=="config")
            {
                name = e.attribute("name","");
            }
            else if (e.tagName()=="files")
            {
                if (e.attribute("type","") == "src")
                {
                    QDomNode n2 = e.firstChild();
                    while (!n2.isNull())
                    {
                        QDomElement e2 = n2.toElement();
                        if (!e2.isNull())
                        {
                            QString src = e2.attribute("src","");
                            Sources.append(src);
                        }
                        n2 = n2.nextSibling();
                    }
                }

                if (e.attribute("type","") == "header")
                {
                    QDomNode n2 = e.firstChild();
                    while (!n2.isNull())
                    {
                        QDomElement e2 = n2.toElement();
                        if (!e2.isNull())
                        {
                            QString h = e2.attribute("src","");
                            Headers.append(h);
                        }
                        n2 = n2.nextSibling();
                    }
                }
            }
        }
        n = n.nextSibling();
    }
}

void AProProject::saveProject()
{
    QFile file(fileName);
    if (!file.open(QIODevice::WriteOnly | QIODevice::Truncate))
    {
        QMessageBox::warning(0,"Erreur","Impossible de sauvegarder le projet !\nErreur 0xaaaaa1");
        return;
    }

    QDomDocument doc("projet");

    QDomElement root = doc.createElement("aproject");
    root.setAttribute("version",APROJECT_CURRENT_VERSION);
    doc.appendChild(root);

    QDomElement config = doc.createElement("config");
    config.setAttribute("name",name);
    root.appendChild(config);

    if (!Sources.empty())
    {
        QDomElement src = doc.createElement("files");
        src.setAttribute("type","src");
        root.appendChild(src);
        for (int i = 0; i < Sources.size(); i++)
        {
            QDomElement fichier = doc.createElement("new");
            fichier.setAttribute("src",Sources[i]);
            src.appendChild(fichier);
        }
    }
    if(!Headers.empty())
    {
        QDomElement head = doc.createElement("files");
        head.setAttribute("type","header");
        root.appendChild(head);
        for (int i = 0; i < Headers.size(); i++)
        {
            QDomElement fichier = doc.createElement("new");
            fichier.setAttribute("src",Headers[i]);
            head.appendChild(fichier);
        }
    }

    QTextStream ts(&file);
    ts << doc.toString();
    file.close();
}

void AProProject::addFile(QString f)
{
    QFileInfo finfo(f);
    if (SExtension.contains(finfo.suffix()))
        Sources.append(f);
    else if (HExtension.contains(finfo.suffix()))
        Headers.append(f);
}

bool AProProject::deleteFile(QString f)
{
    if (!Sources.removeOne(f))
        Headers.removeOne(f);

    if (!QFile::remove(f))
        return false;
    else
        return true;
}
