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

//reader functions

int rgb_keyboard::keyboard::read_active_profile(){
	
	// vars
	int res = 0;
	int transferred = 0;
	uint8_t buffer[64];
	
	// prepare data packet
	uint8_t data_read[64];
	std::copy(std::begin(_data_read), std::end(_data_read), std::begin(data_read));
	data_read[1] = 0x2f;
	data_read[3] = 0x03;
	data_read[4] = 0x2c;
	
	// write data packet to endpoint 3
	res += libusb_interrupt_transfer( _handle, 0x03, data_read, 
	64, &transferred, 1000);
	
	// read from endpoint 2
	res += libusb_interrupt_transfer( _handle, 0x82, buffer, 64, 
	&transferred, 1000);

	// check if valid profile number
	if( buffer[18]+1 >= 1 && buffer[18]+1 <= 3 ){
		_active_profile = buffer[18]+1;
		return 0;
	} else{
		return 1;
	}
}

int rgb_keyboard::keyboard::read_led_settings(){
	
	// vars
	int res = 0;
	int transferred = 0;
	uint8_t input_buffer[3][64];
	
	// prepare data packets
	uint8_t data_read_1[64], data_read_2[64], data_read_3[64];
	std::copy(std::begin(_data_read), std::end(_data_read), std::begin(data_read_1));
	std::copy(std::begin(_data_read), std::end(_data_read), std::begin(data_read_2));
	std::copy(std::begin(_data_read), std::end(_data_read), std::begin(data_read_3));
	
	data_read_1[1] = 0x3d;
	data_read_1[3] = 0x05;
	data_read_1[4] = 0x38;
	data_read_1[5] = 0x00;
	
	data_read_2[1] = 0x67;
	data_read_2[3] = 0x05;
	data_read_2[4] = 0x38;
	data_read_2[5] = 0x2a;
	
	data_read_3[1] = 0x91;
	data_read_3[3] = 0x05;
	data_read_3[4] = 0x38;
	data_read_3[5] = 0x54;
	
	// write data packet 1 to endpoint 3
	res += libusb_interrupt_transfer( _handle, 0x03, data_read_1, 
	64, &transferred, 1000);
	
	// read from endpoint 2
	res += libusb_interrupt_transfer( _handle, 0x82, input_buffer[0], 64, 
	&transferred, 1000);
	
	// write data packet 2 to endpoint 3
	res += libusb_interrupt_transfer( _handle, 0x03, data_read_2, 
	64, &transferred, 1000);
	
	// read from endpoint 2
	res += libusb_interrupt_transfer( _handle, 0x82, input_buffer[1], 64, 
	&transferred, 1000);
	
	// write data packet 3 to endpoint 3
	res += libusb_interrupt_transfer( _handle, 0x03, data_read_3, 
	64, &transferred, 1000);
	
	// read from endpoint 2
	res += libusb_interrupt_transfer( _handle, 0x82, input_buffer[2], 64, 
	&transferred, 1000);
	
	// extract information
	for( int i = 0; i < 3; i++ ){
		
		// color
		_color_r[i] = input_buffer[i][13];
		_color_g[i] = input_buffer[i][14];
		_color_b[i] = input_buffer[i][15];
		if( input_buffer[i][12] == 1 ){
			_rainbow[i] = true;
		} else{
			_rainbow[i] = false;
		}
		
		// brightness
		if( input_buffer[i][9] >= _brightness_min && input_buffer[i][9] <= _brightness_max )
			_brightness[i] = input_buffer[i][9];
		
		// speed
		if( 3-input_buffer[i][10] >= _speed_min && 3-input_buffer[i][10] <= _speed_max )
			_speed[i] = 3-input_buffer[i][10];
		
		// direction
		if( input_buffer[i][11] == 0xff )
			_direction[i] = d_left;
		else if( input_buffer[i][11] == 0x00 )
			_direction[i] = d_right;
		
		// led mode
		switch( input_buffer[i][8] ){
			case 0x01: _mode[i] = m_horizontal_wave; break;
			case 0x02: _mode[i] = m_pulse; break;
			case 0x03: _mode[i] = m_hurricane; break;
			case 0x04: _mode[i] = m_breathing_color; break;
			case 0x05: _mode[i] = m_breathing; break;
			case 0x06: _mode[i] = m_fixed; break;
			case 0x07: _mode[i] = m_reactive_single; break;
			case 0x08: _mode[i] = m_reactive_ripple; break;
			case 0x09: _mode[i] = m_reactive_horizontal; break;
			case 0x0a: _mode[i] = m_waterfall; break;
			case 0x0b: _mode[i] = m_swirl; break;
			case 0x0c: _mode[i] = m_vertical_wave; break;
			case 0x0d: _mode[i] = m_sine; break;
			case 0x0e: _mode[i] = m_vortex; break;
			case 0x0f: _mode[i] = m_rain; break;
			case 0x10: _mode[i] = m_diagonal_wave; break;
			case 0x11: _mode[i] = m_reactive_color; break;
			case 0x12: _mode[i] = m_ripple; break;
			case 0x13: _mode[i] = m_off; break;
			case 0x14: _mode[i] = m_custom; break;
			default: _mode[i] = m_undefined; break;
		}
		
		// reactive-color variant
		if( _mode[i] == m_reactive_color ){
			
			switch( input_buffer[i][16] ){
				case 0x00: _variant[i] = v_color_red; break;
				case 0x01: _variant[i] = v_color_yellow; break;
				case 0x02: _variant[i] = v_color_green; break;
				case 0x03: _variant[i] = v_color_blue; break;
				default: _variant[i] = v_undefined; break;
			}
			
		}
		
		// USB poll rate
		if( input_buffer[i][23] == 0x00 )
			_report_rate[i] = r_125Hz;
		else if( input_buffer[i][23] == 0x01 )
			_report_rate[i] = r_250Hz;
		else if( input_buffer[i][23] == 0x02 )
			_report_rate[i] = r_500Hz;
		else if( input_buffer[i][23] == 0x03 )
			_report_rate[i] = r_1000Hz;
		
	}
	
	return 0;
}

