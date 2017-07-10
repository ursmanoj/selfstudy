        var mainApp = angular.module("mainApp", ['ngRoute']);
         mainApp.config(['$routeProvider', function($routeProvider) {
            $routeProvider.
            
            when('/view1', {
               templateUrl: 'views/view1.htm',
               controller: 'SimpleController'
            }).
            
            when('/view2', {
               templateUrl: 'views/view2.htm',
               controller: 'SimpleController'
            }).
            
            otherwise({
               redirectTo: '/view1'
            });
         }]);
         
         mainApp.controller('SimpleController', function($scope, $timeout, $location) {
            $scope.customers = [
			{name:'Manoj', city: 'Suwon'},
			{name:'Kanika', city: 'Noida'},
			{name:'Hemanta', city: 'Seoul'}
			];
         
		 $scope.addCustomer = function() {
				$scope.customers.push({name: $scope.newCust.name, city: $scope.newCust.city});
			};
			//timer based page change idea from last detailed answer given at: http://stackoverflow.com/questions/38109964/angularjs-switching-between-pages-after-certain-time-limit
			var goToFarPage = function() {
			    $location.path('/view1');
			    console.log("going to far page");
			  };
			  
			  Main.registerkeyevents($location);
			  
			  //$timeout(goToFarPage, 5000);
			  
			  
			  
			  
		 });