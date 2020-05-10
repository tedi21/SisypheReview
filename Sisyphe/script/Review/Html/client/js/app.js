(function() {
  'use strict';

  var sisypheApp = angular.module('sisypheApp', ['ngAnimate', 'ui.bootstrap', 'ngRoute', 'ngScrollTo', 'ngResource', 'ngMessages', 'ui.codemirror', 'siFileBrowser', 'siCodeLayers', 'siPrettify', 'siCppBuffer', 'siModalMovable']);
  
  sisypheApp.config(['$routeProvider',
    function($routeProvider) {
      $routeProvider.
      when('/', {
        templateUrl: 'partials/sisyphe.html',
        controller: 'sisypheCtrl'
      }).
      when('/tester', {
        templateUrl: 'partials/tester.html',
        controller: 'testerCtrl'
      }).
      otherwise({
        redirectTo: '/'
      });
    }
  ]);

}());