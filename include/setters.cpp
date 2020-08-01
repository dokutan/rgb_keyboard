/*
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 3 of the License, or
 * (at your option) any later version.
 * 
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 * 
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston,
 * MA 02110-1301, USA.
 * 
 */

#include "rgb_keyboard.h"

//setter functions

int rgb_keyboard::keyboard::set_ajazzak33_compatibility( bool compatibility ){
	
	_ajazzak33_compatibility = compatibility;
	
	if( compatibility ){
		_keyboard_pid = _keyboard_pid_ajazzak33; // different PID
		_brightness_max = _brightness_max_ajazzak33; // different maximum brightness
	} else{
		_keyboard_pid = _keyboard_pid_others;
		_brightness_max = _brightness_max_others;
	}
	
	return 0;
}

int rgb_keyboard::keyboard::set_mode( mode Mode ){
	_mode[_profile-1] = Mode;
	return 0;
}

int rgb_keyboard::keyboard::set_direction( direction Direction ){
	_direction[_profile-1] = Direction;
	return 0;
}

int rgb_keyboard::keyboard::set_speed( int Speed ){
	if( Speed >= _speed_min && Speed <= _speed_max ){
		_speed[_profile-1] = Speed;
		return 0;
	} else{
		return 1;
	}
}

int rgb_keyboard::keyboard::set_brightness( int Brightness ){
	if( Brightness >= _brightness_min && Brightness <= _brightness_max ){
		_brightness[_profile-1] = Brightness;
		return 0;
	} else{
		return 1;
	}
}

int rgb_keyboard::keyboard::set_color( uint8_t Color_r, uint8_t Color_g, uint8_t Color_b ){
	_color_r[_profile-1] = Color_r;
	_color_g[_profile-1] = Color_g;
	_color_b[_profile-1] = Color_b;
	return 0;
}

int rgb_keyboard::keyboard::set_rainbow( bool Rainbow ){
	_rainbow[_profile-1] = Rainbow;
	return 0;
}

int rgb_keyboard::keyboard::set_variant( mode_variant Variant ){
	_variant[_profile-1] = Variant;
	return 0;
}

int rgb_keyboard::keyboard::keyboard::set_custom_keys( std::string Keys ){
	
	std::string value1 = "";
	std::string value2 = "";
	uint8_t val_r = 0, val_g = 0, val_b = 0;
	std::array<uint8_t, 3> val_rgb;
	std::size_t position1 = 0;
	std::size_t position2 = 0;
	
	//process string
	while( (position1 = Keys.find("=")) != std::string::npos ){
		position2 = Keys.find(";");
		if( position2 != std::string::npos ){
			value1 = Keys.substr(0, position1);
			value2 = Keys.substr(position1+1, position2-position1-1);
			Keys.erase(0, position2+1);
			
			//store values in map
			if( value2.length() == 6 ){
				val_r = stoi( value2.substr(0,2), 0, 16 );
				val_g = stoi( value2.substr(2,2), 0, 16 );
				val_b = stoi( value2.substr(4,2), 0, 16 );
				val_rgb = { val_r, val_g, val_b };
				_key_colors[_profile-1][value1] = val_rgb;
			}
		} else{
			break;
		}
	}
	
	return 0;
}

int rgb_keyboard::keyboard::set_report_rate( report_rate Report_rate ){
	_report_rate[_profile-1] = Report_rate;
	return 0;
}

int rgb_keyboard::keyboard::set_profile( int profile ){
	_profile = profile;
	return 0;
}

int rgb_keyboard::keyboard::set_active_profile( int profile ){
	_active_profile = profile;
	return 0;
}

int rgb_keyboard::keyboard::set_detach_kernel_driver( bool detach_kernel_driver ){
	_detach_kernel_driver = detach_kernel_driver;
	return 0;
}

int rgb_keyboard::keyboard::set_open_interface_0( bool open_interface_0 ){
	_open_interface_0 = open_interface_0;
	return 0;
}
