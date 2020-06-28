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

//macro class
#ifndef RGB_KEYBOARD_MACRO
#define RGB_KEYBOARD_MACRO

#include <array>
#include <string>

namespace rgb_keyboard{
	class macro;
}

/**
 * This class represents an individual macro.
 * 
 * A macro consists of a sequence of key up/down actions with their
 * respective delays and a number of times the sequence should be repeated
 * 
 */
class rgb_keyboard::macro{
	
	public:
		
		/// Type of macro action: key up or key down
		enum action_type{
			t_up,
			t_down
		};
		
		/// The maximum amount of actions in a macro, TODO!
		static const unsigned int max_actions = 10;
		/// The maximum delay value
		static const unsigned int max_delay = 40000;
		
		/// Reset macro to default values
		void clear();
		
		/** Append an action
		 * \return 0 if successful, 1 if unsuccessful
		 */
		int append_action( action_type type, std::string key, unsigned int delay );
		
		/** Get an action
		 * \param number The number of the action to get
		 * \return 0 if successful, 1 if unsuccessful
		 */
		int get_action( unsigned int number, action_type& type, std::string& key, unsigned int& delay );
		
		/// Get the number of actions
		unsigned int get_number_of_actions();
		
		
		/** Set the number of repeats
		 * 0 will be interpreted as 1
		 */
		void set_repeats( uint8_t repeats );
		
		/// Get the number of repeats
		uint8_t get_repeats();
		
	private:
		
		/// The number of repeats for this macro
		uint8_t _repeats = 1;
		/// The number of actions for this macro
		unsigned int _num_actions = 0;
		
		/// The action type for all actions
		std::array< action_type, max_actions > _actions;
		/// The key for all actions
		std::array< std::string, max_actions > _keys;
		/// The delay for all actions
		std::array< unsigned int, max_actions > _delays;
};

#endif
