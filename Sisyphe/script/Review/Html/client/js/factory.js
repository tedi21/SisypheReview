(function() {
  'use strict';

  var sisypheApp = angular.module('sisypheApp');
  
  sisypheApp.factory('sisypheFactory', ['$resource',
    function($resource){   
      return {
        config: $resource('api/config', {}, {query: {method:'GET', isArray:false}}),
        save: $resource('api/save?id=:id&value=:value', {}, {query: {method:'PUT', params:{id: '@id', value: '@value'}, isArray:false}}),
        verify: $resource('api/verify?src=:src', {}, {query: {method:'POST', params:{src: '@src'}, isArray:false}}),
        createDB: $resource('api/createDB?path=:path', {}, {query: {method:'POST', params:{path: '@path'}, isArray:false}}),
        files: $resource('api/files', {}, {query: {method:'GET', isArray:true}}),
        models: $resource('api/models', {}, {query: {method:'GET', params:{path: '@path'}, isArray:true}}),
        fileContent: $resource('api/fileContent?id=:fileId', {}, {query: {method:'GET', params:{fileId:'-1'}, isArray:false}}),
        filterList: $resource('api/filterList?id=:fileId&name=:filterName', {}, {query: {method:'GET', params:{fileId:'-1', filterName:'Errors'}, isArray:false}}),
        fileDebug: $resource('api/fileDebug?id=:fileId', {}, {query: {method:'GET', params:{fileId:'-1'}, isArray:false}}),
        debugDB: $resource('api/debugDB?src=:src', {}, {query: {method:'POST', params:{src: '@src'}, isArray:false}}),
        startDebug: $resource('api/startDebug', {}, {query: {method:'POST', params:{}, isArray:false}})
      };
  }]);
 
}());