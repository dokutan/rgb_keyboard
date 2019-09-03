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

#include <fstream>
#include <utility>

//loads custom pattern confifuration from a file
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
					_key_colors[value1] = val_rgb;
				}
			}
		}
	}
	
	return 0;
}
