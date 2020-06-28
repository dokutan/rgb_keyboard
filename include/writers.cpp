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

//writer functions (apply changes to keyboard)

int rgb_keyboard::keyboard::write_brightness(){
		
	//vars
	int res = 0;
	
	//prepare data packet
	uint8_t data_settings[64];
	std::copy(std::begin(_data_settings), std::end(_data_settings), std::begin(data_settings));
	
	if( _profile == 1 ){
		data_settings[1] = 0x08 + _brightness[_profile-1];
		data_settings[8] = _brightness[_profile-1];
		data_settings[5] = 0x01;
	} else if( _profile == 2 ){
		data_settings[1] = 0x32 + _brightness[_profile-1];
		data_settings[8] = _brightness[_profile-1];
		data_settings[5] = 0x2b;
	} else if( _profile == 3 ){
		data_settings[1] = 0x5c + _brightness[_profile-1];
		data_settings[8] = _brightness[_profile-1];
		data_settings[5] = 0x55;
	} else{
		throw std::invalid_argument("Invalid profile number");
	}
	
	//send data
	res += _write_data( _data_start, 64 );
	res += _write_data( data_settings, 64 );
	res += _write_data( _data_end, 64 );
	
	return res;
}

int rgb_keyboard::keyboard::write_speed(){
		
	//vars
	int res = 0;
	
	//prepare data packet
	uint8_t data_settings[64];
	std::copy(std::begin(_data_settings), std::end(_data_settings), std::begin(data_settings));
	
	if( _profile == 1 ){
		data_settings[1] = 0x0d - _speed[_profile-1];
		data_settings[8] = 0x04 - _speed[_profile-1];
		data_settings[5] = 0x02;
	} else if( _profile == 2 ){
		data_settings[1] = 0x37 - _speed[_profile-1];
		data_settings[8] = 0x04 - _speed[_profile-1];
		data_settings[5] = 0x2c;
	} else if( _profile == 3 ){
		data_settings[1] = 0x61 - _speed[_profile-1];
		data_settings[8] = 0x04 - _speed[_profile-1];
		data_settings[5] = 0x56;
	} else{
		throw std::invalid_argument("Invalid profile number");
	}
	
	//send data
	res += _write_data( _data_start, 64 );
	res += _write_data( data_settings, 64 );
	res += _write_data( _data_end, 64 );
	
	return res;
}

int rgb_keyboard::keyboard::write_direction(){
		
	//vars
	int res = 0;
	
	//prepare data packet
	uint8_t data_settings[64];
	std::copy(std::begin(_data_settings), std::end(_data_settings), std::begin(data_settings));
	
	if( _profile == 1 ){
		switch( _direction[_profile-1] ){
			case d_left:
				data_settings[1] = 0x09;
				data_settings[2] = 0x01;
				data_settings[5] = 0x03;
				data_settings[8] = 0xff;
				break;
			case d_right:
				data_settings[1] = 0x0a;
				data_settings[2] = 0x00;
				data_settings[5] = 0x03;
				data_settings[8] = 0x00;
			default:
				break;
		}
	} else if( _profile == 2 ){
		switch( _direction[_profile-1] ){
			case d_left:
				data_settings[1] = 0x33;
				data_settings[2] = 0x01;
				data_settings[5] = 0x2d;
				data_settings[8] = 0xff;
				break;
			case d_right:
				data_settings[1] = 0x34;
				data_settings[2] = 0x00;
				data_settings[5] = 0x2d;
				data_settings[8] = 0x00;
			default:
				break;
		}
	} else if( _profile == 3 ){
		switch( _direction[_profile-1] ){
			case d_left:
				data_settings[1] = 0x5d;
				data_settings[2] = 0x01;
				data_settings[5] = 0x57;
				data_settings[8] = 0xff;
				break;
			case d_right:
				data_settings[1] = 0x5e;
				data_settings[2] = 0x00;
				data_settings[5] = 0x57;
				data_settings[8] = 0x00;
			default:
				break;
		}
	} else{
		throw std::invalid_argument("Invalid profile number");
	}
	
	//send data
	res += _write_data( _data_start, 64 );
	res += _write_data( data_settings, 64 );
	res += _write_data( _data_end, 64 );
	
	return res;
}

