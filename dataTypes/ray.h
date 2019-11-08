#ifndef RAY_H
#define RAY_H

#include "vect3.h"
#include "dColor.h"
#include "rayHit.h"

typedef struct _Ray {
    vect3_t src;
    vect3_t dir;
} ray_t;

vect3_t ray_extend(ray_t r, double t);

dColor_t ray_colorShading(ray_t ray, vect3_t lsrc, rayHit_t hit, sphere_t* geometry);

rayHit_t ray_trace(ray_t ray, sphere_t* geometry);

dColor_t Ray_traceAndHitToDisplay(ray_t ray, vect3_t lsrc, sphere_t* geometry);

#endif
