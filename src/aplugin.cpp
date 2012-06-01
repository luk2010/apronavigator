#include "aplugin.h"

QScriptValue AProPluginToScriptValue(QScriptEngine *engine, const AProPlugin &s)
{
    QScriptValue sv = engine->newObject();
    sv.setProperty("name", s.name);
    sv.setProperty("author", s.author);
    sv.setProperty("date", s.creationDate);
    sv.setProperty("description", s.description);
    sv.setProperty("lastUpdated", s.lastUpdateDate);
    sv.setProperty("version", s.version);

    return sv;
}

void ScriptValueToAProPlugin(const QScriptValue &obj, AProPlugin &s)
{
    s.author = obj.property("author").toString();
    s.creationDate = obj.property("date").toString();
    s.description = obj.property("description").toString();
    s.lastUpdateDate = obj.property("lastUpdated").toString();
    s.name = obj.property("name").toString();
    s.version = obj.property("version").toString();
}

/*
  Constructor is :

  AProPlugin(name, author, description, version, date, lastUpdated)

*/
QScriptValue createAProPlugin(QScriptContext * context, QScriptEngine *engine)
{
    QString arg1 = context->argumentCount() > 0 ? context->argument(0).toString() : QString();
    QString arg2 = context->argumentCount() > 1 ? context->argument(1).toString() : QString();
    QString arg3 = context->argumentCount() > 2 ? context->argument(2).toString() : QString();
    QString arg4 = context->argumentCount() > 3 ? context->argument(3).toString() : QString();
    QString arg5 = context->argumentCount() > 4 ? context->argument(4).toString() : QString();
    QString arg6 = context->argumentCount() > 5 ? context->argument(5).toString() : QString();

    AProPlugin plug;
    plug.name = arg1;
    plug.author = arg2;
    plug.description = arg3;
    plug.version = arg4;
    plug.creationDate = arg5;
    plug.lastUpdateDate = arg6;

    return engine->toScriptValue(plug);
}
