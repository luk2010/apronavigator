#ifndef PLUGIN_H
#define PLUGIN_H

#include <QObject>
#include <QString>
#include <QList>
#include <QtScript>

#include "mimetype.h"

struct Plugin
{
    QString name;
    QString description;
    QList<MimeType> mimeTypes;
};

Q_DECLARE_METATYPE(Plugin)
Q_DECLARE_METATYPE(QList<Plugin>)

QScriptValue PluginToScriptValue(QScriptEngine *engine, const Plugin &s);
void ScriptValueToPlugin(const QScriptValue &obj, Plugin &s);
QScriptValue createPlugin(QScriptContext * context, QScriptEngine *engine);

#endif // PLUGIN_H
