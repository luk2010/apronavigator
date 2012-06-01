/**
  *  This file has some utilities that your script can load using function importScript.
  *
 **/

/**
  *  Provide an emulated "foreach" for Arrays that have custom-types, like QList.
  *
  *  Example :
  *
  *  var myArray = new Array("bla", "blabla");
  *  foreach(myArray, function(str) {
  *
  *     QMessageBox.information(0, "This is an exemple", str);
  *
  *  });
  *
 **/
var foreach = function(objectList, func)
{
    for(var i = 0; i < objectList.length; i++)
    {
        var object = objectList[i];
        func(object);
    }
}
