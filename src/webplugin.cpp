#include "webplugin.h"

WebPlugin::WebPlugin()
{
    /* Do nothing */
}

WebPlugin::WebPlugin(const WebPlugin &plugin)
{
    setName(plugin.getName());
    setDescription(plugin.getDescription());
    setPlugins(plugin.getPlugins());
}

WebPlugin::WebPlugin(const QString &_name, const QString &_description, const QList<Plugin> &_plugins)
{
    setName(_name);
    setDescription(_description);
    setPlugins(_plugins);
}

WebPlugin::~WebPlugin()
{
    /* Do nothing */
}

QString WebPlugin::getName() const
{
    return name;
}

void WebPlugin::setName(const QString &_name)
{
    name = _name;
}

QString WebPlugin::getDescription() const
{
    return description;
}

void WebPlugin::setDescription(const QString &_description)
{
    description = _description;
}

QList<Plugin> WebPlugin::getPlugins() const
{
    return plugins;
}

void WebPlugin::setPlugins(const QList<Plugin> &_plugins)
{
    plugins = _plugins;
}

QObject* WebPlugin::create(const QString &mimeType, const QUrl &url, const QStringList &argumentNames, const QStringList &argumentValues) const
{
    return NULL;
}

QScriptValue constructWebPlugin(QScriptContext *context, QScriptEngine *engine)
{
    WebPlugin* plugin = new WebPlugin;

    QString arg1 = context->argumentCount() > 0 ? context->argument(0).toString() : QString();
    QString arg2 = context->argumentCount() > 1 ? context->argument(1).toString() : QString();
    QList<Plugin> arg3 = context->argumentCount() > 2 ? qscriptvalue_cast<QList<Plugin> >(context->argument(2)) : QList<Plugin>();

    plugin->setName(arg1);
    plugin->setDescription(arg2);
    plugin->setPlugins(arg3);

    return engine->newQObject(plugin);
}

