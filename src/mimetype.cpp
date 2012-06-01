#include "mimetype.h"

#include <QMessageBox>

QScriptValue MimeTypeToScriptValue(QScriptEngine *engine, const MimeType &s)
{
    QScriptValue obj = engine->newObject();
    obj.setProperty("name", s.name);
    obj.setProperty("description", s.description);
    obj.setProperty("extensions", engine->toScriptValue(s.extensions));

    return obj;
}

void ScriptValueToMimeType(const QScriptValue &obj, MimeType &s)
{
    s.name = obj.property("name").toString();
    s.description = obj.property("description").toString();
    s.extensions = obj.property("extensions").toVariant().toStringList();
}

QScriptValue createMimeType(QScriptContext * context, QScriptEngine *engine)
{
    MimeType s;

    if(context->argumentCount() == 2)
    {
        s.name = context->argument(0).toString();
        s.description = context->argument(1).toString();
    }

    return engine->toScriptValue(s);
}
