### Manual compiling
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
