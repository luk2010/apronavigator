/**
  *  This plugin list every WebPlugin Factory added as Script.
  *
  *  Version : 1
  *  Author : Luk2010
  *  Date : 01/06/2012
  *  Last Updated : 01/06/2012
  *
 **/

var MyPlugin = new AProPlugin("WebPlugin Viewer", "Luk2010",
                           "This plugin show you each WebPlugin Factory in use", "1",
                           "01/06/2012", "01/06/2012");
MainWindow.registerPlugin(MyPlugin);

/**
  *  Populate the given QTreeWidget with informations about WebPlugins.
 **/
function populateTree(tree)
{
    var webPlugins = MainWindow.pluginFactory.getFactories();
    if(webPlugins.length > 0)
    {
        tree.clear();

        for(var i = 0; i < webPlugins.length; i++)
        {
            var webPlugin = webPlugins[i];

            if(webPlugin.plugins.length > 0)
            {
                var plugins = webPlugin.plugins;
                for(var j = 0; j < plugins.length; j++)
                {
                    var plugin = plugins[j];

                    var item = new QTreeWidgetItem();

                    item.setText(0, plugin["name"]);
                    item.setText(1, plugin["description"]);

                    var mimeTypesText = "";
                    var mimeTypes = plugin.mimeTypes;
                    for(var k = 0; k < mimeTypes.length; k++)
                    {
                        mimeTypesText += mimeTypes[k].name;
                    }

                    item.setText(2, mimeTypesText);

                    tree.addTopLevelItem(item);
                }
            }
        }
    }
}

var tree = new QTreeWidget();

tree.columnCount = 3;
tree.headerItem().setText(0, "Name");
tree.headerItem().setText(1, "Description");
tree.headerItem().setText(2, "Type");

tree.setColumnWidth(0, 100);
tree.setColumnWidth(1, 100);
tree.setColumnWidth(2, 100);

tree.minimumWidth = 400;
tree.minimumHeight = 200;

populateTree(tree);

var show = MainWindow.displayMenu.addAction("WebPlugin Viewer");
show["triggered()"].connect(this, function () {
                                populateTree(tree);
                                tree.show();
                            });

