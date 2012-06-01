#include "webpluginprototype.h"

WebPluginPrototype::WebPluginPrototype(QObject *parent)
    : QObject(parent)
{

}

QString WebPluginPrototype::getName() const
{
    WebPlugin* wp = qscriptvalue_cast<WebPlugin*>(thisObject());
    if(wp)
    {
        return wp->getName();
    }

    return QString();
}

void WebPluginPrototype::setName(const QString &_name)
{
    WebPlugin* wp = qscriptvalue_cast<WebPlugin*>(thisObject());
    if(wp)
    {
        return wp->setName(_name);
    }
}

QString WebPluginPrototype::getDescription() const
{
    WebPlugin* wp = qscriptvalue_cast<WebPlugin*>(thisObject());
    if(wp)
    {
        return wp->getDescription();
    }

    return QString();
}

void WebPluginPrototype::setDescription(const QString &_description)
{
    WebPlugin* wp = qscriptvalue_cast<WebPlugin*>(thisObject());
    if(wp)
    {
         wp->setDescription(_description);
    }
}

QList<Plugin> WebPluginPrototype::getPlugins() const
{
    WebPlugin* wp = qscriptvalue_cast<WebPlugin*>(thisObject());
    if(wp)
    {
        return wp->getPlugins();
    }

    return QList<Plugin>();
}

void WebPluginPrototype::setPlugins(const QList<Plugin> &_plugins)
{
    WebPlugin* wp = qscriptvalue_cast<WebPlugin*>(thisObject());
    if(wp)
    {
        wp->setPlugins(_plugins);
    }
}

QString WebPluginPrototype::toString() const
{
    return QString("WebPlugin(name = %0, description = %1)").arg(getName()).arg(getDescription());
}
