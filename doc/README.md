This file will contain a description of the usb protocol used.

# Basic information

The individual data packets send to the keyboard have a length of 64 bytes + 64 bytes of usb header (this can be ignored, they show up as length 128 in wireshark though).
Data is written to usb endpoint 3, and read from usb endpoint 2. After each write, 64 bytes must be read.

To set some property on the keyboard, first a start packet (_data_start) is send, this packet starts with 0x04 0x01 0x00 0x01 and the rest are zeroes.
The next step are some packets for the specific property. Depending on the specific setting, the number of these packets varies.
To finish the process the _data_send packet is written (containing 0x04 0x02 0x00 0x02, rest zeroes).

The data packets can be found in include/data*.cpp.

## Example
This is a piece from write_brightness() (include/writers.cpp), that shows the whole process.

```
//write start data packet to endpoint 3
	res += libusb_interrupt_transfer( _handle, 0x03, _data_start,	64, &transferred, 1000);
	
	//read from endpoint 2
	res += libusb_interrupt_transfer( _handle, 0x82, buffer, 64, &transferred, 1000);
	
	//write brightness data packet to endpoint 3
	res += libusb_interrupt_transfer( _handle, 0x03, data_settings, 64, &transferred, 1000);
	
	//read from endpoint 2
	res += libusb_interrupt_transfer( _handle, 0x82, buffer, 64, &transferred, 1000);
	
	//write end data packet to endpoint 3
	res += libusb_interrupt_transfer( _handle, 0x03, _data_end, 64, &transferred, 1000);
	
	//read from endpoint 2
	res += libusb_interrupt_transfer( _handle, 0x82, buffer, 64, &transferred, 1000);
  ```
  
