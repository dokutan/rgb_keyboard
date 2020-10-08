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
#include <deque>
//#include <assert.h>

#include "macro.h"

namespace rgb_keyboard{
	class keyboard;
}

/**
 * This class represents the keyboard.
 *
 * The keyboard has 3 profiles with independent settings, all settings are stored on the keyboard.
 * To change the settings on the keyboard, the general procedure is as follows:
 *
 * 1. Open the keyboard with open_keyboard() or open_keyboard_bus_device()
 * 2. Call set_*() or load_*() to change the private variables of this class. The setter functions set the setting for \_profile (=1 by default), therefore to change the settings for a different profile call set_profile() first.
 * 3. Call write\_*() to apply the settings to the keyboard
 * 4. Close the keyboard with close_keyboard()
 *
 * To obtain the current settings from the keyboard:
 * 1. Open the keyboard
 * 2. Call read_*() to read the settings from the keyboard
 * 3. Call get_*() to get the state of the private variables
 * 4. Close the keyboard
 * 
 * Due to legacy reasons, the get_*, set_* and most write_* functions act on
 * the profile indicated by _profile (1 by default).
 */
class rgb_keyboard::keyboard{
	
	public:
		
		/// The different led modes
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
		
		/// The directions for animated led patterns
		enum direction{
			d_undefined,
			d_left = 1,
			d_right = 2,
			d_up = 1,
			d_down = 2,
			d_inwards = 1,
			d_outwards = 2
		};
		
		/// The variants for the reactive_color led mode
		enum mode_variant{
			v_undefined,
			v_color_red,
			v_color_yellow,
			v_color_green,
			v_color_blue
		};
		
		/// The available USB poll rates
		enum report_rate{
			r_125Hz,
			r_250Hz,
			r_500Hz,
			r_1000Hz
		};
		
		/// Constructor, sets default settings
		keyboard();
		
		//setter functions: set values for current _profile
		/** Enable/disable Ajazz AK33 compatibility mode.
		 * This changes the way data is send, the USB PID, the maximum brightness, etc.
		 */
		int set_ajazzak33_compatibility( bool compatibility );
		/** Set the profile to which settings are applied with set_*()
		 * \param profile 1-3
		 * \return 0 if successful, 1 if invalid argument
		 */
		int set_profile( int profile );
		/** Set the profile that is active on the keyboard
		 * \param profile 1-3
		 * \return 0 if successful, 1 if invalid argument
		 * \see write_active_profile()
		 */	
		int set_active_profile( int profile );
		/// Set the led mode
		int set_mode( mode Mode );
		/// Set the led pattern direction
		int set_direction( direction Direction );
		/// Set the led brightness
		int set_brightness( int Brightness );
		/// Set the led animation speed
		int set_speed( int Speed );
		/// Set the led color
		int set_color( uint8_t Color_r, uint8_t Color_g, uint8_t Color_b );
		/// Enables/disables rainbow/multicolor mode
		int set_rainbow( bool Rainbow );
		/// Set the variant of the reactive_color led mode
		int set_variant( mode_variant Variant );
		/// Set custom color of individual keys
		int set_custom_keys( std::string Keys );
		/// Set the USB poll rate
		int set_report_rate( report_rate Report_rate );
		/// Set whether to detach the kernel driver for the keyboard
		int set_detach_kernel_driver( bool detach_kernel_driver );
		/// Set whether to open USB interface 0
		int set_open_interface_0( bool open_interface_0 );
		
		//getter functions
		/// LED mode getter
		mode get_mode();
		/// LED animation direction getter
		direction get_direction();
		/// LED brightness getter
		int get_brightness();
		/// LED animation speed getter
		int get_speed();
		/// Color (red component) getter
		uint8_t get_color_r();
		/// Color (green component) getter
		uint8_t get_color_g();
		/// Color (blue component) getter
		uint8_t get_color_b();
		/// LED multicolor mode getter
		bool get_rainbow();
		/// LED rective_color variant getter
		mode_variant get_variant();
		/// USB poll rate getter
		report_rate get_report_rate();
		/// Get whether to detach the kernel driver
		bool get_detach_kernel_driver();
		/// Get whether to open usb interface 0 driver
		bool get_open_interface_0();
		/// Active profile getter
		int get_active_profile();
		/// Get profile to which settings are applied
		int get_profile();
		/// Get whether Ajazz AK33 compatibility is enabled
		bool get_ajazzak33_compatibility();
		
		//writer functions (apply settings to keyboard)
		/// Write the brightness to the keyboard
		int write_brightness();
		/// Write the LED animation speed to the keyboard
		int write_speed();
		/// Write the LED mode to the keyboard
		int write_mode();
		/// Write the LED animation direction to the keyboard
		int write_direction();
		/// Write the LED color to the keyboard
		int write_color();
		/// Write the custom LED pattern to the keyboard
		int write_custom();
		/// Write the reactive_color variant to the keyboard
		int write_variant();
		/// Write the USB poll rate to the keyboard
		int write_report_rate();
		/// Write the keymapping to the keyboard, (ANSI layout only)
		int write_key_mapping_ansi();
		/// Write the active profile to the keyboard
		int write_active_profile();
		
		//reader functions
		/// Read the active profile from the keyboard
		int read_active_profile();
		/** Read the LED settings from the keyboard
		 * These are LED mode, brightness, color, speed, direction,
		 * reactive_color variant and the usb poll rate
		 */
		int read_led_settings();
		
