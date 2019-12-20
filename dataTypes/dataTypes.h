#ifndef DATATYPES_H_
#define DATATYPES_H_

/*
 * Defines all structs used in the code
 */

#define SPHERE_TYPE 0xee
#define TRIANGLE_TYPE 0xae

typedef unsigned char byte;

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
    dColor_t color;
} sphere_t;

typedef struct _TriangleGeoObject {
    vect3_t a;
    vect3_t b;
    vect3_t c;
    vect3_t n;
    double d;
    dColor_t color;
} triangle_t;

union _GeometryType {
    sphere_t sp;
    triangle_t tr;
};

typedef struct _GeometricObject {
    byte type;
    union _GeometryType content;
} geometry_t;

typedef struct _RayHit {
    double dis;
    geometry_t* obj;
} rayHit_t;

typedef struct _ImageGrid {
    vect3_t src;
    vect3_t forward;
    vect3_t up;
    vect3_t left;
    vect3_t centerOfGrid;
    vect3_t topLeftCorner;
    vect3_t bottomRightCorner;
    vect3_t rightStepVector;
    vect3_t downStepVector;

    unsigned int size;
} grid_t;

typedef struct _SceneHolder
{
    grid_t grid;
    geometry_t* geometry; // length of array is stored in memory block

    vect3_t lsrc; // light source
} scene_t;


#endif
