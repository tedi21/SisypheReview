(function() {
  'use strict';

  var sisypheApp = angular.module('sisypheApp', ['ngAnimate', 'ui.bootstrap', 'ngRoute', 'ngScrollTo', 'ngResource', 'ngMessages', 'siFileBrowser', 'siCodeLayers', 'siPrettify', 'siCppBuffer', 'siModalMovable']);
  
  sisypheApp.config(['$routeProvider',
    function($routeProvider) {
      $routeProvider.
      when('/', {
        templateUrl: 'partials/sisyphe.html',
        controller: 'sisypheCtrl'
      }).
      otherwise({
        redirectTo: '/'
      });
    }
  ]);

}());