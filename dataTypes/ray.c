#include <stdio.h>
#include <math.h>

#include "../header.h"
#include "ray.h"
#include "sphere.h"
#include "triangle.h"
#include "dColor.h"
#include "vect3.h"
#include "geometry.h"

vect3_t ray_extend(ray_t r, double t) {
    vect3_t v = { 
        r.src.x + r.dir.x * t, 
        r.src.y + r.dir.y * t, 
        r.src.z + r.dir.z * t
    };
    return v;
}

dColor_t ray_colorShading(ray_t ray, vect3_t lsrc, rayHit_t hit, geometry_t* geometry) {
    // geometry array should be made from array.h so that len(geometry) works

    // (r)(hit.dis)
    vect3_t pointOfHit = ray_extend(ray, hit.dis);

    // lsrc - pointOfHit
    // from point of hit to light src
    vect3_t path = vect3_sub(lsrc, pointOfHit);

    // | lsrc - pointOfHit |
    // double length = vect3_mag(path);

    //   ^
    //  path
    vect3_t pathNormal = vect3_normalize(path);

    vect3_t tinyShift = vect3_scale(pathNormal, 0.00001);

    ray_t lightRay = { vect3_add(pointOfHit, tinyShift), path };
    
    rayHit_t hitPossible = ray_trace(lightRay, geometry);

    vect3_t v = {-1,0,0};
    if (vect3_equals(ray.dir, v)) {
        printf("light hit dis = %.1f\n", hitPossible.dis);
    }

    if (hitPossible.dis < 0 || hitPossible.dis > vect3_mag(path)) {
        // light ray hit nothing as ray_trace returns -1 in that case

        vect3_t surfaceNormal = getNormal(hit.obj, ray);

        double shading = vect3_dot(pathNormal, surfaceNormal);
        if (vect3_equals(ray.dir, v)) {
            printf("shading = %.1f\n", shading);
            printf("pathNormal = < %.1f, %.1f, %.1f>\n", pathNormal.x, pathNormal.y, pathNormal.z);
            printf("surfaceNormal = < %.1f, %.1f, %.1f>\n", surfaceNormal.x, surfaceNormal.y, surfaceNormal.z);
        }
        //printf("shading = %f\n", shading);

        dColor_t objColor = getColor(*(hit.obj));
        dColor_t returnVal = {shading * objColor.r, shading * objColor.g, shading * objColor.b};
        return returnVal;

        //require(-1 <= shading && shading <= 1, s"shading should be in [0, 1], instead $shading")

        //lsrc.applyColor(hit.obj.color * math.abs(shading))  
    }
    
    // else: something hit blocks the light

    dColor_t returnVal = {0, 0, 0};
    return returnVal;
}

rayHit_t ray_trace(ray_t ray, geometry_t* geometry) {
    // sphere_t array needs to be made from array.h
    // returns a rayHit with distance -1 if nothing was hit

    double d = -1;
    int geoIndex = -1;

    double tmpD;

    for (unsigned int i = 0; i < len(geometry); ++i) {
        if (isSphere(geometry[i])) {
            tmpD = sphere_intersection(getSphere(geometry + i), ray);
        }
        else if (isTriangle(geometry[i])) {
            tmpD = triangle_intersection(getTriangle(geometry + i), ray);
        }
        else {
            printErrMsg("Invalid geometry type");
            tmpD = -1;
        }

        if (tmpD > 0.000001 && (tmpD < d || d < 0)) {
            // tmpD > 0.000001 = not intersection with itself
            // tmpD < d = closer intersection
            // d < 0 = no intersection found yet
            // tmpD is recorded if it is smaller than d or there is no d (d == -1)
            d = tmpD;
            geoIndex = i;
        }
    }

    if (d < 0) {
        rayHit_t rh = { -1, NULL };
        return rh;
    }
    else {
        rayHit_t rh = { d, (geometry + geoIndex) };
        return rh;
    }
}

dColor_t ray_traceAndHitToDisplay(ray_t ray, vect3_t lsrc, geometry_t* geometry) {
    // must be fancy sphere array from array.h

    rayHit_t rh = ray_trace(ray, geometry);

    vect3_t v = { -1, 0, 0 };
    if (vect3_equals(ray.dir, v)) {
        printf("ray hit dis = %.1f\n", rh.dis);
    }

    if (rh.dis < 0) {
        // nothing hit
        dColor_t c = {0, 0, 0};
        return c;
    }

    return ray_colorShading(ray, lsrc, rh, geometry);
}
