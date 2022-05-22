import { Component, ViewChild, OnInit, ElementRef } from '@angular/core';
import { Router } from '@angular/router';
import { ResourcesService, FileId, FileContent, FileList, FileItem } from '../ressources/resources.service';
import { CodeStyleService } from '../code-style/code-style.service';

@Component({
  selector: 'app-main-view',
  templateUrl: './main-view.component.html',
  styleUrls: ['./main-view.component.css']
})
export class MainViewComponent implements OnInit {

  public searchInput: string = '';
  public filterInput: string = '';
  public isBottomTableCollapsed: boolean = false;
  public isMenuCollapsed: boolean = true;
  public files: FileId[] = [];
  public fileContent: FileContent = {
    id: 0,
    path: '',
    type: '',
    linesCount: 0,
    errorsCount: 0,
    classesCount: 0,
    enumsCount: 0,
    decMethodsCount: 0,
    defMethodsCount: 0,
    attributesCount: 0,
    macrosCount: 0,
    complexityAvg: 0,
    content: ''
  };
  public filters: string[] = ['Errors', 'Search', 'Diff'];
  public fileList: FileList = {
    name: 'Errors',
    solved: 0,
    newErrors: 0,
    list: []
  };
  @ViewChild('codePanel') codePanel: ElementRef = {} as ElementRef;
  @ViewChild('listInfo') listInfo: ElementRef = {} as ElementRef;

  private diff_files: FileId[] = [];
  private all_files: FileId[] = [];
  private search_list: FileItem[] = [];

  constructor(
    private resourcesService : ResourcesService, 
    private codeStyleService : CodeStyleService,
    private router : Router
  ) { }

  ngOnInit(): void {
    this.resourcesService.getFiles()
    .subscribe({
        next : (files) => {
          this.files = files;
          this.all_files = files;
          this.filter_diff_files(files);
          if (this.files.length > 0) {
            this.initFile(this.files[0]);
          }
        }
      });
  }

  filter_diff_files(files: FileId[]) {
    this.diff_files = []
    for (let i = 0; i < files.length; i++) { 
      (function(me: MainViewComponent, file: FileId){   //Closure
        me.resourcesService.getFileList(file.id, 'diff').subscribe({
          next : (fileList) => {
            if (fileList.newErrors > 0) {
              me.diff_files.push(file);
            }
          }
        });
      })(this, files[i]);
    }
  }

  scrollCodeTo(pos: number) {
    this.codePanel.nativeElement.scrollTop = pos;
  }

  scrollListTo(line: number) {
    let el = this.listInfo.nativeElement.querySelector('#row-list-' + line);
    if (el) {
      el.scrollIntoView();
    }
  }

  initFilter(fileId: number, filterName: string){
    if (filterName != 'Search') {
      this.resourcesService.getFileList(fileId, filterName.toLocaleLowerCase())
      .subscribe({
        next : (fileList) => {
          this.fileList = fileList;
          if (fileList.name == 'Errors' || fileList.name == 'Diff') {
            this.fileContent.content = this.codeStyleService.setErrors(this.fileList.list);
          }
        },
        error : (err) => {
          console.log('resource not found : ' + fileId + ', ' + filterName + ', ' + err);
          this.fileList = new FileList(filterName, 0, 0, []);
        }
      });
    }
    else {
      this.fileList = new FileList(filterName, 0, 0, this.search_list);
      this.fileContent.content = this.codeStyleService.setSearch(this.fileList.list);
    }
  }

  initFile(file : FileId) {
    // Enable currrent file
    file.status = true;
    // Fill content
    this.resourcesService.getFileContent(file.id)
    .subscribe({
      next : (fileContent) => {
        this.fileContent = fileContent;
        this.codeStyleService.setBlank(fileContent.content);
        this.scrollCodeTo(0);
        this.initFilter(file.id, this.fileList.name);
      }
    });
  }

  initList(item: FileItem) {
    if (false == item.clicked || undefined == item.clicked) {
      // set clicked attribute
      for (var i = 0; i < this.fileList.list.length; i++) {
        this.fileList.list[i].clicked = false;
      }
      item.clicked = true;
      // set selection
      this.fileContent.content = this.codeStyleService.select(item);
    }
    else {
      // deselect
      item.clicked = false;
      this.fileContent.content = this.codeStyleService.deselect();
    }
  }

  // set files click handler
  public onFileClicked(file : FileId) {
    // Disable old files
    for (let i = 0; i < this.files.length; i++) {
      this.files[i].status = false;
    }
    // Remove search
    this.search_list = [];
    // Update filter
    this.initFile(file);
  }

  // set list click handler
  public onFilterClicked(filterName: string) {
    if ((this.fileList.name == 'Diff' || filterName == 'Diff') && 
        (this.fileList.name != filterName)) {
      // Disable old files
      for (let i = 0; i < this.files.length; i++) {
        this.files[i].status = false;
      }
      // Set files
      if (filterName == 'Diff') {
        this.files = this.diff_files;
      }
      else {
        this.files = this.all_files;
      }
      // Set filter name
      this.fileList = new FileList(filterName, 0, 0, []);
      // Load file data
      if (this.files.length > 0) {
        // Remove search
        this.search_list = [];
        // Update file
        this.initFile(this.files[0]);
      }
    }
    else {
      this.initFilter(this.fileContent.id, filterName);
    }
  }

  // set list click handler
  public onListClicked(item: FileItem) {
    this.initList(item);
    // get line number
    if (item.clicked == true) {
      let lineNumber = item.lineNumber;
      // set scrollbar position (- 5 lines to see previous content)
      let lines = lineNumber - 1 - 5;
      let pos = Math.floor(10 + 18 * lines);
      this.scrollCodeTo(pos);
    }
  }

  // set error click handler
  public onErrorClicked(index: number) {
    let item = this.fileList.list[index];
    this.initList(item);
    if (item.clicked == true) {
      this.scrollListTo(item.start);
    }
  }

  // set search click handler
  public onSearchClicked(exp: string) {
    // Set search
    this.search_list = this.codeStyleService.search(exp);
    // Update filter
    this.initFilter(this.fileContent.id, 'Search');
    // Open view
    if (exp !== '' && exp !== undefined) {
      this.isBottomTableCollapsed = false;
    }
  }

  // set list view click handler
  public onListView() {
    if (this.isBottomTableCollapsed) {
      this.isBottomTableCollapsed = false;
      let found = this.fileList.list.find(function(item: FileItem) {
        return item.clicked === true;
      });
      if (found) {
        this.scrollListTo(found.start);
      }
    }
    else {
      this.isBottomTableCollapsed = true;
    }
  }

  public onTesterClicked() {
    this.router.navigateByUrl('/tester');
  };

  public onTableClicked() {
    this.router.navigateByUrl('/table');
  };
  
}
