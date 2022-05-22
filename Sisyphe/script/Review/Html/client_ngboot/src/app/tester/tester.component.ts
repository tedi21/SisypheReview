import { Component, OnInit, ViewChild, ElementRef } from '@angular/core';
import { FileList, FileItem } from '../ressources/resources.service';
import { Editor, Position } from 'codemirror';
import { CodemirrorComponent } from '@ctrl/ngx-codemirror'
import { TdscriptService, Source } from '../tdscript/tdscript.service';
import { LoadingComponent } from '../loading/loading.component'

declare var consolePrint: (text: string) => void;

@Component({
  selector: 'app-tester',
  templateUrl: './tester.component.html',
  styleUrls: ['./tester.component.css']
})
export class TesterComponent implements OnInit {

  private sourceText = '// Paste your source code and click button Check';
  private headerText = '// Paste your header code and click button Check';
  private macroExample = 'function Macro(fileData, errorList)\n  success = true;\n  errorMatch = new Match();\n  /* Exemple : Recherche du mot DEBUG */\n  content = fileData.SourceCode;\n  start = 0;\n  end = #content;\n  while content.Search(start, end, "\\<DEBUG\\>", errorMatch, start) do\n    success = false;\n    line = GetLine(fileData, errorMatch.StringPos)+1;\n    description = "Le mot DEBUG est utilisé";\n    /* Décommenter pour ajouter l\'erreur : AppendError(fileData, errorList, 1000, "Macro [R1000]", description, line);*/\n  endwhile\n  /*return*/ success;\nendfunction';
  public content0 = this.sourceText;
  public content1 = this.sourceText;
  public filterInput: string = '';
  public isBottomTableCollapsed: boolean = false;
  public fileList: FileList = {
    name: 'Errors',
    solved: 0,
    newErrors: 0,
    list: []
  };
  public types = ['source', 'header', 'header+source'];
  public type = 'source';
  public activeTab = 1;
  public consoleText = '';
  public macroText = this.macroExample;
  public keyword = '';
  public preprocessors = '';
  public rules = '';
  public filename = 'file0';
  public checking = false;
  @ViewChild('listInfo') listInfo: ElementRef = {} as ElementRef;
  @ViewChild('codemirror0') codeMirror0: CodemirrorComponent = {} as CodemirrorComponent;
  @ViewChild('codemirror1') codeMirror1: CodemirrorComponent = {} as CodemirrorComponent;
  @ViewChild('loading') loading: LoadingComponent = {} as LoadingComponent;
  
  constructor(private tdscriptService : TdscriptService) { }

  ngOnInit() {

    consolePrint = (text: string) => {
      this.consoleText += text + '\n';
    };

    // execute the Observable and print the result of each notification
    this.tdscriptService.loadModule((str: string) => {consolePrint(str);}).subscribe({
      next : (num) => { console.log('TESTER :: Loading resource ' + num); },
      complete : () => { console.log('TESTER :: Finished sequence'); this.loading.close(); },
      error : (error) => { console.error('TESTER :: ' + error); this.loading.close(); }
    });
  }

  ngAfterViewChecked (){
    if (!this.loading.isOpened()) {
      this.loading.open();
    }
  } 

  scrollListTo(line: number) {
    let el = this.listInfo.nativeElement.querySelector('#row-list-' + line);
    if (el) {
      el.scrollIntoView();
    }
  }

  initList(item: FileItem) {
    if (false == item.clicked || undefined == item.clicked) {
      // set clicked attribute
      for (var i = 0; i < this.fileList.list.length; i++) {
        this.fileList.list[i].clicked = false;
      }
      item.clicked = true;
    }
    else {
      // deselect
      item.clicked = false;
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

  getEditor(cm : CodemirrorComponent) : Editor | undefined {
    return cm.codeMirror;
  }

  // set list click handler
  public onListClicked(item: FileItem) {
    this.initList(item);
    // get line number
    if (item.clicked == true) {
      let lineNumber = item.lineNumber;
      let a1: Position = {line: lineNumber-1, ch: 0 };
      let a2: Position = {line: lineNumber-1, ch: Number.MAX_VALUE };
      if (item.start == 0) {
        this.getEditor(this.codeMirror0)?.setSelection(a1, a2);
      }
      else {
        this.getEditor(this.codeMirror1)?.setSelection(a1, a2);
      }
    }
  }

  public onTypeClicked(typeName: string) {
    this.type = typeName;
    if (this.type == 'source' && 
        this.content0 == this.headerText) {
      this.content0 = this.sourceText;
    }
    if ((this.type == 'header+source' ||
         this.type == 'header') && 
         this.content0 == this.sourceText) {
      this.content0 = this.headerText;
    }
  }

  public onCheckClicked() {
    let sourceList = [];
    if (this.type == 'header+source') {
      sourceList.push(new Source(this.content0, 1, this.filename + '.h'));
      sourceList.push(new Source(this.content1, 2, this.filename + '.cpp'));
    }
    else if (this.type == 'header') {
      sourceList.push(new Source(this.content0, 1, this.filename + '.h'));
    }
    else if (this.type == 'source') {
      sourceList.push(new Source(this.content0, 2, this.filename + '.cpp'));
    }
    else {
      console.warn('Bad type : ' + this.type);
    }
    this.checking = true;
    this.fileList.list = [];

    let options = this.macroText + '\n';
    if (this.rules != '') {
      this.rules.split(';').forEach((rule: string) => {
        var n = Math.floor(Number(rule));
        if (n !== Infinity && String(n) === rule && n >= 0) {
          options += 'constant:ENABLED_RULES.Rule' + rule + ' = false;' + '\n';
        }
      });
    }
    if (this.keyword != '') {
      options += 'constant:SETTINGS.IgnoreErrorKeyword = "' + this.keyword + '";' + '\n';
    }
    if (this.preprocessors != '') {
      options += 'constant:SETTINGS.IgnorePreprocessorList = "' + this.preprocessors + '".Split(";");' + '\n';
    }

    this.tdscriptService.reviewCode(sourceList, options).subscribe(
      {
        next: (error: FileItem) => {this.fileList.list.push(error);},
        error: (e) => console.error(e),
        complete: () =>  {
          this.fileList.list.sort(function(a, b){
            var d = a.start - b.start;
            if (d == 0) d = a.length - b.length
            return d;
          });
          this.activeTab = 1;
          this.checking = false;
        }
      });
  }


}