		//helper functions
		/** Initialize libusb and open keyboard by USB VID and USB PID
		 * \see _keyboard_vid
		 * \see _keyboard_pid
		 * \return 0 if successful
		 */
		int open_keyboard();
		/** Initialize libusb and open keyboard with bus number and device id
		 * \return 0 if successful
		 */
		int open_keyboard_bus_device( uint8_t bus, uint8_t device );
		/// Close the keyboard and libusb
		int close_keyboard();
		
		//loader functions (read settings from file)
		/** Load custom led pattern from the specified file
		 * \return 0 if successful
		 * \see write_custom()
		 */
		int load_custom( std::string File );
		/** Load keymap from the specified file
		 * \return 0 if successful
		 */
		int load_keymap( std::string File );
		
		//prints all valid keycodes
		/// Print all valid key names for custom led patterns to stdout
		int print_keycodes_led();
		/// Print all valid key names for key remapping to stdout
		int print_keycodes_remap();
		/// Print all valid options for key remapping to stdout
		int print_keycodes_options();
		
	private:
		
		/// Wrapper around libusb for sending data
		int _write_data( unsigned char* data, int length );
		
		/** If this is variable is set to true, usb control transfers are used for sending data.
		 *  This enables compatibility with other keyboards (Ajazz AK 33).
		 */
		bool _ajazzak33_compatibility = false;
		
		/// Profile (1-3): this determines the profile to which the settings are applied
		int _profile;
		
		/// Currently active profile
		int _active_profile;
		
		// rgb control vars
		/// LED mode
		std::array< mode, 3 > _mode;
		/// LED animation direction
		std::array< direction, 3 > _direction;
		/// LED brightness
		std::array< int, 3 > _brightness;
		/// LED animation direction
		std::array< int, 3 > _speed;
		/// LED color (red component)
		std::array< uint8_t, 3 > _color_r;
		/// LED color (green component)
		std::array< uint8_t, 3 > _color_g;
		/// LED color (blue component)
		std::array< uint8_t, 3 > _color_b;
		/// LED multicolor status
		std::array< bool, 3 > _rainbow;
		/// Variant for the reactive color LED mode
		std::array< mode_variant, 3 > _variant;
		/// USB poll rate
		std::array< report_rate, 3 > _report_rate;
		
		//min and max values
		/// Minimum value for brightness
		const int _brightness_min = 0;
		/// Maximum value for brightness for the Ajazz AK 33
		const int _brightness_max_ajazzak33 = 5;
		/// Maximum value for brightness for keyboards except the Ajazz AK 33
		const int _brightness_max_others = 9;
		/// Maximum value for brightness (this is not constant, the Ajazz AK33 has a different value)
		int _brightness_max = _brightness_max_others;
		/// Minimum led pattern animation speed
		const int _speed_min = 0;
		/// Maximum led pattern animation speed
		const int _speed_max = 3;
		
		
		//usb device vars
		/// USB vendor id
		const uint16_t _keyboard_vid = 0x0c45;
		
		// TODO! rewrite this
		/// USB product id for the Ajazz AK33
		std::vector< uint16_t > _keyboard_pid_ajazzak33 = { 0x7903, 0x5204, 0x5104, 0x5004, 0x8520 };
		/** USB product ids for other keyboards
		 * Tecware Phantom, GMMK = 0x652f
		 * Redragon K550 Yama = 0x5204
		 * Redragon K552 Kumara = 0x5104
		 * Redragon K556 Devarajas = 0x5004
		 * Warrior Kane TC235 = 0x8520
		 */
		std::vector< uint16_t > _keyboard_pid_others = { 0x5204, 0x5104, 0x5004, 0x8520, 0x652f };
		/// USB product id, this is not constant as the Ajazz AK33 has a different PID
		std::vector< uint16_t > _keyboard_pid = _keyboard_pid_others;
		
		/// If true, try to detach the kernel driver when opening the keyboard
		bool _detach_kernel_driver = true;
		
		/// Detached  kernel driver? → for attaching after being done
		bool _detached_driver_0 = false;
		/// Detached  kernel driver? → for attaching after being done
		bool _detached_driver_1 = false;
		
		/// Try to open usb interface 0 ?
		bool _open_interface_0 = true;
		
		/// libusb device handle
		libusb_device_handle* _handle = NULL;
		
		
		//usb data packets
		static uint8_t _data_start[64];
		static uint8_t _data_end[64];
		static uint8_t _data_settings[64];
		static uint8_t _data_remap_1[64];
		static uint8_t _data_remap_2[64];
		static uint8_t _data_remap_3[64];
		static uint8_t _data_remap_4[64];
		static uint8_t _data_remap_5[64];
		static uint8_t _data_remap_6[64];
		static uint8_t _data_remap_7[64];
		static uint8_t _data_remap_8[64];
		static uint8_t _data_remap_9[64];
		static uint8_t _data_remap_10[64];
		static uint8_t _data_profile[64];
		static uint8_t _data_macros[64];
		static uint8_t _data_read[64];
		
		/// Stores the key names for custom key colors
		static std::map< std::string, std::array<uint8_t, 3> > _keycodes;
		/// Stores custom key colors
		std::array< std::map < std::string, std::array<uint8_t, 3> >, 3> _key_colors;
		
		/// Offsets for key remapping ( key → data positon ) ["string":[ [x,y], [x,y], [x,y] ]]
		static std::map < std::string, std::array< std::array<uint8_t, 2>, 3 > > _keymap_offsets;
		/// Keymap options (what a key can do when pressed)  ( option → code )
		static std::map < std::string, std::array<uint8_t, 3> > _keymap_options;
		/// Stores current keymapping ( key → option)
		std::array< std::map < std::string, std::string >, 3> _keymap;
		
		/// All macros
		std::array< rgb_keyboard::macro, 100 > _macros;
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
