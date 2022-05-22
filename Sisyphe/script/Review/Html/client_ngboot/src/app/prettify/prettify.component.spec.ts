import { ComponentFixture, TestBed } from '@angular/core/testing';

import { PrettifyComponent } from './prettify.component';

describe('PrettifyComponent', () => {
  let component: PrettifyComponent;
  let fixture: ComponentFixture<PrettifyComponent>;

  beforeEach(async () => {
    await TestBed.configureTestingModule({
      declarations: [ PrettifyComponent ]
    })
    .compileComponents();
  });

  beforeEach(() => {
    fixture = TestBed.createComponent(PrettifyComponent);
    component = fixture.componentInstance;
    fixture.detectChanges();
  });

  it('should create', () => {
    expect(component).toBeTruthy();
  });
});
