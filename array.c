#include <stdlib.h>
#include <stdio.h>

#include "array.h"

void* newArray(size_t length, size_t size) {
    long* ptr = (long*) malloc(length * size + sizeof(size_t));
    if (ptr == NULL) {
        fprintf(stderr, "Memory allocation failed");
        exit(1);
    }
    
    *(ptr) = length;
    return (char *)ptr + sizeof(size_t);
}

size_t len(void* ptr) {
    return * ((size_t *) ((char *)ptr - sizeof(size_t)));
}

void freeArray(void* ptr) {
    free((char*)(ptr) - sizeof(size_t));
}