(function() {
  'use strict';

  var sisypheApp = angular.module('sisypheApp');
    
  sisypheApp.controller('configVerifierCtrl', ['$scope', '$timeout', '$uibModalInstance', 'sisypheFactory', 'param', function ($scope, $timeout, $uibModalInstance, sisypheFactory, param) {

    $scope.ok = function () {
      sisypheFactory.save.query({id: 'embeddedFile', value: $scope.parsing.embeddedFile.toString()}, function () {
        sisypheFactory.save.query({id: 'rules', value: $scope.parsing.rules}, function () {
          sisypheFactory.save.query({id: 'dbPath', value: $scope.databasePath.selectedPath}, function () {
            sisypheFactory.save.query({id: 'exePath', value: $scope.executablePath.selectedPath}, function () {
              sisypheFactory.save.query({id: 'rulesScript', value: $scope.rulesScript.selectedPath}, function () {
                sisypheFactory.save.query({id: 'reportModel', value: $scope.modelName}, function () {
                  param.onFinish();
                });
              });
            });
          });
        });
      });
      $uibModalInstance.close();
    };

    $scope.cancel = function () {
      $uibModalInstance.dismiss('cancel');
    };
    
    sisypheFactory.config.query(function(config){
      $scope.parsing = { 
        embeddedFile: (config.embeddedFile === 'true'),
        rules: config.rules
      };
    
      $scope.databasePath = {
        popoverTemplate: 'popoverDatabasePath.html', 
        isOpen: false,
        selectedPath: config.dbPath,
        filter: '*.db',
        canSelectFolder: false
      };
      
      $scope.executablePath = {
        popoverTemplate: 'popoverExecutablePath.html', 
        isOpen: false,
        selectedPath: config.exePath,
        filter: 'tdscript.exe',
        canSelectFolder: false
      };
      
      $scope.rulesScript = {
        popoverTemplate: 'popoverRulesScript.html', 
        isOpen: false,
        selectedPath: config.rulesScript,
        filter: '*.td',
        canSelectFolder: false,
        canCreateDirectory: false,
        OnSelectedPathChanged: function (filename) {
          sisypheFactory.models.query({path: filename}, function(list){
            $scope.models = list;
            if (list.length > 0) {
              $scope.modelName = list[0];
            }
          });
        }
      };
      
      var dbDefaultPath = config.dbPath.substr(0, config.dbPath.lastIndexOf('\\') + 1);
      $scope.dbOutputPath = {
        popoverTemplate: 'popoverDBOutputPath.html', 
        isOpen: false,
        selectedPath: dbDefaultPath,
        databaseName: 'cppBase',
        filter: '',
        canSelectFolder: true,
        canCreateDirectory: true
      };
      
      $scope.modelName = config.reportModel;
      sisypheFactory.models.query({path: config.rulesScript}, function(list){
        $scope.models = list;
      });
    });
    
    $scope.databaseClicked = function () {
      $scope.executablePath.isOpen = false;
      $scope.databasePath.isOpen = !$scope.databasePath.isOpen;
    };
    
    $scope.executableClicked = function () {
      $scope.databasePath.isOpen = false;
      $scope.executablePath.isOpen = !$scope.executablePath.isOpen;
    };
    
    $scope.rulesScriptClicked = function () {
      $scope.rulesScript.isOpen = !$scope.rulesScript.isOpen;
    };
    
    $scope.dbOutputPathClicked = function () {
      $scope.dbOutputPath.isOpen = !$scope.dbOutputPath.isOpen;
    };
    
    $scope.createDBClicked = function () {
      var filepath = $scope.dbOutputPath.selectedPath + $scope.dbOutputPath.databaseName + '.db';
      sisypheFactory.createDB.query({path: filepath}, function() {
        $scope.databasePath.selectedPath = filepath;
        $scope.isNotificationCollapsed = false;
        $timeout(function () {
          $scope.isNotificationCollapsed = true;
        }, 3000);
      });
    };
        
    $scope.isNotificationCollapsed = true;
  }]);
 
}());