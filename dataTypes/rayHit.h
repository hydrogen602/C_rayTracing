#ifndef RAYHIT_H
#define RAYHIT_H

#include "sphere.h"

/* allocate GeometricObjects on the heap otherwise I'm going to lose my mind */

typedef struct _RayHit {
    double dis;
    sphere_t* obj;
} rayHit_t;

#endif
