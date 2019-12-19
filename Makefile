CC = gcc
CFLAGS = -Wall -pedantic -O -std=c99
LDLIBS = -lm
# add $(LDLIBS) for math

VALGRIND = -O0 -g

HEADERS := $(wildcard *.h)
HEADERS += $(wildcard support/*.h)

all: dataTypes/dColor.o dataTypes/ray.o dataTypes/sphere.o dataTypes/vect3.o array.o grid.o main.o
	$(CC) -o main dataTypes/dColor.o dataTypes/ray.o dataTypes/sphere.o dataTypes/vect3.o array.o grid.o main.o $(LDLIBS)

pythonInterface: dataTypes/dColor.o dataTypes/ray.o dataTypes/sphere.o dataTypes/vect3.o array.o grid.o pythonInterface.o
	$(CC) -o pythonInterface dataTypes/dColor.o dataTypes/ray.o dataTypes/sphere.o dataTypes/vect3.o array.o grid.o pythonInterface.o $(LDLIBS)

%.o: %.c $(HEADERS)
	$(CC) $(CFLAGS) -c $*.c -o $@

dataTypes/%.o: dataTypes/%.c $(HEADERS)
	$(CC) $(CFLAGS) -c dataTypes/$*.c -o $@

.PHONY: py
py: setup.py interface.pyx
	python3 setup.py build_ext --inplace

.PHONY: clean
clean:
	rm -f *.o dataTypes/*.o main *.so build/temp.linux-x86_64-3.6/*.o build/temp.linux-x86_64-3.6/dataTypes/*.o

.PHONY: debug
debug: CFLAGS += $(VALGRIND)
debug: clean all
	@echo "done compiling"

