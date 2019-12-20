
#ifndef ARRAY_H_
#define ARRAY_H_

#include <stddef.h>

void* newArray(size_t length, size_t size);

size_t len(void* ptr);

void freeArray(void* ptr);

#endif
