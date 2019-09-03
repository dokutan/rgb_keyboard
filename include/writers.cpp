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

//writer functions (apply changes to keyboard)

int rgb_keyboard::keyboard::write_brightness(){
		
	//vars
	int res = 0;
	int transferred = 0;
	uint8_t buffer[64];
	
	//prepare data packet
	uint8_t data_settings[64];
	std::copy(std::begin(_data_settings), std::end(_data_settings), std::begin(data_settings));
	data_settings[1] = 0x08 + _brightness;
	data_settings[8] = _brightness;
	data_settings[5] = 0x01;
	
	//send data
	
	//write start data packet to endpoint 3
	res += libusb_interrupt_transfer( _handle, 0x03, _data_start, 
	64, &transferred, 1000);
	
	//read from endpoint 2
	res += libusb_interrupt_transfer( _handle, 0x82, buffer, 64, 
	&transferred, 1000);
	
	//write brightness data packet to endpoint 3
	res += libusb_interrupt_transfer( _handle, 0x03, data_settings, 
	64, &transferred, 1000);
	
	//read from endpoint 2
	res += libusb_interrupt_transfer( _handle, 0x82, buffer, 64, 
	&transferred, 1000);
	
	//write end data packet to endpoint 3
	res += libusb_interrupt_transfer( _handle, 0x03, _data_end, 
	64, &transferred, 1000);
	
	//read from endpoint 2
	res += libusb_interrupt_transfer( _handle, 0x82, buffer, 64, &transferred, 1000);
	
	return res;
}

int rgb_keyboard::keyboard::write_speed(){
		
	//vars
	int res = 0;
	int transferred = 0;
	uint8_t buffer[64];
	
	//prepare data packet
	uint8_t data_settings[64];
	std::copy(std::begin(_data_settings), std::end(_data_settings), std::begin(data_settings));
	data_settings[1] = 0x0d - _speed;
	data_settings[8] = 0x04 - _speed;
	data_settings[5] = 0x02;
	
	//send data
	
	//write start data packet to endpoint 3
	res += libusb_interrupt_transfer( _handle, 0x03, _data_start, 
	64, &transferred, 1000);
	
	//read from endpoint 2
	res += libusb_interrupt_transfer( _handle, 0x82, buffer, 64, 
	&transferred, 1000);
	
	//write data packet to endpoint 3
	res += libusb_interrupt_transfer( _handle, 0x03, data_settings, 
	64, &transferred, 1000);
	
	//read from endpoint 2
	res += libusb_interrupt_transfer( _handle, 0x82, buffer, 64, 
	&transferred, 1000);
	
	//write end data packet to endpoint 3
	res += libusb_interrupt_transfer( _handle, 0x03, _data_end, 
	64, &transferred, 1000);
	
	//read from endpoint 2
	res += libusb_interrupt_transfer( _handle, 0x82, buffer, 64, &transferred, 1000);
		
	return res;
}

