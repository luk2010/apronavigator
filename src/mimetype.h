#ifndef MIMETYPE_H
#define MIMETYPE_H

#include <QObject>
#include <QString>
#include <QList>
#include <QtScript>

struct MimeType
{
    QString name;
    QString description;
    QStringList extensions;
};

Q_DECLARE_METATYPE(MimeType)
Q_DECLARE_METATYPE(QList<MimeType>)

QScriptValue MimeTypeToScriptValue(QScriptEngine *engine, const MimeType &s);
void ScriptValueToMimeType(const QScriptValue &obj, MimeType &s);
QScriptValue createMimeType(QScriptContext * context, QScriptEngine *engine);

#endif // MIMETYPE_H
