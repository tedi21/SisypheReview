import { Pipe, PipeTransform } from '@angular/core';

interface FilterObject {
  query: string;
  enabled: boolean;
}

@Pipe({
    name: 'ruleFilter',
    pure: false
})
export class RuleFilterPipe implements PipeTransform {
    transform(items: any[], obj: Object): any {
      let filtered = items;
      let filter = obj as FilterObject;
      if (filter.query && filter.enabled)
      {
        let query = filter.query;
        filtered = [];
        let neg = query.startsWith('!');
        if (neg)
        {
          query = query.slice(1);
        }
        let rules = query.split(',');
        items.forEach(function(item) {
          let found = false;
          rules.forEach(function(rule) {
            if(item.category.includes(rule)){
              found = true;
            }
          }, found);
          if (found != neg) {
            filtered.push(item);
          }
        }, filtered);
      }
      return filtered;
    }
}