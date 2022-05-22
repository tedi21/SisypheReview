import { Component, ViewEncapsulation, OnInit } from '@angular/core';
import { NgbModal } from '@ng-bootstrap/ng-bootstrap';

@Component({
  selector: 'app-about',
  templateUrl: './about.component.html',
  encapsulation: ViewEncapsulation.None,
  styleUrls: ['./about.component.css']
})
export class AboutComponent implements OnInit {

  constructor(private modalService: NgbModal) {}

  open(content : any) {
    this.modalService.open(content, 
      {
        ariaLabelledBy: 'about',
        modalDialogClass: 'dark-modal'
      });
  }

  ngOnInit(): void {
  }

}
