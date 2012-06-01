#include "scriptengine.h"

#include <QFile>
#include <QTextStream>
#include <QMessageBox>

#include "mimetype.h"
#include "plugin.h"
#include "webplugin.h"
#include "awebpluginfactory.h"
#include "aplugin.h"

QScriptEngine* ScriptEngine::engine = NULL;

QScriptValue preloadScript(QScriptContext* context, QScriptEngine* engine)
{
    QString arg1 = context->argumentCount() > 0 ? context->argument(0).toString() : QString();
    bool arg2 = context->argumentCount() > 1 ? context->argument(1).toBool() : true;

    if(arg1.isEmpty())
        return QScriptValue(engine, false);

    if(arg2)
        arg1.prepend("plugins/");
    QMessageBox::information(0, "", arg1);

    context->setActivationObject(context->parentContext()->activationObject());
    context->setThisObject(context->parentContext()->thisObject());
    ScriptEngine::loadScript(arg1);
    return QScriptValue(engine, true);
}

QScriptValue importExtension(QScriptContext* context, QScriptEngine* engine)
{
    QString arg1 = context->argumentCount() > 0 ? context->argument(0).toString() : QString();

    if(arg1.isEmpty())
        return QScriptValue(engine, false);

    ScriptEngine::get()->importExtension(arg1);
    return QScriptValue(engine, true);
}

ScriptEngine::ScriptEngine()
{

}

void ScriptEngine::init()
{
    qScriptRegisterSequenceMetaType<QList<QWebPluginFactory*> >(get());

    QScriptValue funImportScript = engine->newFunction(preloadScript);
    engine->globalObject().setProperty("importScript", funImportScript);

    QScriptValue funImportExtension = engine->newFunction(importExtension);
    engine->globalObject().setProperty("importExtension", funImportExtension);

    qScriptRegisterMetaType(get(), AProPluginToScriptValue, ScriptValueToAProPlugin);
    QScriptValue apluginctor = get()->newFunction(createAProPlugin);
    get()->globalObject().setProperty("AProPlugin", apluginctor);
    qScriptRegisterSequenceMetaType<QList<AProPlugin> >(get());

    qScriptRegisterMetaType(get(), MimeTypeToScriptValue, ScriptValueToMimeType);
    QScriptValue ctor = get()->newFunction(createMimeType);
    get()->globalObject().setProperty("MimeType", ctor);
    qScriptRegisterSequenceMetaType<QList<MimeType> >(get());

    qScriptRegisterMetaType(get(), PluginToScriptValue, ScriptValueToPlugin);
    QScriptValue ctor2 = get()->newFunction(createPlugin);
    get()->globalObject().setProperty("Plugin", ctor2);
    qScriptRegisterSequenceMetaType<QList<Plugin> >(get());

    qScriptRegisterMetaType(get(), webPluginToScriptValue, webPluginFromScriptValue);
    QScriptValue ctor3 = get()->newFunction(constructWebPlugin);
    get()->globalObject().setProperty("WebPlugin", ctor3);
    qScriptRegisterSequenceMetaType<QList<WebPlugin*> >(get());

    qScriptRegisterMetaType(get(), aWebPluginFactoryToScriptValue, aWebPluginFactoryFromScriptValue);
}

QScriptEngine* ScriptEngine::get()
{
    if(engine == NULL)
        engine = new QScriptEngine();

    return engine;
}

void ScriptEngine::loadScript(QString script)
{
    if(engine == NULL)
        ScriptEngine::get();

    QFile file(script);
    file.open(QIODevice::ReadOnly);

    QTextStream stream(&file);
    QString content = stream.readAll();
    file.close();

    if(content.isEmpty())
    {
        QMessageBox::information(0, "Error", QString("Couldn't load script %0 ...").arg(script));
        return;
    }

    QScriptValue result = engine->evaluate(content);
    if(engine->hasUncaughtException())
    {
        int line = engine->uncaughtExceptionLineNumber();
        QMessageBox::information(0, "", QString("Script : ") + script + " caused uncaught exeception at line : " +
                                 QString::number(line) + " : " + result.toString());
    }
}
