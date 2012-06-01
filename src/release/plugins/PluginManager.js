/**
  *  This plugin is a Plugin Manager.
  *
  *  Author : Luk2010
  *  Version : 1.0
  *  Date : 01/06/2012
  *  Last Updated : 01/06/2012
  *
 **/

importScript("utilities/Core.js");

var MyPlugin = new AProPlugin("Plugin Manager", "Luk2010",
                              "List every plugins.", "1.0",
                              "01/06/2012", "01/06/2012");
MainWindow.registerPlugin(MyPlugin);

function populateTree(tree)
{
    tree.clear();

    var plugins = MainWindow.plugins;

    foreach(plugins, function(plugin) {

                var item = new QTreeWidgetItem;

                item.setText(0, plugin.name);
                item.setText(1, plugin.description);
                item.setText(2, plugin.author);
                item.setText(3, plugin.lastUpdated);

                tree.addTopLevelItem(item);

    });

}

var tree = new QTreeWidget();
tree.windowTitle = "Plugin Manager";
tree.columnCount = 4;

tree.headerItem().setText(0, "Name");
tree.headerItem().setText(1, "Description");
tree.headerItem().setText(2, "Author");
tree.headerItem().setText(3, "Last Update");

populateTree(tree);

var action = MainWindow.displayMenu.addAction("Plugin Manager");
action["triggered()"].connect(this, function() {
                                  populateTree(tree);
                                  tree.show();
                              });
