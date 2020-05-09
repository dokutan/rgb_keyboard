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
	
	//vars
	int res = 0;
	int transferred = 0;
	uint8_t buffer[64];
	
	//prepare data packet
	uint8_t data_read[64];
	std::copy(std::begin(_data_read), std::end(_data_read), std::begin(data_read));
	data_read[1] = 0x2f;
	data_read[3] = 0x03;
	data_read[4] = 0x2c;
	
	//write data packet to endpoint 3
	res += libusb_interrupt_transfer( _handle, 0x03, data_read, 
	64, &transferred, 1000);
	
	//read from endpoint 2
	res += libusb_interrupt_transfer( _handle, 0x82, buffer, 64, 
	&transferred, 1000);

	_active_profile = buffer[18]+1;
	return 0;
}

int rgb_keyboard::keyboard::read_color(){
	/*
	//vars
	int res = 0;
	int transferred = 0;
	uint8_t buffer[64];
	
	//prepare data packet
	uint8_t data_read[64];
	std::copy(std::begin(_data_read_profile), std::end(_data_read_profile), std::begin(data_read));
	
	
	//write data packet to endpoint 3
	res += libusb_interrupt_transfer( _handle, 0x03, data_read, 
	64, &transferred, 1000);
	
	//read from endpoint 2
	res += libusb_interrupt_transfer( _handle, 0x82, buffer, 64, 
	&transferred, 1000);
	
	for( int i = 0; i < 64; i++ ){
		std::cout << (int)buffer[i] << "\n";
	}
	
	//_active_profile = buffer[18]+1;
	*/
	return 0;
}
