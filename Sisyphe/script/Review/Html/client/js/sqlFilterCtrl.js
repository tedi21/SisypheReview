(function() {
  'use strict';

  var sisypheApp = angular.module('sisypheApp');
  
  sisypheApp.controller('sqlFilterCtrl', ['$q', '$window', '$location', '$scope', '$timeout', '$uibModal', 'sisypheFactory', function ($q, $window, $location, $scope, $timeout, $uibModal, sisypheFactory) {

    var loadWindow;
	var base;
    var pageSize = 100;
    $scope.console = { text : '' };
    $scope.ResultView = [];
    $scope.pages = [];
    $scope.count = 0;
    $scope.min = 0;
    $scope.max = 0;
    $scope.query = "";
	$scope.deroration = "";
	$scope.pageSize = pageSize;
    $scope.selectedIndex = 1;
	$scope.derogationLoaded = false;
    $scope.isCollapsed = true;
    $scope.btnEditDerogIcon = 'folded';

    var init = function() {
    $timeout(function(){
      base = new $window.Module.VectorByte();
      sisypheFactory.db.query(function(file){
        const bytes = new Uint8Array(file.data);
        for (var i = 0; i < bytes.length; i++) { 
          base.push_back(bytes[i]);
        }
        buildView();
        loadWindow.close(0);
      });
	}, 500);
    }

    $scope.logoClicked = function () {
      sisypheFactory.aboutHtml.then(function(html){
        var modalInstance = $uibModal.open({
          animation: true,
          template: html.data,
        });
      });
    };

    var filter = function(vec, query, limit, offset) {
      var deferred = $q.defer();
      $timeout(function () {
        var out = $window.Module.filter(vec, query, limit, offset); 
        deferred.resolve(out);
      }, 0);
      return deferred.promise;
    };

	var buildView = function() {
      $scope.console.text = '';
      filter(base, $scope.query, $scope.pageSize, $scope.pageSize * ($scope.selectedIndex - 1))
        .then(function(rows){
          //console.log(rows);
          var results = [];
          var pages = [];
          const limit = $scope.pageSize;
          var rowsArray = rows.split('\n');
          for (var i = 1; (i <= limit) && (i < rowsArray.length - 2); i++) {
            var item = rowsArray[i].split('\t');
            if (item.length > 14) {
			  results.push({
				identifier: item[0],				
				path: item[1],
				name: item[2],
				type: item[3],
				ruleNumber: item[4],
				category: item[5],
				description: item[6],
				lineNumber: item[7],
				isNew: item[8],
				commitHash: item[9],
				commitDate: item[10],
				commitAuthor: item[11],
				commitLine: item[12],
				orderOfError: item[13],
				derogation: item[14],
				derogationDB: item[14],
			    derogationWrote : false,
			  });
            }
          }
		  //console.log(rowsArray[i]);
          $scope.count = Math.ceil(rowsArray[i] / $scope.pageSize);
          $scope.min = $scope.selectedIndex - 4;
          if ($scope.min <= 0) {
            $scope.min = 1;
          }
          $scope.max = $scope.min + 8;
          if ($scope.max > $scope.count) {
            $scope.max = $scope.count;
            $scope.min = $scope.max - 8;
            if ($scope.min <= 0) {
              $scope.min = 1;
            }
          }
          for (var i = $scope.min; i <= $scope.max; i++) {     
		    pages.push(i);
	      }
		  $scope.ResultView = results;
		  $scope.pages = pages;
      });
    }

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

        sisypheFactory.loadHtml.then(function(html){
          loadWindow = $uibModal.open({
            animation: true,
            template: html.data,
            backdrop: 'static',
            keyboard: false
          });
        });

        if (scriptLoaded) {
          // Init web assembly
          console.log('start loading');

          $window.Module = {
            preRun: [],
            postRun: [],
            print: function(text) {
              if (arguments.length > 1) text = Array.prototype.slice.call(arguments).join(' ');
              console.log('OUT::' + text);
              $window.consolePrint(text);
            },
            printErr: function(text) {
              if (arguments.length > 1) text = Array.prototype.slice.call(arguments).join(' ');
              console.error('ERR:: ' + text);
              //loadWindow.close(0);
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
                init();
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
		else {
          init();
		}
    });
    
    $scope.filterClicked = function() {
	  $scope.selectedIndex = 1;
      buildView();
    };

    $scope.selectClicked = function(value) {
      $scope.selectedIndex = Math.floor((($scope.selectedIndex - 1) * pageSize) / value) + 1;
	  pageSize = value;
      buildView();
    };

    $scope.paginationClicked = function(value) {
	  $scope.selectedIndex = value;
      buildView();
    };

    $scope.nextPageClicked = function(value) {
	  $scope.selectedIndex = $scope.selectedIndex + 1;
      buildView();
    };

    $scope.previousPageClicked = function(value) {
	  $scope.selectedIndex = $scope.selectedIndex - 1;
      buildView();
    };

    $scope.filterIconClicked = function () {
      sisypheFactory.helpSQL.then(function(html){
        var modalInstance = $uibModal.open({
          animation: true,
          template: html.data,
        });
      });
    };

    $scope.exportView = function () {
      $scope.console.text = '';
      filter(base, $scope.query, 4294967295, 4294967295)
        .then(function(rows){
          //console.log(rows);
          var blob = new Blob([ rows ], { type : 'text/csv' });
          var downloadLink = angular.element('<a></a>');
          downloadLink.attr('href',window.URL.createObjectURL(blob));
          downloadLink.attr('download', 'errors.csv');
          downloadLink[0].click();
      });
    }

	$scope.newDerogationFile = function() {
		$window.Module.resetDerogations();
	    $scope.derogationLoaded = true;
		buildView();
	};

	$scope.saveDerogationFile = function() {
    	filter(base, 'ErrorDerogation<>""', 4294967295, 4294967295)
          .then(function(rows){
          	//console.log(rows);
          	var blob = new Blob([ rows ], { type : 'text/csv' });
          	var downloadLink = angular.element('<a></a>');
          	downloadLink.attr('href',window.URL.createObjectURL(blob));
          	downloadLink.attr('download', 'derogation.csv');
          	downloadLink[0].click();
      	});
	};

    var readFileAsync = function (file) {
        var deferred = $q.defer(),
        fileReader = new FileReader();
        fileReader.readAsText(file);

        fileReader.onload = function (e) {
            deferred.resolve(e.target.result);
        };
        return deferred.promise;
	};

	$scope.loadDerogationFile = function(files) {
  		//console.log(files);
		if (files.length > 0) {
		  readFileAsync(files[0]).then(function (fileContent) {
              //console.log(fileContent);
			  $window.Module.loadDerogations(fileContent);
			  $scope.derogationLoaded = true;
			  buildView();
          });
		}
	};

	$scope.cancelDerogationClicked = function(item) {
		item.derogationWrote = false;
		item.derogation = item.derogationDB; 
	};

	$scope.textDerogationClicked= function(item) {
		item.derogationWrote = true;
	};

	$scope.validDerogationClicked = function(item) {
        var vec = new $window.Module.VectorDerogation();
        vec.push_back({CommitHash: item.commitHash, CommitLine: parseInt(item.commitLine, 10), OrderOfError: parseInt(item.orderOfError, 10), Comment: item.derogation});
		$window.Module.addDerogations(vec);
	    item.derogationWrote = false;
		item.derogationDB = item.derogation;
		buildView();
	};

	$scope.editAllClicked = function() {
		var vec = new $window.Module.VectorDerogation();
		for (var i = 0; i < $scope.ResultView.length; i++) {
		    var item = $scope.ResultView[i];
			if (item.commitHash != '') {
				item.derogation = $scope.deroration;
				vec.push_back({CommitHash: item.commitHash, CommitLine: parseInt(item.commitLine, 10), OrderOfError: parseInt(item.orderOfError, 10), Comment: item.derogation});
				item.derogationWrote = false;
				item.derogationDB = item.derogation;
			}
		}
		$window.Module.addDerogations(vec);
		buildView();
	};

    $scope.changeEditDerog = function() {
      if ($scope.btnEditDerogIcon == 'folded') {
        $scope.isCollapsed = false;
        $scope.btnEditDerogIcon = 'unfolded';
      }
      else {
        $scope.isCollapsed = true;
        $scope.btnEditDerogIcon = 'folded';
      }
    };

  }]);

  sisypheApp.directive('filelistBind', function() {
	  return function( scope, elm, attrs ) {
		elm.bind('change', function( evt ) {
		  scope.$apply(function() {
			scope[ attrs.load ](evt.target.files);
		  });
		});
	  };
	});

}());

