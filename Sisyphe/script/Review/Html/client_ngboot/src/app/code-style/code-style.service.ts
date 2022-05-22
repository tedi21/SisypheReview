import { Injectable } from '@angular/core';
import { FileItem } from '../ressources/resources.service';

declare global {
  interface String {
    splice( idx: number, rem: number, s: string ) : string;
  }
}

String.prototype.splice = function( idx: number, rem: number, s: string ) {
  let me = String(this);
  return (me.slice(0, idx) + s + me.slice(idx + Math.abs(rem)));
};

@Injectable({
  providedIn: 'root'
})
export class CodeStyleService {
  blank: string = '';
  deselection: string = '';

  constructor() { }

  public setBlank(blank: string) {
    this.blank = blank;
    this.deselection = blank;
  }

  public setErrors(listErrors: FileItem[]) {
    let content = `${this.blank}`;
    for (var i = 0; i < listErrors.length; i++) {
      let item = listErrors[i];
      let nline = item.lineNumber - 1;
      content = this.setStyle2(content, nline, 'code-error', item.description, 'onErrorClicked(' + i + ')', false);
    }
    this.deselection = content;
    return content;
  }

  public setSearch(listSearch: FileItem[]) {
    let content = `${this.blank}`;
    for (var i = listSearch.length-1; i >= 0; i--) {
      content = this.setStyle(content, listSearch[i].start, listSearch[i].length, 'code-search', '', '', false);
    }
    this.deselection = content;
    return content;
  }

  public select(item: FileItem) {
    let content = `${this.deselection}`;
    let nline = item.lineNumber - 1;
    return this.setStyle2(content, nline, 'code-selection', '', '', true);
  }

  public deselect() {
    return this.deselection;
  }

  public search(exp: string) {
    let listSearch: FileItem[] = [];
    let buffer = `${this.blank}`;
    if (exp !== '' && exp !== undefined) {
      var esc_exp = exp.replace(/[-\/\\^$*+?.()|[\]{}]/g, '\\$&');
      var rawBuffer = this.raw(buffer);
      //console.log(rawBuffer);
      var foundIndex = rawBuffer.search(esc_exp);
      var bufferIndex = foundIndex;
      while (foundIndex != -1 && bufferIndex < rawBuffer.length) {
        listSearch.push(new FileItem(
          this.countLine(rawBuffer, bufferIndex), 
          bufferIndex, 
          exp.length, 
          'search '+ exp, 
          rawBuffer.substring(
            this.expandLeft(rawBuffer, bufferIndex), 
            this.expandRight(rawBuffer, bufferIndex+exp.length)
          )
        ));
        //console.log(list[list.length - 1].lineNumber + ' ' + list[list.length - 1].category + ' ' + list[list.length - 1].description);
        bufferIndex += 1;
        foundIndex = rawBuffer.substring(bufferIndex).search(esc_exp);
        bufferIndex += foundIndex;
      }
    }
    return listSearch;
  }

  html(buffer: string) {
    let encoded = '';
    if (buffer !== undefined) {
      encoded = buffer.replace(/&(?!(lt|amp);)/g, '&amp;').replace(/<(?!(span)|(\/span))/g, '&lt;');
    }
    return '<span>' + encoded + '</span>';
  }
  
  purify(buffer: string) {
    let raw = '';
    if (buffer !== undefined) {
      raw = buffer.replace(/&(?=(lt|amp);)/g, '&amp;').replace(/<(?=(span)|(\/span))/g, '&lt;');
    }
    return raw;
  }
  
  countLine(buffer: string, pos: number) {
    let array = buffer.split('\n');
    let line = 0;
    let count = 0;
    while (count <= pos && pos < buffer.length && line < array.length) {
      count += array[line].length + 1;
      line++;
    }
    return line;
  }
  
  getHtmlLen(buffer: string, index: number) {
    let len = 0;
    let i = 0;
    let a = buffer.indexOf('<', i);
    let b = buffer.indexOf('&lt;', i);
    let c = buffer.indexOf('&gt;', i);
    let d = buffer.indexOf('&amp;', i);
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
      let l = 0;
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
  }
  
  getTagLen(buffer: string, begin: number, end: number) {
    let tag = { 
      index : end,
      length : 0
    };
    let i = buffer.indexOf('<', begin);
    if (i != -1 && i < end) {
      tag.index = i;
      tag.length = buffer.indexOf('>', i) + 1 - i;
    }
    return tag;
  }
  
  expandLeft(buffer: string, start: number) {
    let newStart = start;
    while (newStart > 0 && buffer[newStart-1] != '\n') newStart--;
    return newStart;
  }
  
  expandRight(buffer: string, end: number) {
    let newEnd = end;
    while (newEnd < buffer.length && buffer[newEnd] != '\r' && buffer[newEnd] != '\n') newEnd++;
    return newEnd;
  }
  
  setStyle(buffer: string, start: number, len: number, style: string, title: string, clickHandler: string, expandLine: boolean) {
    let bal1 = '<span class="' + style + '"';
    if (title !== '') {
      bal1 += ' title="' + title + '"';
    }
    if (clickHandler !== '') {
      bal1 += ' click="' + clickHandler + '"';
    }
    bal1 += '>';
    let bal2 = '</span>';
    let begin = start + this.getHtmlLen(buffer, start);
    let end = start + len + this.getHtmlLen(buffer, start + len);
    if (expandLine) {
      begin = this.expandLeft(buffer, begin);
      end = this.expandRight(buffer, end);
    }
    let tag = this.getTagLen(buffer, begin, end);
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
  }
  
  setStyle2(buffer: string, nline: number, style: string, title: string, clickHandler: string, expandLine: boolean) {
    let str = '<span'
    let bal = '<span class="' + style + '"';
    if (title !== '') {
      bal += ' title="' + title + '"';
    }
    if (clickHandler !== '') {
      bal += ' click="' + clickHandler + '"';
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
  }
  
  raw(html: string) {
    let decoded = '';
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
  }  
}
