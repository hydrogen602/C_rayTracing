#ifndef GRID_H_
#define GRID_H_

#include "dataTypes/dataTypes.h"

dColor_t grid_rayTraceOnce(grid_t g, int i, int j, sphereArray_t geometry, vect3_t lsrc);

double grid_rayTraceOnceDistance(grid_t g, int i, int j, sphereArray_t geometry);

grid_t grid_init(vect3_t src, vect3_t forward, vect3_t up, unsigned int size);

#endif
