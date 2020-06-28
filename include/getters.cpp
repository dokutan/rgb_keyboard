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

int rgb_keyboard::keyboard::get_speed(){
	return _speed[_profile-1];
}

int rgb_keyboard::keyboard::get_brightness(){
	return _brightness[_profile-1];
}

rgb_keyboard::keyboard::mode rgb_keyboard::keyboard::get_mode(){
	return _mode[_profile-1];
}

rgb_keyboard::keyboard::direction rgb_keyboard::keyboard::get_direction(){
	return _direction[_profile-1];
}

uint8_t rgb_keyboard::keyboard::get_color_r(){
	return _color_r[_profile-1];
}

uint8_t rgb_keyboard::keyboard::get_color_g(){
	return _color_g[_profile-1];
}

uint8_t rgb_keyboard::keyboard::get_color_b(){
	return _color_b[_profile-1];
}

bool rgb_keyboard::keyboard::get_rainbow(){
	return _rainbow[_profile-1];
}

rgb_keyboard::keyboard::mode_variant rgb_keyboard::keyboard::get_variant(){
	return _variant[_profile-1];
}

rgb_keyboard::keyboard::report_rate rgb_keyboard::keyboard::get_report_rate(){
	return _report_rate[_profile-1];
}

bool rgb_keyboard::keyboard::get_detach_kernel_driver(){
	return _detach_kernel_driver;
}

bool rgb_keyboard::keyboard::get_open_interface_0(){
	return _open_interface_0;
}

int rgb_keyboard::keyboard::get_active_profile(){
	return _active_profile;
}

int rgb_keyboard::keyboard::get_profile(){
	return _profile;
}

bool rgb_keyboard::keyboard::get_ajazzak33_compatibility(){
	return _ajazzak33_compatibility;
}
