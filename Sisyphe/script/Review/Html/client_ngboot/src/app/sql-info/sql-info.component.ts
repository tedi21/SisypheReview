import { Component, ViewEncapsulation, OnInit } from '@angular/core';
import { NgbModal } from '@ng-bootstrap/ng-bootstrap';

@Component({
  selector: 'app-sql-info',
  templateUrl: './sql-info.component.html',
  encapsulation: ViewEncapsulation.None,
  styleUrls: ['./sql-info.component.css']
})
export class SqlInfoComponent implements OnInit {

  constructor(private modalService: NgbModal) { }

  open(content : any) {
    this.modalService.open(content, 
      {
        ariaLabelledBy: 'help',
        size: 'lg',
        modalDialogClass: 'dark-modal'
      });
    }

  ngOnInit(): void {
  }

}
