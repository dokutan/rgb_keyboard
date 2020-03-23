# rgb_keyboard
Controls the RGB lighting on some keyboards. Tested on Linux, should work on other operating systems.

**Disclaimer: This software is not supported by the manufacturer of the hardware in any way, and relies completely on information from reverse-engineering. There is no warranty, especially in case of damage to the hardware.**

## Supported keyboards
USB keyboards with VID 0x0c45 and PID 0x652f.
Tested with:
- Tecware Phantom RGB TKL
- Glorious GMMK full-size ANSI

You can help expand this list by providing information whether this software works correctly or not.

Note on ISO layout: As i do not have access to a compatible keyboard with an ISO layout, ~~remapping and~~ setting the color of the ISO international key (Int_Key) is supported but not tested. Remapping is reported as being broken, it is required to capture the USB communication on an affected keyboard to fix this. Therefore if you are affected and capable of doing this, you can help with this issue.

## Installing
- Clone this repository
```
git clone https://github.com/dokutan/rgb_keyboard
cd ./rgb_keyboard
```
- Make sure you have [libusb](https://libusb.info/) installed (on some distros you might need a dev package)

### Automated (recommended)
- compile and copy everything to the right place with (not required: replace the 4 with the number of cpu cores you have)
```
make -j4
sudo make install
```
- restart for the udev rule to take effect (without this you probably won't be able to use this softwate without root)

### Updating
- If you have a previous version installed and want to upgrade (this will not add the udev rule), clone the repository and run:
```
make
sudo make upgrade
```

### Manual
- Compile with:
```
g++ -c include/constructor.cpp include/fileio.cpp include/getters.cpp include/helpers.cpp include/print_help.cpp include/print_keycodes.cpp include/setters.cpp include/writers.cpp rgb_keyboard.cpp -Wall -Wextra -O2
g++ *.o -Wall -Wextra -O2 -lusb-1.0 -o rgb_keyboard
```
- (Optionally) add the binary to some place in your PATH variable
- IMPORTANT: make the keyboard accessible without root rights by adding a udev rule
  - create a file named 'keyboard.rules' in /etc/udev/rules.d/
  - add the following lines to the file and restart afterwards
```
SUBSYSTEM=="usb", ATTRS{idVendor}=="0c45", ATTRS{idProduct}=="652f", MODE:="0666"
SUBSYSTEM=="usb_device", ATTRS{idVendor}=="0c45", ATTRS{idProduct}=="652f", MODE:="0666"
```

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

### --ajazzak33 option

This enables experimental support for the AjazzAK33 Keyboard.

## GUI

A separate frontend written in Tcl/Tk exists, however not all features are implemented. Running the gui:
```
chmod +x rgb_keyboard-gui.tcl
./rgb_keyboard-gui.tcl
```
The gui is not copied to /usr/bin by default, you can do so manually.

## TODO
- [x] Implemented all lighting modes from the official software.
- [x] Create option to change individual keys in custom mode.
- [x] Rewrite the frontend (code is old and messy) (improved and cleaned up, changed options)
- [ ] Read current settings from the keyboard
- [x] Add reprogramming and macro functionality
  - [x] Complete reprogramming
  - [ ] Add macros to reprogramming
- [x] Complete profile support
- [ ] Add a manpage

# License
This program is free software; you can redistribute it and/or modify it under the terms of the GNU General Public License as published by the Free Software Foundation; either version 3 of the License, or (at your option) any later version.

