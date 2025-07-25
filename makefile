CC=gcc
CXX=-Wall -Wextra
LIB=-lncurses -lX11 -lXrandr
SRC=main.c
BIN=brighttui

default:clean
	$(CC) $(CXX) $(SRC) -o $(BIN) $(LIB)

clean:
	rm -rf $(BIN)
