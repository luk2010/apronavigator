#ifndef AWEBPLUGINFACTORY_H
#define AWEBPLUGINFACTORY_H

#include <QWebPluginFactory>
#include <QtScript>

#include "scriptengine.h"
#include "webplugin.h"

typedef Plugin APlugin;
typedef MimeType AMimeType;

class AWebPluginFactory : public QWebPluginFactory
{
    Q_OBJECT

    Q_PROPERTY(QList<WebPlugin*> factories READ getFactories WRITE setFactories)

public:
    explicit AWebPluginFactory(QObject *parent = 0);

    QObject* create(const QString &mimeType, const QUrl &, const QStringList &argumentNames, const QStringList &argumentValues) const;
    
signals:
    
public slots:
    void addPluginFactory(WebPlugin* factory);
    void removePluginFactory(WebPlugin* factory);

    QList<WebPlugin*> getFactories() const;
    void setFactories(QList<WebPlugin*> facts);

    QList<QWebPluginFactory::Plugin> plugins() const;

private:
    QList<WebPlugin*> factories;

};

Q_DECLARE_METATYPE(AWebPluginFactory*)

Q_DECLARE_METATYPE(QWebPluginFactory*)

Q_DECLARE_METATYPE(QList<QWebPluginFactory*>)

QScriptValue aWebPluginFactoryToScriptValue(QScriptEngine *engine, AWebPluginFactory* const &in);
void aWebPluginFactoryFromScriptValue(const QScriptValue &object, AWebPluginFactory* &out);

#endif // AWEBPLUGINFACTORY_H
