(function() {
  'use strict';

  var siFileBrowser = angular.module('siFileBrowser', []);
  
  siFileBrowser.directive('filebrowser', ['fileBrowserFactory', function (fileBrowserFactory) {
    return {
      restrict: 'E',
      scope: {
        fileSettings: '=filesettings'
      },
      templateUrl: '../partials/filebrowser.html',
      link: function (scope, element, attr) {
        if (scope.fileSettings.selectedPath != undefined) {
          scope.currentPath = scope.fileSettings.selectedPath.substr(0, scope.fileSettings.selectedPath.lastIndexOf('\\') + 1);
        }
        fileBrowserFactory.drives.query(function(drives) {
          scope.drives = drives;
        });
        var updateFile = function(filename) {
          scope.fileSettings.selectedPath = filename;
          if (scope.fileSettings.OnSelectedPathChanged !== undefined) {
            scope.fileSettings.OnSelectedPathChanged(filename);
          }
        };       
        var updateFiles = function(filepath) {
          scope.currentPath = filepath.path;
          scope.files = filepath.files;
          if (scope.fileSettings.canSelectFolder) {
            updateFile(filepath.path);
          }
        };
        fileBrowserFactory.files.query({id: 3, path: encodeURIComponent(scope.currentPath)}, updateFiles);
        scope.close = function () {
          scope.fileSettings.isOpen = false;
        };
        scope.driveClicked = function (drive) {
          fileBrowserFactory.files.query({id: 3, path: encodeURIComponent(drive)}, updateFiles);
        };
        scope.homeClicked = function () {
          fileBrowserFactory.files.query({id: 1}, updateFiles);
        };
        scope.parentClicked = function () {
          fileBrowserFactory.files.query({id: 2, path: encodeURIComponent(scope.currentPath)}, updateFiles);
        };
        scope.newFolderClicked = function () {
          scope.newFolderLine = !scope.newFolderLine;
        };
        scope.createFolderClicked = function (folder) {
          var folderPath = scope.currentPath + folder + '\\';
          fileBrowserFactory.mkdir.query({path: encodeURIComponent(folderPath)}, function () {
            scope.newFolderLine = false;
            fileBrowserFactory.files.query({id: 3, path: encodeURIComponent(folderPath)}, updateFiles);
          });
        };
        scope.fileClicked = function (file) {
          for (var i = 0; i < scope.files.length; i++) {
            scope.files[i].clicked = false;
          }
          file.clicked = true;
          if (file.isDirectory) {
            fileBrowserFactory.files.query({id: 3, path: encodeURIComponent(file.path)}, updateFiles);
          }
          else {
            updateFile(file.path);
          }
        };
      }
    };
  }]);

  siFileBrowser.factory('fileBrowserFactory', ['$resource',
    function($resource){   
      return {
        drives: $resource('api/filebrowser/drives', {}, {query: {method:'GET', isArray:true}}),
        files: $resource('api/filebrowser/files?id=:id&path=:path', {}, {query: {method:'GET', params:{id:'1', path:''}, isArray:false}}),
        mkdir: $resource('api/filebrowser/mkdir?path=:path', {}, {query: {method:'POST', params:{path: '@path'}, isArray:false}})
      };
  }]);
  
  siFileBrowser.filter('fileBrowserFilter', function() {
   return function( items, input) {
    var filtered = [];
    var specialCharacters = /([.])/g;
    var patt = new RegExp('^' + input.replace(specialCharacters, "\\$1").replace(/\*/g, '.*'));
    angular.forEach(items, function(item) {
       if(item.isDirectory || item.name.match(patt)) {
          filtered.push(item);
        }
    });
    return filtered;
  };
});
  
}());
