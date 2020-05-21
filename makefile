PREFIX = /usr
BIN_DIR = $(PREFIX)/bin
DOC_DIR = $(PREFIX)/share/doc
MAN_DIR = $(PREFIX)/share/man/man1
CC = g++

build: rgb_keyboard.o constructor.o fileio.o getters.o helpers.o print_help.o print_keycodes.o setters.o writers.o readers.o data.o
	$(CC) *.o -o rgb_keyboard -lusb-1.0 -Wall -Wextra -O2

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
	$(CC) -c include/data.cpp -Wall -Wextra -O2

constructor.o:
	$(CC) -c include/constructor.cpp -Wall -Wextra -O2

fileio.o:
	$(CC) -c include/fileio.cpp -Wall -Wextra -O2

getters.o:
	$(CC) -c include/getters.cpp -Wall -Wextra -O2

helpers.o:
	$(CC) -c include/helpers.cpp -Wall -Wextra -O2

print_help.o:
	$(CC) -c include/print_help.cpp -Wall -Wextra -O2

print_keycodes.o:
	$(CC) -c include/print_keycodes.cpp -Wall -Wextra -O2

setters.o:
	$(CC) -c include/setters.cpp -Wall -Wextra -O2

writers.o:
	$(CC) -c include/writers.cpp -Wall -Wextra -O2

rgb_keyboard.o:
	$(CC) -c rgb_keyboard.cpp -Wall -Wextra -O2

readers.o:
	$(CC) -c include/readers.cpp -Wall -Wextra -O2

