(function() {
  'use strict';

  var siPrettify = angular.module('siPrettify', []);

  siPrettify.directive('prettify', ['$compile', function ($compile) {
    return {
      restrict: 'E',
      scope: {
        errorClick : '&'
      },
      link: function ( scope, element, attrs ) {
        attrs.$observe( 'content', function ( content ) {
          if ( angular.isDefined(content) ) {
            var angularElt = $compile('<pre class="prettyprint linenums">' + content + '</pre>')( scope );
            element.html('');
            element.append(angularElt);
          }
        });
      }
    };
  }]);

}());