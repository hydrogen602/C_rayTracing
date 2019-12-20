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

#include "pythonInterface.h"

void initTriangle(triangle_t * t, double ax, double ay, double az, double bx, double by, double bz, double cx, double cy, double cz) {
    vect3_t a = { ax, ay, az };
    vect3_t b = { bx, by, bz };
    vect3_t c = { cx, cy, cz };
    dColor_t green = { 0x0, 0xff, 0x0 };

    triangle_t new = newTriangle(a, b, c, green);
    *(t) = new;
}

void initScene(scene_t * sc, unsigned int size, triangle_t * tri, unsigned int triLen) {
    //grid_t g = grid_init(vect3_init(10, 0, 0), vect3_init(-1, 0, 0), vect3_init(0, 1, 0), size);
    grid_t g = grid_init(vect3_init(0, 0, 10), vect3_init(0, 0, -1), vect3_init(-1, 0, 0), size);
    //vect3_t center = { 0, 0, 0 };
    //dColor_t lightBlue = { 162, 209, 230 };
    //sphere_t sp = { center, 4, lightBlue };

    geometry_t * geo = newArray(triLen, sizeof(geometry_t));
    //geo[0] = newGeometrySp(sp);
    
    // vect3_t a = { 10, -10, -10 };
    // vect3_t b = { 10, 10, -10 };
    // vect3_t c = { -10, 0, 10 };
    // dColor_t green = { 0x00, 0xff, 0x00 };

    //geo[1] = newGeometryTr(newTriangle(a, b, c, green));

    for (unsigned int i = 0; i < triLen; ++i) {
        geo[i] = newGeometryTr(tri[i]);
    }

    sc->grid = g;
    sc->geometry = geo;
    vect3_t lsrc = { 0, 0, 100 };
    sc->lsrc = lsrc;
}

int generateImage(byte* rgb, scene_t * scPtr) {
    scene_t sc = *scPtr;
    // should be arrays of size * size where size is sc.grid.size
    unsigned int size = sc.grid.size;
    for (unsigned int i = 0; i < size; i++) {
        for (unsigned int j = 0; j < size; j++) {
            dColor_t d = grid_rayTraceOnce(sc, i, j);

            rgb[(i * size + j) * 3 + 0] = d.r;
            rgb[(i * size + j) * 3 + 1] = d.g;
            rgb[(i * size + j) * 3 + 2] = d.b;

            //red[i * size + j] = 1;

            //printf("%02x %02x %02x, ", (int)d.r, (int)d.g, (int)d.b);
        }

    }

    return 0;
}

int main() {
    scene_t sc;
    initScene(&sc, 11, NULL, 0);

    byte rgb[121 * 3];

    generateImage(rgb, &sc);

    for (unsigned int i = 0; i < 11; i++) {
        for (unsigned int j = 0; j < 11; j++) {
            printf("%02x ", rgb[(i * 11 + j) * 3]);
        }
        putchar('\n');
    }

    return 0;
}
