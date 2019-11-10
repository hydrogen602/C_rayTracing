CC = gcc
CFLAGS = -Wall -pedantic -O -std=c99
LDLIBS = -lm
# add $(LDLIBS) for math

all: dataTypes/dColor.o dataTypes/ray.o dataTypes/sphere.o dataTypes/vect3.o array.o main.o
	$(CC) -o main dataTypes/dColor.o dataTypes/ray.o dataTypes/sphere.o dataTypes/vect3.o array.o main.o

dataTypes/dColor.o: dataTypes/dColor.c header.h dataTypes/dColor.h
	$(CC) $(CFLAGS) $(LDLIBS) -c dataTypes/dColor.c -o dataTypes/dColor.o

dataTypes/ray.o: dataTypes/ray.c header.h dataTypes/ray.h dataTypes/sphere.h dataTypes/dColor.h dataTypes/rayHit.h dataTypes/vect3.h
	$(CC) $(CFLAGS) $(LDLIBS) -c dataTypes/ray.c -o dataTypes/ray.o

dataTypes/sphere.o: dataTypes/sphere.c header.h dataTypes/sphere.h dataTypes/vect3.h dataTypes/ray.h
	$(CC) $(CFLAGS) $(LDLIBS) -c dataTypes/sphere.c -o dataTypes/sphere.o

dataTypes/vect3.o: dataTypes/vect3.c header.h dataTypes/vect3.h
	$(CC) $(CFLAGS) $(LDLIBS) -c dataTypes/vect3.c -o dataTypes/vect3.o

array.o: array.c array.h
	$(CC) $(CFLAGS) $(LDLIBS) -c array.c -o array.o

main.o: main.c header.h dataTypes/dataTypes.h dataTypes/dColor.h dataTypes/ray.h dataTypes/rayHit.h dataTypes/sphere.h dataTypes/vect3.h
	$(CC) $(CFLAGS) $(LDLIBS) -c main.c -o main.o

clean:
	rm *.o dataTypes/*.o main

