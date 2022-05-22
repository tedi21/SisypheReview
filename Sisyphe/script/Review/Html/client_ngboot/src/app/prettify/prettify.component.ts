import { Component, Input, Output, OnInit, SimpleChanges, ViewEncapsulation, ElementRef, EventEmitter } from '@angular/core';
import { DomSanitizer } from '@angular/platform-browser';

@Component({
  selector: 'app-prettify',
  templateUrl: './prettify.component.html',
  styleUrls: ['./prettify.component.css'],
  encapsulation: ViewEncapsulation.None
})
export class PrettifyComponent implements OnInit {

  @Input() content: string = '';
  @Output() onErrorClickedHandler: EventEmitter<any> = new EventEmitter();
  html: any;
  initialized: boolean = false;
  constructor(private sanitizer: DomSanitizer,
              private elementRef:ElementRef) {}

  ngOnInit() {
  }

  ngOnChanges(changes: SimpleChanges) {
    if (changes['content'] != undefined) {
      this.html = this.sanitizer.bypassSecurityTrustHtml('<pre class="prettyprint linenums">' + changes['content'].currentValue + '</pre>');
      this.initialized = false;
    }
  }

  onClick(id: number) {
    this.onErrorClickedHandler.emit([id]);
  }

  ngAfterViewChecked (){
    if ((this.onErrorClickedHandler != undefined) && !this.initialized) {
      let nodeList: any[] = this.elementRef.nativeElement.querySelectorAll('[click^="onErrorClicked"]');
      nodeList.forEach(node => {
        node.addEventListener('click', this.onClick.bind(this, +node.getAttribute('click').match(/\d+/g)));
      });
      this.initialized = true;
    }
  } 
}

