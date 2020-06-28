(function() {
  'use strict';

  var sisypheApp = angular.module('sisypheApp');
  
  sisypheApp.factory('sisypheFactory', ['$resource', '$http',
    function($resource, $http){   
      return {
        // Return about page
        // No parameter
        // Return about html page
        aboutHtml: $http(
          {method: 'get', url: 'partials/about.html'}
        ),
        
        // Return help page
        // No parameter
        // Return help html page
        helpHtml: $http(
          {method: 'get', url: 'partials/help.html'}
        ),

        // Return help page
        // No parameter
        // Return help html page
        helpSQL: $http(
          {method: 'get', url: 'partials/sql.html'}
        ),

        // Return load page
        // No parameter
        // Return load html page
        loadHtml: $http(
          {method: 'get', url: 'partials/load.html'}
        ),
        
        // Return the list of analyzed files
        // No parameter
        // Return List [] of files {id, name}
        files: $resource('json/files.json', {}, {
          query: {method: 'get', isArray: true}
        }),

        
        // Return the file content
        // 'fileId' parameter : file identifier
        // return Json structure {id, path, content, type, linesCount, errorsCount, classesCount, enumsCount, decMethodsCount,  defMethodsCount, attributesCount, macrosCount, complexityAvg}
        fileContent: $resource('json/file_:fileId.json', {fileId: '@fileId'}, {
          query: {method: 'get', isArray: false}
        }),

        
        // Return the file entities filtered by filterName
        // 'fileId' parameter : file identifier
        // 'filterName' parameter : selected filter
        // return Json structure {name, list}
        fileEntities: $resource('json/:filterName:sep:fileId.json', {fileId: '@fileId', filterName: '@filterName', sep:'_'}, {
          query: {method: 'get', isArray: false}
        }),


        // Return the db
        // No parameter
        // Return List [] of bytes
		db: $resource('json/cppbase.db', {}, {
          query: {
		    responseType: 'arraybuffer',
            transformResponse: function(data, headersGetter) {
              return { data : data };
            }
          }
		})

      };
  }]);
 
}());
