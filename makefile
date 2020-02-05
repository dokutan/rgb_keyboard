BIN_DIR = /usr/bin

install:
	g++ rgb_keyboard.cpp -o rgb_keyboard -lusb-1.0 -Wall -O2 && \
	cp ./rgb_keyboard $(BIN_DIR)/rgb_keyboard
	cp ./keyboard.rules /etc/udev/rules.d

uninstall:
	rm $(BIN_DIR)/rgb_keyboard && \
	rm /etc/udev/rules.d/keyboard.rules

clean:
	rm ./rgb_keyboard

upgrade:
	g++ rgb_keyboard.cpp -o rgb_keyboard -lusb-1.0 && \
	cp ./rgb_keyboard $(BIN_DIR)/rgb_keyboard
