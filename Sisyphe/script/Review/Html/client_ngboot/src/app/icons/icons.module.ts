import { NgModule } from '@angular/core';

import { BootstrapIconsModule } from 'ng-bootstrap-icons';
import { 
  PlayCircle, 
  CardList, 
  Search, 
  FileEarmarkTextFill, 
  FilterCircle, 
  QuestionCircleFill, 
  ExclamationCircleFill, 
  InfoCircleFill, 
  ChevronBarUp, 
  ChevronBarDown, 
  Upload,
  Download,
  PencilSquare,
  Trash,
  CheckLg
} from 'ng-bootstrap-icons/icons';

import { FontAwesomeModule, FaIconLibrary } from '@fortawesome/angular-fontawesome';
import { faSpinner } from '@fortawesome/free-solid-svg-icons';

// Select some icons (use an object, not an array)
const icons = {
  PlayCircle,
  CardList,
  Search,
  FileEarmarkTextFill,
  FilterCircle,
  QuestionCircleFill,
  ExclamationCircleFill,
  InfoCircleFill,
  ChevronBarDown,
  ChevronBarUp,
  Upload,
  Download,
  PencilSquare,
  Trash,
  CheckLg
};

@NgModule({
  imports: [
    BootstrapIconsModule.pick(icons),
    FontAwesomeModule
  ],
  exports: [
    BootstrapIconsModule,
    FontAwesomeModule
  ]
})
export class IconsModule {
  constructor(library: FaIconLibrary) {
    library.addIcons(faSpinner);
  }
}
