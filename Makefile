CC = gcc
CFLAGS = -Wall -pedantic -O -std=c99
LDLIBS = -lm

HEAD := $(wildcard *.h)
SRCS := $(wildcard *.c)

all: spirals/tiffReader.o
	$(CC) -o main spirals/tiffReader.o

primeSpiralsTiff.o:
	$(CC) $(CFLAGS) -c $(LDLIBS) spirals/primeSpiralsTiff.c

tiffReader.o:
	$(CC) $(CFLAGS) -c $(LDLIBS) spirals/tiffReader.c


