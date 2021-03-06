#include <stdio.h>

#include "header.h"
#include "dataTypes/dataTypes.h"
#include "dataTypes/dColor.h"
#include "dataTypes/ray.h"
#include "dataTypes/sphere.h"
#include "dataTypes/triangle.h"
#include "dataTypes/vect3.h"
#include "grid.h"
#include "dataTypes/geometry.h"

int main() {

    vect3_t src = { 10, 0, 0 };
    vect3_t dir = { -1, 0, 0 };
    ray_t r = { src, dir };

    vect3_t center = { 0, 0, 0 };
    dColor_t red = { 0xff, 0x00, 0x00 };
    sphere_t sp = { center, 4, red };

    vect3_t a = { 10, 10, 10 };
    vect3_t b = { 10, 10, -10 };
    vect3_t c = { -10, -10, 0 };
    triangle_t tr = newTriangle(a, b, c, red); 
    const unsigned int geoCount = 1;

    geometry_t * geometry = newArray(geoCount, sizeof(geometry_t)); 

    //geometry[0] = newGeometrySp(sp);
    geometry[0] = newGeometryTr(tr);

    rayHit_t rh = ray_trace(r, geometry);

    printf("distance = %0.2f\n", rh.dis);


    // RayC r = Ray(Vect3(20, 0, 0), Vect3(-1, 0, 0));

    // RayHitC rh = r.trace(&r, geometry, geoLength);

    // printf("Ray Tracing Result: d = %.3f\n", rh.dis);
    // if (rh.obj != NULL) {
    //     rh.obj->print(rh.obj);
    // }

    const unsigned int size = 11;

    //vect3_t lsrc = { 0, 0, 100 };

    grid_t g = grid_init(vect3_init(10, 0, 0), vect3_init(-1, 0, 0), vect3_init(0, 0, 1), size);

    for (int i = 0; i < size; i++) {
        for (int j = 0; j < size; j++) {
            //dColor_t d = grid_rayTraceOnce(g, i, j, geometry, lsrc);
            double dis = grid_rayTraceOnceDistance(g, i, j, geometry);
            printf("%5.2f ", dis);

            //printf("%02x %02x %02x, ", (int)d.r, (int)d.g, (int)d.b);
        }
        printf("\n");
    }

    freeArray(geometry);

    return 0;
}
