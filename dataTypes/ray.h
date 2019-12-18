#ifndef RAY_H_
#define RAY_H_

#include "../header.h"
#include "dataTypes.h"

vect3_t ray_extend(ray_t r, double t);

dColor_t ray_colorShading(ray_t ray, vect3_t lsrc, rayHit_t hit, sphereArray_t geometry);

rayHit_t ray_trace(ray_t ray, sphereArray_t geometry);

dColor_t ray_traceAndHitToDisplay(ray_t ray, vect3_t lsrc, sphereArray_t geometry);

#endif
