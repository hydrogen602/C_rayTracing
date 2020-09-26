#include "../header.h"
#include "dataTypes.h"

triangle_t newTriangle(vect3_t a, vect3_t b, vect3_t c, dColor_t dc);

vect3_t triangle_getNormal(triangle_t* tr, __attribute__((unused)) ray_t r);

double triangle_intersection(triangle_t* tr, ray_t ray);
