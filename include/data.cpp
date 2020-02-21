/*
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 3 of the License, or
 * (at your option) any later version.
 * 
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.	See the
 * GNU General Public License for more details.
 * 
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston,
 * MA 02110-1301, USA.
 * 
 */

//#include "rgb_keyboard.h"

//usb data packets

uint8_t rgb_keyboard::keyboard::_data_start[] =
	{ 0x04,	 0x01,	 0x00,	 0x01,	 0x00,	 0x00,	 0x00,	 0x00,
	0x00,	 0x00,	 0x00,	 0x00,	 0x00,	 0x00,	 0x00,	 0x00,
	0x00,	 0x00,	 0x00,	 0x00,	 0x00,	 0x00,	 0x00,	 0x00,
	0x00,	 0x00,	 0x00,	 0x00,	 0x00,	 0x00,	 0x00,	 0x00,
	0x00,	 0x00,	 0x00,	 0x00,	 0x00,	 0x00,	 0x00,	 0x00,
	0x00,	 0x00,	 0x00,	 0x00,	 0x00,	 0x00,	 0x00,	 0x00,
	0x00,	 0x00,	 0x00,	 0x00,	 0x00,	 0x00,	 0x00,	 0x00,
	0x00,	 0x00,	 0x00,	 0x00,	 0x00,	 0x00,	 0x00,	 0x00 };
	
uint8_t rgb_keyboard::keyboard::_data_end[] =
	{ 0x04,	 0x02,	 0x00,	 0x02,	 0x00,	 0x00,	 0x00,	 0x00,
	0x00,	 0x00,	 0x00,	 0x00,	 0x00,	 0x00,	 0x00,	 0x00,
	0x00,	 0x00,	 0x00,	 0x00,	 0x00,	 0x00,	 0x00,	 0x00,
	0x00,	 0x00,	 0x00,	 0x00,	 0x00,	 0x00,	 0x00,	 0x00,
	0x00,	 0x00,	 0x00,	 0x00,	 0x00,	 0x00,	 0x00,	 0x00,
	0x00,	 0x00,	 0x00,	 0x00,	 0x00,	 0x00,	 0x00,	 0x00,
	0x00,	 0x00,	 0x00,	 0x00,	 0x00,	 0x00,	 0x00,	 0x00,
	0x00,	 0x00,	 0x00,	 0x00,	 0x00,	 0x00,	 0x00,	 0x00 };

uint8_t rgb_keyboard::keyboard::_data_settings[] =
	{ 0x04,	 0x00,	 0x00,	 0x06,	 0x01,	 0x00,	 0x00,	 0x00,
	0x00,	 0x00,	 0x00,	 0x00,	 0x00,	 0x00,	 0x00,	 0x00,
	0x00,	 0x00,	 0x00,	 0x00,	 0x00,	 0x00,	 0x00,	 0x00,
	0x00,	 0x00,	 0x00,	 0x00,	 0x00,	 0x00,	 0x00,	 0x00,
	0x00,	 0x00,	 0x00,	 0x00,	 0x00,	 0x00,	 0x00,	 0x00,
	0x00,	 0x00,	 0x00,	 0x00,	 0x00,	 0x00,	 0x00,	 0x00,
	0x00,	 0x00,	 0x00,	 0x00,	 0x00,	 0x00,	 0x00,	 0x00,
	0x00,	 0x00,	 0x00,	 0x00,	 0x00,	 0x00,	 0x00,	 0x00 };
	
