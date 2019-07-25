(function() {
  'use strict';

  var sisypheApp = angular.module('sisypheApp');
  
  sisypheApp.controller('sisypheCtrl', ['$scope', '$timeout', '$uibModal', 'sisypheFactory', 'searchFactory', 'codeSearch', 'cppBuffer', 'codeSelection', 'codeError', 'ScrollTo', function ($scope, $timeout, $uibModal, sisypheFactory, searchFactory, codeSearch, cppBuffer, codeSelection, codeError, ScrollTo) {
    var attributes = {
      diff_files : [],
      all_files  : []
    };
    
    // init btn view details : unfolded by default
    $scope.btnViewDetailsIcon = 'unfolded';
    $scope.isCollapsed = false;
    
    // init filters
    $scope.filters = ['Errors', 'Search', 'Diff'];
    $scope.currentFilter = {'name': 'Errors', 'list': []};
    
    var filter_diff_files = function (files) {
        attributes.diff_files = []
        for (var i = 0; i < files.length; i++) { 
          (function(file){   //Closure. This line does the magic!!
            sisypheFactory.fileEntities.query({fileId: files[i].id, filterName: 'diff'}, function(filter){
              if (filter.new > 0) {
                attributes.diff_files.push(file);
              }
            });
          })(files[i]); //This one too
        }
    }
    
    // init files 
    var refresh = function() {
      sisypheFactory.files.query(function(files){
        $scope.files = files;
        attributes.all_files = files;
        filter_diff_files(files);
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
        sisypheFactory.fileEntities.query({fileId: id, filterName: name.toLowerCase()}, function(filter){
          // Fill filter list
          $scope.currentFilter = filter;
          if (filter.name == 'Errors' || filter.name == 'Diff') {
            $scope.currentFile.content = codeError.select($scope.currentFile.content, filter.list);
          }
        }, function(error){
          console.log('resource not found : ' + name + ', ' + id);
          var filter = {'name': name,
                        'solved': 0,
                        'new': 0,
                        'list': []};
          $scope.currentFilter = filter;
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

        var pos = 10;
        ScrollTo.idOrName('code-panel', pos);
        updateCurrentFilter(file.id, $scope.currentFilter.name);
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
      if (($scope.currentFilter.name == 'Diff' || filter == 'Diff') && 
          ($scope.currentFilter.name != filter)) {
          // Disable old files
          for (var i = 0; i < $scope.files.length; i++) {
            $scope.files[i].status = '';
          }
          // Set files
          if (filter == 'Diff') {
            $scope.files = attributes.diff_files;
          }
          else {
            $scope.files = attributes.all_files;
          }
          // Set filter name
          $scope.currentFilter = 
                       {'name': filter,
                        'solved': 0,
                        'new': 0,
                        'list': []};
          // Load file data
          if ($scope.files.length > 0) {
            // Remove search
            searchFactory.clear();
            // Update filter
            updateCurrentFile($scope.files[0]);
          }
      }
      else {
        updateCurrentFilter($scope.currentFile.id, filter);
      }
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
    $scope.errorClicked = function (index, ev) {
      ev.stopPropagation();
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
    
    $scope.logoClicked = function (index) {
      sisypheFactory.aboutHtml.then(function(html){
        var modalInstance = $uibModal.open({
          animation: true,
          template: html.data,
          controller: 'logoCtrl',
        });
      });
    };
    
  }]);

}());