int rgb_keyboard::keyboard::write_direction(){
		
	//vars
	int res = 0;
	int transferred = 0;
	uint8_t buffer[64];
	
	//prepare data packet
	uint8_t data_settings[64];
	std::copy(std::begin(_data_settings), std::end(_data_settings), std::begin(data_settings));
	switch( _direction ){
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
	
	//send data
	
	//write start data packet to endpoint 3
	res += libusb_interrupt_transfer( _handle, 0x03, _data_start, 
	64, &transferred, 1000);
	
	//read from endpoint 2
	res += libusb_interrupt_transfer( _handle, 0x82, buffer, 64, 
	&transferred, 1000);
	
	//write data packet to endpoint 3
	res += libusb_interrupt_transfer( _handle, 0x03, data_settings, 
	64, &transferred, 1000);
	
	//read from endpoint 2
	res += libusb_interrupt_transfer( _handle, 0x82, buffer, 64, 
	&transferred, 1000);
	
	//write end data packet to endpoint 3
	res += libusb_interrupt_transfer( _handle, 0x03, _data_end, 
	64, &transferred, 1000);
	
	//read from endpoint 2
	res += libusb_interrupt_transfer( _handle, 0x82, buffer, 64, &transferred, 1000);
		
	return res;
}

int rgb_keyboard::keyboard::write_mode(){
		
	//vars
	int res = 0;
	int transferred = 0;
	uint8_t buffer[64];
	
	//prepare data packet
	uint8_t data_settings[64];
	std::copy(std::begin(_data_settings), std::end(_data_settings), std::begin(data_settings));
	switch( _mode ){
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
		default:
			break;
	}
			
	//send data
	
	//write start data packet to endpoint 3
	res += libusb_interrupt_transfer( _handle, 0x03, _data_start, 
	64, &transferred, 1000);
	
	//read from endpoint 2
	res += libusb_interrupt_transfer( _handle, 0x82, buffer, 64, 
	&transferred, 1000);
	
	//write data packet to endpoint 3
	res += libusb_interrupt_transfer( _handle, 0x03, data_settings, 
	64, &transferred, 1000);
	
	//read from endpoint 2
	res += libusb_interrupt_transfer( _handle, 0x82, buffer, 64, 
	&transferred, 1000);
	
	//write end data packet to endpoint 3
	res += libusb_interrupt_transfer( _handle, 0x03, _data_end, 
	64, &transferred, 1000);
	
	//read from endpoint 2
	res += libusb_interrupt_transfer( _handle, 0x82, buffer, 64, &transferred, 1000);
	
	return res;
}

int rgb_keyboard::keyboard::write_color(){
		
	//vars
	int res = 0;
	int transferred = 0;
	uint8_t buffer[64];
	
	//prepare data packet
	uint8_t data_settings_1[64];
	std::copy(std::begin(_data_settings), std::end(_data_settings), std::begin(data_settings_1));
	uint8_t data_settings_2[64];
	std::copy(std::begin(_data_settings), std::end(_data_settings), std::begin(data_settings_2));
	
	data_settings_1[1] = 0x0b;
	data_settings_1[5] = 0x04;
	if( _rainbow ){
		data_settings_1[1] = 0x0c;
		data_settings_1[8] = 0x01;
	}
	
	data_settings_2[2] = 0x02;
	data_settings_2[4] = 0x03;
	data_settings_2[5] = 0x05;
	data_settings_2[8] = _color_r;
	data_settings_2[9] = _color_g;
	data_settings_2[10] = _color_b;
	
	//send data
	
	//write start data packet to endpoint 3
	res += libusb_interrupt_transfer( _handle, 0x03, _data_start, 
	64, &transferred, 1000);
	
	//read from endpoint 2
	res += libusb_interrupt_transfer( _handle, 0x82, buffer, 64, 
	&transferred, 1000);
	
	//write data packet to endpoint 3
	res += libusb_interrupt_transfer( _handle, 0x03, data_settings_1, 
	64, &transferred, 1000);
	
	//read from endpoint 2
	res += libusb_interrupt_transfer( _handle, 0x82, buffer, 64, 
	&transferred, 1000);
	
	//write data packet to endpoint 3
	res += libusb_interrupt_transfer( _handle, 0x03, data_settings_2, 
	64, &transferred, 1000);
	
	//read from endpoint 2
	res += libusb_interrupt_transfer( _handle, 0x82, buffer, 64, 
	&transferred, 1000);
	
	//write end data packet to endpoint 3
	res += libusb_interrupt_transfer( _handle, 0x03, _data_end, 
	64, &transferred, 1000);
	
	//read from endpoint 2
	res += libusb_interrupt_transfer( _handle, 0x82, buffer, 64, &transferred, 1000);
		
	return res;
}

//writes custom pattern to keyboard
int rgb_keyboard::keyboard::write_custom(){
	
	//vars
	int res = 0;
	int transferred = 0;
	uint8_t buffer[64];
	
	//prepare data packet
	uint8_t data_settings[64];
	std::copy(std::begin(_data_settings), std::end(_data_settings), std::begin(data_settings));
	data_settings[2] = 0x02;
	data_settings[3] = 0x11;
	data_settings[4] = 0x03;
	
	//write start data packet to endpoint 3
	res += libusb_interrupt_transfer( _handle, 0x03, _data_start, 
	64, &transferred, 1000);
	
	//read from endpoint 2
	res += libusb_interrupt_transfer( _handle, 0x82, buffer, 64, 
	&transferred, 1000);
	
	//process loaded config and send data
	for( std::pair< std::string, std::array<uint8_t, 3> > element : _key_colors ){
		if( _keycodes.find( element.first ) != _keycodes.end() ){
			//if keycode is stored in _keycodes: set values in data packets
			
			//prepare data packet
			data_settings[1] = _keycodes.at(element.first)[0];
			data_settings[5] = _keycodes.at(element.first)[1];
			data_settings[6] = _keycodes.at(element.first)[2];
			
			data_settings[8] = element.second[0];
			data_settings[9] = element.second[1];
			data_settings[10] = element.second[2];
			
			//send data
			//write first data packet to endpoint 3
			res += libusb_interrupt_transfer( _handle, 0x03, data_settings, 
			64, &transferred, 1000);
			
			//read from endpoint 2
			res += libusb_interrupt_transfer( _handle, 0x82, buffer, 64, 
			&transferred, 1000);
		}
	}
	
	//write end data packet to endpoint 3
	res += libusb_interrupt_transfer( _handle, 0x03, _data_end, 
	64, &transferred, 1000);
	
	//read from endpoint 2
	res += libusb_interrupt_transfer( _handle, 0x82, buffer, 64, &transferred, 1000);
	
	return res;
}

int rgb_keyboard::keyboard::write_variant(){
	
	//vars
	int res = 0;
	int transferred = 0;
	uint8_t buffer[64];
	
	//prepare data packet
	uint8_t data_settings[64];
	std::copy(std::begin(_data_settings), std::end(_data_settings), std::begin(data_settings));
	data_settings[5] = 0x08;
	
	//convert variant string
	if( _variant == v_color_red ){
		data_settings[1] = 0x0f;
		data_settings[8] = 0x00;
	} else if( _variant == v_color_yellow ){
		data_settings[1] = 0x10;
		data_settings[8] = 0x01;
	} else if( _variant == v_color_green ){
		data_settings[1] = 0x11;
		data_settings[8] = 0x02;
	} else if( _variant == v_color_blue ){
		data_settings[1] = 0x12;
		data_settings[8] = 0x03;
	} else{
		return 1;
	}
	
	//send data
	
	//write start data packet to endpoint 3
	res += libusb_interrupt_transfer( _handle, 0x03, _data_start, 
	64, &transferred, 1000);
	
	//read from endpoint 2
	res += libusb_interrupt_transfer( _handle, 0x82, buffer, 64, 
	&transferred, 1000);
	
	//write data packet to endpoint 3
	res += libusb_interrupt_transfer( _handle, 0x03, data_settings, 
	64, &transferred, 1000);
	
	//read from endpoint 2
	res += libusb_interrupt_transfer( _handle, 0x82, buffer, 64, 
	&transferred, 1000);
	
	//write end data packet to endpoint 3
	res += libusb_interrupt_transfer( _handle, 0x03, _data_end, 
	64, &transferred, 1000);
	
	//read from endpoint 2
	res += libusb_interrupt_transfer( _handle, 0x82, buffer, 64, &transferred, 1000);
	
	return res;
}
