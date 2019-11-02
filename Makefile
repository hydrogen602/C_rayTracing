CC = gcc
CFLAGS = -Wall -pedantic -O -std=c99
LDLIBS = -lm

HEAD := $(wildcard *.h)
SRCS := $(wildcard *.c)

all: spirals/tiffReader.o
	$(CC) -o main spirals/tiffReader.o

tiffReader.o: spirals/tiffReader.c spirals/tiffReader.h header.h
	$(CC) $(CFLAGS) -c $(LDLIBS) spirals/tiffReader.c


