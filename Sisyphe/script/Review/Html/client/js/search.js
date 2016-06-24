(function() {
  'use strict';

  var sisypheApp = angular.module('sisypheApp');
    
  sisypheApp.factory('searchFactory', ['cppBuffer', 
    function (cppBuffer){
      var searchFactory = {};
      
      searchFactory.search = function (buffer, exp) {
        var list = [];
        if (exp !== '' && exp !== undefined) {
          var foundIndex = buffer.search(exp);
          var bufferIndex = foundIndex;
          while (foundIndex != -1 && bufferIndex < buffer.length) {
            list.push({
                        'lineNumber': cppBuffer.countLine(buffer, bufferIndex),
                        'start': bufferIndex,
                        'length': exp.length,
                        'category': 'search ' + exp,
                        'description': buffer.substring(cppBuffer.expandLeft(buffer, bufferIndex), 
                                                        cppBuffer.expandRight(buffer, bufferIndex+exp.length))
                      });
            //console.log(list[list.length - 1].lineNumber + ' ' + list[list.length - 1].category + ' ' + list[list.length - 1].description);
            bufferIndex += 1;
            foundIndex = buffer.substring(bufferIndex).search(exp);
            bufferIndex += foundIndex;
          }
        }
        searchFactory.list = list;
      };
      
      
      searchFactory.results = function () {
        var list = [];
        if (searchFactory.list !== undefined) {
          list = searchFactory.list;
        }
        return list;
      };
      
      searchFactory.clear = function () {
        searchFactory.list = undefined;
      };
      
      return searchFactory;
  }]);
 
}());