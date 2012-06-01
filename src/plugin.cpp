#include "plugin.h"
#include "scriptengine.h"

QScriptValue PluginToScriptValue(QScriptEngine *engine, const Plugin &s)
{
    QScriptValue obj = engine->newObject();
    obj.setProperty("name", s.name);
    obj.setProperty("description", s.description);
    obj.setProperty("mimeTypes", engine->toScriptValue(s.mimeTypes));

    return obj;
}

void ScriptValueToPlugin(const QScriptValue &obj, Plugin &s)
{
    s.name = obj.property("name").toString();
    s.description = obj.property("description").toString();
    s.mimeTypes = ScriptEngine::get()->fromScriptValue<QList<MimeType> >(obj.property("mimeTypes"));
}

QScriptValue createPlugin(QScriptContext * context, QScriptEngine *engine)
{
    Plugin plugin;

    if(context->argumentCount() == 2)
    {
        plugin.name = context->argument(0).toString();
        plugin.description = context->argument(1).toString();
    }

    return engine->toScriptValue(plugin);
}
