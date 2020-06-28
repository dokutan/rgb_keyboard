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

#include <cstdio>
#include <cstdint>
#include <cstdlib>
#include <iostream>
#include <iomanip>
#include <string>
#include <map>
#include <exception>
#include <regex>
#include <libusb-1.0/libusb.h>
#include <getopt.h>

#include "include/rgb_keyboard.h"
#include "include/print_help.h"

int main( int argc, char **argv ){
	
	using namespace std;
	
	// command line options
	static struct option long_options[] = {
		{"help", no_argument, 0, 'h'},
		{"color", required_argument, 0, 'c'},
		{"brightness", required_argument, 0, 'b'},
		{"speed", required_argument, 0, 's'},
		{"direction", required_argument, 0, 'd'},
		{"leds", required_argument, 0, 'l'},
		{"variant", required_argument, 0, 'v'},
		{"custom-pattern", required_argument, 0, 'P'},
		{"custom-keys", required_argument, 0, 'K'},
		{"report-rate", required_argument, 0, 'R'},
		{"keymap", required_argument, 0, 'M'},
		{"list-keys", required_argument, 0, 'L'},
		{"bus", required_argument, 0, 'B'},
		{"device", required_argument, 0, 'D'},
		{"profile", required_argument, 0, 'p'},
		{"active", required_argument, 0, 'a'},
		{"kernel-driver", no_argument, 0, 'k'},
		{"ajazzak33", no_argument, 0, 'A'},
		{"interface0", no_argument, 0, 'I'},
		{"read", no_argument, 0, 'r'},
		{0, 0, 0, 0}
	};
	
	// these variables store the commandline options
	bool flag_color = false;
	bool flag_brightness = false;
	bool flag_speed = false;
	bool flag_direction = false;
	bool flag_leds = false;
	bool flag_variant = false;
	bool flag_custom_pattern = false;
	bool flag_custom_keys = false;
	bool flag_report_rate = false;
	bool flag_keymap = false;
	bool flag_list_keys = false;
	bool flag_bus = false;
	bool flag_device = false;
	bool flag_profile = false;
	bool flag_active = false;
	bool flag_kernel_driver = false;
	bool flag_ajazzak33 = false;
	bool flag_interface0 = false;
	bool flag_read = false;
	
	string string_color;
	string string_brightness;
	string string_speed;
	string string_direction;
	string string_leds;
	string string_variant;
	string string_custom_pattern;
	string string_custom_keys;
	string string_report_rate;
	string string_keymap;
	string string_list_keys;
	string string_bus;
	string string_device;
	string string_active;
	string string_profile;
	
	// check number of commandline options
	if( argc == 1 ){
		print_help();
		return 0;
	}
	
	// parse command line options
	int c, option_index = 0;
	while( (c = getopt_long( argc, argv, "hc:b:s:d:l:v:P:K:R:M:L:B:D:p:a:kAIr",
	long_options, &option_index ) ) != -1 ){
		
		switch( c ){
			case 'h':
				print_help();
				return 0;
				break;
				
			case 'c':
				flag_color = true;
				string_color = optarg;
				break;
			case 'b':
				flag_brightness = true;
				string_brightness = optarg;
				break;
			case 's':
				flag_speed = true;
				string_speed = optarg;
				break;
			case 'd':
				flag_direction = true;
				string_direction = optarg;
				break;
			case 'l':
				flag_leds = true;
				string_leds = optarg;
				break;
			case 'v':
				flag_leds = true;
				string_leds = "reactive-color";
				flag_variant = true;
				string_variant = optarg;
				break;
				
			case 'P':
				flag_leds = true;
				string_leds = "custom";
				flag_custom_pattern = true;
				string_custom_pattern = optarg;
				break;
			case 'K':
				//flag_leds = true;
				//string_leds = "custom";
				flag_custom_keys = true;
				string_custom_keys = optarg;
				break;
				
			case 'R':
				flag_report_rate = true;
				string_report_rate = optarg;
				break;
			case 'M':
				flag_keymap = true;
				string_keymap = optarg;
				break;
			case 'L':
				flag_list_keys = true;
				string_list_keys = optarg;
				break;
				
			case 'B':
				flag_bus = true;
				string_bus = optarg;
				break;
			case 'D':
				flag_device = true;
				string_device = optarg;
				break;
				
			case 'p':
				flag_profile = true;
				string_profile = optarg;
				break;
			case 'a':
				flag_active = true;
				string_active = optarg;
				break;
				
			case 'k':
				flag_kernel_driver = true;
				break;
				
			case 'A':
				flag_ajazzak33 = true;
				break;
				
			case 'I':
				flag_interface0 = true;
				break;
				
			case 'r':
				flag_read = true;
				break;
				
			case '?':
				return 1;
				break;
			default:
				break;
		}
		
	}
	
	
	// keyboard object
	rgb_keyboard::keyboard kbd;
	
	// set compatbility mode
	if( flag_ajazzak33 ){
		kbd.set_ajazzak33_compatibility( true );
	}
	
	//parse list keys flag
	if( flag_list_keys ){
		
		if( string_list_keys == "led" || string_list_keys == "custom" ){
			// list physical keys for custom led pattern
			std::cout << "Keynames for custom pattern:\n(Some keys might have multiple names)\n\n";
			kbd.print_keycodes_led();
		} else if( string_list_keys == "map" || string_list_keys == "keymap" ){
			// list physical keys for key remapping
			std::cout << "Keynames of physical keys for remapping:\n(Some keys might have multiple names)\n\n";
			kbd.print_keycodes_remap();
		} else if( string_list_keys == "function" || string_list_keys == "option" ){
			// list options for remapping
			std::cout << "Options for key remapping:\n(Some options might have multiple names)\n\n";
			kbd.print_keycodes_options();
		} else{
			std::cout << "Valid options:\n";
			std::cout << "\"--list-keys led\" or \"--list-keys custom\"\n";
			std::cout << "\"--list-keys map\" or \"--list-keys keymap\"\n";
			std::cout << "\"--list-keys function\" or \"--list-keys option\"\n";
		}
		
		return 0;
	}
	
	// detach kernel driver ?
	if( flag_kernel_driver )
		kbd.set_detach_kernel_driver( false );
	
	// open interface 0 ?
	if( flag_interface0 )
		kbd.set_open_interface_0( false );
	
	// open keyboard, apply settigns, close keyboard
	try{
		
		// open keyboard
		if( flag_bus != flag_device ){ // only -B xor -D: error
			std::cerr << "--bus and --device must be used together\n";
			return 1;
		} else if( flag_bus && flag_device ){ // -B and -D
			
			// check -B and -D arguments
			if( std::regex_match( string_bus, std::regex("[0-9]+") ) && 
				std::regex_match( string_device, std::regex("[0-9]+") ) ){
				
				if( kbd.open_keyboard_bus_device( stoi(string_bus), stoi(string_device) ) != 0 ){
					std::cerr << "Could not open keyboard, check hardware and permissions.\nTry with or without the --kernel-driver option.\n";
					return 1;
				}
			
			} else{
				std::cerr << "Wrong format for --bus and --device\n";
				return 1;
			}
			
		} else{ // open with default vid and pid
			if( kbd.open_keyboard() != 0 ){
				std::cerr << "Could not open keyboard, check hardware and permissions.\nTry with or without the --kernel-driver option.\n";
				return 1;
			}
		}
		
		// read settings from keyboard
		if( flag_read && flag_ajazzak33 ){
			std::cout << "This feature is currently not supported for the Ajazz AK33\n";
			std::cout << "You can help to implement it by capturing USB communication, for more information open an issue on Github.\n";
		} else if( flag_read ){
			
			// a copy of the main kbd object, this prevents unintentional behaviour
			rgb_keyboard::keyboard kbd_in = kbd;
			
			std::cout << "This feature is experimental, not everything is read, please report bugs\n";
			
			// active profile
			kbd_in.read_active_profile();
			std::cout << "Active profile: " << kbd_in.get_active_profile() << "\n";
			
			// read settings
			kbd_in.read_led_settings();
			
			// iterate over profiles and print settings
			for( int i = 1; i < 4; i++ ){
				kbd_in.set_profile( i );
				std::cout << "\nProfile " << kbd_in.get_profile() << ":\n";
				
				// led mode
				std::cout << "Led mode: ";
				switch( kbd_in.get_mode() ){
					case rgb_keyboard::keyboard::m_horizontal_wave: std::cout << "horizontal-wave\n"; break;
					case rgb_keyboard::keyboard::m_pulse: std::cout << "pulse\n"; break;
					case rgb_keyboard::keyboard::m_hurricane: std::cout << "hurricane\n"; break;
					case rgb_keyboard::keyboard::m_breathing_color: std::cout << "breathing-color\n"; break;
					case rgb_keyboard::keyboard::m_breathing: std::cout << "breathing\n"; break;
					case rgb_keyboard::keyboard::m_fixed: std::cout << "fixed\n"; break;
					case rgb_keyboard::keyboard::m_reactive_single: std::cout << "reactive-single\n"; break;
					case rgb_keyboard::keyboard::m_reactive_ripple: std::cout << "reactive-ripple\n"; break;
					case rgb_keyboard::keyboard::m_reactive_horizontal: std::cout << "reactive-horizontal\n"; break;
					case rgb_keyboard::keyboard::m_waterfall: std::cout << "waterfall\n"; break;
					case rgb_keyboard::keyboard::m_swirl: std::cout << "swirl\n"; break;
					case rgb_keyboard::keyboard::m_vertical_wave: std::cout << "vertical-wave\n"; break;
					case rgb_keyboard::keyboard::m_sine: std::cout << "sine\n"; break;
					case rgb_keyboard::keyboard::m_vortex: std::cout << "vortex\n"; break;
					case rgb_keyboard::keyboard::m_rain: std::cout << "rain\n"; break;
					case rgb_keyboard::keyboard::m_diagonal_wave: std::cout << "diagonal-wave\n"; break;
					case rgb_keyboard::keyboard::m_reactive_color: std::cout << "reactive-color\n"; break;
					case rgb_keyboard::keyboard::m_ripple: std::cout << "ripple\n"; break;
					case rgb_keyboard::keyboard::m_off: std::cout << "off\n"; break;
					case rgb_keyboard::keyboard::m_custom: std::cout << "custom\n"; break;
					default: std::cout << "unknown\n"; break;
				}
				
				// reactive-color variant
				if( kbd_in.get_mode() == rgb_keyboard::keyboard::m_reactive_color ){
					
					std::cout << "Variant: ";
					switch( kbd_in.get_variant() ){
						case rgb_keyboard::keyboard::v_color_red: std::cout << "red\n"; break;
						case rgb_keyboard::keyboard::v_color_yellow: std::cout << "yellow\n"; break;
						case rgb_keyboard::keyboard::v_color_green: std::cout << "green\n"; break;
						case rgb_keyboard::keyboard::v_color_blue: std::cout << "blue\n"; break;
						default: std::cout << "unknown\n"; break;
					}
					
				}
				
				// direction
				if( kbd_in.get_direction() == rgb_keyboard::keyboard::d_left )
					std::cout << "Direction: left\n";
				else if( kbd_in.get_direction() == rgb_keyboard::keyboard::d_right )
					std::cout << "Direction: right\n";
				
				// color
				if( kbd_in.get_rainbow() ){
					std::cout << "Color: multi\n";
				} else{
					std::cout << "Color: ";
					std::cout << std::hex << std::setfill('0') << std::setw(2) << (int)kbd_in.get_color_r();
					std::cout << std::hex << std::setfill('0') << std::setw(2) << (int)kbd_in.get_color_g();
					std::cout << std::hex << std::setfill('0') << std::setw(2) << (int)kbd_in.get_color_b();
					std::cout << "\n" << std::dec << std::setfill(' ') << std::setw(0);
				}
				
				// brightness
				std::cout << "Brightness: " << kbd_in.get_brightness() << "\n";
				
				// speed
				std::cout << "Speed: " << kbd_in.get_speed() << "\n";
				
				// usb poll rate
				std::cout << "Report rate: ";
				if( kbd_in.get_report_rate() == rgb_keyboard::keyboard::r_125Hz )
					std::cout << "125 Hz\n";
				else if( kbd_in.get_report_rate() == rgb_keyboard::keyboard::r_250Hz )
					std::cout << "250 Hz\n";
				else if( kbd_in.get_report_rate() == rgb_keyboard::keyboard::r_500Hz )
					std::cout << "500 Hz\n";
				else if( kbd_in.get_report_rate() == rgb_keyboard::keyboard::r_1000Hz )
					std::cout << "1000 Hz\n";
				else
					std::cout << "unknown\n";
				
			}
			
		}
		
		// parse active flag, set active profile
		if( flag_active ){
			
			if( std::regex_match( string_active, std::regex("[1-3]") ) ){
				kbd.set_active_profile( stoi( string_active ) );
				kbd.write_active_profile();
			} else{
				std::cerr << "Invalid profile, expected 1-3\n";
				kbd.close_keyboard();
				return 1;
			}
			
		}
		
		
		// parse profile flag, set profile (to which profile settings are applied)
		if( flag_profile ){
			
			if( std::regex_match( string_profile, std::regex("[1-3]") ) ){
				kbd.set_profile( stoi( string_profile ) );
			} else{
				std::cerr << "Invalid profile, expected 1-3\n";
				kbd.close_keyboard();
				return 1;
			}
			
		}
		
		// parse leds flag, set led pattern
		if( flag_leds ){
			
			map< string, rgb_keyboard::keyboard::mode > mode_list{
				{ "fixed", rgb_keyboard::keyboard::m_fixed },
				{ "sine", rgb_keyboard::keyboard::m_sine },
				{ "rain", rgb_keyboard::keyboard::m_rain },
				{ "waterfall", rgb_keyboard::keyboard::m_waterfall },
				{ "vortex", rgb_keyboard::keyboard::m_vortex },
				{ "swirl", rgb_keyboard::keyboard::m_swirl },
				{ "breathing", rgb_keyboard::keyboard::m_breathing },
				{ "breathing-color", rgb_keyboard::keyboard::m_breathing_color },
				{ "reactive-ripple", rgb_keyboard::keyboard::m_reactive_ripple },
				{ "reactive-single", rgb_keyboard::keyboard::m_reactive_single },
				{ "reactive-horizontal", rgb_keyboard::keyboard::m_reactive_horizontal },
				{ "reactive-color", rgb_keyboard::keyboard::m_reactive_color },
				{ "horizontal-wave", rgb_keyboard::keyboard::m_horizontal_wave },
				{ "vertical-wave", rgb_keyboard::keyboard::m_vertical_wave },
				{ "diagonal-wave", rgb_keyboard::keyboard::m_diagonal_wave },
				{ "pulse", rgb_keyboard::keyboard::m_pulse },
				{ "hurricane", rgb_keyboard::keyboard::m_hurricane },
				{ "ripple", rgb_keyboard::keyboard::m_ripple },
				{ "custom", rgb_keyboard::keyboard::m_custom },
				{ "off", rgb_keyboard::keyboard::m_off }
			};
			
			if( mode_list.find( string_leds ) != mode_list.end() ){
				
				// parse variant flag (variant for reactive-color)
				if( flag_variant ){
					
					if( string_variant == "red" ){
						kbd.set_variant( rgb_keyboard::keyboard::v_color_red );
					} else if( string_variant == "yellow" ){
						kbd.set_variant( rgb_keyboard::keyboard::v_color_yellow );
					} else if( string_variant == "green" ){
						kbd.set_variant( rgb_keyboard::keyboard::v_color_green );
					} else if( string_variant == "blue" ){
						kbd.set_variant( rgb_keyboard::keyboard::v_color_blue );
					} else{
						std::cerr << "Unknown variant for reactive-color.\n";
						kbd.close_keyboard();
						return 1;
					}
					
					kbd.write_variant();
				}
				
				// parse custom pattern flag
				if( flag_custom_pattern ){
					
					//set custom pattern
					if( kbd.load_custom( string_custom_pattern ) == 0 ){
						kbd.write_custom();
					} else{
						std::cerr << "Couldn't open custom pattern file.\n";
					}
					
				}
				
				// write led pattern
				kbd.set_mode( mode_list.at( string_leds ) );
				kbd.write_mode();
				
			} else{
				std::cerr << "Unknown led pattern\n";
				kbd.close_keyboard();
				return 1;
			}
			
		}
		
		
		// parse custom keys flag
		if( flag_custom_keys ){
			
			kbd.set_custom_keys( string_custom_keys );
			kbd.write_custom();
			
		}
					
		
		//parse color flag
		if( flag_color ){
			
			//set color
			if( string_color == "multi" ){ // multicolor
				kbd.set_rainbow( true );
				kbd.write_color();
			} else if( std::regex_match( string_color, std::regex("[0-9a-fA-F]{6}") ) ){ // normal color
				kbd.set_rainbow( false );
				kbd.set_color( stoi( string_color.substr(0,2), 0, 16 ), 
					stoi( string_color.substr(2,2), 0, 16 ),
					stoi( string_color.substr(4,2), 0, 16 ) );
				kbd.write_color();
			} else{ // wrong format
				std::cerr << "Wrong color format, expected rrggbb or multi.\n";
				kbd.close_keyboard();
				return 1;
			}
			
		}
		
		
		//parse brightness flag
		if( flag_brightness ){
			
			//set brightness
			if( std::regex_match( string_brightness, std::regex("[0-9]") ) ){
				
				if( kbd.set_brightness( stoi(string_brightness) ) == 0 ){
					kbd.write_brightness();
				} else{
					std::cerr << "Wrong brightness format, expected 0-9 (0-5 for AjazzAK33).\n";
					kbd.close_keyboard();
					return 1;
				}
				
			} else{
				std::cerr << "Wrong brightness format, expected 0-9 (0-5 for AjazzAK33).\n";
				kbd.close_keyboard();
				return 1;
			}
			
		}
		
		
		//parse speed flag
		if( flag_speed ){
			
			//set speed
			if( std::regex_match( string_speed, std::regex("[0-3]") ) ){
				kbd.set_speed( stoi(string_speed) );
				kbd.write_speed();
			} else{
				std::cerr << "Wrong speed format, expected 0-3.\n";
				kbd.close_keyboard();
				return 1;
			}
		}
		
		
		//parse direction flag
		if( flag_direction ){
			//set direction
			if( string_direction == "left" || string_direction == "up" || string_direction == "inwards" ){
				kbd.set_direction( rgb_keyboard::keyboard::d_left );
				kbd.write_direction();
			} else if( string_direction == "right" || string_direction == "down" || string_direction == "outwards" ){
				kbd.set_direction( rgb_keyboard::keyboard::d_right );
				kbd.write_direction();
			} else{
				std::cerr << "Unknown direction.\n";
				kbd.close_keyboard();
				return 1;
			}
		}
		
		
		//parse report rate flag
		if( flag_report_rate ){
			//set report rate
			if( string_report_rate == "125" ){
				kbd.set_report_rate( rgb_keyboard::keyboard::r_125Hz );
				kbd.write_report_rate();
			} else if( string_report_rate == "250" ){
				kbd.set_report_rate( rgb_keyboard::keyboard::r_250Hz );
				kbd.write_report_rate();
			}  else if( string_report_rate == "500" ){
				kbd.set_report_rate( rgb_keyboard::keyboard::r_500Hz );
				kbd.write_report_rate();
			}  else if( string_report_rate == "1000" ){
				kbd.set_report_rate( rgb_keyboard::keyboard::r_1000Hz );
				kbd.write_report_rate();
			} else{
				std::cerr << "Unsupported report rate.\n";
				kbd.close_keyboard();
				return 1;
			}
		}
		
		
		//parse keymap flag
		if( flag_keymap && !flag_ajazzak33 ){
			
			// ask user for confirmation?
			std::cout << "Remapping the keys is experimental and potentially dangerous.\n";
			std::cout << "On ISO-layout boards and on the Ajazz AK33 this has been reported to mess up all keys.\n";
			std::cout << "You can help to improve it by capturing USB communication, for more information open an issue on Github.\n";
			std::cout << "If you accept the risk of permanent damage to the keyboard, type YES and press enter to continue.\n";
			std::cout << "Anything else will cancel this process.\n";
			
			std::string user_input;
			std::cin >> user_input;
			
			if( user_input == "YES" ){
				if( kbd.load_keymap( string_keymap ) == 0 ){
					kbd.write_key_mapping_ansi();
				} else{
					std::cerr << "Couldn't open keymap file.\n";
					kbd.close_keyboard();
					return 1;
				}
			} else{
				std::cout << "Not remapping the keys.\n";
			}
		}
		
	// catch exception
	}catch( std::exception &e ){
		std::cerr << "Caught exception: " << e.what() << "\n";
		kbd.close_keyboard();
		return 1;
	}
	
	// close keyboard
	kbd.close_keyboard();
	
	return 0;
}
