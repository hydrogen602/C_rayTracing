CC = gcc
CFLAGS = -Wall -pedantic -O -std=c99
#LDLIBS = -lm

all: spirals/tiffReader.o
	$(CC) -o main spirals/tiffReader.o

spirals/tiffReader.o: spirals/tiffReader.c spirals/tiffReader.h header.h
	echo "compiling!"
	$(CC) $(CFLAGS) -c spirals/tiffReader.c  

# add $(LDLIBS) for math