int rgb_keyboard::keyboard::write_mode(){
		
	//vars
	int res = 0;
	
	//prepare data packet
	uint8_t data_settings[64];
	std::copy(std::begin(_data_settings), std::end(_data_settings), std::begin(data_settings));
	
	if( _profile == 1 ){
		switch( _mode[_profile-1] ){
			case m_horizontal_wave://ok
				data_settings[1] = 0x08;
				data_settings[8] = 0x01;
				break;
			case m_pulse://ok
				data_settings[1] = 0x09;
				data_settings[8] = 0x02;
				break;
			case m_hurricane://ok
				data_settings[1] = 0x0a;
				data_settings[8] = 0x03;
				break;
			case m_breathing_color://ok
				data_settings[1] = 0x0b;
				data_settings[8] = 0x04;
				break;
			case m_breathing://ok
				data_settings[1] = 0x0c;
				data_settings[8] = 0x05;
				break;
			case m_fixed://ok
				data_settings[1] = 0x0d;
				data_settings[8] = 0x06;
				break;
			case m_reactive_single://ok
				data_settings[1] = 0x0e;
				data_settings[8] = 0x07;
				break;
			case m_reactive_ripple://ok
				data_settings[1] = 0x0f;
				data_settings[8] = 0x08;
				break;
			case m_reactive_horizontal://ok
				data_settings[1] = 0x10;
				data_settings[8] = 0x09;
				break;
			case m_waterfall://ok
				data_settings[1] = 0x11;
				data_settings[8] = 0x0a;
				break;
			case m_swirl://ok
				data_settings[1] = 0x12;
				data_settings[8] = 0x0b;
				break;
			case m_vertical_wave://ok
				data_settings[1] = 0x13;
				data_settings[8] = 0x0c;
				break;
			case m_sine://ok
				data_settings[1] = 0x14;
				data_settings[8] = 0x0d;
				break;
			case m_vortex://ok
				data_settings[1] = 0x15;
				data_settings[8] = 0x0e;
				break;
			case m_rain://ok
				data_settings[1] = 0x16;
				data_settings[8] = 0x0f;
				break;
			case m_diagonal_wave://ok
				data_settings[1] = 0x17;
				data_settings[8] = 0x10;
				break;
			case m_reactive_color://ok
				data_settings[1] = 0x18;
				data_settings[8] = 0x11;
				break;
			case m_ripple://ok
				data_settings[1] = 0x19;
				data_settings[8] = 0x12;
				break;
			case m_custom://ok
				data_settings[1] = 0x1b;
				data_settings[8] = 0x14;
				break;
			case m_off://ok
				data_settings[1] = 0x1a;
				data_settings[8] = 0x13;
				break;
			default:
				break;
		}
	} else if( _profile == 2 ){
		switch( _mode[_profile-1] ){
			case m_horizontal_wave://ok
				data_settings[1] = 0x32;
				data_settings[5] = 0x2a;
				data_settings[8] = 0x01;
				break;
			case m_pulse://ok
				data_settings[1] = 0x33;
				data_settings[5] = 0x2a;
				data_settings[8] = 0x02;
				break;
			case m_hurricane://ok
				data_settings[1] = 0x34;
				data_settings[5] = 0x2a;
				data_settings[8] = 0x03;
				break;
			case m_breathing_color://ok
				data_settings[1] = 0x35;
				data_settings[5] = 0x2a;
				data_settings[8] = 0x04;
				break;
			case m_breathing://ok
				data_settings[1] = 0x36;
				data_settings[5] = 0x2a;
				data_settings[8] = 0x05;
				break;
			case m_fixed://ok ---
				data_settings[1] = 0x37;
				data_settings[5] = 0x2a;
				data_settings[8] = 0x06;
				break;
			case m_reactive_single://ok
				data_settings[1] = 0x38;
				data_settings[5] = 0x2a;
				data_settings[8] = 0x07;
				break;
			case m_reactive_ripple://ok
				data_settings[1] = 0x39;
				data_settings[5] = 0x2a;
				data_settings[8] = 0x08;
				break;
			case m_reactive_horizontal://ok
				data_settings[1] = 0x3a;
				data_settings[5] = 0x2a;
				data_settings[8] = 0x09;
				break;
			case m_waterfall://ok
				data_settings[1] = 0x3b;
				data_settings[5] = 0x2a;
				data_settings[8] = 0x0a;
				break;
			case m_swirl://ok
				data_settings[1] = 0x3c;
				data_settings[5] = 0x2a;
				data_settings[8] = 0x0b;
				break;
			case m_vertical_wave://ok
				data_settings[1] = 0x3d;
				data_settings[5] = 0x2a;
				data_settings[8] = 0x0c;
				break;
			case m_sine://ok
				data_settings[1] = 0x3e;
				data_settings[5] = 0x2a;
				data_settings[8] = 0x0d;
				break;
			case m_vortex://ok
				data_settings[1] = 0x3f;
				data_settings[5] = 0x2a;
				data_settings[8] = 0x0e;
				break;
			case m_rain://ok
				data_settings[1] = 0x40;
				data_settings[5] = 0x2a;
				data_settings[8] = 0x0f;
				break;
			case m_diagonal_wave://ok
				data_settings[1] = 0x41;
				data_settings[5] = 0x2a;
				data_settings[8] = 0x10;
				break;
			case m_reactive_color://ok
				data_settings[1] = 0x42;
				data_settings[5] = 0x2a;
				data_settings[8] = 0x11;
				break;
			case m_ripple://ok
				data_settings[1] = 0x43;
				data_settings[5] = 0x2a;
				data_settings[8] = 0x12;
				break;
			case m_custom://ok
				data_settings[1] = 0x45;
				data_settings[5] = 0x2a;
				data_settings[8] = 0x14;
				break;
			case m_off://ok
				data_settings[1] = 0x44;
				data_settings[5] = 0x2a;
				data_settings[8] = 0x13;
				break;
			default:
				break;
		}
	} else if( _profile == 3 ){
		switch( _mode[_profile-1] ){
			case m_horizontal_wave://ok
				data_settings[1] = 0x5c;
				data_settings[5] = 0x54;
				data_settings[8] = 0x01;
				break;
			case m_pulse://ok
				data_settings[1] = 0x5d;
				data_settings[5] = 0x54;
				data_settings[8] = 0x02;
				break;
			case m_hurricane://ok
				data_settings[1] = 0x5e;
				data_settings[5] = 0x54;
				data_settings[8] = 0x03;
				break;
			case m_breathing_color://ok
				data_settings[1] = 0x5f;
				data_settings[5] = 0x54;
				data_settings[8] = 0x04;
				break;
			case m_breathing://ok
				data_settings[1] = 0x60;
				data_settings[5] = 0x54;
				data_settings[8] = 0x05;
				break;
			case m_fixed://ok ---
				data_settings[1] = 0x61;
				data_settings[5] = 0x54;
				data_settings[8] = 0x06;
				break;
			case m_reactive_single://ok
				data_settings[1] = 0x62;
				data_settings[5] = 0x54;
				data_settings[8] = 0x07;
				break;
			case m_reactive_ripple://ok
				data_settings[1] = 0x63;
				data_settings[5] = 0x54;
				data_settings[8] = 0x08;
				break;
			case m_reactive_horizontal://ok
				data_settings[1] = 0x64;
				data_settings[5] = 0x54;
				data_settings[8] = 0x09;
				break;
			case m_waterfall://ok
				data_settings[1] = 0x65;
				data_settings[5] = 0x54;
				data_settings[8] = 0x0a;
				break;
			case m_swirl://ok
				data_settings[1] = 0x66;
				data_settings[5] = 0x54;
				data_settings[8] = 0x0b;
				break;
			case m_vertical_wave://ok
				data_settings[1] = 0x67;
				data_settings[5] = 0x54;
				data_settings[8] = 0x0c;
				break;
			case m_sine://ok
				data_settings[1] = 0x68;
				data_settings[5] = 0x54;
				data_settings[8] = 0x0d;
				break;
			case m_vortex://ok
				data_settings[1] = 0x69;
				data_settings[5] = 0x54;
				data_settings[8] = 0x0e;
				break;
			case m_rain://ok
				data_settings[1] = 0x6a;
				data_settings[5] = 0x54;
				data_settings[8] = 0x0f;
				break;
			case m_diagonal_wave://ok
				data_settings[1] = 0x6b;
				data_settings[5] = 0x54;
				data_settings[8] = 0x10;
				break;
			case m_reactive_color://ok
				data_settings[1] = 0x6c;
				data_settings[5] = 0x54;
				data_settings[8] = 0x11;
				break;
			case m_ripple://ok
				data_settings[1] = 0x6d;
				data_settings[5] = 0x54;
				data_settings[8] = 0x12;
				break;
			case m_custom://ok
				data_settings[1] = 0x6f;
				data_settings[5] = 0x54;
				data_settings[8] = 0x14;
				break;
			case m_off://ok
				data_settings[1] = 0x6e;
				data_settings[5] = 0x54;
				data_settings[8] = 0x13;
				break;
			default:
				break;
		}
	} else{
		throw std::invalid_argument("Invalid profile number");
	}
	
	//send data
	res += _write_data( _data_start, 64 );
	res += _write_data( data_settings, 64 );
	res += _write_data( _data_end, 64 );
	
	return res;
}

