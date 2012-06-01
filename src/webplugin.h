#ifndef WEBPLUGIN_H
#define WEBPLUGIN_H

#include <QObject>
#include <QString>
#include <QList>
#include <QtScript>

#include "mimetype.h"
#include "plugin.h"

class WebPlugin : public QObject
{
    Q_OBJECT

    Q_PROPERTY(QString name READ getName WRITE setName)
    Q_PROPERTY(QString description READ getDescription WRITE setDescription)
    Q_PROPERTY(QList<Plugin> plugins READ getPlugins WRITE setPlugins)

public:

    WebPlugin();
    WebPlugin(const WebPlugin& plugin);
    WebPlugin(const QString & _name, const QString& _description, const QList<Plugin>& _plugins = QList<Plugin>());

    ~WebPlugin();

public slots:

    virtual QObject* create(const QString &mimeType, const QUrl & url, const QStringList &argumentNames, const QStringList &argumentValues) const;

    QString getName() const;
    void setName(const QString& _name);

    QString getDescription() const;
    void setDescription(const QString& _description);

    QList<Plugin> getPlugins() const;
    void setPlugins(const QList<Plugin>& _plugins);

private:

    QString name;
    QString description;
    QList<Plugin> plugins;
};

Q_DECLARE_METATYPE(WebPlugin*)
Q_DECLARE_METATYPE(QList<WebPlugin*>)

QScriptValue constructWebPlugin(QScriptContext *context, QScriptEngine *engine);

#endif // WEBPLUGIN_H
