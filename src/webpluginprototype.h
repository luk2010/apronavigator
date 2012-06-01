#ifndef WEBPLUGINPROTOTYPE_H
#define WEBPLUGINPROTOTYPE_H

#include "webplugin.h"

class WebPluginPrototype : public QObject,
        protected QScriptable
{
    Q_OBJECT

    Q_PROPERTY(QString name READ getName WRITE setName)
    Q_PROPERTY(QString description READ getDescription WRITE setDescription)
    Q_PROPERTY(QList<Plugin> plugins READ getPlugins WRITE setPlugins)

public:
    WebPluginPrototype(QObject* parent = 0);

    QString getName() const;
    void setName(const QString& _name);

    QString getDescription() const;
    void setDescription(const QString& _description);

    QList<Plugin> getPlugins() const;
    void setPlugins(const QList<Plugin>& _plugins);

public slots:
    QString toString() const;
};

#endif // WEBPLUGINPROTOTYPE_H
