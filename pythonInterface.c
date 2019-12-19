#include <stdio.h>

#include "header.h"
#include "dataTypes/dataTypes.h"
#include "dataTypes/dColor.h"
#include "dataTypes/ray.h"
#include "dataTypes/rayHit.h"
#include "dataTypes/sphere.h"
#include "dataTypes/vect3.h"
#include "grid.h"

#include "pythonInterface.h"

void initScene(scene_t * sc, unsigned int size) {
    grid_t g = grid_init(vect3_init(10, 0, 0), vect3_init(-1, 0, 0), vect3_init(0, 0, 1), size);
    vect3_t center = { 0, 0, 0 };
    dColor_t lightBlue = { 162, 209, 230 };
    sphere_t sp = { center, 4, lightBlue };
    sphereArray_t geo = newArray(1, sizeof(sphere_t));
    geo[0] = sp;

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
    initScene(&sc, 11);

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
