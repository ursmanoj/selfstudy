var Main = {};

var loc;

console.log("KeyHandling init");

Main.registerkeyevents = function (locParam) {
	
	loc = locParam;

	// add eventListener for keydown
    document.addEventListener('keydown', function(e) {
    	    	
    	switch(e.keyCode){
    	case tvKey.LEFT: //LEFT arrow
        	console.log("LEFT");
    		break;
    	case tvKey.UP: //UP arrow
    		console.log("UP");
    		break;
    	case tvKey.RIGHT: //RIGHT arrow
    		console.log("RIGHT");
    		break;
    	case tvKey.DOWN: //DOWN arrow
    		console.log("DOWN");
    		break;
    	case tvKey.ENTER: //OK button
    		console.log("OK");
    		$('html').injector().get('$location').path("/view2");

    		//AVPlayer.setDisplayArea(0, 0, 1920, 1080);
    		break;
    	case tvKey.RETURN: //RETURN button
    		console.log("RETURN");
    		//AVPlayer.setDisplayArea(0, 0, 960, 540);
    		//loc.path('/view1');
    		$('html').injector().get('$location').path("/view1");
		    console.log("back to near page");
    		break;
    	case tvKey.PLAYPAUSE: // PLAYPAUSE button
    		console.log("PLAYPAUSE");
    		break;
    	case tvKey.PLAY: // PLAY button
    		console.log("PLAY");
    		break;
    	case tvKey.PAUSE: // PAUSE button
    		console.log("PAUSE");
    		break;
    	default:
    		console.log("Key code : " + e.keyCode);
    		break;
    	}
    });
}


