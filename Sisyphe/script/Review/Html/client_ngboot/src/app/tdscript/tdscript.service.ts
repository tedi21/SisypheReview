import { Injectable } from '@angular/core';
import { Observer, Observable } from 'rxjs'
import { FileItem } from '../ressources/resources.service';

declare var createModule: (options: any) => Promise<any>;

export class Source {
  constructor(
    public content: string,
    public type: number,
    public name: string,
  ) {
    this.content = content;
    this.type = type;
    this.name = name;
  }
}

export class Record {
  constructor(
    public identifier: number,				
    public path: string,
    public name: string,
    public type: number,
    public ruleNumber: number,
    public category: string,
    public description: string,
    public lineNumber: number,
    public isNew: number,
    public commitHash: string,
    public commitDate: string,
    public commitAuthor: string,
    public commitLine: number,
    public orderOfError: number,
    public derogation: string,
    public derogationDB: string,
    public derogationWrote : boolean,
  ) {
    this.identifier = identifier;				
    this.path = path;
    this.name = name;
    this.type = type;
    this.ruleNumber = ruleNumber;
    this.category = category;
    this.description = description;
    this.lineNumber = lineNumber;
    this.isNew = isNew;
    this.commitHash = commitHash;
    this.commitDate = commitDate;
    this.commitAuthor = commitAuthor;
    this.commitLine = commitLine;
    this.orderOfError = orderOfError;
    this.derogation = derogation;
    this.derogationDB = derogationDB;
    this.derogationWrote = derogationWrote;  
  }
}

export class Table {
  constructor(
    public rows : Record[],
    public pageCount : number,
    public pageMin : number,
    public pageMax : number,
    public blameError : boolean
  ) {
    this.rows = rows;
    this.pageCount = pageCount;
    this.pageMin = pageMin;
    this.pageMax = pageMax;
    this.blameError = blameError;
  }
}

export class Derogation {
  constructor(
    public hash : string,
    public line : number,
    public order : number,
    public comment : string
  ) {
    this.hash = hash;
    this.line = line;
    this.order = order;
    this.comment = comment;
  } 
}

@Injectable({
  providedIn: 'root'
})
export class TdscriptService {

  private Module: any;

  constructor() { 
  }

  public loadDb(bytes: Uint8Array)
  {
    return new Observable((observer: Observer<FileItem>) => {
      let base = new this.Module.VectorByte();
      bytes.forEach(b => {
        base.push_back(b);
      });
      this.Module.loadDb(base);
      observer.complete();
      return {
        unsubscribe() { }
      };
    });
  }

  public filter(query: string, pageSize: number, pageIndex: number)
  {
    return new Observable((observer: Observer<Table>) => {
      let out = this.Module.filter(query, pageSize, pageSize * (pageIndex - 1));
      //console.log(out);
      let rows : Record[] = [];
      let rowsArray = out.split('\n');
      for (var i = 1; (i <= pageSize) && (i < rowsArray.length - 2); i++) {
        let item = rowsArray[i].split('\t');
        if (item.length > 14) {
            rows.push(new Record(
              parseInt(item[0], 10),
              item[1],
              item[2],
              parseInt(item[3], 10),
              parseInt(item[4], 10),
              item[5],
              item[6],
              parseInt(item[7], 10),
              parseInt(item[8], 10),
              item[9],
              item[10],
              item[11],
              parseInt(item[12], 10),
              parseInt(item[13], 10),
              item[14],
              item[14],
              false
            ));
        }
      }
      let table = new Table(rows, 0, 0, 0, true);
      let counts = rowsArray[i].split('\t');
      if (counts.length >= 1) {
        table.pageCount = Math.ceil(counts[0] / pageSize);
        table.pageMin = pageIndex - 4;
        if (table.pageMin <= 0) {
          table.pageMin = 1;
        }
        table.pageMax = table.pageMin + 8;
        if (table.pageMax > table.pageCount) {
          table.pageMax = table.pageCount;
          table.pageMin = table.pageMax - 8;
          if (table.pageMin <= 0) {
            table.pageMin = 1;
          }
        }
        table.blameError = (counts[1] > 0);
      }
      observer.next(table);
      observer.complete();
      return {
        unsubscribe() { }
      };
    });
  }

