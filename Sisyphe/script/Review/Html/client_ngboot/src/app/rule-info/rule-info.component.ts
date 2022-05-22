import { Component, ViewEncapsulation, OnInit } from '@angular/core';
import { NgbModal } from '@ng-bootstrap/ng-bootstrap';

@Component({
  selector: 'app-rule-info',
  templateUrl: './rule-info.component.html',
  encapsulation: ViewEncapsulation.None,
  styleUrls: ['./rule-info.component.css']
})
export class RuleInfoComponent implements OnInit {

  constructor(private modalService: NgbModal) {}

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