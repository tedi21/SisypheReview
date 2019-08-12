(function() {
  'use strict';

  var sisypheApp = angular.module('sisypheApp');
    
  sisypheApp.filter('ruleFilter', function(){
    return function (items, obj){
      var filtered = items;
      if (obj.query && obj.enabled)
      {
        var query = obj.query;
        filtered = [];
        var neg = query.startsWith('!');
        if (neg)
        {
          query = query.slice(1);
        }
        var rules = query.split(',');
        angular.forEach(items, function(item) {
          var found = false;
          angular.forEach(rules, function(rule) {
            if(item.category.includes(rule)){
              found = true;
            }
          }, found);
          if (found != neg) {
            this.push(item);
          }
        }, filtered);
      }
      return filtered;
    };
  });
 
}());
