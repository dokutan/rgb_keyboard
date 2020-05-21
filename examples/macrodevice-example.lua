--[[

This shows how the key leds can be used to indicate caps lock and num lock

Requires https://github.com/dokutan/macrodevice

]]--


-- macrodevice settings
backend = "xindicator"
settings = { }

-- led colors
led_off = "ffffff"
led_on = "00ff00"

-- Enable custom mode
os.execute( "rgb_keyboard -I --leds custom" )

function input_handler( event )
	
	if event[1] == "0" then -- turn all leds off
		os.execute( "rgb_keyboard -I -K \"Caps_Lock="..led_off..";Num_Lock="..led_off..";\"" )
	end
	
	if event[1] == "1" then -- turn caps lock on
		os.execute( "rgb_keyboard -I -K \"Caps_Lock="..led_on..";Num_Lock="..led_off..";\"" )
	end
	
	if event[1] == "2" then -- turn num lock on
		os.execute( "rgb_keyboard -I -K \"Caps_Lock="..led_off..";Num_Lock="..led_on..";\"" )
	end
	
	if event[1] == "3" then -- turn all leds on
		os.execute( "rgb_keyboard -I -K \"Caps_Lock="..led_on..";Num_Lock="..led_on..";\"" )
	end
	
end
