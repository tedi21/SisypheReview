(function() {
  'use strict';

  var sisypheApp = angular.module('sisypheApp', ['ngAnimate', 'ui.bootstrap', 'ngRoute', 'ngScrollTo', 'ngResource', 'siFileBrowser', 'siCodeLayers', 'siPrettify', 'siCppBuffer']);
  
  sisypheApp.config(['$routeProvider',
    function($routeProvider) {
      $routeProvider.
      when('/', {
        templateUrl: '../partials/sisyphe.html',
        controller: 'sisypheCtrl'
      }).
      otherwise({
        redirectTo: '/'
      });
    }
  ]);

}());