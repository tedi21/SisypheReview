import { TestBed } from '@angular/core/testing';

import { CodeStyleService } from './code-style.service';

describe('CodeStyleService', () => {
  let service: CodeStyleService;

  beforeEach(() => {
    TestBed.configureTestingModule({});
    service = TestBed.inject(CodeStyleService);
  });

  it('should be created', () => {
    expect(service).toBeTruthy();
  });
});
