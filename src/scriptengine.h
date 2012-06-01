#ifndef SCRIPTENGINE_H
#define SCRIPTENGINE_H

#include <QtScript/QScriptEngine>

class ScriptEngine
{
public:
    ScriptEngine();

    static QScriptEngine* get();

    static void loadScript(QString script);

    static void init();

private:
    static QScriptEngine* engine;
};

#endif // SCRIPTENGINE_H
