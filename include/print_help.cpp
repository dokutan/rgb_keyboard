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

#include "print_help.h"
#include <iostream>

void print_help(){
	std::cout << "This software controls the RGB lighting on some "
	"keyboards.\n";
	std::cout << "Licensed under the GNU GPL version 3 or later.\n\n";
	std::cout << "Options:\n";
	std::cout << "\t-h --help\t\tDisplays this message\n";
	std::cout << "\t-L --list-keys=arg\tList valid keynames (arg: led, map, option)\n";
	
	std::cout << "\n\t-p --profile=arg\tSet profile to which the settings are applied (1-3)\n";
	std::cout << "\t-a --active=arg\t\tSet currently active profile (1-3)\n";
	
	std::cout << "\n\t-c --color=color\t\tSets color of the current animation\n";
	std::cout << "\t-b --brightness=brightness\tSets brightness of the current animation.\n"
	"\t\tInteger from 0 to 9 (0-5 for AjazzAK33).\n";
	std::cout << "\t-s --speed=speed\t\tSets speed of the current animation.\n"
	"\t\tInteger from 0 to 3.\n";
	std::cout << "\t-d --direction=direction\tSets direction of the current animation.\n"
	"\t\t\"left\", \"right\", \"up\", \"down\", \"inwards\", \"outwards\".\n\n";
	
	std::cout << "\t-l --leds=arg\tSets the led mode (pattern), valid values are:\n";
	std::cout << "\t\tfixed, sine, rain, waterfall, vortex, swirl, breathing, breathing-color,\n";
	std::cout << "\t\treactive-ripple, reactive-single, reactive-horizontal, reactive-color,\n";
	std::cout << "\t\thorizontal-wave, vertical-wave, diagonal-wave, pulse, hurricane, ripple, custom, off\n";
	
	std::cout << "\t-v --variant=arg\tSets the variant of the reactive color mode, valid values are\n";
	std::cout << "\t\tred, yellow, green, blue\n";
	
	std::cout << "\n\t-P --custom-pattern=file\tSets pattern in custom mode\n";
	std::cout << "\t-K --custom-keys=keys\t\tSets pattern in custom mode\n";
	
	std::cout << "\n\t-R --report-rate=rate\tSets USB report rate (125, 250, 500, 1000) Hz\n";

	std::cout << "\n\t-M --keymap=file\tLoad keymap from specified file\n";
	
	std::cout << "\n\t-r --read\tRead and print stored settings from the keyboard (experimental)\n";
	
	std::cout << "\n\t-B --bus=number\t\tSpecify USB bus id, must be used with --device\n";
	std::cout << "\t-D --device=number\tSpecify USB device number, must be used with --bus\n";
	std::cout << "\t-k --kernel-driver\tDon't try to detach the kernel driver, required on some systems\n";
	std::cout << "\t-I --interface0\t\tDon't open usb interface 0\n";
	
	std::cout << "\n\t-A --ajazzak33\tEnable experimental support for the AjazzAK33\n";
	
	std::cout << "\nColors need to be specified in hexadecimal without "
	"any prefix (rrggbb).\n\"multi\" can also be used to create a rainbow effect.\n\n";
}
