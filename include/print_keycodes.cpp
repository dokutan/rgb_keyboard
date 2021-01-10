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

//prints all keys for custom led pattern
int rgb_keyboard::keyboard::print_keycodes_led(std::ostream& output){
	
	for( auto i : _keycodes ){
		output << i.first << "\n";
	}
	
	return 0;
}

//prints all keys for remapping
int rgb_keyboard::keyboard::print_keycodes_remap(std::ostream& output){
	
	for( auto i : _keymap_offsets ){
		output << i.first << "\n";
	}
	
	return 0;
}

//prints all rempping options
int rgb_keyboard::keyboard::print_keycodes_options(std::ostream& output){
	
	for( auto i : _keymap_options ){
		output << i.first << "\n";
	}
	
	return 0;
}
