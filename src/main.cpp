#include <QApplication>
#include <QtPlugin>
#include <QtGUI>
#include "AppAll.h"
#include "scriptengine.h"

using namespace std;

int main(int argc,char *argv[])
{
    //Initialisation Qt
    QApplication QApp(argc,argv);
    QApp.setApplicationName("Atlanti's project");
    QApp.setApplicationVersion(VERSION);
    QApp.setOrganizationName("Atlanti's Corporation");

    //Initialisation du QT Script
    ScriptEngine::init();

    //Chargement des extensions
    QStringList paths = QApp.libraryPaths();

    QDir dir = QApplication::applicationDirPath();
    if(!dir.cd("script"))
    {
        QMessageBox::warning(NULL, "Error", "Can't find script folder !");
    }
    else
    {
        paths << dir.absolutePath();
        QApp.setLibraryPaths(paths);

        QStringList extensions;
        extensions  << "qt.core"
                    << "qt.gui"
                    << "qt.xml"
                    << "qt.svg"
                    << "qt.network"
                    << "qt.sql"
                    << "qt.opengl"
                    << "qt.webkit"
                    << "qt.xmlpatterns"
                    << "qt.uitools";

        QStringList failedExtensions;
        for(int i = 0; i < extensions.count(); i++)
        {
            QScriptValue ret = ScriptEngine::get()->importExtension(extensions.at(i));
            if(ret.isError())
            {
                failedExtensions << extensions.at(i);
            }
        }

        if(failedExtensions.count() > 0)
        {
            QString failedMessage("Script Extension has failed loading all extensions. Extensions are : ");
            for(int i = 0; i < failedExtensions.count(); ++i)
                failedMessage.append(failedExtensions.at(i) + ", ");

            QMessageBox::warning(NULL, "Error", failedMessage);
        }
    }

#ifndef Q_WS_SIMULATOR
    QFile lisence("license.txt");
    if (!lisence.open(QIODevice::ReadOnly | QIODevice::Text))
        {
            QMessageBox::information(0,"Attention","Vous n'avez pas de license !");
            return 2;
        }
    lisence.close();
#endif

    //Creation de la fenetre principale
    Fenetre_Princ MainWindow;
    MainWindow.gestionSonInit();
    MainWindow.showMaximized();

    QObject::connect(&MainWindow,SIGNAL(quitquit()),&QApp,SLOT(quit()));

    //Chargement des plugins
    MainWindow.loadPlugins();

    //Et on envoie !
#ifndef Q_WS_SIMULATOR
    while (!MainWindow.getQuit())
    {
        QApp.processEvents();
        MainWindow.gestionSonUpdate();
        MainWindow.LEC_UpdatePosition();
    }
    return 0;
#else
    return QApp.exec();
#endif
}
