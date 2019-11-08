#ifndef VECT3_H_
#define VECT3_H_

#include "../header.h"

typedef struct _VectorLength3 {
    double x;
    double y;
    double z;
} vect3_t;

void vect3_print(vect3_t v);

vect3_t vect3_scale(vect3_t c, double sc);

vect3_t vect3_add(vect3_t a, vect3_t b);

vect3_t vect3_sub(vect3_t a, vect3_t b);

double vect3_dot(vect3_t a, vect3_t b);

vect3_t vect3_cross(vect3_t a, vect3_t b);

double vect3_squareOfMag(vect3_t a);

double vect3_mag(vect3_t a);

vect3_t vect3_normalize(vect3_t a);

int vect3_equals(vect3_t a, vect3_t b);

#endif
