(function() {
  'use strict';

  var sisypheApp = angular.module('sisypheApp');
  
  sisypheApp.controller('testerCtrl', ['$q', '$window', '$scope', '$timeout', '$uibModal', 'sisypheFactory', function ($q, $window, $scope, $timeout, $uibModal, sisypheFactory) {

    $scope.console = { text : ''};
    var sourceText = '// Paste your source code and click button Check';
    var headerText = '// Paste your header code and click button Check';
    $scope.content0 = sourceText;
    $scope.content1 = sourceText;
    $scope.checking = false;

    $scope.types = ['source', 'header', 'header+source'];
    $scope.type = 'source';

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

    $scope.typeClicked = function (text) {
      $scope.type = text;
      if ($scope.type == 'source' && 
          $scope.content0 == headerText) {
        $scope.content0 = sourceText;
      }
      if (($scope.type == 'header+source' ||
           $scope.type == 'header') && 
          $scope.content0 == sourceText) {
        $scope.content0 = headerText;
      }
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
        //var lines = lineNumber - 1 - 5;
        //var pos = Math.floor(5 + 20 * lines);
        //$scope.editor.scrollTo(null, pos);
        var a1 = {line: lineNumber-1, ch: 0 };
        var a2 = {line: lineNumber-1, ch: Number.MAX_VALUE };
        if (item.icontent == 0)
          $scope.editor0.setSelection(a1, a2);
        else
          $scope.editor1.setSelection(a1, a2);
      }
    };

    var reviewCode = function(vec) {
      var deferred = $q.defer();
      $timeout(function () {
        var out = $window.Module.tdscript(vec); 
        deferred.resolve(out);
      }, 100);
      return deferred.promise;
    };

    $scope.checkClicked = function() {
      $scope.checking = true;
      var vec = new $window.Module.VectorContent();
      if ($scope.type != 'header+source') {
        var nType = 2;
        if ($scope.type == 'header') nType = 1;
        vec.push_back({Text: $scope.content0, Type: nType});
      }
      else {
        vec.push_back({Text: $scope.content0, Type: 1});
        vec.push_back({Text: $scope.content1, Type: 2});
      }
      reviewCode(vec)
        .then(function(errors){
          var filter = {'list': []};
          //console.log(errors);
          var errorsArray = errors.split('\n');
          for (var i = 0; i < errorsArray.length; i++) {
            var error = errorsArray[i].split('\t');
            if (error[0].length > 0) {
              filter.list.push(
                {
                  icontent: error[0],
                  start : error[1],
                  lineNumber : error[2],
                  category : error[3],
                  description : error[4]
                }
              );
            }
          }
          filter.list.sort(function(a, b){
            var d = a.icontent - b.icontent;
            if (d == 0) d = a.start - b.start
            return d;
          });
          $scope.currentFilter = filter;
          $scope.active = 1;
          $scope.checking = false;
        });
    };

    $scope.codemirror0Loaded = function(_editor){
      $scope.editor0 = _editor;
    };

    $scope.codemirror1Loaded = function(_editor){
      $scope.editor1 = _editor;
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

