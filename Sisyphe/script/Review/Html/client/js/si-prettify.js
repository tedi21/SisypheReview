(function() {
  'use strict';

  var siPrettify = angular.module('siPrettify', ['siCppBuffer']);

  siPrettify.directive('prettify', ['$compile', 'cppBuffer', function ($compile, cppBuffer) {
    return {
      restrict: 'E',
      scope: true,
      link: function ( scope, element, attrs ) {
        attrs.$observe( 'content', function ( content ) {
          if ( angular.isDefined(content) ) {
            var prettified = prettyPrintOne(cppBuffer.html(content), 'cpp', true);
            var angularElt = $compile('<pre class="prettyprint linenums">' + prettified + '</pre>')( scope );
            element.html('');
            element.append(angularElt);
          }
        });
      }
    };
  }]);

}());