#include "awebpluginfactory.h"
#include <QMessageBox>

QScriptValue aWebPluginFactoryToScriptValue(QScriptEngine *engine, AWebPluginFactory* const &in)
{
    return engine->newQObject(in, QScriptEngine::QtOwnership, QScriptEngine::PreferExistingWrapperObject);
}

void aWebPluginFactoryFromScriptValue(const QScriptValue &object, AWebPluginFactory* &out)
{
    out = qobject_cast<AWebPluginFactory*>(object.toQObject());
}

AWebPluginFactory::AWebPluginFactory(QObject *parent) :
    QWebPluginFactory(parent)
{

}

QObject* AWebPluginFactory::create(const QString &mimeType, const QUrl & url, const QStringList &argumentNames,
                                   const QStringList &argumentValues) const
{
    for(int i = 0; i < factories.count(); ++i)
    {
        QObject* ret = factories.at(i)->create(mimeType, url, argumentNames, argumentValues);
        if(ret != NULL)
            return ret;
    }

    return NULL;
}

QList<QWebPluginFactory::Plugin> AWebPluginFactory::plugins() const
{
    QList<QWebPluginFactory::Plugin> list;

    for(int i = 0; i < factories.count(); i++)
    {
        WebPlugin* pluginFactory = factories.at(i);
        QList<APlugin> pluginList = pluginFactory->getPlugins();

        for(int j = 0; j < pluginList.count(); j++)
        {
            APlugin plugin = pluginList.at(j);

            // Construct each plugin
            QWebPluginFactory::Plugin plugin_;
            plugin_.name = plugin.name;
            plugin_.description = plugin.description;

            for(int k = 0; k < plugin.mimeTypes.count(); k++)
            {
                AMimeType mimeType = plugin.mimeTypes.at(k);

                // Construct each mime type
                QWebPluginFactory::MimeType mimeType_;
                mimeType_.name = mimeType.name;
                mimeType_.description = mimeType.description;
                mimeType_.fileExtensions = mimeType.extensions;

                plugin_.mimeTypes.append(mimeType_);
            }

            list.append(plugin_);
        }
    }

    return list;
}

void AWebPluginFactory::addPluginFactory(WebPlugin *factory)
{
    if(factory != NULL)
    {
        QMessageBox::information(0, "In Real", factory->getPlugins().first().mimeTypes.first().name);
        factories.append(factory);
    }
}

void AWebPluginFactory::removePluginFactory(WebPlugin *factory)
{
    if(factory != NULL)
        factories.removeOne(factory);
}

QList<WebPlugin *> AWebPluginFactory::getFactories() const
{
    return factories;
}

void AWebPluginFactory::setFactories(QList<WebPlugin*> facts)
{
    factories = facts;
}
