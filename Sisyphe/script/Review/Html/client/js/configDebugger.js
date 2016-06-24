(function() {
  'use strict';

  var sisypheApp = angular.module('sisypheApp');
    
  sisypheApp.controller('configDebuggerCtrl', ['$scope', '$uibModalInstance', 'sisypheFactory', 'param', function ($scope, $uibModalInstance, sisypheFactory, param) {
    
    $scope.ok = function () {
      sisypheFactory.save.query({id: 'debugPath', value: $scope.exePath.selectedPath}, function () {
        sisypheFactory.save.query({id: 'pdbPath', value: $scope.pdbPath.selectedPath}, function () {
          param.onFinish(); 
        });          
      });
      $uibModalInstance.close();
    };

    $scope.cancel = function () {
      $uibModalInstance.dismiss('cancel');
    };
    
    sisypheFactory.config.query(function(config){
      $scope.exePath = {
        popoverTemplate: 'popoverExePath.html', 
        isOpen: false,
        selectedPath: config.debugPath,
        filter: '*.exe',
        canSelectFolder: false
      };
      
      $scope.pdbPath = {
        popoverTemplate: 'popoverPdbPath.html', 
        isOpen: false,
        selectedPath: config.pdbPath,
        filter: '*.pdb',
        canSelectFolder: false
      };
    });
    
    $scope.exeClicked = function () {
      $scope.pdbPath.isOpen = false;
      $scope.exePath.isOpen = !$scope.exePath.isOpen;
    };
    
    $scope.pdbClicked = function () {
      $scope.exePath.isOpen = false;
      $scope.pdbPath.isOpen = !$scope.pdbPath.isOpen;
    };
    
  }]);
 
}());