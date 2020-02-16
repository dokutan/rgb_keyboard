# rgb_keyboard
Controls the RGB lighting on some keyboards. Tested on Linux, should work on other operating systems.

## Supported keyboards
USB keyboards with VID 0c45 and PID 652f. 
Tested with:
- Tecware Phantom RGB TKL
- Glorious GMMK full-size ANSI

You can help expand this list by providing information whether this software works correctly or not.

Note on ISO layout: As i do not have access to a compatible keyboard with an ISO layout, remapping and setting the color of the ISO international key (Int_Key) is supported but not tested.

## Installing
- Clone this repository
    ```
    git clone https://github.com/dokutan/rgb_keyboard
    cd ./rgb_keyboard
    ```
- Make sure you have [libusb](https://libusb.info/) installed (on some distros you might need a dev package)

### Automated (recommended)
- compile and copy everything to the right place with
    ```
    sudo make install
    ```
- restart for the udev rule to take effect

### Updating
- If you have a previous version installed and want to upgrade (this will not add the udev rule), clone the repository and run:
	```
    sudo make upgrade
    ```

### Manual
- Compile with:
    ``g++ rgb_keyboard.cpp -o rgb_keyboard -lusb-1.0 -Wall -O2``
- (Optionally) add the binary to some place in your PATH variable
- IMPORTANT: make the keyboard accessible without root rights by adding a udev rule
  - create a file named 'keyboard.rules' in /etc/udev/rules.d/
  - add the following lines to the file and restart afterwards
  ```
  SUBSYSTEM=="usb", ATTRS{idVendor}=="0c45", ATTRS{idProduct}=="652f", MODE:="0666"
  SUBSYSTEM=="usb_device", ATTRS{idVendor}=="0c45", ATTRS{idProduct}=="652f", MODE:="0666"
  ```

## Usage
    rgb_keyboard --help
to see all options

    rgb_keyboard --list-keys arg
to see all keynames (arg = led, map, option)

For the gui see the appropriate section below

### Profiles

Three individual profiles (1-3) are stored on the keyboard. Examples:

    rgb_keyboard --active 2
to change to the second profile.

    rgb_keyboard --profile 3 ⟨further options⟩
to apply settings to profile 3. Without this option profile 1 is used.

### Examples
    
    rgb_keyboard --brightness 5 --speed 2 --color 00ff00 --rain
to set a specific pattern.
    
    rgb_keyboard --custom-pattern example.conf
to set a custom pattern from a file.

    rgb_keyboard --keymap example.keymap
to set a custom keymap from a file.

### Config files (Key mapping and color)

Each line line in the file consists of two fields separated by a tab. The first field is the key name (include/constructor.cpp for a full list), the second field is the color as hexcode without any prefix. Lines starting with # are ignored.

### Change custom key colors from the commandline

Similar to the config file, instead of a tab an equal sign and instead of a newline a semicolon is being used. Comments are not allowed. The string must end with a semicolon.

    rgb_keyboard --custom-keys "key_name=color;key_name=color;"

### --bus and --device options

In case you have multiple keyboards attached or you suspect a keyboard with a different vendor id or product id might be compatible, the keyboard can also be opened by specifying the bus number and device id. These can be found by running lsusb.

```
rgb_keyboard --bus ⟨bus id⟩ --device ⟨device number⟩ ...
```

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
- [x] Rewrite the frontend (code is old and messy) (improved and cleaned up)
- [ ] Read current settings from the keyboard
- [x] Add reprogramming and macro functionality
  - [x] Complete reprogramming
  - [ ] Add macros to reprogramming
- [x] Complete profile support
