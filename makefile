BIN_DIR = /usr/bin
CC = g++

build: rgb_keyboard.o constructor.o fileio.o getters.o helpers.o print_help.o print_keycodes.o setters.o writers.o
	g++ *.o -o rgb_keyboard -lusb-1.0 -Wall -Wextra -O2

install:
	cp ./rgb_keyboard $(BIN_DIR)/rgb_keyboard
	cp ./keyboard.rules /etc/udev/rules.d

uninstall:
	rm $(BIN_DIR)/rgb_keyboard && \
	rm /etc/udev/rules.d/keyboard.rules

clean:
	rm ./rgb_keyboard *.o

upgrade: build
	cp ./rgb_keyboard $(BIN_DIR)/rgb_keyboard


# individual .cpp files
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
