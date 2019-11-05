# rgb_keyboard
Controls the RGB lighting on some keyboards. Only tested on Linux.

## Supported keyboards
USB keyboards with VID 0c45 and PID 652f. 
Tested with:
- Tecware Phantom RGB TKL
- Glorious GMMK full-size ANSI

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

### Manual
- Compile with:
    g++ rgb_keyboard.cpp -o rgb_keyboard -lusb-1.0
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

### Examples
    
    rgb_keyboard --brightness 5 --speed 2 --color 00ff00 --rain
to set a specific pattern.
    
    rgb_keyboard --custom-pattern example.conf
to set a custom pattern from a file.

### Config files

Each line line in the file consists of two fields separated by a tab. The first field is the key name (include/constructor.cpp for a full list), the second field is the color as hexcode without any prefix. Lines starting with # are ignored.

### Change custom key colors from the commandline

Similar to the config file, instead of a tab an equal sign and instead of a newline a semicolon is being used. Comments are not allowed. The string must end with a semicolon.

    rgb_keyboard --custom-keys "key_name=color;key_name=color;"

## TODO
- [x] Implemented all lighting modes from the official software.
- [x] Create option to change individual keys in custom mode.
- [ ] Rewrite the frontend (code is old and messy)
- [ ] Read current settings from the keyboard
