/** @file QTFormWebPlugin.js
  *
  * This file shows an example on how to create a simple WebPlugin for Atlanti's Project Engine,
  * using Qt Script.
  *
  * @author Luk2010
  * @date 16/05/2012
  */

////////////////////////////////////////////////////////////
//                       Utilities                        //
////////////////////////////////////////////////////////////

function getArgumentValue(name, names, values, from)
{
    var i = (from == undefined) ? 0 : from;
    for ( ; i < names.length; ++i) {
        if (names[i] == name)
            return values[i];
    }
    return undefined;
}

////////////////////////////////////////////////////////////
//                    Plugin Class                        //
////////////////////////////////////////////////////////////

function QTFormWebPlugin(formUrl, scriptUrl, parent)
{
    QWidget.call(this, parent);

    this.initialized = false;
    this.formReply = this.downloadFile(formUrl, this.formDownloaded);
    if (scriptUrl == undefined)
        this.script = "";
    else
        this.scriptReply = this.downloadFile(scriptUrl, this.scriptDownloaded);
}

QTFormWebPlugin.prototype = new QWidget();

QTFormWebPlugin.prototype.downloadFile = function(url, callback)
{
    if (this.accessManager == undefined)
        this.accessManager = new QNetworkAccessManager();
    var reply = this.accessManager.get(new QNetworkRequest(url));
    reply.finished.connect(this, callback);
    return reply;
}

QTFormWebPlugin.prototype.formDownloaded = function()
{
    var loader = new QUiLoader();
    this.form = loader.load(this.formReply);
    var layout = new QVBoxLayout(this);
    layout.addWidget(this.form, 0, Qt.AlignCenter);
    this.initialize();
}

QTFormWebPlugin.prototype.scriptDownloaded = function()
{
    var stream = new QTextStream(this.scriptReply);
    this.script = stream.readAll();
    this.initialize();
}

QTFormWebPlugin.prototype.initialize = function()
{
    if (this.initialized)
        return;
    if ((this.form == undefined) || (this.script == undefined))
        return;
    var ctor = eval(this.script);
    if (typeof ctor != "function")
        return;
    this.instance = new ctor(this.form);
    this.initialized = true;
}

////////////////////////////////////////////////////////////
//                 Plugin Factory                         //
////////////////////////////////////////////////////////////

var WebPluginFactory = new WebPlugin("QtForm WebPluginFactory", "Plugins that show Qt Form live ;p !");

/** @function create(mimeType, url, argumentNames, argumentValues)
  *
  * Create a QObject that will handle the mimeType.
  *
  */
WebPluginFactory.create = function(mimeType, url, argumentNames, argumentValues)
{
    if (mimeType != "application/x-qtform")
            return null;

        var formUrl = getArgumentValue("form", argumentNames, argumentValues);
        var scriptUrl = getArgumentValue("script", argumentNames, argumentValues);
        if (formUrl == undefined)
            return null;

        return new QTFormWebPlugin(new QUrl(formUrl), new QUrl(scriptUrl));
}

////////////////////////////////////////////////////////////
//                 Plugin Description                     //
////////////////////////////////////////////////////////////

var plugin = new Plugin();
plugin.name = "QtForm Handler";
plugin.description = "Handles QtForm in QWebkit";
plugin.mimeTypes = new Array(new MimeType("application/x-qtform", "Mime Type for QtForm"));

WebPluginFactory.setPlugins(new Array(plugin));
QMessageBox.information(0, "In Script", WebPluginFactory.plugins[0].mimeTypes[0].description);

////////////////////////////////////////////////////////////
//                Plugin Registration                     //
////////////////////////////////////////////////////////////

MainWindow.pluginFactory.addPluginFactory(WebPluginFactory);
