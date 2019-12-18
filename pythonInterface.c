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
    sphere_t sp = { center, 4 };
    sphere_t geo[1] = { sp };

    sc->grid = g;
    sc->geometry = geo;
    vect3_t lsrc = { 0, 0, 100 };
    sc->lsrc = lsrc;
}

int generateImage(byte* red, byte* blue, byte* green, scene_t * scPtr) {
    scene_t sc = *scPtr;
    // should be arrays of size * size where size is sc.grid.size
    unsigned int size = sc.grid.size;
    for (unsigned int i = 0; i < size; i++) {
        for (unsigned int j = 0; j < size; j++) {
            dColor_t d = grid_rayTraceOnce(sc, i, j);
            red[i * size + j] = d.r;
            green[i * size + j] = d.g;
            blue[i * size + j] = d.b;

            //printf("%02x %02x %02x, ", (int)d.r, (int)d.g, (int)d.b);
        }

    }

    return 0;
}
