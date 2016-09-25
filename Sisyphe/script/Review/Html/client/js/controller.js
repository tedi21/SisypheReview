(function() {
  'use strict';

  var sisypheApp = angular.module('sisypheApp');
  
  sisypheApp.controller('sisypheCtrl', ['$scope', '$timeout', '$uibModal', 'sisypheFactory', 'searchFactory', 'codeSearch', 'codeSelection', 'codeError', 'ScrollTo', function ($scope, $timeout, $uibModal, sisypheFactory, searchFactory, codeSearch, codeSelection, codeError, ScrollTo) {
    // init btn view details : folded by default
    $scope.btnViewDetailsIcon = 'folded';
    $scope.isCollapsed = true;
    
    // init filters
    $scope.filters = ['Errors', 'Classes', 'Functions', 'Attributes', 'Enumerations', 'Macros', 'Search'];
    $scope.currentFilter = {'name': 'Errors', 'list': []};
    
    // init files 
    var refresh = function() {
      sisypheFactory.files.query(function(files){
        $scope.files = files;
        if (files.length > 0) {
          updateCurrentFile(files[0]);
        }
      });
    };
    refresh();
    
    // on update filter
    var updateCurrentFilter = function(id, name){
      // Delete layers
      codeSelection.deSelect();
      codeError.deSelect();
      codeSearch.deSelect();
      if (name != 'Search') {
        sisypheFactory.filterList.query({fileId: id, filterName: name}, function(filter){
          // Fill filter list
          $scope.currentFilter = filter;
          if (filter.name == 'Errors') {
            $scope.currentFile.content = codeError.select($scope.currentFile.content, filter.list);
          }
        });
      }
      else {
        $scope.currentFilter = {'name': 'Search', 'list': searchFactory.results()};
        $scope.currentFile.content = codeSearch.select($scope.currentFile.content, searchFactory.results());
      }
    };
    
    // on update file
    var updateCurrentFile = function(file){
      // Enable current file
      file.status = 'Active';
      // Fill content
      sisypheFactory.fileContent.query({fileId: file.id}, function(file){
        $scope.currentFile = file;
        $scope.currentFile.linesDebug = [];
        for (var i = 0; i < $scope.currentFile.linesCount-1; i++) {
          $scope.currentFile.linesDebug.push({'isVisible': false, 'info': undefined});
        }
        updateCurrentFilter(file.id, $scope.currentFilter.name);
        // Retrieve debug information for the file
        sisypheFactory.fileDebug.query({fileId: file.id}, function(filedebug){
          for (var i = 0; i < filedebug.debugSymbols.length; i++) {
            var lineNumber = filedebug.debugSymbols[i].lineNumber-1;
            $scope.currentFile.linesDebug[lineNumber].isVisible = true;
            $scope.currentFile.linesDebug[lineNumber].info = filedebug.debugSymbols[i];
          }
        });
      });
    };
    
    // clear selection
    var clearSelection = function(){
      if (codeSelection.hasSelection()) {
          $scope.currentFile.content = codeSelection.deSelect();
      }
      if (codeError.hasSelection()) {
          $scope.currentFile.content = codeError.deSelect();
      }
      if (codeSearch.hasSelection()) {
          $scope.currentFile.content = codeSearch.deSelect();
      }
    };
    
    // set files click handler
    $scope.setFile = function(file) {
      // Disable old files
      for (var i = 0; i < $scope.files.length; i++) {
        $scope.files[i].status = '';
      }
      // Remove search
      searchFactory.clear();
      // Update filter
      updateCurrentFile(file);
    };
    
    // set filters click handler
    $scope.setFilter = function(filter) {
      clearSelection();
      updateCurrentFilter($scope.currentFile.id, filter);
    };
    
    // set changeViewDetails click handler
    $scope.changeViewDetails = function() {
      if ($scope.btnViewDetailsIcon == 'folded') {
        $scope.isCollapsed = false;
        $scope.btnViewDetailsIcon = 'unfolded';
        // view selection
        $timeout(function () {
          var index = 0;
          var found = false;
          while (index < $scope.currentFilter.list.length && !found) {
            if ($scope.currentFilter.list[index].clicked === true) {
              found = true;
            }
            else {
              index++;
            }
          }
          ScrollTo.idOrName('row-list-' + index, -1);
        }, 0);
      }
      else {
        $scope.isCollapsed = true;
        $scope.btnViewDetailsIcon = 'folded';
      }
    };
    
    var updateCurrentCode = function (index) {
      if (index < $scope.currentFilter.list.length) {
        var item = $scope.currentFilter.list[index];
        if (false === item.clicked || undefined === item.clicked) {
          // set clicked attribute
          for (var i = 0; i < $scope.currentFilter.list.length; i++) {
            $scope.currentFilter.list[i].clicked = false;
          }
          item.clicked = true;
          // set selection
          var content = $scope.currentFile.content;
          if (codeSelection.hasSelection()) {
            content = codeSelection.deSelect();
          }
          $scope.currentFile.content = codeSelection.select(content, item);
        }
        else {
          // deselect
          item.clicked = false;
          $scope.currentFile.content = codeSelection.deSelect();
        }
      }
    };
    
    // set list click handler
    $scope.listClicked = function (index) {
      updateCurrentCode(index);
      // get line number
      var item = $scope.currentFilter.list[index];
      if (item.clicked === true) {
        var lineNumber = item.lineNumber;
        // set scrollbar position (- 5 lines to see previous content)
        var lines = lineNumber - 1 - 5;
        var pos = Math.floor(10 + 18 * lines);
        ScrollTo.idOrName('code-panel', pos);
      }
    };
    
    // set error click handler
    $scope.errorClicked = function (index) {
      updateCurrentCode(index);
      var item = $scope.currentFilter.list[index];
      if (item.clicked === true) {
        ScrollTo.idOrName('row-list-' + index, -1);
      }
    };
    
    // set search click handler
    $scope.searchClicked = function (exp) {
      // Remove selection
      clearSelection();
      // Set search
      searchFactory.search($scope.currentFile.content, exp);
      // Update list
      updateCurrentFilter($scope.currentFile.id, 'Search');
      // Open view
      if (exp !== '' && exp !== undefined) {
        $scope.btnViewDetailsIcon = 'folded';
        $scope.changeViewDetails();
      }
    };
    
    // set verify parameters click handler
    $scope.configVerifierClicked = function () {
      var modalInstance = $uibModal.open({
        animation: true,
        templateUrl: '../partials/configVerifier.html',
        controller: 'configVerifierCtrl',
        resolve: {
          param: function () {
            return {
              onFinish: function () {
                refresh();
                $scope.spinning = false;
                $timeout(function () {
                  $scope.loading = false;
                }, 1500);
              }
            };
          }
        }
      });
            
      modalInstance.result.then(function(files) {
        // ok
        $scope.loading = true;
        $scope.spinning = true;
      }, function () {
        // cancel 
      });
    };
    
    // set run click handler
    $scope.runVerifierClicked = function () {
      var modalInstance = $uibModal.open({
        animation: true,
        templateUrl: '../partials/runVerifier.html',
        controller: 'runVerifierCtrl',
        resolve: {
          param: function () {
            var srcPath = '';
            if ($scope.currentFile) {
              var indexName = Math.max($scope.currentFile.path.lastIndexOf('\\'), $scope.currentFile.path.lastIndexOf('/'));
              srcPath = $scope.currentFile.path.substr(0, indexName+1);
            }
            return {
              sourcePath: srcPath,
              onFinish: function () {
                refresh();
                $scope.spinning = false;
                $timeout(function () {
                  $scope.loading = false;
                }, 1500);
              }
            };
          }
        }
      });
      
      modalInstance.result.then(function(files) {
        // ok
        $scope.loading = true;
        $scope.spinning = true;
      }, function () {
        // cancel 
      });
    };
    
    // set config click handler
    $scope.configDebuggerClicked = function () {
      var modalInstance = $uibModal.open({
        animation: true,
        templateUrl: '../partials/configDebugger.html',
        controller: 'configDebuggerCtrl',
        resolve: {
          param: function () {
            return {
              onFinish: function () {
                /*refresh();
                $scope.spinning = false;
                $timeout(function () {
                  $scope.loading = false;
                }, 1500);*/
              }
            };
          }
        }
      });
      
      modalInstance.result.then(function(files) {
        // ok
        //$scope.loading = true;
        //$scope.spinning = true;
      }, function () {
        // cancel 
      });
    };
    
    // set run click handler
    $scope.runDebuggerClicked = function () {
      var srcPath = '';
      if ($scope.currentFile) {
        var indexName = Math.max($scope.currentFile.path.lastIndexOf('\\'), $scope.currentFile.path.lastIndexOf('/'));
        srcPath = $scope.currentFile.path.substr(0, indexName+1);
      }
      sisypheFactory.debugDB.query({src: srcPath}, function() {
        refresh();
      });
    };
    
    // set debug function
    $scope.debugFunction = function (index) {
      var info = {};
      info.functionName = $scope.currentFile.linesDebug[index].info.name;
      info.functionAddress = $scope.currentFile.linesDebug[index].info.address;
      info.debugStartAddress = $scope.currentFile.linesDebug[index].info.debugStart;
      info.debugEndAddress = $scope.currentFile.linesDebug[index].info.debugEnd;
      info.debugVariables = $scope.currentFile.linesDebug[index].info.debugVariables;
      for (var i = 0; i < info.debugVariables.length; i++) {
        info.debugVariables[i].value = 9;
      }
      info.debugFunctionId = $scope.currentFile.linesDebug[index].info.debugFunctionId;
      info.debugReturn = $scope.currentFile.linesDebug[index].info.debugReturn;
      sisypheFactory.startDebug.save({}, info, function() {
        sisypheFactory.fileDebug.query({fileId: $scope.currentFile.id}, function(filedebug){
          for (var i = 0; i < filedebug.debugSymbols.length; i++) {
            var lineNumber = filedebug.debugSymbols[i].lineNumber-1;
            if (lineNumber == index) {
              var debug = {};
              debug.variablesList = filedebug.debugSymbols[i].debugVariables;
              var modalInstance = $uibModal.open({
                animation: true,
                templateUrl: '../partials/debugResult.html',
                controller: 'debugResultCtrl',
                resolve: {debug}
              });
              break;
            }
          }
        });
      });
    };
    
  }]);

}());

