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

int rgb_keyboard::keyboard::get_speed(){
	return _speed;
}

int rgb_keyboard::keyboard::get_brightness(){
	return _brightness;
}

rgb_keyboard::keyboard::mode rgb_keyboard::keyboard::get_mode(){
	return _mode;
}

rgb_keyboard::keyboard::direction rgb_keyboard::keyboard::get_direction(){
	return _direction;
}

uint8_t rgb_keyboard::keyboard::get_color_r(){
	return _color_r;
}

uint8_t rgb_keyboard::keyboard::get_color_g(){
	return _color_r;
}

uint8_t rgb_keyboard::keyboard::get_color_b(){
	return _color_r;
}

bool rgb_keyboard::keyboard::get_rainbow(){
	return _rainbow;
}

rgb_keyboard::keyboard::mode_variant rgb_keyboard::keyboard::get_variant(){
	return _variant;
}
