CC=gcc
CFLAGS=-Wall -Wextra -pedantic
BIN=./run
TRASH=$(BIN) *.o *.so
RAYLIB=`pkg-config --cflags --libs raylib`
LIBS=-lm


main: main.c
	$(CC) $(CFLAGS) -o $(BIN) main.c $(RAYLIB) $(LIBS)

clean:
	rm -rf $(TRASH)