//key mapping data (ansi layout)
//
//uint8_t rgb_keyboard::keyboard::_data_remap_1[] = {
//0x04, 0x2a, 0x01, 0x0a, 0x10, 0x00, 0x00, 0x00,
//0xaa, 0x55, 0x10, 0x00, 0x00, 0x00, 0x01, 0x00,
//0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
//0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
//0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
//0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
//0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
//0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
//};
//
//uint8_t rgb_keyboard::keyboard::_data_remap_2[] = {
//0x04, 0xcd, 0x07, 0x08, 0x38, 0x00, 0x00, 0x00, /* ....8... */
//0x05, 0xa2, 0xa2, 0x02, 0x02, 0x29, 0x02, 0x02, /* .....).. */
//0x3a, 0x02, 0x02, 0x3b, 0x02, 0x02, 0x3c, 0x02, /* :..;..<. */
//0x02, 0x3d, 0x02, 0x02, 0x3e, 0x02, 0x02, 0x3f, /* .=..>..? */
//0x02, 0x02, 0x40, 0x02, 0x02, 0x41, 0x02, 0x02, /* ..@..A.. */
//0x42, 0x02, 0x02, 0x43, 0x02, 0x02, 0x44, 0x02, /* B..C..D. */
//0x02, 0x45, 0x03, 0xb6, 0x00, 0x03, 0xcd, 0x00, /* .E...... */
//0x03, 0xb5, 0x00, 0x05, 0xa2, 0x01, 0x02, 0x02  /* ........ */
//};
//
//uint8_t rgb_keyboard::keyboard::_data_remap_3[] = {
//0x04, 0x8b, 0x04, 0x08, 0x38, 0x38, 0x00, 0x00, /* ....88.. */
//0x35, 0x02, 0x02, 0x1e, 0x02, 0x02, 0x1f, 0x02, /* 5....... */
//0x02, 0x20, 0x02, 0x02, 0x21, 0x02, 0x02, 0x22, /* . ..!.." */
//0x02, 0x02, 0x23, 0x02, 0x02, 0x24, 0x02, 0x02, /* ..#..$.. */
//0x25, 0x02, 0x02, 0x26, 0x02, 0x02, 0x27, 0x02, /* %..&..'. */
//0x02, 0x2d, 0x02, 0x02, 0x2e, 0x02, 0x02, 0x53, /* .-.....S */
//0x02, 0x02, 0x54, 0x02, 0x02, 0x55, 0x05, 0xa2, /* ..T..U.. */
//0x02, 0x02, 0x02, 0x2b, 0x02, 0x02, 0x14, 0x02  /* ...+.... */
//};
//
//uint8_t rgb_keyboard::keyboard::_data_remap_4[] = {
//0x04, 0x2c, 0x04, 0x08, 0x38, 0x70, 0x00, 0x00, /* .,..8p.. */
//0x02, 0x1a, 0x02, 0x02, 0x08, 0x02, 0x02, 0x15, /* ........ */
//0x02, 0x02, 0x17, 0x02, 0x02, 0x1c, 0x02, 0x02, /* ........ */
//0x18, 0x02, 0x02, 0x0c, 0x02, 0x02, 0x12, 0x02, /* ........ */
//0x02, 0x13, 0x02, 0x02, 0x2f, 0x02, 0x02, 0x30, /* ..../..0 */
//0x02, 0x02, 0x5f, 0x02, 0x02, 0x60, 0x02, 0x02, /* .._..`.. */
//0x61, 0x05, 0xa2, 0x03, 0x02, 0x02, 0x39, 0x02, /* a.....9. */
//0x02, 0x04, 0x02, 0x02, 0x16, 0x02, 0x02, 0x07  /* ........ */
//};
//
//uint8_t rgb_keyboard::keyboard::_data_remap_5[] = {
//0x04, 0x2a, 0x04, 0x08, 0x38, 0xa8, 0x00, 0x00, /* .*..8... */
//0x02, 0x02, 0x09, 0x02, 0x02, 0x0a, 0x02, 0x02, /* ........ */
//0x0b, 0x02, 0x02, 0x0d, 0x02, 0x02, 0x0e, 0x02, /* ........ */
//0x02, 0x0f, 0x02, 0x02, 0x33, 0x02, 0x02, 0x34, /* ....3..4 */
//0x02, 0x02, 0x31, 0x02, 0x02, 0x5c, 0x02, 0x02, /* ..1..\.. */
//0x5d, 0x02, 0x02, 0x5e, 0x05, 0xa2, 0x04, 0x02, /* ]..^.... */
//0x01, 0x02, 0x02, 0x02, 0x1d, 0x02, 0x02, 0x1b, /* ........ */
//0x02, 0x02, 0x06, 0x02, 0x02, 0x19, 0x02, 0x02  /* ........ */
//};
//
//uint8_t rgb_keyboard::keyboard::_data_remap_6[] = {
//0x04, 0x11, 0x05, 0x08, 0x38, 0xe0, 0x00, 0x00, /* ....8... */
//0x05, 0x02, 0x02, 0x11, 0x02, 0x02, 0x10, 0x02, /* ........ */
//0x02, 0x36, 0x02, 0x02, 0x37, 0x02, 0x02, 0x38, /* .6..7..8 */
//0x02, 0x01, 0x20, 0x02, 0x02, 0x28, 0x02, 0x02, /* .. ..(.. */
//0x59, 0x02, 0x02, 0x5a, 0x02, 0x02, 0x5b, 0x05, /* Y..Z..[. */
//0xa2, 0x05, 0x02, 0x01, 0x01, 0x02, 0x01, 0x08, /* ........ */
//0x02, 0x01, 0x04, 0x02, 0x02, 0x2c, 0x02, 0x01, /* .....,.. */
//0x40, 0x05, 0x02, 0x02, 0x02, 0x02, 0x65, 0x02  /* @.....e. */
//};
//
//uint8_t rgb_keyboard::keyboard::_data_remap_7[] = {
//0x04, 0xdf, 0x06, 0x08, 0x38, 0x18, 0x01, 0x00, /* ....8... */
//0x01, 0x10, 0x02, 0x02, 0x50, 0x02, 0x02, 0x51, /* ....P..Q */
//0x02, 0x02, 0x52, 0x02, 0x02, 0x4f, 0x02, 0x02, /* ..R..O.. */
//0x2a, 0x02, 0x02, 0x62, 0x02, 0x02, 0x63, 0x02, /* *..b..c. */
//0x02, 0x58, 0x02, 0x02, 0x91, 0x02, 0x02, 0x90, /* .X...... */
//0x02, 0x01, 0x80, 0x02, 0x02, 0x64, 0x02, 0x02, /* .....d.. */
//0x46, 0x02, 0x02, 0x47, 0x02, 0x02, 0x48, 0x02, /* F..G..H. */
//0x02, 0x38, 0x02, 0x02, 0x49, 0x02, 0x02, 0x4a  /* .8..I..J */
//};
//
//uint8_t rgb_keyboard::keyboard::_data_remap_8[] = {
//0x04, 0xd7, 0x07, 0x08, 0x15, 0x50, 0x01, 0x00, /* .....P.. */
//0x02, 0x02, 0x4b, 0x02, 0x02, 0x4c, 0x02, 0x02, /* ..K..L.. */
//0x4d, 0x02, 0x02, 0x4e, 0x02, 0x02, 0x56, 0x02, /* M..N..V. */
//0x02, 0x57, 0x03, 0xe2, 0x00, 0x02, 0x63, 0x02, /* .W....c. */
//0x02, 0x58, 0x02, 0x02, 0x91, 0x02, 0x02, 0x90, /* .X...... */
//0x02, 0x01, 0x80, 0x02, 0x02, 0x64, 0x02, 0x02, /* .....d.. */
//0x46, 0x02, 0x02, 0x47, 0x02, 0x02, 0x48, 0x02, /* F..G..H. */
//0x02, 0x38, 0x02, 0x02, 0x49, 0x02, 0x02, 0x4a  /* .8..I..J */
//};
