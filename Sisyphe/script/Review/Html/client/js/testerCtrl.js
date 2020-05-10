(function() {
  'use strict';

  var sisypheApp = angular.module('sisypheApp');
  
  sisypheApp.controller('testerCtrl', ['$q', '$window', '$scope', '$timeout', '$uibModal', 'sisypheFactory', function ($q, $window, $scope, $timeout, $uibModal, sisypheFactory) {

    $scope.console = { text : ''};
    $scope.content = '// Paste your code and click button Check';
    $scope.checking = false;

    // init btn view details : unfolded by default
    $scope.btnViewDetailsIcon = 'unfolded';
    $scope.isCollapsed = false;

    // set changeViewDetails click handler
    $scope.changeViewDetails = function() {
      if ($scope.btnViewDetailsIcon == 'folded') {
        $scope.isCollapsed = false;
        $scope.btnViewDetailsIcon = 'unfolded';
        // view selection
        $timeout(function () {
          var found = $scope.currentFilter.list.find(function(item) {
            return item.clicked === true;
          });
          if (found) {
            ScrollTo.idOrName('row-list-' + found.start, -1);
          }
        }, 0);
      }
      else {
        $scope.isCollapsed = true;
        $scope.btnViewDetailsIcon = 'folded';
      }
    };

    $scope.logoClicked = function () {
      sisypheFactory.aboutHtml.then(function(html){
        var modalInstance = $uibModal.open({
          animation: true,
          template: html.data,
        });
      });
    };

    $scope.filterIconClicked = function () {
      sisypheFactory.helpHtml.then(function(html){
        var modalInstance = $uibModal.open({
          animation: true,
          template: html.data,
        });
      });
    };

    var updateCurrentCode = function (item) {
      if (false === item.clicked || undefined === item.clicked) {
        // set clicked attribute
        for (var i = 0; i < $scope.currentFilter.list.length; i++) {
          $scope.currentFilter.list[i].clicked = false;
        }
        item.clicked = true;
      }
      else {
        // deselect
        item.clicked = false;
      }
    };
    
    // set list click handler
    $scope.listClicked = function (item) {
      updateCurrentCode(item);
      // get line number
      if (item.clicked === true) {
        var lineNumber = item.lineNumber;
        // set scrollbar position (- 5 lines to see previous content)
        var lines = lineNumber - 1 - 5;
        var pos = Math.floor(5 + 20 * lines);
        $scope.editor.scrollTo(null, pos);
      }
    };

    var reviewCode = function(text) {
      var deferred = $q.defer();
      $timeout(function () {
        var out = $window.Module.tdscript(text); 
        deferred.resolve(out);
      }, 100);
      return deferred.promise;
    };

    $scope.checkClicked = function() {
      $scope.checking = true;
      reviewCode($scope.content)
        .then(function(errors){
          var filter = {'list': []};
          //console.log(errors);
          var errorsArray = errors.split('\n');
          for (var i = 0; i < errorsArray.length; i++) {
            var error = errorsArray[i].split(':|:');
            if (error[0].length > 0) {
              filter.list.push(
                {
                  start : error[0],
                  lineNumber : error[1],
                  category : error[2],
                  description : error[3]
                }
              );
            }
          }
          filter.list.sort(function(a, b){
            return a.start - b.start;
          });
          $scope.currentFilter = filter;
          $scope.active = 1;
          $scope.checking = false;
        });
    };

    $scope.codemirrorLoaded = function(_editor){
      $scope.editor = _editor;
    };

    var loadScript = function(url, type, charset, async) {
      var deferred = $q.defer();
      if (type===undefined) type = 'text/javascript';
      if (url) {
          var loaded = false;
          var script = document.querySelector("script[src*='"+url+"']");
          if (!script) {
              var heads = document.getElementsByTagName("head");
              if (heads && heads.length) {
                  var head = heads[0];
                  if (head) {
                      script = document.createElement('script');
                      script.setAttribute('src', url);
                      script.setAttribute('type', type);
                      script.async = async;
                      if (charset) script.setAttribute('charset', charset);
                      head.appendChild(script);
                      loaded = true;
                  }
              }
          }
          deferred.resolve(loaded);
      }
      return deferred.promise;
    };
    
    loadScript('tdscript.js', 'text/javascript', null, true)
      .then(function(scriptLoaded){
        $window.consolePrint = function(text) {
          $scope.console.text += text + '\n';
        };

        if (scriptLoaded) {
          // Init web assembly
          console.log('start loading');
          var loadWindow;
          sisypheFactory.loadHtml.then(function(html){
            loadWindow = $uibModal.open({
              animation: true,
              template: html.data,
              backdrop: 'static',
              keyboard: false
            });
          });

          $window.Module = {
            preRun: [],
            postRun: [],
            print: function(text) {
              if (arguments.length > 1) text = Array.prototype.slice.call(arguments).join(' ');
              //console.log('OUT::' + text);
              $window.consolePrint(text);
            },
            printErr: function(text) {
              if (arguments.length > 1) text = Array.prototype.slice.call(arguments).join(' ');
              console.error('ERR:: ' + text);
              loadWindow.close(0);
            },
            canvas: [],
            setStatus: function(text) {
              if (!$window.Module.setStatus.last) $window.Module.setStatus.last = { text: '' };
              if (text === $window.Module.setStatus.last.text) return;
              $window.Module.setStatus.last.text = text;
              console.log(text);
            },
            totalDependencies: 0,
            monitorRunDependencies: function(left) {
              this.totalDependencies = Math.max(this.totalDependencies, left);
              $window.Module.setStatus(left ? 'Preparing... (' + (this.totalDependencies-left) + '/' + this.totalDependencies + ')' : 'All downloads complete.');
              if (!left) {
                console.log('Stop loading');
                loadWindow.close(0);
              }
            }
          };

          $window.Module.setStatus('Downloading...');
          $window.onerror = function() {
            $window.Module.setStatus('Exception thrown, see JavaScript console');
            $window.Module.setStatus = function(text) {
              if (text) $window.Module.printErr('[post-exception status] ' + text);
            };
          };
        }
     });

  }]);

}());

