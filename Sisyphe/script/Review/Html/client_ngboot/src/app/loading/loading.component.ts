import { Component, ViewEncapsulation, OnInit, ViewChild, TemplateRef } from '@angular/core';
import { NgbModal, NgbModalRef } from '@ng-bootstrap/ng-bootstrap';

@Component({
  selector: 'app-loading',
  templateUrl: './loading.component.html',
  encapsulation: ViewEncapsulation.None,
  styleUrls: ['./loading.component.css']
})
export class LoadingComponent implements OnInit {
  @ViewChild('content') content: TemplateRef<any> = {} as TemplateRef<any>;
  private modal? : NgbModalRef;

  constructor(private modalService: NgbModal) {}

  public open() {
    this.modal = this.modalService.open(this.content, 
      {
        ariaLabelledBy: 'loading',
        modalDialogClass: 'dark-modal',
        backdrop: 'static'
      });
  }

  public close() {
    this.modal?.close();
  }

  public isOpened() {
    return this.modal? true: false;
  }

  ngOnInit(): void {
  }

}