int rgb_keyboard::keyboard::write_color(){
		
	//vars
	int res = 0;
	
	//prepare data packet
	uint8_t data_settings_1[64];
	std::copy(std::begin(_data_settings), std::end(_data_settings), std::begin(data_settings_1));
	uint8_t data_settings_2[64];
	std::copy(std::begin(_data_settings), std::end(_data_settings), std::begin(data_settings_2));
	
	if( _profile == 1 ){
		data_settings_1[1] = 0x0b;
		data_settings_1[5] = 0x04;
		if( _rainbow[_profile-1] ){
			data_settings_1[1] = 0x0c;
			data_settings_1[8] = 0x01;
		}
		
		data_settings_2[2] = 0x02;
		data_settings_2[4] = 0x03;
		data_settings_2[5] = 0x05;
		data_settings_2[8] = _color_r[_profile-1];
		data_settings_2[9] = _color_g[_profile-1];
		data_settings_2[10] = _color_b[_profile-1];
	} else if( _profile == 2 ){
		data_settings_1[1] = 0x35;
		data_settings_1[5] = 0x2e;
		if( _rainbow[_profile-1] ){
			data_settings_1[1] = 0x36;
			data_settings_1[5] = 0x2e;
			data_settings_1[8] = 0x01;
		}
		
		data_settings_2[4] = 0x03;
		data_settings_2[5] = 0x2f;
		data_settings_2[8] = _color_r[_profile-1];
		data_settings_2[9] = _color_g[_profile-1];
		data_settings_2[10] = _color_b[_profile-1];
	} else if( _profile == 3 ){
		data_settings_1[1] = 0x5f;
		data_settings_1[5] = 0x58;
		if( _rainbow[_profile-1] ){
			data_settings_1[1] = 0x60;
			data_settings_1[5] = 0x58;
			data_settings_1[8] = 0x01;
		}
		
		data_settings_2[4] = 0x03;
		data_settings_2[5] = 0x59;
		data_settings_2[8] = _color_r[_profile-1];
		data_settings_2[9] = _color_g[_profile-1];
		data_settings_2[10] = _color_b[_profile-1];
	} else{
		throw std::invalid_argument("Invalid profile number");
	}
	
	//send data
	res += _write_data( _data_start, 64 );
	res += _write_data( data_settings_1, 64 );
	res += _write_data( data_settings_2, 64 );
	res += _write_data( _data_end, 64 );
	
	return res;
}

