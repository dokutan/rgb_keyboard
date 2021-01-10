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

// functions from the rgb_keyboard namespace
uint16_t rgb_keyboard::detect_pid( uint16_t vid ){
	
	uint16_t pid = 0;
	
	// libusb init
	if( libusb_init( NULL ) < 0 )
		return 0;
	
	// get device list
	libusb_device **dev_list;
	ssize_t num_devs = libusb_get_device_list(NULL, &dev_list);
	
	if( num_devs < 0 )
		return 0;
	
	for( ssize_t i = 0; i < num_devs; i++ ){
		
		// get device descriptor
		libusb_device_descriptor descriptor;
		libusb_get_device_descriptor( dev_list[i], &descriptor );
		
		// compare USB ids against known ids
		for( auto p : keyboard_pid ){
			if( p == descriptor.idProduct && vid == descriptor.idVendor )
				pid = descriptor.idProduct;
		}
		if( pid != 0 )
			break;
		
	}
	
	// free device list, unreference devices
	libusb_free_device_list( dev_list, 1 );
	
	// exit libusb
	libusb_exit( NULL );
	
	return pid;
}
