import { Injectable } from '@angular/core';
import { HttpClient } from '@angular/common/http'; 
import { map } from 'rxjs/operators';

export class FileId {
  public status: boolean = false;

  constructor(public id: number, public name: string) {
    this.id = id;
    this.name = name;
  }
}

export class FileContent {
  constructor(
    public id: number, 
    public path: string, 
    public type: string,
    public linesCount: number,
    public errorsCount: number,
    public classesCount: number,
    public enumsCount: number,
    public decMethodsCount: number,
    public defMethodsCount: number,
    public attributesCount: number,
    public macrosCount: number,
    public complexityAvg: number,
    public content: string,
    ) {
    this.id = id;
    this.path = path;
    this.type = type;
    this.linesCount = linesCount;
    this.errorsCount = errorsCount;
    this.classesCount = classesCount;
    this.enumsCount = enumsCount;
    this.decMethodsCount = decMethodsCount;
    this.defMethodsCount = defMethodsCount;
    this.attributesCount = attributesCount;
    this.macrosCount = macrosCount;
    this.complexityAvg = complexityAvg;
    this.content = content;
  }
}

export class FileItem {
  public clicked: boolean = false;

  constructor(
    public lineNumber: number,
    public start: number,
    public length: number,
    public category: string,
    public description: string
  ) {
    this.lineNumber = lineNumber;
    this.start = start;
    this.length = length;
    this.category = category;
    this.description = description;
  }
}

export class FileList {
  constructor(
    public name: string,
    public solved: number,
    public newErrors: number,
    public list: FileItem[]
  ) {
    this.name = name;
    this.solved = solved;
    this.newErrors = newErrors;
    this.list = list;
  }
}

@Injectable({
  providedIn: 'root'
})
export class ResourcesService {

  constructor(private http: HttpClient) { }

  // Return the list of analyzed files
  // No parameter
  // Return List [] of files {id, name}
  public getFiles() {
    return this.http.get<Array<FileId>>("json/files.json").pipe(
      map(
        (data: any) => data.map(
          (file: any) => new FileId(
            file.id,
            file.name
          )
        ) 
      )
    );
  }

  // Return the file content
  // 'fileId' parameter : file identifier
  // return Json structure {id, path, content, type, linesCount, errorsCount, classesCount, enumsCount, decMethodsCount,  defMethodsCount, attributesCount, macrosCount, complexityAvg}
  public getFileContent(id: number) {
    return this.http.get("json/file_" + id + ".json").pipe(
      map(
        (data: any) => new FileContent(
          data.id, 
          data.path, 
          data.type, 
          data.linesCount, 
          data.errorsCount, 
          data.classesCount, 
          data.enumsCount, 
          data.decMethodsCount, 
          data.defMethodsCount, 
          data.attributesCount, 
          data.macrosCount, 
          data.complexityAvg, 
          data.content
        )
      )
    );
  }
  
  // Return the file list filtered by filterName
  // 'fileId' parameter : file identifier
  // 'filterName' parameter : selected filter
  // return Json structure {name, list}
  public getFileList(id: number, filterName: string) {
    return this.http.get("json/" + filterName + "_" + id + ".json").pipe(
      map(
        (data: any) => new FileList(
          data.name, 
          data.solved, 
          data.new, 
          data.list.map(
            (item: any) => new FileItem(
              item.lineNumber, 
              item.start, 
              item.length, 
              item.category, 
              item.description
            )
          )
        )
      )
    );
  }

  // Return the db
  // No parameter
  // Return List [] of bytes
  public getDb() {
    return this.http.get("json/cppbase.db", { responseType: 'arraybuffer' }).pipe(
      map(
        (data: any) => new Uint8Array(data)
      )
    );
  }
}