//writes custom pattern to keyboard
int rgb_keyboard::keyboard::write_custom(){
	
	//vars
	int res = 0;
	
	//prepare data packet
	uint8_t data_settings[64];
	std::copy(std::begin(_data_settings), std::end(_data_settings), std::begin(data_settings));
	data_settings[2] = 0x02;
	data_settings[3] = 0x11;
	data_settings[4] = 0x03;
	
	// write start data
	res += _write_data( _data_start, 64 );
	
	//process loaded config and send data
	for( std::pair< std::string, std::array<uint8_t, 3> > element : _key_colors[_profile-1] ){
		if( _keycodes.find( element.first ) != _keycodes.end() ){
			//if keycode is stored in _keycodes: set values in data packets
			
			//prepare data packet
			if( _profile == 1 ){
				//keycode
				data_settings[1] = _keycodes.at(element.first)[0];
				data_settings[5] = _keycodes.at(element.first)[1];
				data_settings[6] = _keycodes.at(element.first)[2];
				
				//color
				data_settings[8] = element.second[0];
				data_settings[9] = element.second[1];
				data_settings[10] = element.second[2];
			} else if( _profile == 2 ){
				//keycode
				data_settings[1] = _keycodes.at(element.first)[0] + 0x02;
				data_settings[5] = _keycodes.at(element.first)[1];
				data_settings[6] = _keycodes.at(element.first)[2] + 0x02;
				
				//color
				data_settings[8] = element.second[0];
				data_settings[9] = element.second[1];
				data_settings[10] = element.second[2];
			} else if( _profile == 3 ){
				//keycode
				data_settings[1] = _keycodes.at(element.first)[0] + 0x04;
				data_settings[5] = _keycodes.at(element.first)[1];
				data_settings[6] = _keycodes.at(element.first)[2] + 0x04;
				
				//color
				data_settings[8] = element.second[0];
				data_settings[9] = element.second[1];
				data_settings[10] = element.second[2];
			}
			
			//send data
			res += _write_data( data_settings, 64 );
			
		}
	}
	
	// write end data
	res += _write_data( _data_end, 64 );
	
	return res;
}

