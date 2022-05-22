import { ComponentFixture, TestBed } from '@angular/core/testing';

import { SqlInfoComponent } from './sql-info.component';

describe('SqlInfoComponent', () => {
  let component: SqlInfoComponent;
  let fixture: ComponentFixture<SqlInfoComponent>;

  beforeEach(async () => {
    await TestBed.configureTestingModule({
      declarations: [ SqlInfoComponent ]
    })
    .compileComponents();
  });

  beforeEach(() => {
    fixture = TestBed.createComponent(SqlInfoComponent);
    component = fixture.componentInstance;
    fixture.detectChanges();
  });

  it('should create', () => {
    expect(component).toBeTruthy();
  });
});
