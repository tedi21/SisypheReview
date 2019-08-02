(function() {
  'use strict';

  var siModalMovable = angular.module('siModalMovable', []);
  siModalMovable.directive('modalMovable', ['$document',
      function($document) {
          return {
              restrict: 'AC',
              link: function(scope, iElement, iAttrs) {
                  var startX = 0,
                      startY = 0,
                      x = 0,
                      y = 0;

                  var dialogWrapper = iElement.parent();
                  var dialogHeader = angular.element(iElement[0].getElementsByClassName('modal-header'));

                  dialogWrapper.css({
                      position: 'relative'
                  });

                  dialogHeader.on('mousedown', function(event) {
                      // Prevent default dragging of selected content
                      event.preventDefault();
                      startX = event.pageX - x;
                      startY = event.pageY - y;
                      $document.on('mousemove', mousemove);
                      $document.on('mouseup', mouseup);
                  });

                  function mousemove(event) {
                      y = event.pageY - startY;
                      x = event.pageX - startX;
                      dialogWrapper.css({
                          top: y + 'px',
                          left: x + 'px'
                      });
                  }

                  function mouseup() {
                      $document.unbind('mousemove', mousemove);
                      $document.unbind('mouseup', mouseup);
                  }
              }
          };
      }
  ]);
}());