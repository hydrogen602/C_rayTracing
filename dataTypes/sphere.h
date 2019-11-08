#ifndef SPHERE_H
#define SPHERE_H

#include "vect3.h"

typedef struct _SphereGeoObject {
    vect3_t n;
    double d;
} sphere_t;

vect3_t sphere_getNormal(sphere_t* sp, ray_t ray);

double sphere_intersection(sphere_t* sp, ray_t ray);

#endif
