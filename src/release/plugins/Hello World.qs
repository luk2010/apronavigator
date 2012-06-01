MainWindow.displayMenu.addSeparator();

var MyMenu = MainWindow.displayMenu.addMenu("Hello World");

var myAlternativePrevious = MyMenu.addAction("Alternative Previous");
myAlternativePrevious["triggered()"].connect(this, function () {
                                                 MainWindow.NAV_precedent_action();
                                             });

var myAbout = MyMenu.addAction("About Hello World.qs");
myAbout["triggered()"].connect(this, function () {
                                   QMessageBox.information(0, "About", "Hello World.js is the first script ! This script is the first QtScript that can use the Navigator default functions and classes. You can add whatever you want, just like every QtScript ;)");
                               });
