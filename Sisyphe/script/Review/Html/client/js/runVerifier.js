(function() {
  'use strict';

  var sisypheApp = angular.module('sisypheApp');
    
  sisypheApp.controller('runVerifierCtrl', ['$scope', '$uibModalInstance', 'sisypheFactory', 'param', function ($scope, $uibModalInstance, sisypheFactory, param) {
    
    $scope.ok = function () {
      sisypheFactory.save.query({id: 'outPath', value: $scope.destinationPath.selectedPath}, function () {
        sisypheFactory.save.query({id: 'projectName', value: $scope.projectName}, function () {
          sisypheFactory.verify.query({src: $scope.sourcePath.selectedPath}, function() {
            param.onFinish();
          });
        });
      });    
      $uibModalInstance.close();
    };

    $scope.cancel = function () {
      $uibModalInstance.dismiss('cancel');
    };
    
    $scope.sourcePath = {
      popoverTemplate: 'popoverSourcePath.html', 
      isOpen: false,
      selectedPath: param.sourcePath,
      filter: '',
      canSelectFolder: true
    };
    
    $scope.sourceClicked = function () {
      $scope.destinationPath.isOpen = false;
      $scope.sourcePath.isOpen = !$scope.sourcePath.isOpen;
    };
    
    sisypheFactory.config.query(function(config){ 
      $scope.destinationPath = {
        popoverTemplate: 'popoverDestinationPath.html', 
        isOpen: false,
        selectedPath: config.outPath,
        filter: '',
        canSelectFolder: true,
        canCreateDirectory: true
      };
      
      $scope.destinationClicked = function () {
        $scope.sourcePath.isOpen = false;
        $scope.destinationPath.isOpen = !$scope.destinationPath.isOpen;
      };
      
      $scope.projectName = config.projectName;
      
    });
    
  }]);
 
}());