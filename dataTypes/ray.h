#ifndef RAY_H
#define RAY_H

#include "vect3.h"

typedef struct _Ray {
    vect3_t src;
    vect3_t dir;
} ray_t;

#endif
