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
        encoded = buffer.replace(/&(?!(lt|amp);)/g, '&amp;').replace(/<(?!(span)|(\/span))/g, '&lt;');
      }
      return '<span>' + encoded + '</span>';
    };
    
    this.purify = function (buffer) {
      var raw;
      if (buffer !== undefined) {
        raw = buffer.replace(/&(?=(lt|amp);)/g, '&amp;').replace(/<(?=(span)|(\/span))/g, '&lt;');
      }
      return raw;
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
    
    this.getHtmlLen = function (buffer, index) {
      var len = 0;
      var i = 0;
      var a = buffer.indexOf('<', i);
      var b = buffer.indexOf('&lt;', i);
      var c = buffer.indexOf('&gt;', i);
      var d = buffer.indexOf('&amp;', i);
      while ( i <= (index + len) && i >= 0 && i < buffer.length) {
        if ((a < i) && (a != -1)){
          a = buffer.indexOf('<', i);
        }
        if ((b < i) && (b != -1)){
          b = buffer.indexOf('&lt;', i);
        }
        if ((c < i) && (c != -1)){
          c = buffer.indexOf('&gt;', i);
        }
        if ((d < i) && (d != -1)){
          d = buffer.indexOf('&amp;', i);
        }
        var l = 0;
        if ((a != -1) && (a < b || b == -1) && (a < c || c == -1) && (a < d || d == -1)) {
          i = a;
          l = buffer.indexOf('>', i) + 1 - i;
          if ((i + 5 < buffer.length) && (buffer.substring(i, i + 5) == '</li>')) {
            i = i + 1;
            l = l - 1; // (\n)
          }
        }
        else if ((b != -1) && (b < c || c == -1) && (b < d || d == -1)) {
          i = b + 1;
          l = 3; // 4 (&lt;) - 1 (<)
        }
        else if ((c != -1) && (c < d || d == -1)) {
          i = c + 1;
          l = 3; // 4 (&gt;) - 1 (<)
        }
        else if (d != -1) {
          i = d + 1;
          l = 4; // 5 (&amp;) - 1 (&)
        }
        else {
          i = -1;
          l = 0;
        }
        if ( i <= (index + len) && i >= 0 ) {
          len += l;
          i += l;
        }
      }
      return len;
    };
    
    this.getTagLen = function(buffer, begin, end) {
      var tag = { 
        index : end,
        length : 0
      };
      var i = buffer.indexOf('<', begin);
      if (i != -1 && i < end) {
        tag.index = i;
        tag.length = buffer.indexOf('>', i) + 1 - i;
      }
      return tag;
    };
    
    this.expandLeft = function(buffer, start) {
      var newStart = start;
      while (newStart > 0 && buffer[newStart-1] != '\n') newStart--;
      return newStart;
    };
    
    this.expandRight = function(buffer, end) {
      var newEnd = end;
      while (newEnd < buffer.length && buffer[newEnd] != '\r' && buffer[newEnd] != '\n') newEnd++;
      return newEnd;
    };
    
    this.setStyle = function (buffer, start, len, style, title, clickHandler, expandLine) {
      var bal1 = '<span class="' + style + '"';
      if (title !== '') {
        bal1 += ' title="' + title + '"';
      }
      if (clickHandler !== '') {
        bal1 += ' ng-click="' + clickHandler + '"';
      }
      bal1 += '>';
      var bal2 = '</span>';
      var begin = start + this.getHtmlLen(buffer, start);
      var end = start + len + this.getHtmlLen(buffer, start + len);
      if (expandLine) {
        begin = this.expandLeft(buffer, begin);
        end = this.expandRight(buffer, end);
      }
      var tag = this.getTagLen(buffer, begin, end);
      while (begin < end) {
        if (begin != tag.index) {
          buffer = buffer.splice(begin, 0, bal1);
          tag.index += bal1.length;
          end += bal1.length;
          buffer = buffer.splice(tag.index, 0, bal2);
          tag.index += bal2.length;
          end += bal2.length;
        }
        begin = tag.index + tag.length;
        tag = this.getTagLen(buffer, begin, end);
      }
      //console.log(buffer);
      return buffer;
    };
    
    this.setStyle2 = function (buffer, nline, style, title, clickHandler, expandLine) {
      var str = '<span'
      var bal = '<span class="' + style + '"';
      if (title !== '') {
        bal += ' title="' + title + '"';
      }
      if (clickHandler !== '') {
        bal += ' ng-click="' + clickHandler + '"';
      }
      if (expandLine) {
        str += ' id="L' + nline + '"';
        bal += ' id="L' + nline + '"';
      }
      else {
        str += ' id="T' + nline + '"';
        bal += ' id="T' + nline + '"';
      }
      str += '>';
      bal += '>';
      return buffer.replace(str, bal);
    };
    
    this.raw = function (html) {
      var decoded;
      if (html !== undefined) {
        decoded = html.replace(/<span[^>]*>/g, '');
        decoded = decoded.replace(/<\/span>/g, '');
        decoded = decoded.replace(/<\/li><li[^>]*>/g, '\n');
        decoded = decoded.replace(/<\/li><\/ol>/g, '');
        decoded = decoded.replace(/<ol[^>]*><li[^>]*>/g, '');
        decoded = decoded.replace(/&lt;/g, '<');
        decoded = decoded.replace(/&gt;/g, '>');
        decoded = decoded.replace(/&amp;/g, '&');
      }
      return decoded;
    };
  });

}());