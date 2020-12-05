# rgb_keyboard
Controls the RGB lighting on some keyboards. Tested on Linux and FreeBSD, should work on other operating systems.

**Disclaimer: This software is not supported by the manufacturer of the hardware in any way, and relies completely on information from reverse-engineering. There is no warranty, especially in case of damage to the hardware.**

- [Supported keyboards](#supported-keyboards)
- [Installing](#installing)
	- [Linux](#linux)
	- [FreeBSD](#freebsd)
- [Usage](#usage)
	- [Profiles](#profiles)
	- [Examples](#examples)
	- [Config files](#config-files-key-mapping-and-color)
	- [Change custom key colors from the commandline](#change-custom-key-colors-from-the-commandline)
	- [--bus and --device options](#--bus-and---device-options)
	- [--kernel-driver option](#--kernel-driver-option)
	- [--interface0 option](#--interface0-option)
	- [--ajazzak33 option](#--ajazzak33-option)
- [GUI](#gui)
- [TODO](#todo)
- [License](#license)

## Supported keyboards
USB keyboards with VID 0x0c45, maybe others.

Name | PID | Tested | Notes
---|---|---|---
Tecware Phantom RGB TKL | 0x652f | Yes |
Glorious GMMK full-size ANSI and TKL ANSI | 0x652f | Yes |
Ajazz AK33 | 0x7903 | Yes | requires the ``--ajazzak33`` option
Redragon K550 Yama | 0x5204 | Yes | requires the ``--ajazzak33`` option
Redragon K556 Devarajas | 0x5004 | Yes | requires the ``--ajazzak33`` option
Redragon K552 Kumara | 0x5104 | No |
Warrior Kane TC235 | 0x8520 | No |

You can help to expand this list by providing information whether this software works correctly or not.

### Known issues that require your help (please open an issue or pull request if you want to contribute):
- **Remapping keys on the Ajazz AK33 and ISO boards is broken (all keys are shifted around)**
- Setting the color of the ISO international key (Int_Key) in custom pattern mode is supported but not tested.
- Setting the USB report/poll rate on the Ajazz AK33 is untested
- Custom led patterns don't work correctly on the Redragon K550 Yama and K556 Devarajas

## Installing
- Clone this repository or download a release
```
git clone https://github.com/dokutan/rgb_keyboard
cd ./rgb_keyboard
```
- Make sure you have [libusb](https://libusb.info/) installed (on some distros (e.g. Ubuntu) you might need a dev package)

### Linux
- compile and copy everything to the right place with (not required: replace the 4 with the number of cpu cores you have)
```
make -j4
sudo make install
```
- restart for the udev rule to take effect (without this you probably won't be able to use this softwate without root)

### FreeBSD
- install pkgconf
- compile with
```
make CC=clang++ -j4
```

- copy ``rgb_keyboard`` to some directory in your $PATH, or execute it directly with
```
./rgb_keyboard
```

- Current limitations on FreeBSD:
	- You need root privileges to use the program
	- After the program has finished, the keyboard won't work and needs to be unplugged and plugged back in.

## Usage

```
rgb_keyboard --help
```
to see all options

```
rgb_keyboard --list-keys arg
```
to see all keynames (arg = led, map, option)

For the gui see the appropriate section below

### Profiles

Three individual profiles (1-3) are stored on the keyboard. Examples:

```
rgb_keyboard --active 2
```
to change to the second profile.

```
rgb_keyboard --profile 3 ⟨further options⟩
```
to apply settings to profile 3. Without this option profile 1 is used.

### Examples

```
rgb_keyboard --brightness 5 --speed 2 --color 00ff00 --leds rain
```
to set a specific pattern.

```
rgb_keyboard --custom-pattern example.conf
```
to set a custom pattern from a file.

```
rgb_keyboard --keymap example.keymap
```
to set a custom keymap from a file.

### Config files (Key mapping and color)
Take a look at example.conf and example.keymap.

### Change custom key colors from the commandline

Similar to the config file, instead of a tab an equal sign and instead of a newline a semicolon is being used. Comments are not allowed. The string must end with a semicolon.

```
rgb_keyboard --custom-keys "key_name=color;key_name=color;"
```

### --bus and --device options

In case you have multiple keyboards attached or you suspect a keyboard with a different vendor id or product id might be compatible, the keyboard can also be opened by specifying the bus number and device id. These can be found by running lsusb.
```
rgb_keyboard --bus ⟨bus id⟩ --device ⟨device number⟩ ...
```

### --kernel-driver option
On some systems libusb might no be able to properly detach the kernel driver, and the program will fail to open the keyboard. The --kernel-driver option skips this step and is intended for better compatibility.

### --interface0 option
Don't open usb interface 0 on the keyboard. This allows input to happen while settings are applied, and is primarily intended for scripting purposes. Because compatibility is untested, this needs to be specifically enabled with this option.

### --ajazzak33 option
This is required for the Ajazz AK33 keyboard, as it uses a slightly different method of transmitting data.

## GUI

A separate frontend written in Tcl/Tk exists, however not all features are implemented. Running the gui:
```
chmod +x rgb_keyboard-gui.tcl
./rgb_keyboard-gui.tcl
```
The gui is not copied to /usr/bin by default, you can do so manually.

## TODO
[TODO.md](https://github.com/dokutan/rgb_keyboard/blob/master/TODO.md)

## License
This program is free software; you can redistribute it and/or modify it under the terms of the GNU General Public License as published by the Free Software Foundation; either version 3 of the License, or (at your option) any later version.

