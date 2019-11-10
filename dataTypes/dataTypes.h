#ifndef DATATYPES_H_
#define DATATYPES_H_

/*
 * Defines all structs used in the code
 */

typedef struct _DoubleBasedColor {
    double r;
    double g;
    double b;

} dColor_t;

typedef struct _VectorLength3 {
    double x;
    double y;
    double z;
} vect3_t;

typedef struct _Ray {
    vect3_t src;
    vect3_t dir;
} ray_t;

/* allocate GeometricObjects on the heap otherwise I'm going to lose my mind */
typedef struct _SphereGeoObject {
    vect3_t n;
    double d;
} sphere_t;

// to differentiate between sphere pointers and arrays
typedef sphere_t * sphereArray_t;

typedef struct _RayHit {
    double dis;
    sphere_t* obj;
} rayHit_t;

#endif
