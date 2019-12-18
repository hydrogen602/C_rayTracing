#include <stdio.h>
#include <math.h>

#include "../header.h"
#include "vect3.h"

void vect3_print(vect3_t v) {
    printf("<%.3f, %.3f, %.3f>\n", v.x, v.y, v.z);
}

vect3_t vect3_scale(vect3_t c, double sc) {
    vect3_t cNew;
    cNew.x = c.x * sc;
    cNew.y = c.y * sc;
    cNew.z = c.z * sc;
    return cNew;
}

vect3_t vect3_add(vect3_t a, vect3_t b) {
    vect3_t cNew;
    cNew.x = a.x + b.x;
    cNew.y = a.y + b.y;
    cNew.z = a.z + b.z;
    return cNew; 
}

vect3_t vect3_sub(vect3_t a, vect3_t b) {
    vect3_t cNew;
    cNew.x = a.x - b.x;
    cNew.y = a.y - b.y;
    cNew.z = a.z - b.z;
    return cNew; 
}

double vect3_dot(vect3_t a, vect3_t b) {
    return a.x * b.x + a.y * b.y + a.z * b.z; 
}

vect3_t vect3_cross(vect3_t a, vect3_t b) {
    vect3_t cNew;
    cNew.x = a.y * b.z - a.z * b.y;
    cNew.y = -(a.x * b.z - a.z * b.x);
    cNew.z = a.x * b.y - a.y * b.x;
    return cNew; 
}

double vect3_squareOfMag(vect3_t a) {
    return a.x * a.x + a.y * a.y + a.z * a.z;
}

double vect3_mag(vect3_t a) {
    return sqrt(vect3_squareOfMag(a));
}

vect3_t vect3_normalize(vect3_t a) {
    return vect3_scale(a, 1.0 / vect3_mag(a));
}

int vect3_equals(vect3_t a, vect3_t b) {
    return fabs(a.x - b.x) < 0.0001 && fabs(a.y - b.y) < 0.0001 && fabs(a.z - b.z) < 0.0001;
}

vect3_t vect3_init(double x, double y, double z) {
    vect3_t a = { x, y, z };
    return a;
}
