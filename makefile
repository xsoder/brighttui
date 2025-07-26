CC=				gcc
CXX=			-Wall -Wextra
LIB=			-lncurses
SRC=			brighttui.c
TARGET=			brighttui
PREFIX?=		/usr/local/bin
INSTALL?=		install

default:clean
	$(CC) $(CXX) $(SRC) -o $(TARGET) $(LIB)

install: default
	$(INSTALL) -d $(PREFIX)
	$(INSTALL) -C $(BIN)/$(TARGET) $(PREFIX)

uninstall: clean
	rm -rf $(PREFIX)/$(TARGET)
	echo "Uninstalld brighttui"
clean:
	rm -rf $(TARGET)
