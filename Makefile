CC=gcc
CFLAGS=-Wall -Wextra -pedantic
BIN=./run
TRASH=$(BIN) *.o *.so
RAYLIB=`pkg-config --cflags --libs raylib`
LIBS=-lm

main: noise.o main.c
	$(CC) $(CFLAGS) -o $(BIN) main.c $(RAYLIB) $(LIBS) noise.o

noise.o: noise.c
	$(CC) $(CFLAGS) -o noise.o -c noise.c $(RAYLIB) $(LIBS)

clean:
	rm -rf $(TRASH)
