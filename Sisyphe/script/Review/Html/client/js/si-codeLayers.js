(function() {
  'use strict';
  
  var siCodeLayers = angular.module('siCodeLayers', ['siCppBuffer']);
    
  siCodeLayers.factory('codeSelection', ['cppBuffer', function (cppBuffer) {
    var codeSelection = {};
    
    codeSelection.select = function (buffer, item) {
      codeSelection.before = buffer;
      return cppBuffer.setStyle(buffer, item.start, item.length, 'code-selection', '', '', true);
    };
    
    codeSelection.deSelect = function () {
      var content = codeSelection.before;
      codeSelection.before = undefined;
      return content;
    };
    
    codeSelection.hasSelection = function () {
      return codeSelection.before !== undefined;
    };
    
    return codeSelection;
  }]);
  
  siCodeLayers.factory('codeError', ['cppBuffer', function (cppBuffer) {
    var codeError = {};
    
    codeError.select = function (buffer, listErrors) {
      codeError.before = buffer;
      var content = buffer;
      for (var i = listErrors.length-1; i >= 0; i--) {
        content = cppBuffer.setStyle(content, listErrors[i].start, listErrors[i].length, 'code-error', listErrors[i].description, 'errorClicked(' + i + ')', false);
      }
      return content;
    };
    
    codeError.deSelect = function () {
      var content = codeError.before;
      codeError.before = undefined;
      return content;
    };
    
    codeError.hasSelection = function () {
      return codeError.before !== undefined;
    };
    
    return codeError;
  }]);
  
  
  siCodeLayers.factory('codeSearch', ['cppBuffer', function (cppBuffer) {
    var codeSearch = {};
    
    codeSearch.select = function (buffer, listSearch) {
      codeSearch.before = buffer;
      var content = buffer;
      for (var i = listSearch.length-1; i >= 0; i--) {
        content = cppBuffer.setStyle(content, listSearch[i].start, listSearch[i].length, 'code-search', '', '', false);
      }
      return content;
    };
    
    codeSearch.deSelect = function () {
      var content = codeSearch.before;
      codeSearch.before = undefined;
      return content;
    };
    
    codeSearch.hasSelection = function () {
      return codeSearch.before !== undefined;
    };
    
    return codeSearch;
  }]);
  
}());