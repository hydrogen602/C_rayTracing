CC = gcc
CFLAGS = -Wall -pedantic -O -std=c99
LDLIBS = -lm
# add $(LDLIBS) for math

VALGRIND = -O0 -g

HEADERS := $(wildcard *.h)
HEADERS += $(wildcard support/*.h)

all: dataTypes/dColor.o dataTypes/ray.o dataTypes/sphere.o dataTypes/vect3.o array.o grid.o main.o
	$(CC) -o main dataTypes/dColor.o dataTypes/ray.o dataTypes/sphere.o dataTypes/vect3.o array.o grid.o main.o $(LDLIBS)

%.o: %.c $(HEADERS)
	$(CC) $(CFLAGS) -c $*.c -o $@

dataTypes/%.o: dataTypes/%.c $(HEADERS)
	$(CC) $(CFLAGS) -c dataTypes/$*.c -o $@

#dataTypes/dColor.o: dataTypes/dColor.c header.h dataTypes/dColor.h
#	$(CC) $(CFLAGS) $(LDLIBS) -c dataTypes/dColor.c -o dataTypes/dColor.o
#
#dataTypes/ray.o: dataTypes/ray.c header.h dataTypes/ray.h dataTypes/sphere.h dataTypes/dColor.h dataTypes/rayHit.h dataTypes/vect3.h
#	$(CC) $(CFLAGS) $(LDLIBS) -c dataTypes/ray.c -o dataTypes/ray.o
#
#dataTypes/sphere.o: dataTypes/sphere.c header.h dataTypes/sphere.h dataTypes/vect3.h dataTypes/ray.h
#	$(CC) $(CFLAGS) $(LDLIBS) -c dataTypes/sphere.c -o dataTypes/sphere.o
#
#dataTypes/vect3.o: dataTypes/vect3.c header.h dataTypes/vect3.h
#	$(CC) $(CFLAGS) $(LDLIBS) -c dataTypes/vect3.c -o dataTypes/vect3.o
#
#array.o: array.c array.h
#	$(CC) $(CFLAGS) $(LDLIBS) -c array.c -o array.o
#
#grid.o: grid.c grid.h dataTypes/dataTypes.h dataTypes/vect3.h dataTypes/ray.h dataTypes/rayHit.h
#	$(CC) $(CFLAGS) $(LDLIBS) -c grid.c -o grid.o
#
#main.o: main.c header.h dataTypes/dataTypes.h dataTypes/dColor.h dataTypes/ray.h dataTypes/rayHit.h dataTypes/sphere.h dataTypes/vect3.h grid.h
#	$(CC) $(CFLAGS) $(LDLIBS) -c main.c -o main.o

.PHONY: clean
clean:
	rm -f *.o dataTypes/*.o main

.PHONY: debug
debug: CFLAGS += $(VALGRIND)
debug: clean all
	@echo "done compiling"

