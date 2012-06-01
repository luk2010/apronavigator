function updatePluginTree()
{
    tree.clear();

    var plugins = MainWindow.pluginFactory.factories;

    QMessageBox.information(0, "");

    for(plugin in plugins)
    {

        var item = new QTreeWidgetItem();
        item.setText(0, plugin.name);
        item.setText(1, plugin.description);

        var mimeTypes = plugin.mimeTypes;
        var mimes = "";
        for(mimeType in mimeTypes)
        {
            mimes += mimeType + " | ";
        }

        item.setText(2, mimes);
        tree.addTopLevelItem(item);

    }

    var header = new QTreeWidgetItem();
    header.setText(0, "Name");
    header.setText(1, "Description");
    header.setText(2, "Mime Types");

    tree.setHeaderItem(header);
}

function showPluginViewer()
{
    updatePluginTree();
    window.show();
}

var window = new QWidget();
window.windowTitle = "Plugin Viewer";

var layout = new QVBoxLayout();
window.setLayout(layout);

var tree = new QTreeWidget();
layout.addWidget(tree, 0, 0);

updatePluginTree();

var show = MainWindow.displayMenu.addAction("Plugin Viewer");
show["triggered()"].connect(this, showPluginViewer);
