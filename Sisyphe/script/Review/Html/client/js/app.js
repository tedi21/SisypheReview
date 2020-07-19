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
      when('/sqlFilter', {
        templateUrl: 'partials/sqlFilter.html',
        controller: 'sqlFilterCtrl'
      }).
      otherwise({
        redirectTo: '/'
      });
    }
  ]);

  sisypheApp.config(['$compileProvider',
    function ($compileProvider) {
        $compileProvider.aHrefSanitizationWhitelist(/^\s*(https?|ftp|mailto|tel|file|blob):/);
  }]);

}());
