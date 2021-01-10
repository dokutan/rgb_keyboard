PREFIX = /usr
BIN_DIR = $(PREFIX)/bin
DOC_DIR = $(PREFIX)/share/doc
MAN_DIR = $(PREFIX)/share/man/man1
CC = g++
CC_FLAGS = -Wall -Wextra -O2

build: rgb_keyboard.o constructor.o fileio.o getters.o helpers.o print_help.o print_keycodes.o setters.o writers.o readers.o data.o macro.o functions.o
	$(CC) *.o -o rgb_keyboard -lusb-1.0 $(CC_FLAGS)

install:
	cp ./rgb_keyboard $(BIN_DIR)/rgb_keyboard
	cp ./keyboard.rules /etc/udev/rules.d
	mkdir $(DOC_DIR)/rgb_keyboard | true
	cp ./examples/example.conf $(DOC_DIR)/rgb_keyboard/
	cp ./examples/example.keymap $(DOC_DIR)/rgb_keyboard/
	cp ./README.md $(DOC_DIR)/rgb_keyboard/
	cp ./rgb_keyboard.1 $(MAN_DIR)/

uninstall:
	rm $(BIN_DIR)/rgb_keyboard
	rm /etc/udev/rules.d/keyboard.rules
	rm -rf $(DOC_DIR)/rgb_keyboard
	rm -f $(MAN_DIR)/rgb_keyboard.1

clean:
	rm ./rgb_keyboard *.o

# individual .cpp files
data.o:
	$(CC) -c include/data.cpp -Wall $(CC_FLAGS)

constructor.o:
	$(CC) -c include/constructor.cpp $(CC_FLAGS)

fileio.o:
	$(CC) -c include/fileio.cpp $(CC_FLAGS)

getters.o:
	$(CC) -c include/getters.cpp $(CC_FLAGS)

helpers.o:
	$(CC) -c include/helpers.cpp $(CC_FLAGS)

print_help.o:
	$(CC) -c include/print_help.cpp $(CC_FLAGS)

print_keycodes.o:
	$(CC) -c include/print_keycodes.cpp $(CC_FLAGS)

setters.o:
	$(CC) -c include/setters.cpp $(CC_FLAGS)

writers.o:
	$(CC) -c include/writers.cpp $(CC_FLAGS)

rgb_keyboard.o:
	$(CC) -c rgb_keyboard.cpp $(CC_FLAGS)

readers.o:
	$(CC) -c include/readers.cpp $(CC_FLAGS)

macro.o:
	$(CC) -c include/macro.cpp $(CC_FLAGS)

functions.o:
	$(CC) -c include/functions.cpp $(CC_FLAGS)
