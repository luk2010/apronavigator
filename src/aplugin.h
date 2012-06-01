#ifndef APLUGIN_H
#define APLUGIN_H

#include <QString>
#include <QtScript>
#include <QList>

struct AProPlugin
{
    QString name;
    QString description;
    QString author;
    QString version;
    QString creationDate;
    QString lastUpdateDate;
};

Q_DECLARE_METATYPE(AProPlugin)
Q_DECLARE_METATYPE(QList<AProPlugin>)

QScriptValue AProPluginToScriptValue(QScriptEngine *engine, const AProPlugin &s);
void ScriptValueToAProPlugin(const QScriptValue &obj, AProPlugin &s);
QScriptValue createAProPlugin(QScriptContext * context, QScriptEngine *engine);

#endif // APLUGIN_H
