CC=			gcc
CXX=			-Wall -Wextra
LIB=			-lncurses
SRC=			main.c
TARGET=			brighttui
PREFIX?=		/usr/local/bin
INSTALL?=		install
BIN=			bin

default:clean
	mkdir -p $(BIN)
	$(CC) $(CXX) $(SRC) -o $(BIN)/$(TARGET) $(LIB)

install: default
	$(INSTALL) -d $(PREFIX)
	$(INSTALL) -C $(BIN)/$(TARGET) $(PREFIX)
	echo "Installed brighttui"

uninstall: clean
	rm -rf $(PREFIX)/$(BIN)
	echo "Uninstalld brighttui "
clean:
	rm -rf $(BIN)
