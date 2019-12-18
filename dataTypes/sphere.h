#ifndef SPHERE_H_
#define SPHERE_H_

#include "../header.h"
#include "dataTypes.h"

void sphere_print(sphere_t sp);

vect3_t sphere_getNormal(sphere_t* sp, ray_t ray);

double sphere_intersection(sphere_t* sp, ray_t ray);

#endif