int rgb_keyboard::keyboard::write_variant(){
	
	//vars
	int res = 0;
	
	//prepare data packet
	uint8_t data_settings[64];
	std::copy(std::begin(_data_settings), std::end(_data_settings), std::begin(data_settings));
	data_settings[5] = 0x08;
	
	//convert variant	
	if( _profile == 1 ){
		if( _variant[_profile-1] == v_color_red ){
			data_settings[1] = 0x0f;
			data_settings[8] = 0x00;
		} else if( _variant[_profile-1] == v_color_yellow ){
			data_settings[1] = 0x10;
			data_settings[8] = 0x01;
		} else if( _variant[_profile-1] == v_color_green ){
			data_settings[1] = 0x11;
			data_settings[8] = 0x02;
		} else if( _variant[_profile-1] == v_color_blue ){
			data_settings[1] = 0x12;
			data_settings[8] = 0x03;
		} else{
			return 1;
		}
	} else if( _profile == 2 ){
		if( _variant[_profile-1] == v_color_red ){
			data_settings[1] = 0x39;
			data_settings[5] = 0x32;
			data_settings[8] = 0x00;
		} else if( _variant[_profile-1] == v_color_yellow ){
			data_settings[1] = 0x3a;
			data_settings[5] = 0x32;
			data_settings[8] = 0x01;
		} else if( _variant[_profile-1] == v_color_green ){
			data_settings[1] = 0x3b;
			data_settings[5] = 0x32;
			data_settings[8] = 0x02;
		} else if( _variant[_profile-1] == v_color_blue ){
			data_settings[1] = 0x3c;
			data_settings[5] = 0x32;
			data_settings[8] = 0x03;
		} else{
			return 1;
		}
	} else if( _profile == 3 ){
		if( _variant[_profile-1] == v_color_red ){
			data_settings[1] = 0x63;
			data_settings[5] = 0x5c;
			data_settings[8] = 0x00;
		} else if( _variant[_profile-1] == v_color_yellow ){
			data_settings[1] = 0x64;
			data_settings[5] = 0x5c;
			data_settings[8] = 0x01;
		} else if( _variant[_profile-1] == v_color_green ){
			data_settings[1] = 0x65;
			data_settings[5] = 0x5c;
			data_settings[8] = 0x02;
		} else if( _variant[_profile-1] == v_color_blue ){
			data_settings[1] = 0x66;
			data_settings[5] = 0x5c;
			data_settings[8] = 0x03;
		} else{
			return 1;
		}
	} else{
		throw std::invalid_argument("Invalid profile number");
	}
	
	//send data
	res += _write_data( _data_start, 64 );
	res += _write_data( data_settings, 64 );
	res += _write_data( _data_end, 64 );
	
	return res;
}