  public getDerogations() {
    return new Observable((observer: Observer<string>) => {
      let out = this.Module.filter('ErrorDerogation<>""', 4294967295, 4294967295);
      observer.next(out);
      observer.complete();
      return {
        unsubscribe() { }
      };
    });
  }

  public exportFilter(query: string) {
    return new Observable((observer: Observer<string>) => {
      let out = this.Module.filter(query, 4294967295, 4294967295);
      observer.next(out);
      observer.complete();
      return {
        unsubscribe() { }
      };
    });
  }

  public resetDerogations() {
    this.Module.resetDerogations();
  }

  public loadDerogations(content: string) {
    this.Module.loadDerogations(content);
  }

  public addDerogations(derogations: Derogation[]) {
    let vec = new this.Module.VectorDerogation();
    derogations.forEach(item => {
      let derog = new this.Module.Derogation();
      derog.CommitHash = item.hash;
      derog.CommitLine = item.line;
      derog.OrderOfError = item.order;
      derog.Comment = item.comment;
      vec.push_back(derog);
    })
    this.Module.addDerogations(vec);
  }

  public reviewCode(sourceList: Source[], macro: string)
  {
    return new Observable((observer: Observer<FileItem>) => {
      let vec = new this.Module.VectorContent();
      sourceList.forEach(item => {
        let cont = new this.Module.Content();
        cont.Type = item.type;
        cont.Text = item.content; 
        cont.Name = item.name;
        vec.push_back(cont);
      });
      setTimeout(() => {
        let errors = this.Module.tdscript(vec, macro);
        let errorsArray = errors.split('\n');
        errorsArray.forEach((error: string) => {
          let itemsArray = error.split('\t');
          if (itemsArray[0].length > 0) {
            let fi = new FileItem(
              parseInt(itemsArray[2]), 
              parseInt(itemsArray[0]),
              parseInt(itemsArray[1]),
              itemsArray[3],
              itemsArray[4]);
            observer.next(fi);
          }
        });
        observer.complete();
      }, 100);
      return {
        unsubscribe() { }
      };
    });
  }

  private loadScript(path: string) {
    return new Promise((resolve: (value: boolean) => void, 
                        reject: (reason: any) => void) => {
      //load script
      let loaded = false;
      let script = document.querySelector("script[src*='"+path+"']");
      if (!script) {
        let script = document.createElement('script');
        script.type = 'text/javascript';
        script.src = path;
        script.async = true;
        script.onload = () => {
          loaded = true;
          resolve(loaded);
        };
        script.onerror = (error: any) => reject(error);
        document.getElementsByTagName('head')[0].appendChild(script);
      }
      else {
        resolve(loaded);
      }
    });
  }

  public loadModule(printer: (str: string) => void) {
    return new Observable((observer: Observer<number>) => {

      this.loadScript('assets/js/tdscript.js')
      .then((scriptLoaded: boolean) => {
        if (scriptLoaded) {
          let options = {
            print: function(text: string) {
              if (arguments.length > 1) text = Array.prototype.slice.call(arguments).join(' ');
              printer(text);
            },
            printErr: function(text: string) {
              if (arguments.length > 1) text = Array.prototype.slice.call(arguments).join(' ');
              console.error('ERR:: ' + text);
            },
            monitorRunDependencies: function(left: number) {
              observer.next(left);
            }
          };

          createModule(options)
          .then((module: any) => {
            this.Module = module;
            observer.complete();
          })
          .catch((error: any) => {
            observer.error(error);
          });
        }
        else {
          observer.complete();
        }
      })
      .catch((error: any) => {
        observer.error(error);
      });
      
      return {
        unsubscribe() { }
      };
    });
  }

}
