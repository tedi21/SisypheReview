import { Component, OnInit, ViewChild } from '@angular/core';
import { ResourcesService } from '../ressources/resources.service';
import { TdscriptService, Table, Record, Derogation } from '../tdscript/tdscript.service';
import { LoadingComponent } from '../loading/loading.component'

declare var consolePrint: (text: string) => void;

@Component({
  selector: 'app-table',
  templateUrl: './table.component.html',
  styleUrls: ['./table.component.css']
})
export class TableComponent implements OnInit {
  public isMenuCollapsed: boolean = true;
  public warningClosed: boolean = false;
  public consoleText: string = '';
  public query: string = '';
  public pageSize: number = 100;
  public derogation: string = '';
  public isEditDerogationCollapsed = true;
  public derogationLoaded: boolean = false;
  public pages : number[] = [];
  public selectedIndex: number = 1;
  public table: Table = {
    rows : [],
    pageCount : 0,
    pageMin : 0,
    pageMax : 0,
    blameError : false
  };
  @ViewChild('loading') loading: LoadingComponent = {} as LoadingComponent;

  constructor(
    private resourcesService : ResourcesService, 
    private tdscriptService : TdscriptService
  ) { }

  ngOnInit(): void {
    consolePrint = (text: string) => {
      this.consoleText += text + '\n';
    };

    // execute the Observable and print the result of each notification
    this.tdscriptService.loadModule((str: string) => {consolePrint(str);}).subscribe({
      next : (num) => { console.log('TESTER :: Loading resource ' + num); },
      complete : () => { console.log('TESTER :: Finished sequence'); this.loadDb(); },
      error : (error) => { console.error('TESTER :: ' + error); this.loading.close(); }
    });
  }

  ngAfterViewChecked() {
    if (!this.loading.isOpened()) {
      this.loading.open();
    }
  } 

  loadDb() : void {
    this.resourcesService.getDb()
    .subscribe({
        next : (bytes) => {
          this.tdscriptService.loadDb(bytes).subscribe(
            {
              next: () => {},
              error: (e) => console.error(e),
              complete: () =>  {
                this.buildView();
              }
            });
        }
      });
  }

  buildView() {
    this.pages = [];
    this.consoleText = '';
    this.tdscriptService.filter(this.query, this.pageSize, this.selectedIndex).subscribe(
      {
        next: (table) => {
          this.table = table; 
          for (let i = this.table.pageMin; i <= this.table.pageMax; i++) {     
            this.pages.push(i);
          }
        },
        error: (e) => console.error(e),
        complete: () =>  {
          if (this.loading.isOpened()) {
            this.loading.close();
          }
        }
      });
  }

  public filterClicked() {
	  this.selectedIndex = 1;
    this.buildView();
  }

	public textDerogationClicked(item : Record) {
		item.derogationWrote = true;
	};

	public cancelDerogationClicked(item : Record) {
		item.derogationWrote = false;
		item.derogation = item.derogationDB; 
	}

	public validDerogationClicked(item : Record) {
    let derogations : Derogation[] = [];
    derogations.push({hash: item.commitHash, line: item.commitLine, order: item.orderOfError, comment: item.derogation});
    this.tdscriptService.addDerogations(derogations);
	  item.derogationWrote = false;
		item.derogationDB = item.derogation;
		this.buildView();
	};

	public editAllClicked() {
    let derogations : Derogation[] = [];
		for (let i = 0; i < this.table.rows.length; i++) {
		  let item = this.table.rows[i];
			if (item.commitHash != '') {
				item.derogation = this.derogation;
				derogations.push({hash: item.commitHash, line: item.commitLine, order: item.orderOfError, comment: item.derogation});
				item.derogationWrote = false;
				item.derogationDB = item.derogation;
			}
		}
		this.tdscriptService.addDerogations(derogations);
		this.buildView();
	};

  public selectClicked(value: number) {
    this.selectedIndex = Math.floor(((this.selectedIndex - 1) * this.pageSize) / value) + 1;
    this.pageSize = value;
    this.buildView();
  }

  public paginationClicked(value: number) {
	  this.selectedIndex = value;
    this.buildView();
  }

  public nextPageClicked() {
	  this.selectedIndex = this.selectedIndex + 1;
    this.buildView();
  }

  public previousPageClicked() {
	  this.selectedIndex = this.selectedIndex - 1;
    this.buildView();
  }

	public newDerogationFile() {
		this.tdscriptService.resetDerogations();
	  this.derogationLoaded = true;
		this.buildView();
	}

	public saveDerogationFile() {
    this.tdscriptService.getDerogations().subscribe(
      {
        next: (text) => {
          //console.log(rows);
          let blob = new Blob([ '\ufeff' + text ], { type : 'text/csv' });
          let downloadLink = document.createElement('a');
          downloadLink.href = window.URL.createObjectURL(blob);
          downloadLink.download = 'derogation.csv';
          downloadLink.click();
        },
        error: (e) => console.error(e)
      });
	}

  public exportView() {
    this.consoleText = '';
    this.tdscriptService.exportFilter(this.query).subscribe(
      {
        next: (text) => {
          //console.log(rows);
          let blob = new Blob([ '\ufeff' + text ], { type : 'text/csv' });
          let downloadLink = document.createElement('a');
          downloadLink.href = window.URL.createObjectURL(blob);
          downloadLink.download = 'errors.csv';
          downloadLink.click();
        },
        error: (e) => console.error(e)
      });
  }

  private readFileAsync(file: File) {
    return new Promise((resolve: (value: string) => void, 
                        reject: (reason: any) => void) => {
      let fileReader = new FileReader();
      fileReader.readAsText(file);
      fileReader.onload = function (e) {
        resolve(e.target?.result as string);
      };
    });
  }

  public loadDerogationFile(event: Event) {
    let files = (<HTMLInputElement>event.target)?.files;
		if (files && files.length > 0) {
		  this.readFileAsync(files[0]).then((fileContent) => {
			  this.tdscriptService.loadDerogations(fileContent);
			  this.derogationLoaded = true;
			  this.buildView();
      });
		}
	};
}