int rgb_keyboard::keyboard::write_report_rate(){
	
	//vars
	int res = 0;
	
	//prepare data packet
	uint8_t data_settings[64];
	std::copy(std::begin(_data_settings), std::end(_data_settings), std::begin(data_settings));
	data_settings[5] = 0x0f;
	
	//convert report rate	
	if( _profile == 1 ){
		if( _report_rate[_profile-1] == r_125Hz ){
			data_settings[1] = 0x16;
			data_settings[8] = 0x00;
		} else if( _report_rate[_profile-1] == r_250Hz ){
			data_settings[1] = 0x17;
			data_settings[8] = 0x01;
		} else if( _report_rate[_profile-1] == r_500Hz ){
			data_settings[1] = 0x18;
			data_settings[8] = 0x02;
		} else if( _report_rate[_profile-1] == r_1000Hz ){
			data_settings[1] = 0x19;
			data_settings[8] = 0x03;
		} else{
			return 1;
		}
	} else if( _profile == 2 ){
		if( _report_rate[_profile-1] == r_125Hz ){
			data_settings[1] = 0x40;
			data_settings[5] = 0x39;
			data_settings[8] = 0x00;
		} else if( _report_rate[_profile-1] == r_250Hz ){
			data_settings[1] = 0x41;
			data_settings[5] = 0x39;
			data_settings[8] = 0x01;
		} else if( _report_rate[_profile-1] == r_500Hz ){
			data_settings[1] = 0x42;
			data_settings[5] = 0x39;
			data_settings[8] = 0x02;
		} else if( _report_rate[_profile-1] == r_1000Hz ){
			data_settings[1] = 0x43;
			data_settings[5] = 0x39;
			data_settings[8] = 0x03;
		} else{
			return 1;
		}
	} else if( _profile == 3 ){
		if( _report_rate[_profile-1] == r_125Hz ){
			data_settings[1] = 0x6a;
			data_settings[5] = 0x63;
			data_settings[8] = 0x00;
		} else if( _report_rate[_profile-1] == r_250Hz ){
			data_settings[1] = 0x6b;
			data_settings[5] = 0x63;
			data_settings[8] = 0x01;
		} else if( _report_rate[_profile-1] == r_500Hz ){
			data_settings[1] = 0x6c;
			data_settings[5] = 0x63;
			data_settings[8] = 0x02;
		} else if( _report_rate[_profile-1] == r_1000Hz ){
			data_settings[1] = 0x6d;
			data_settings[5] = 0x63;
			data_settings[8] = 0x03;
		} else{
			return 1;
		}
	} else{
		throw std::invalid_argument("Invalid profile number");
	}
	
	//send data
	res += _write_data( _data_start, 64 );
	res += _write_data( data_settings, 64 );
	res += _write_data( _data_end, 64 );
	
	return res;
}

