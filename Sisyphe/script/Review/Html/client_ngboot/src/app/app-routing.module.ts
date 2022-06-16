import { NgModule } from '@angular/core';
import { RouterModule, Routes } from '@angular/router';

import { MainViewComponent } from './main-view/main-view.component';
import { TesterComponent } from './tester/tester.component';
import { TableComponent } from './table/table.component';

const routes: Routes = [
  {
    path: 'tester',
    component: TesterComponent,
    resolve: {
    }
  },
  {
    path: 'table',
    component: TableComponent,
    resolve: {
    }
  },
  {
    path: '**',
    component: MainViewComponent,
    resolve: {
    }
  },
];

@NgModule({
  imports: [RouterModule.forRoot(routes)],
  exports: [RouterModule]
})
export class AppRoutingModule { }
