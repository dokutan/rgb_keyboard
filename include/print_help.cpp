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

#include <iostream>

//prints a help message
void print_help(){
	std::cout << "This software controls the RGB lighting on some "
	"keyboards.\n";
	std::cout << "Licensed under the GNU GPL version 3 or later.\n\n";
	std::cout << "Options:\n";
	std::cout << "\t-h --help\tDisplays this message\n";
	std::cout << "\t-L --list-keys=arg\tList valid keynames (arg: led, map, option)\n";
	
	std::cout << "\n\t-A --active=arg\tSet currently active profile (1-3)\n";
	
	std::cout << "\n\t-c --color=color\tSets color of the current animation\n";
	std::cout << "\t-b --brightness=brightness\tSets brightness of the current animation.\n"
	"\t\tInteger from 0 to 9.\n";
	std::cout << "\t-s --speed=speed\tSets speed of the current animation.\n"
	"\t\tInteger from 0 to 3.\n";
	std::cout << "\t-t --direction=direction\tSets direction of the current animation.\n"
	"\t\t\"left\", \"right\", \"up\", \"down\", \"inwards\", \"outwards\".\n\n";
	
	std::cout << "\t-f --fixed\tSets a fixed color\n";
	std::cout << "\t-i --sine\tSets a sine wave animation\n";
	std::cout << "\t-r --rain\tSets a raindrop animation\n";
	std::cout << "\t-w --waterfall\tSets a waterfall animation\n";
	std::cout << "\t-v --vortex\tSets a vortex animation\n";
	std::cout << "\t-l --swirl\tSets a swirl animation\n";
	std::cout << "\t-d --diagonal\tSets a diagonal wave animation\n";
	std::cout << "\t-e --breathing\tSets a breathing animation\n";
	std::cout << "\t-a --breathing-color\tSets a colorful breathing animation\n";
	std::cout << "\t-p --reactive-ripple\tSets a reactive ripple animation\n";
	std::cout << "\t-g --reactive-single\tSets a reactive single-key animation\n";
	std::cout << "\t-o --reactive-horizontal\tSets a reactive horizontal animation\n";
	std::cout << "\t-z --horizontal-wave\tSets a horizontal wave animation\n";
	std::cout << "\t-m --vertical-wave\tSets a vertical wave animation\n";
	std::cout << "\t-u --pulse\tSets a pulse wave animation\n";
	std::cout << "\t-n --hurricane\tSets a hurricane animation\n";
	std::cout << "\t-x --ripple\tSets a ripple animation\n";
	std::cout << "\t-y --reactive-color=variant\tSets a reactive color animation.\n"
	"\t\"red\", \"yellow\", \"green\", \"blue\", \"none\" (doesn't change color).\n";
	std::cout << "\t-q --off\tTurn all leds off\n";
	
	std::cout << "\n\t-j --custom\tEnables custom mode\n";
	//std::cout << "\t--custom-clear\tEnables custom mode and clears pattern\n";
	std::cout << "\t-P --custom-pattern=file\tSets pattern in custom mode\n";
	std::cout << "\t-K --custom-keys=keys\tSets pattern in custom mode\n";
	
	std::cout << "\n\t-R --report-rate=rate\tSets USB report rate (125, 250, 500, 1000) Hz\n";

	std::cout << "\n\t-M --keymap=file\tLoad keymap from specified file\n";
	
	std::cout << "\n\t-D --bus=number\tSpecify USB bus id, must be used with --device\n";
	std::cout << "\t-D --device=number\tSpecify USB device number, must be used with --bus\n";
	
	std::cout << "\nColors need to be specified in hexadecimal without "
	"any prefix.\n\"multi\" can also be used to create a rainbow effect.\n\n";
}
