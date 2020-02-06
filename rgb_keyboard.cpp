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
 * To compile run:
 * g++ rgb_keyboard.cpp -o rgb_keyboard -lusb-1.0
 * 
 */

#include <cstdio>
#include <cstdint>
#include <cstdlib>
#include <iostream>
#include <string>
#include <exception>
#include <regex>
#include <libusb-1.0/libusb.h>
#include <getopt.h>

#include "include/rgb_keyboard.h"
#include "include/print_help.cpp"

int main( int argc, char **argv ){
	
	using namespace std;
	
	//command line options
	static struct option long_options[] = {
		{"help", no_argument, 0, 'h'},
		{"color", required_argument, 0, 'c'},
		{"brightness", required_argument, 0, 'b'},
		{"speed", required_argument, 0, 's'},
		{"direction", required_argument, 0, 't'},
		{"sine", no_argument, 0, 'i'},
		{"rain", no_argument, 0, 'r'},
		{"waterfall", no_argument, 0, 'w'},
		{"vortex", no_argument, 0, 'v'},
		{"diagonal", no_argument, 0, 'd'},
		{"fixed", no_argument, 0, 'f'},
		{"swirl", no_argument, 0, 'l'},
		{"breathing", no_argument, 0, 'e'},
		{"breathing-color", no_argument, 0, 'a'},
		{"reactive-ripple", no_argument, 0, 'p'},
		{"reactive-single", no_argument, 0, 'g'},
		{"reactive-horizontal", no_argument, 0, 'o'},
		{"horizontal-wave", no_argument, 0, 'z'},
		{"vertical-wave", no_argument, 0, 'm'},
		{"pulse", no_argument, 0, 'u'},
		{"hurricane", no_argument, 0, 'n'},
		{"ripple", no_argument, 0, 'x'},
		{"reactive-color", required_argument, 0, 'y'},
		{"off", no_argument, 0, 'q'},
		{"custom", no_argument, 0, 'j'},
		//{"custom-clear", no_argument, 0, 'C'},
		{"custom-pattern", required_argument, 0, 'P'},
		{"custom-keys", required_argument, 0, 'K'},
		{"report-rate", required_argument, 0, 'R'},
		{"keymap", required_argument, 0, 'M'},
		{"list-keys", required_argument, 0, 'L'},
		{"bus", required_argument, 0, 'B'},
		{"device", required_argument, 0, 'D'},
		{"profile", required_argument, 0, 'O'},
		{"active", required_argument, 0, 'A'},
		{0, 0, 0, 0}
	};
	
	static int mode_flag = 0;
	static string variant;
	static bool color_flag = false;
	static string color;
	static bool brightness_flag = false;
	static string brightness;
	static bool speed_flag = false;
	static string speed;
	static bool direction_flag = false;
	static string direction;
	static string conf_file;
	static string bg_color;
	static string keys;
	static string r_rate;
	static bool r_rate_flag = false;
	static string keymap_file;
	static bool keymap_flag = false;
	static string list_keys_arg;
	static bool list_keys_flag = false;
	bool bus_flag = false, device_flag = false;
	string bus_string, device_string;
	bool active_flag = false;
	string active_string;
	bool profile_flag = false;
	string profile_string;
	
	//check commandline options
	if( argc == 1 ){
		print_help();
		return 0;
	}
	
	//parse command line options
	int c, option_index = 0;
	while( (c = getopt_long( argc, argv, "hc:b:s:t:irwvdfleapgozmunxy:qjP:K:R:M:L:B:D:O:A:",
	long_options, &option_index ) ) != -1 ){
		
		switch( c ){
			case 'h':
				print_help();
				return 0;
				break;
			case 'c':
				color_flag = true;
				color = optarg;
				break;
			case 'b':
				brightness_flag = true;
				brightness = optarg;
				break;
			case 's':
				speed_flag = true;
				speed = optarg;
				break;
			case 't':
				direction_flag = true;
				direction = optarg;
				break;
			case 'i':
				mode_flag = 'i';
				break;
			case 'r':
				mode_flag = 'r';
				break;
			case 'w':
				mode_flag = 'w';
				break;
			case 'v':
				mode_flag = 'v';
				break;
			case 'd':
				mode_flag = 'd';
				break;
			case 'f':
				mode_flag = 'f';
				break;
			case 'l':
				mode_flag = 'l';
				break;
			case 'e':
				mode_flag = 'e';
				break;
			case 'a':
				mode_flag = 'a';
				break;
			case 'p':
				mode_flag = 'p';
				break;
			case 'g':
				mode_flag = 'g';
				break;
			case 'o':
				mode_flag = 'o';
				break;
			case 'z':
				mode_flag = 'z';
				break;
			case 'm':
				mode_flag = 'm';
				break;
			case 'u':
				mode_flag = 'u';
				break;
			case 'n':
				mode_flag = 'n';
				break;
			case 'x':
				mode_flag = 'x';
				break;
			case 'y':
				mode_flag = 'y';
				variant = optarg;
				break;
			case 'q':
				mode_flag = 'q';
				break;
			case 'j':
				mode_flag = 'j';
				break;
			case 'P':
				mode_flag = 'P';
				conf_file = optarg;
				break;
			/*case 'C':
				mode_flag = 'C';
				break;*/
			case 'K':
				mode_flag = 'K';
				keys = optarg;
				break;
			case 'R':
				r_rate_flag = true;
				r_rate = optarg;
				break;
			case 'M':
				keymap_flag = true;
				keymap_file = optarg;
				break;
			case 'L':
				list_keys_flag = true;
				list_keys_arg = optarg;
				break;
			case 'B':
				bus_flag = true;
				bus_string = optarg;
				break;
			case 'D':
				device_flag = true;
				device_string = optarg;
				break;
			case 'O':
				profile_flag = true;
				profile_string = optarg;
				break;
			case 'A':
				active_flag = true;
				active_string = optarg;
				break;
			case '?':
				break;
			default:
				break;
		}
		
	}
	
	//keyboard object
	rgb_keyboard::keyboard kbd;
	
	//parse list keys flag
	if( list_keys_flag ){
		
		if( list_keys_arg == "led" || list_keys_arg == "custom" ){
			//list physical keys for custom led pattern
			std::cout << "Keynames for custom pattern:\n(Some keys might have multiple names)\n\n";
			kbd.print_keycodes_led();
		} else if( list_keys_arg == "map" || list_keys_arg == "keymap" ){
			//list physical keys for key remapping
			std::cout << "Keynames of physical keys for remapping:\n(Some keys might have multiple names)\n\n";
			kbd.print_keycodes_remap();
		} else if( list_keys_arg == "function" || list_keys_arg == "option" ){
			//list options for remapping
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
	
	
	try{
		
		//open keyboard
		if( bus_flag != device_flag ){ // only -B xor -D: error
			std::cerr << "--bus and --device must be used together\n";
			return 1;
		} else if( bus_flag && device_flag ){ // -B and -D
			
			// check -B and -D arguments
			if( std::regex_match( bus_string, std::regex("[0-9]+") ) && 
				std::regex_match( device_string, std::regex("[0-9]+") ) ){
				
				if( kbd.open_keyboard_bus_device( stoi(bus_string), stoi(device_string) ) != 0 ){
					std::cerr << "Could not open keyboard, check hardware and permissions.\n";
					return 1;
				}
			
			} else{
				std::cerr << "Wrong format for --bus and --device\n";
				return 1;
			}
			
		} else{ // open with default vid and pid
			if( kbd.open_keyboard() != 0 ){
				std::cerr << "Could not open keyboard, check hardware and permissions.\n";
				return 1;
			}
		}
		
		//parse active flag, set active profile
		if( active_flag ){
			
			if( std::regex_match( active_string, std::regex("[1-3]") ) ){
				kbd.set_active_profile( stoi( active_string) );
				kbd.write_active_profile();
			} else{
				std::cerr << "Invalid profile, expected 1-3\n";
				return 1;
			}
			
		}
		
		//parse profile flag, set profile
		if( profile_flag ){
			
			if( std::regex_match( profile_string, std::regex("[1-3]") ) ){
				kbd.set_profile( stoi( profile_string) );
			} else{
				std::cerr << "Invalid profile, expected 1-3\n";
				return 1;
			}
			
		}
		
		//parse mode flag
		switch( mode_flag ){
			case 'i':
				//set sine wave animation
				kbd.set_mode( rgb_keyboard::keyboard::m_sine );
				kbd.write_mode();
				break;
			case 'r':
				//set raindrop animation
				kbd.set_mode( rgb_keyboard::keyboard::m_rain );
				kbd.write_mode();
				break;
			case 'w':
				//set waterfall animation
				kbd.set_mode( rgb_keyboard::keyboard::m_waterfall );
				kbd.write_mode();
				break;
			case 'v':
				//set vortex animation
				kbd.set_mode( rgb_keyboard::keyboard::m_vortex );
				kbd.write_mode();
				break;
			case 'd':
				//set diagonal wave animation
				kbd.set_mode( rgb_keyboard::keyboard::m_diagonal_wave );
				kbd.write_mode();
				break;
			case 'f':
				//set fixed color
				kbd.set_mode( rgb_keyboard::keyboard::m_fixed );
				kbd.write_mode();
				break;
			case 'l':
				//set swirl animation
				kbd.set_mode( rgb_keyboard::keyboard::m_swirl );
				kbd.write_mode();
				break;
			case 'e':
				//set breathing animation
				kbd.set_mode( rgb_keyboard::keyboard::m_breathing );
				kbd.write_mode();
				break;
			case 'a':
				//set colorful breathing animation
				kbd.set_mode( rgb_keyboard::keyboard::m_breathing_color );
				kbd.write_mode();
				break;
			case 'p':
				//set reactive ripple animation
				kbd.set_mode( rgb_keyboard::keyboard::m_reactive_ripple );
				kbd.write_mode();
				break;
			case 'g':
				//set reactive single-key animation
				kbd.set_mode( rgb_keyboard::keyboard::m_reactive_single );
				kbd.write_mode();
				break;
			case 'o':
				//set reactive horizontal animation
				kbd.set_mode( rgb_keyboard::keyboard::m_reactive_horizontal );
				kbd.write_mode();
				break;
			case 'z':
				//set horizontal wave animation
				kbd.set_mode( rgb_keyboard::keyboard::m_horizontal_wave );
				kbd.write_mode();
				break;
			case 'm':
				//set vertical wave animation
				kbd.set_mode( rgb_keyboard::keyboard::m_vertical_wave );
				kbd.write_mode();
				break;
			case 'u':
				//set pulse wave animation
				kbd.set_mode( rgb_keyboard::keyboard::m_pulse );
				kbd.write_mode();
				break;
			case 'n':
				//set hurricane animation
				kbd.set_mode( rgb_keyboard::keyboard::m_hurricane );
				kbd.write_mode();
				break;
			case 'x':
				//set ripple animation
				kbd.set_mode( rgb_keyboard::keyboard::m_ripple );
				kbd.write_mode();
				break;
			case 'y':
				//set reactive color animation
				kbd.set_mode( rgb_keyboard::keyboard::m_reactive_color );
				if( variant == "red" ){
					kbd.set_variant( rgb_keyboard::keyboard::v_color_red );
					kbd.write_variant();
				} else if( variant == "yellow" ){
					kbd.set_variant( rgb_keyboard::keyboard::v_color_yellow );
					kbd.write_variant();
				} else if( variant == "green" ){
					kbd.set_variant( rgb_keyboard::keyboard::v_color_green );
					kbd.write_variant();
				} else if( variant == "blue" ){
					kbd.set_variant( rgb_keyboard::keyboard::v_color_blue );
					kbd.write_variant();
				} else if( variant == "none" ){
					// do not change variant
				} else{
					std::cerr << "Unknown variant for reactive-color.\n";
				}
				kbd.write_mode();
				break;
			case 'q':
				// turn leds off
				kbd.set_mode( rgb_keyboard::keyboard::m_off );
				kbd.write_mode();
				break;
			case 'j':
				//set custom mode
				kbd.set_mode( rgb_keyboard::keyboard::m_custom );
				kbd.write_mode();
				break;
			case 'P':
				//set custom pattern
				if( kbd.load_custom( conf_file ) == 0 ){
					kbd.set_mode( rgb_keyboard::keyboard::m_custom );
					kbd.write_custom();
					kbd.write_mode();
				} else{
					std::cerr << "Couldn't open custom pattern file.\n";
				}
				break;
			/*case 'C':
				//set and clear custom pattern
				///clear_custom();
				break;*/
			case 'K':
				//set custom pattern from string
				kbd.set_custom_keys( keys );
				kbd.set_mode( rgb_keyboard::keyboard::m_custom );
				kbd.write_custom();
				kbd.write_mode();
				break;
			default:
				break;
		}
		
		
		//parse color flag
		if( color_flag ){
			
			//set color
			if( color == "multi" ){ // multicolor
				kbd.set_rainbow( true );
				kbd.write_color();
			} else if( std::regex_match( color, std::regex("[0-9a-fA-F]{6}") ) ){ // normal color
				kbd.set_rainbow( false );
				kbd.set_color( stoi( color.substr(0,2), 0, 16 ), 
					stoi( color.substr(2,2), 0, 16 ),
					stoi( color.substr(4,2), 0, 16 ) );
				kbd.write_color();
			} else{ // wrong format
				std::cerr << "Wrong color format, expected rrggbb.\n";
			}
			
		}
		
		//parse brightness flag
		if( brightness_flag ){
			
			//set brightness
			if( std::regex_match( brightness, std::regex("[0-9]") ) ){
				kbd.set_brightness( stoi(brightness) );
				kbd.write_brightness();
			} else{
				std::cerr << "Wrong brightness format, expected 0-9.\n";
			}
			
		}
		
		//parse speed flag
		if( speed_flag ){
			
			//set speed
			if( std::regex_match( speed, std::regex("[0-3]") ) ){
				kbd.set_speed( stoi(speed) );
				kbd.write_speed();
			} else{
				std::cerr << "Wrong speed format, expected 0-3.\n";
			}
		}
		
		//parse direction flag
		if( direction_flag ){
			//set direction
			if( direction == "left" || direction == "up" || direction == "inwards" ){
				kbd.set_direction( rgb_keyboard::keyboard::d_left );
				kbd.write_direction();
			} else if( direction == "right" || direction == "down" || direction == "outwards" ){
				kbd.set_direction( rgb_keyboard::keyboard::d_right );
				kbd.write_direction();
			} else{
				std::cerr << "Unknown direction.\n";
			}
		}
		
		//parse report rate flag
		if( r_rate_flag ){
			//set report rate
			if( r_rate == "125" ){
				kbd.set_report_rate( rgb_keyboard::keyboard::r_125Hz );
				kbd.write_report_rate();
			} else if( r_rate == "250" ){
				kbd.set_report_rate( rgb_keyboard::keyboard::r_250Hz );
				kbd.write_report_rate();
			}  else if( r_rate == "500" ){
				kbd.set_report_rate( rgb_keyboard::keyboard::r_500Hz );
				kbd.write_report_rate();
			}  else if( r_rate == "1000" ){
				kbd.set_report_rate( rgb_keyboard::keyboard::r_1000Hz );
				kbd.write_report_rate();
			} else{
				std::cerr << "Unsupported report rate.\n";
			}
		}
		
		//parse keymap flag
		if( keymap_flag ){
			if( kbd.load_keymap( keymap_file ) == 0 ){
				kbd.write_key_mapping();
			} else{
				std::cerr << "Couldn't open keymap file.\n";
			}
		}
		
	}catch( std::exception &e ){
		std::cerr << "Caught exception: " << e.what() << "\n";
		kbd.close_keyboard();
		return 1;
	}
	
	kbd.close_keyboard();
	
	return 0;
}
