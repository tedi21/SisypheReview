(function() {
  'use strict';

  var sisypheApp = angular.module('sisypheApp');
    
  sisypheApp.controller('debugResultCtrl', ['$scope', '$uibModalInstance', 'debug', function ($scope, $uibModalInstance, debug) {
    
    $scope.debug = debug;   
    
  }]);
 
}());