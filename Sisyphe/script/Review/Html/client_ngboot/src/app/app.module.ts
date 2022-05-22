import { NgModule } from '@angular/core';
import { BrowserModule } from '@angular/platform-browser';
import { AppRoutingModule } from './app-routing.module';
import { HttpClientModule } from '@angular/common/http';
import { FormsModule } from '@angular/forms'; 
import { CodemirrorModule } from '@ctrl/ngx-codemirror';

import { AppComponent } from './app.component';
import { MainViewComponent } from './main-view/main-view.component';
import { NgbModule } from '@ng-bootstrap/ng-bootstrap';
import { IconsModule } from './icons/icons.module';
import { AboutComponent } from './about/about.component';
import { LoadingComponent } from './loading/loading.component';
import { PrettifyComponent } from './prettify/prettify.component';
import { RuleFilterPipe } from './main-view/rule-filter';
import { RuleInfoComponent } from './rule-info/rule-info.component';
import { TesterComponent } from './tester/tester.component';
import { TableComponent } from './table/table.component';
import { SqlInfoComponent } from './sql-info/sql-info.component';

@NgModule({
  declarations: [
    AppComponent,
    MainViewComponent,
    AboutComponent,
    LoadingComponent,
    PrettifyComponent,
    RuleFilterPipe,
    RuleInfoComponent,
    TesterComponent,
    TableComponent,
    SqlInfoComponent
  ],
  imports: [
    BrowserModule,
    AppRoutingModule,
    HttpClientModule,
    NgbModule,
    IconsModule,
    CodemirrorModule,
    FormsModule
  ],
  providers: [],
  bootstrap: [AppComponent]
})
export class AppModule { }
