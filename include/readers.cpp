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
		_color_r[i] = input_buffer[i][13];
		_color_g[i] = input_buffer[i][14];
		_color_b[i] = input_buffer[i][15];
		if( input_buffer[i][12] == 1 ){
			_rainbow[i] = true;
		} else{
			_rainbow[i] = false;
		}
		
		if( input_buffer[i][9] >= _brightness_min && input_buffer[i][9] <= _brightness_max )
			_brightness[i] = input_buffer[i][9];
		
	}
	
	return 0;
}
