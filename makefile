PREFIX = /usr
BIN_DIR = $(PREFIX)/bin
DOC_DIR = $(PREFIX)/share/doc
MAN_DIR = $(PREFIX)/share/man/man1
CXX = g++
CXXFLAGS = -Wall -Wextra -O2 -std=c++11

build: rgb_keyboard.o constructor.o fileio.o getters.o helpers.o print_keycodes.o setters.o writers.o readers.o data.o macro.o functions.o
	$(CXX) *.o -o rgb_keyboard -lusb-1.0 $(CXXFLAGS)

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

format:
	clang-format -i --style=file include/* *.cpp

# individual .cpp files
data.o:
	$(CXX) -c include/data.cpp -Wall $(CXXFLAGS)

constructor.o:
	$(CXX) -c include/constructor.cpp $(CXXFLAGS)

fileio.o:
	$(CXX) -c include/fileio.cpp $(CXXFLAGS)

getters.o:
	$(CXX) -c include/getters.cpp $(CXXFLAGS)

helpers.o:
	$(CXX) -c include/helpers.cpp $(CXXFLAGS)

print_keycodes.o:
	$(CXX) -c include/print_keycodes.cpp $(CXXFLAGS)

setters.o:
	$(CXX) -c include/setters.cpp $(CXXFLAGS)

writers.o:
	$(CXX) -c include/writers.cpp $(CXXFLAGS)

rgb_keyboard.o:
	$(CXX) -c rgb_keyboard.cpp $(CXXFLAGS)

readers.o:
	$(CXX) -c include/readers.cpp $(CXXFLAGS)

macro.o:
	$(CXX) -c include/macro.cpp $(CXXFLAGS)

functions.o:
	$(CXX) -c include/functions.cpp $(CXXFLAGS)
