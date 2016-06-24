(function() {
  'use strict';

  String.prototype.splice = function( idx, rem, s ) {
    return (this.slice(0,idx) + s + this.slice(idx + Math.abs(rem)));
  };
  
  var siCppBuffer = angular.module('siCppBuffer', []);
  
  siCppBuffer.service('cppBuffer', function() {
    this.html = function (buffer) {
      var encoded;
      if (buffer !== undefined) {
        encoded = buffer.replace(/&/g, '&amp;').replace(/<(?!(span)|(\/span))/g, '&lt;');
      }
      return encoded;
    };
    
    this.countLine = function (buffer, pos) {
      var array = buffer.split('\n');
      var line = 0;
      var count = 0;
      while (count <= pos && pos < buffer.length && line < array.length) {
        count += array[line].length + 1;
        line++;
      }
      return line;
    };

    this.getIgnoredLen = function (buffer, index) {
      var len = 0;
      var i = 0;
      while ( i <= (index + len) && i >= 0 && i < buffer.length) {
        var a = buffer.indexOf('<span', i);
        var b = buffer.indexOf('</span>', i);
        var l = 0;
        if (a < b) {
          i = a;
          l = buffer.indexOf('">', i) + 2 - i;
        }
        else {
          i = b;
          l = 7;
        }
        if ( i <= (index + len) && i >= 0 ) {
          len += l;
          i += l;
        }
      }
      return len;
    };
    
    this.expandLeft = function(buffer, start) {
      var newStart = start;
      while (newStart > 0 && buffer[newStart-1] != '\n') newStart--;
      return newStart;
    };
    
    this.expandRight = function(buffer, end) {
      var newEnd = end;
      while (newEnd < (buffer.length-1) && buffer[newEnd+1] != '\n') newEnd++;
      return newEnd;
    };
    
    this.setStyle = function (buffer, start, len, style, title, clickHandler, expandLine) {
      var offset = this.getIgnoredLen(buffer, start);
      var bal1 = '<span class="' + style + '"';
      if (title !== '') {
        bal1 += ' title="' + title + '"';
      }
      if (clickHandler !== '') {
        bal1 += ' ng-click="' + clickHandler + '"';
      }
      bal1 += '>';
      var bal2 = '</span>';
      var begin = start + offset;
      if (expandLine) {
        begin = this.expandLeft(buffer, begin);
      }
      buffer = buffer.splice(begin, 0, bal1);
      offset += bal1.length;
      var end = start + offset + len;
      if (expandLine) {
        end = this.expandRight(buffer, end);
      }
      buffer = buffer.splice(end, 0, bal2);
      //console.log(buffer);
      return buffer;
    };
  });

}());