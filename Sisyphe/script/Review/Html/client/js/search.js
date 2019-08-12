(function() {
  'use strict';

  var sisypheApp = angular.module('sisypheApp');
    
  sisypheApp.factory('searchFactory', ['cppBuffer', 
    function (cppBuffer){
      var searchFactory = {};
      
      searchFactory.search = function (buffer, exp) {
        var list = [];
        if (exp !== '' && exp !== undefined) {
          var esc_exp = exp.replace(/[-\/\\^$*+?.()|[\]{}]/g, '\\$&');
          var rawBuffer = cppBuffer.raw(buffer);
          //console.log(rawBuffer);
          var foundIndex = rawBuffer.search(esc_exp);
          var bufferIndex = foundIndex;
          while (foundIndex != -1 && bufferIndex < rawBuffer.length) {
            list.push({
                        'lineNumber': cppBuffer.countLine(rawBuffer, bufferIndex),
                        'start': bufferIndex,
                        'length': exp.length,
                        'category': 'search ' + exp,
                        'description': rawBuffer.substring(cppBuffer.expandLeft(rawBuffer, bufferIndex), 
                                                        cppBuffer.expandRight(rawBuffer, bufferIndex+exp.length))
                      });
            //console.log(list[list.length - 1].lineNumber + ' ' + list[list.length - 1].category + ' ' + list[list.length - 1].description);
            bufferIndex += 1;
            foundIndex = rawBuffer.substring(bufferIndex).search(esc_exp);
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
