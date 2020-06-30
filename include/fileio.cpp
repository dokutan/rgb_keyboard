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

#include <fstream>
#include <utility>

//loads custom pattern configuration from a file
int rgb_keyboard::keyboard::load_custom( std::string File ){
	
	//open file
	std::ifstream config_in( File );
	if( !config_in.is_open() ){
		return 1;
	}
	
	//process file
	std::string value1 = "";
	std::string value2 = "";
	uint8_t val_r = 0, val_g = 0, val_b = 0;
	std::array<uint8_t, 3> val_rgb;
	std::size_t position = 0;
	
	for( std::string line; std::getline(config_in, line); ){
		//process individual line
		if( line.length() != 0 ){
			if( line[0] != '#' ){
				position = 0;
				position = line.find("\t", position);
				value1 = line.substr(0, position);
				value2 = line.substr(position+1);
													
				//store values in map
				if( value2.length() == 6 ){
					val_r = stoi( value2.substr(0,2), 0, 16 );
					val_g = stoi( value2.substr(2,2), 0, 16 );
					val_b = stoi( value2.substr(4,2), 0, 16 );
					val_rgb = { val_r, val_g, val_b };
					_key_colors[_profile-1][value1] = val_rgb;
				}
			}
		}
	}
	
	return 0;
}

//loads keymap from file
int rgb_keyboard::keyboard::load_keymap( std::string File ){
	
	//open file
	std::ifstream config_in( File );
	if( !config_in.is_open() ){
		return 1;
	}
	
	
	// read file
	std::string line, current_section = "";
	while( std::getline(config_in, line) ){
		
		// is empty?
		if( line.length() == 0 )
			continue;
		
		// is comment?
		if( line[0] == ';' || line[0] == '#' )
			continue;
		
		// remove whitespace
		line = std::regex_replace( line, std::regex("[[:space:]]"), "" );
		
		// section header?
		if( std::regex_match( line, std::regex("\\[[[:print:]]+\\]") ) ){
			current_section = std::regex_replace( line, std::regex("[\\[\\]]"), "" );
			continue;
		}
		
		// is section == keymap
		if( current_section == "keymap" ){
			
			// key=value ?
			if( std::regex_match( line, std::regex("[[:print:]]+=[[:print:]]+") ) ){
				_keymap[_profile-1].emplace( std::regex_replace( line, std::regex("=[[:print:]]+"), "" ),
					std::regex_replace( line, std::regex("[[:print:]]+="), "" ) );
			}
			
		// is section a macro definition ?
		} else if( std::regex_match( current_section, std::regex("macro[0-9]+") ) ){
			
			// get number of macro
			std::string macroname = current_section;
			int macronumber = std::stoi( macroname.erase(0, 5) );
			
			// number of repeats ?
			if( std::regex_match( line, std::regex("repeat=[0-9]+") ) ){
				uint8_t repeats = std::stoi( std::regex_replace( line, std::regex("repeat="), "" ) );
				_macros.at(macronumber).set_repeats( repeats );
				continue;
			}
			
			// invalid macro command? → continue
			if( !std::regex_match( line, std::regex("[[:print:]]+=[[:print:]]+=[[:print:]]+") ) )
				continue;
			
			// extract individual parts of the macro command
			std::string type_string = std::regex_replace( line, std::regex("=[[:print:]]+=[[:print:]]+"), "" );
			rgb_keyboard::macro::action_type type;
			
			std::string key = std::regex_replace( line, std::regex("[[:print:]]+?="), "", std::regex_constants::format_first_only );
			key = std::regex_replace( key, std::regex("=[[:print:]]+"), "" );
			
			int delay = std::stoi( std::regex_replace( line, std::regex("[[:print:]]+=[[:print:]]+="), "" ) );
			
			// determine action type
			if( type_string == "up" )
				type = rgb_keyboard::macro::t_up;
			else if( type_string == "down" )
				type = rgb_keyboard::macro::t_down;
			else
				continue;
			
			// check for range of macronumber, store macro command
			if( macronumber <= 100 && macronumber >= 1 )
				_macros.at(macronumber).append_action( type, key, delay );
			
		}
		
	}
	
	return 0;
}
