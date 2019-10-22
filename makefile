BIN_DIR = /usr/bin

install:
	g++ rgb_keyboard.cpp -o rgb_keyboard -lusb-1.0 && \
	cp ./rgb_keyboard $(BIN_DIR)/rgb_keyboard
	cp ./keyboard.rules /etc/udev/rules.d