int rgb_keyboard::keyboard::write_key_mapping_ansi(){
	
	// sanity check, this function does not support the Ajazz AK33
	if( _ajazzak33_compatibility )
		throw std::invalid_argument("Not supported on the Ajazz AK33");
	
	//vars
	int res = 0;
	
	//prepare data packets
	uint8_t data_remap[8][64];
	std::copy(std::begin(_data_remap_1), std::end(_data_remap_1), std::begin(data_remap[0]));
	std::copy(std::begin(_data_remap_2), std::end(_data_remap_2), std::begin(data_remap[1]));
	std::copy(std::begin(_data_remap_3), std::end(_data_remap_3), std::begin(data_remap[2]));
	std::copy(std::begin(_data_remap_4), std::end(_data_remap_4), std::begin(data_remap[3]));
	std::copy(std::begin(_data_remap_5), std::end(_data_remap_5), std::begin(data_remap[4]));
	std::copy(std::begin(_data_remap_6), std::end(_data_remap_6), std::begin(data_remap[5]));
	std::copy(std::begin(_data_remap_7), std::end(_data_remap_7), std::begin(data_remap[6]));
	std::copy(std::begin(_data_remap_8), std::end(_data_remap_8), std::begin(data_remap[7]));
	
	
	// change data for correct profile
	if( _profile == 2 ){
		
		for( int i = 1; i < 8; i++ ){
			data_remap[i][1] = data_remap[i][1] + 0x02;
			data_remap[i][6] = data_remap[i][6] + 0x02;
		}
		
	} else if( _profile == 3 ){
		
		for( int i = 1; i < 8; i++ ){
			data_remap[i][1] = data_remap[i][1] + 0x04;
			data_remap[i][6] = data_remap[i][6] + 0x04;
		}
		
	}
	
	// change data to include keycodes at the right positions
	for( std::pair< std::string, std::string > element : _keymap[_profile-1] ){
		
		// is key name and key function known?
		if( _keymap_offsets.find( element.first ) != _keymap_offsets.end() &&
			_keymap_options.find( element.second ) != _keymap_options.end() ){
				
			data_remap[ _keymap_offsets[element.first][0][0] ][ _keymap_offsets[element.first][0][1] ]
			= _keymap_options[ element.second ][0];
			data_remap[ _keymap_offsets[element.first][1][0] ][ _keymap_offsets[element.first][1][1] ]
			= _keymap_options[ element.second ][1];
			data_remap[ _keymap_offsets[element.first][2][0] ][ _keymap_offsets[element.first][2][1] ]
			= _keymap_options[ element.second ][2];
			
			// is key name known and function is a macro?
		} else if( _keymap_offsets.find( element.first ) != _keymap_offsets.end() &&
			std::regex_match( element.second, std::regex("macro[0-9]+") ) ){
			
			std::string macroname = element.second;
			int macronumber = std::stoi( macroname.erase(0, 5) );
			
			// check for range of macronumber
			if( macronumber <= 100 && macronumber >= 1 ){
			
				data_remap[ _keymap_offsets[element.first][0][0] ][ _keymap_offsets[element.first][0][1] ]
				= 0x05;
				data_remap[ _keymap_offsets[element.first][1][0] ][ _keymap_offsets[element.first][1][1] ]
				= 0x01;
				data_remap[ _keymap_offsets[element.first][2][0] ][ _keymap_offsets[element.first][2][1] ]
				= macronumber-1;
				
			}
			
		}
		
	}
	
	// prepare macro data packets
	/*uint8_t data_macros[19][64];
	for( int i = 0; i < 19; i++ ){
		std::copy(std::begin(_data_macros), std::end(_data_macros), std::begin(data_macros[i]));
		data_macros[i][2] = 0x06 + (2*i); // set packet counter
	}
	
	// special values in the first packet
	data_macros[0][8] = 0xaa;
	data_macros[0][9] = 0x55;
	data_macros[0][10] = 0x32;
	data_macros[0][11] = 0x00;
	data_macros[0][12] = _macro_bytes.size(); // set number of macros
	data_macros[0][13] = 0x00;
	data_macros[0][14] = 0x01;
	data_macros[0][15] = 0x00;
	data_macros[0][24] = 0x10 + (2*_macro_bytes.size()); // set number of macros
	
	// copy _macro_bytes
	int packet_index = 0, byte_index = 25; // macro data begins at 25 for the first packet
	for( unsigned int i = 0; i < _macro_bytes.size(); i++ ){ // for each macro
		
		for( unsigned int j = 0; j < _macro_bytes[i].size(); j++ ){ // for each byte
			data_macros[packet_index][byte_index] = _macro_bytes[i][j];
			
			// increment packet and byte index
			byte_index++;
			if( byte_index >= 64 ){
				byte_index = 8; // macro bytes start at 8 for all other packets
				packet_index++;
				if( packet_index >= 19 ){
					return 1; // this means not enough space for all macros
				}
			}
		}
		
	}*/
		
	//send start data
	res += _write_data( _data_start, 64 );
	
	//write macro data here
	/*for( int i = 0; i <= packet_index; i++ ){
		
		if( _ajazzak33_compatibility ){
			
			//write end data packet to endpoint 0
			libusb_control_transfer( _handle, 0x21, 0x09, 0x0204, 0x0001, data_macros[i], 64, 1000 );
			//read from endpoint 2
			res += libusb_interrupt_transfer( _handle, 0x82, buffer, 64, &transferred, 1000);
		
		} else{
			
			//write data packet to endpoint 3
			res += libusb_interrupt_transfer( _handle, 0x03, data_macros[i], 64, &transferred, 1000);
			//read from endpoint 2
			res += libusb_interrupt_transfer( _handle, 0x82, buffer, 64, &transferred, 1000);
			
		}
		
	}*/
	
	//write keymap data
	for( int i = 0; i < 8; i++ )
		res += _write_data( data_remap[i], 64 );
	
	// write end data
	res += _write_data( _data_end, 64 );
	
	return res;
}

int rgb_keyboard::keyboard::write_active_profile(){
	
	//vars
	int res = 0;
	
	//prepare data packets
	uint8_t data_profile[64];
	std::copy(std::begin(_data_profile), std::end(_data_profile), std::begin(data_profile));
	
	// change data
	if( _active_profile == 1 ){
		
		// 1 is default, do nothing
		
	} else if( _active_profile == 2 ){
		
		data_profile[1] = 0xe1;
		data_profile[18] = 0x01;
		
	} else if( _active_profile == 3 ){
		
		data_profile[1] = 0xe2;
		data_profile[18] = 0x02;
		
	} else{
		throw std::invalid_argument("Invalid profile number");
	}
	
	// write data
	res += _write_data( data_profile, 64 );
	
	return res;
}
