#include <stdio.h>
#include <math.h>

#include "../header.h"
#include "vect3.h"
#include "ray.h"
#include "sphere.h"

void sphere_print(sphere_t sp) {
    printf("Sphere: center=<%.3f, %.3f, %.3f>, radius=%.3f\n", sp.n.x, sp.n.y, sp.n.z, sp.d);
}

vect3_t sphere_getNormal(sphere_t* sp, ray_t ray) {
    double t = sphere_intersection(sp, ray);

    if (t < 0) {
        // nothing hit
        printf("reflectRay should only be called on intersecting rays\n");
        
        vect3_t nullVector = {0, 0, 0};
        return nullVector;
    }
    
    vect3_t pointReflected = ray_extend(ray, t);

    return vect3_normalize(vect3_sub(pointReflected, sp->n));
}

double sphere_intersection(sphere_t* sp, ray_t ray) {
    /* 
        * r0   =   start point of ray
        * r    =   direction from start
        * n    =   center of the sphere
        * d    =   radius of sphere
        * 
        * returns scalar t that satisfies |r(t) - n|^2 = radius^2
        * where r(t) is r0 + r * t
        *
        * returns -1 upon failure aka no solution
        */

    // r0 + r * t is the point of the tip of the ray

    // see CS notebook for math

    // components of quadratic equation
    // ax^2 + bx + c = 0

    double a = vect3_squareOfMag(ray.dir);
    double b = -2 * vect3_dot(sp->n, ray.dir) + 2 * vect3_dot(ray.src, ray.dir);

    double radiusSq = sp->d * sp->d;

    double c = (vec3t_squareOfMag(sp->n) - (2 * vect3_dot(sp->n, ray.src)) + (vect3_squareOfMag(ray.src)) - radiusSq);

    // quadratic equation time

    // -b +- sqrt(b^2 - 4ac)
    // ---------------------
    //          2a

    double thingInSquareRoot = b * b - 4 * a * c;
    //println(thingInSquareRoot)

    if (thingInSquareRoot < 0) {
        // no solution
        return -1;
    }
    else {
        double positiveSide = (-b + sqrt(thingInSquareRoot)) / (2 * a);
        double negativeSide = (-b - sqrt(thingInSquareRoot)) / (2 * a);

        if (positiveSide < 0 && negativeSide < 0) 
            return -1;
        else if (positiveSide < 0) 
            return negativeSide;
        else if (negativeSide < 0) 
            return positiveSide;
        else if (positiveSide < negativeSide) 
            return positiveSide;
        else
            return negativeSide;
    }
}
