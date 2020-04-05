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

//helper functions

//init libusb and open keyboard with default vid and pid
int rgb_keyboard::keyboard::open_keyboard(){
	
	//vars
	int res = 0;
	
	//libusb init
	res = libusb_init( NULL );
	if( res < 0 ){
		return res;
	}
	
	//open device
	_handle = libusb_open_device_with_vid_pid( NULL, _keyboard_vid, 
	_keyboard_pid );
	if( !_handle ){
		res++;
		return res;
	}
	
	if( _detach_kernel_driver ){
		
		if( _open_interface_0 ){
			//detach kernel driver on interface 0 if active 
			if( libusb_kernel_driver_active( _handle, 0 ) ){
				res += libusb_detach_kernel_driver( _handle, 0 );
				if( res == 0 ){
					_detached_driver_0 = true;
				} else{
					return res;
				}
			}
		}
		
		//detach kernel driver on interface 1 if active 
		if( libusb_kernel_driver_active( _handle, 1 ) ){
			res += libusb_detach_kernel_driver( _handle, 1 );
			if( res == 0 ){
				_detached_driver_1 = true;
			} else{
				return res;
			}
		}
	}
	
	if( _open_interface_0 ){
		//claim interface 0
		res += libusb_claim_interface( _handle, 0 );
		if( res != 0 ){
			return res;
		}
	}
	
	//claim interface 1
	res += libusb_claim_interface( _handle, 1 );
	if( res != 0 ){
		return res;
	}
	
	return res;
}

//init libusb and open keyboard with bus and device id
int rgb_keyboard::keyboard::open_keyboard_bus_device( uint8_t bus, uint8_t device ){
	
	//vars
	int res = 0;
	
	//libusb init
	res = libusb_init( NULL );
	if( res < 0 ){
		return res;
	}
	
	//open device (_handle)
	
	libusb_device **dev_list; // device list
	ssize_t num_devs = libusb_get_device_list(NULL, &dev_list); //get device list
	
	if( num_devs < 0 )
		return 1;
	
	for( ssize_t i = 0; i < num_devs; i++ ){
		
		// check if correct bus and device
		if( bus == libusb_get_bus_number( dev_list[i] ) &&
			device == libusb_get_device_address( dev_list[i] ) ){
			
			// open device
			if( libusb_open( dev_list[i], &_handle ) != 0 ){
				return 1;
			} else{
				break;
			}
			
		}
		
	}
	
	//free device list, unreference devices
	libusb_free_device_list( dev_list, 1 );
	
	if( _detach_kernel_driver ){
		
		if( _open_interface_0){
			//detach kernel driver on interface 0 if active 
			if( libusb_kernel_driver_active( _handle, 0 ) ){
				res += libusb_detach_kernel_driver( _handle, 0 );
				if( res == 0 ){
					_detached_driver_0 = true;
				} else{
					return res;
				}
			}
		}
		
		//detach kernel driver on interface 1 if active 
		if( libusb_kernel_driver_active( _handle, 1 ) ){
			res += libusb_detach_kernel_driver( _handle, 1 );
			if( res == 0 ){
				_detached_driver_1 = true;
			} else{
				return res;
			}
		}
	}
	
	if( _open_interface_0 ){
		//claim interface 0
		res += libusb_claim_interface( _handle, 0 );
		if( res != 0 ){
			return res;
		}
	}
	
	//claim interface 1
	res += libusb_claim_interface( _handle, 1 );
	if( res != 0 ){
		return res;
	}
	
	return res;
}

//close keyboard
int rgb_keyboard::keyboard::close_keyboard(){
	
	//release interface 0 and 1
	if( _open_interface_0 ){
		libusb_release_interface( _handle, 0 );
	}
	libusb_release_interface( _handle, 1 );
	
	//attach kernel driver for interface 0
	if( _detached_driver_0 && _open_interface_0 ){
		libusb_attach_kernel_driver( _handle, 0 );
	}
	
	//attach kernel driver for interface 1
	if( _detached_driver_0 ){
		libusb_attach_kernel_driver( _handle, 1 );
	}
	
	//exit libusb
	libusb_exit( NULL );
	
	return 0;
}
