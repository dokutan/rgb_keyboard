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

//main class
#ifndef RGB_KEYBOARD
#define RGB_KEYBOARD

#include <libusb-1.0/libusb.h>
#include <iostream>
#include <map>
#include <array>
#include <vector>
#include <string>
#include <algorithm>
#include <exception>
#include <regex>
//#include <assert.h>

namespace rgb_keyboard{
	class keyboard;
}

class rgb_keyboard::keyboard{
	
	public:
		
		enum mode{
			m_undefined,
			m_fixed,
			m_sine,
			m_rain,
			m_waterfall,
			m_vortex,
			m_swirl,
			m_breathing,
			m_breathing_color,
			m_reactive_ripple,
			m_reactive_single,
			m_reactive_horizontal,
			m_reactive_color,
			m_horizontal_wave,
			m_vertical_wave,
			m_diagonal_wave,
			m_pulse,
			m_hurricane,
			m_ripple,
			m_custom,
			m_off
		};
		
		enum direction{
			d_undefined,
			d_left = 1,
			d_right = 2,
			d_up = 1,
			d_down = 2,
			d_inwards = 1,
			d_outwards = 2
		};
		
		enum mode_variant{
			v_undefined,
			v_color_red,
			v_color_yellow,
			v_color_green,
			v_color_blue
		};
		
		enum report_rate{
			r_125Hz,
			r_250Hz,
			r_500Hz,
			r_1000Hz
		};
		
		//constructor
		keyboard();
		
		//setter functions
		int set_profile( int profile );
		int set_active_profile( int profile );
		int set_mode( mode Mode );
		int set_direction( direction Direction );
		int set_brightness( int Brightness );
		int set_speed( int Speed );
		int set_color( uint8_t Color_r, uint8_t Color_g, uint8_t Color_b );
		int set_rainbow( bool Rainbow );
		int set_variant( mode_variant Variant );
		int set_custom_keys( std::string Keys );
		int set_report_rate( report_rate Report_rate );
		int set_detach_kernel_driver( bool detach_kernel_driver );
		
		//getter functions
		mode get_mode();
		direction get_direction();
		int get_brightness();
		int get_speed();
		uint8_t get_color_r();
		uint8_t get_color_g();
		uint8_t get_color_b();
		bool get_rainbow();
		mode_variant get_variant();
		report_rate get_report_rate();
		bool get_detach_kernel_driver();
		
		//writer functions (apply settings to keyboard)
		int write_brightness(); // compatibility done 2 3
		int write_speed(); // compatibility done 2 3
		int write_mode(); // compatibility done 2 3
		int write_direction(); // compatibility done 2 3
		int write_color(); // compatibility done 2 3
		int write_custom(); // compatibility done 2 3
		int write_variant(); // compatibility done 2 3
		int write_report_rate(); // compatibility done 2 3
		int write_key_mapping();
		int write_active_profile();
		
		//helper functions
		int open_keyboard(); // open keyboard with default vid and pid
		int open_keyboard_bus_device( uint8_t bus, uint8_t device ); // open keyboard with bus and device id
		int close_keyboard();
		
		//loader functions (read settings from file)
		int load_custom( std::string File );
		int load_keymap( std::string File );
		
		//prints all valid keycodes
		int print_keycodes_led(); //for custom led pattern
		int print_keycodes_remap(); //physical keys for remapping
		int print_keycodes_options(); //remapping options
		
	private:
		
		bool _ajazzak33_compatibility = true;
		
		// profile (1-3): this changes the profile to which the settings
		// are applied
		int _profile = 1;
		
		// currently active profile
		int _active_profile = 1;
		
		//rgb control vars
		mode _mode = m_fixed;
		direction _direction;
		int _brightness;
		int _speed;
		uint8_t _color_r, _color_g, _color_b;
		bool _rainbow;
		mode_variant _variant;
		report_rate _report_rate;
		
		//min and max values
		const int _brightness_min = 0, _brightness_max = 9;
		const int _speed_min = 0, _speed_max = 3;
		
		//usb device vars
		const uint16_t _keyboard_vid = 0x0c45;
		const uint16_t _keyboard_pid = 0x652f;
		bool _detach_kernel_driver = true;
		bool _detached_driver_0 = false, _detached_driver_1 = false;
		libusb_device_handle* _handle = NULL;
		
		//usb data packets
		static uint8_t _data_start[];
		static uint8_t _data_end[];
		static uint8_t _data_settings[];
		static uint8_t _data_remap_1[];
		static uint8_t _data_remap_2[];
		static uint8_t _data_remap_3[];
		static uint8_t _data_remap_4[];
		static uint8_t _data_remap_5[];
		static uint8_t _data_remap_6[];
		static uint8_t _data_remap_7[];
		static uint8_t _data_remap_8[];
		static uint8_t _data_remap_9[];
		static uint8_t _data_remap_10[];
		static uint8_t _data_profile[];
		
		//stores key codes for custom colors
		std::map< std::string, std::array<uint8_t, 3> > _keycodes;
		//stores custom key colors
		std::map < std::string, std::array<uint8_t, 3> > _key_colors;
		
		//offsets for key remapping ( key → data positon ) ["string":[ [x,y], [x,y], [x,y] ]]
		//std::map < std::string, std::array< std::array<uint8_t, 2>, 3 > > _keymap_offsets;
		std::map < std::string, std::array< std::array<uint8_t, 2>, 3 > > _keymap_offsets;
		//keymap options (what a key can do when pressed)  ( option → code )
		std::map < std::string, std::array<uint8_t, 3> > _keymap_options;
		//stores current keymapping ( key → option)
		std::map < std::string, std::string > _keymap;
		
		// stores the usb packets for macros
		int _num_macro_packets = 0;
		uint8_t _data_macros[19][64];
};


/*#include "data.cpp"
#include "data_profile.cpp"
#include "setters.cpp"
#include "getters.cpp"
#include "writers.cpp"
#include "helpers.cpp"
#include "fileio.cpp"
#include "constructor.cpp"
#include "print_keycodes.cpp"
*/

#endif
