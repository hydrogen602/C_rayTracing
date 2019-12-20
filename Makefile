CC = gcc
CFLAGS = -Wall -pedantic -O -std=c99
LDLIBS = -lm
# add $(LDLIBS) for math

VALGRIND = -O0 -g

HEADERS := $(wildcard *.h)
HEADERS += $(wildcard support/*.h)

GEOMETRY := dataTypes/sphere.o dataTypes/triangle.o dataTypes/geometry.o

DATA_TYPES := dataTypes/dColor.o dataTypes/ray.o dataTypes/vect3.o array.o

all: $(DATA_TYPES) $(GEOMETRY) grid.o main.o
	$(CC) -o main $(DATA_TYPES) $(GEOMETRY) grid.o main.o $(LDLIBS)

pythonInterface: $(DATA_TYPES) $(GEOMETRY) grid.o pythonInterface.o
	$(CC) -o pythonInterface $(DATA_TYPES) $(GEOMETRY) grid.o pythonInterface.o $(LDLIBS)

%.o: %.c $(HEADERS)
	$(CC) $(CFLAGS) -c $*.c -o $@

dataTypes/%.o: dataTypes/%.c $(HEADERS)
	$(CC) $(CFLAGS) -c dataTypes/$*.c -o $@

.PHONY: py
py: setup.py interface.pyx
	python3.7 setup.py build_ext --inplace

.PHONY: clean
clean:
	rm -f *.o dataTypes/*.o main *.so build/temp.linux-x86_64-3.6/*.o build/temp.linux-x86_64-3.6/dataTypes/*.o test.png

.PHONY: debug
debug: CFLAGS += $(VALGRIND)
debug: clean all
	@echo "done compiling"

.PHONY: run
run: clean py
	python3.7 run.py

