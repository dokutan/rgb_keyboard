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

#ifndef PRINT_HELP
#define PRINT_HELP

/// Prints the help message (usage information)
void print_help() {

	std::cout <<
		R"(This software controls the RGB lighting on some keyboards.
Licensed under the GNU GPL version 3 or later.

Options:
    -h --help           Displays this message
    -L --list-keys=arg  List valid keynames (arg: led, map, option)
    -p --profile=arg     Set profile to which the settings are applied
						Integer from 1 to 3.
    -a --active=arg     Set currently active profile (1-3)
    -c --color=color    Sets color of the current animation
    -b --brightness=arg Sets brightness of the current animation.
                        Integer from 0 to 9 (0-5 for AjazzAK33).
    -s --speed=arg      Sets speed of the current animation.
                        Integer from 0 to 3.
    -d --direction=arg  Sets direction of the current animation.
                        left, right, up, down, inwards, outwards
    -l --leds=arg       Sets the led mode (pattern), valid values are:
                        off, fixed, sine, rain, waterfall, vortex, swirl,
                        breathing, breathing-color,    reactive-ripple,
                        reactive-single, reactive-horizontal,
                        reactive-color,    horizontal-wave, vertical-wave,
                        diagonal-wave, pulse, hurricane, ripple, custom
    -v --variant=arg    Sets the variant of the reactive color mode,
                        valid values are: red, yellow, green, blue
    -P --custom-pattern=arg     Sets pattern in custom mode
    -K --custom-keys=arg        Sets pattern in custom mode
    -R --report-rate=arg        Sets USB report rate in Hz
                                125, 250, 500, 1000
    -M --keymap=arg     Load keymap from specified file
    -r --read           Read and print stored settings from the keyboard
    -B --bus=arg        Specify USB bus id, must be used with -D
    -D --device=arg     Specify USB device number, must be used with -B
    -k --kernel-driver  Don't try to detach the kernel driver
    -I --interface0     Don't open usb interface 0
    -C --control=arg    Manually enable or disable control transfer mode
                        true, false

Colors need to be specified in hexadecimal without any prefix (rrggbb).
multi can also be used to create a rainbow effect.
)";
}

#endif
