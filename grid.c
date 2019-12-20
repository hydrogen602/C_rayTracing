#include <stdio.h>
#include <math.h>

#include "grid.h"
#include "dataTypes/dataTypes.h"
#include "dataTypes/vect3.h"
#include "dataTypes/ray.h"

dColor_t grid_rayTraceOnce(scene_t sc, int i, int j) {

    vect3_t xShift = vect3_scale(sc.grid.rightStepVector, i);
    vect3_t yShift = vect3_scale(sc.grid.downStepVector, j);

    vect3_t ptOnGrid = vect3_add(vect3_add(sc.grid.topLeftCorner, xShift), yShift);

    ray_t ray = { sc.grid.src, vect3_sub(ptOnGrid, sc.grid.src) };

    if (i == 5 && j == 5) {
        printf("ray dir = <%.1f, %.1f, %.1f>\n", ray.dir.x, ray.dir.y, ray.dir.z);
        printf("ray src = <%.1f, %.1f, %.1f>\n", ray.src.x, ray.src.y, ray.src.z);
    }

    dColor_t c = ray_traceAndHitToDisplay(ray, sc.lsrc, sc.geometry);
    return c;
}

double grid_rayTraceOnceDistance(grid_t g, int i, int j, geometry_t * geometry) {
    vect3_t xShift = vect3_scale(g.rightStepVector, i);
    vect3_t yShift = vect3_scale(g.downStepVector, j);

    vect3_t ptOnGrid = vect3_add(vect3_add(g.topLeftCorner, xShift), yShift);

    ray_t ray = { g.src, vect3_sub(ptOnGrid, g.src) };

    rayHit_t rh = ray_trace(ray, geometry);  
    return rh.dis;     
}

grid_t grid_init(vect3_t src, vect3_t forward, vect3_t up, unsigned int size) {
    grid_t g;

    if (fabs(vect3_squareOfMag(forward) - 1) > 0.001 || fabs(vect3_squareOfMag(up) - 1) > 0.001) {
        fprintf(stderr, "forward and up vectors should be unit vectors\n");
    }

    g.src = src;
    g.forward = forward;
    g.up = up;
    g.size = size;

    g.left = vect3_cross(up, forward);
    g.centerOfGrid = vect3_add(src, forward);

    g.topLeftCorner = vect3_add(vect3_add(g.centerOfGrid, up), g.left);

    g.bottomRightCorner = vect3_sub(vect3_sub(g.centerOfGrid, up), g.left);

    unsigned int scalar = size - 1;

    /*
     * Think of a grid. It has squares, but for simplicity I'm going to shoot the rays
     * at the corners of the box. Now there is one less square lengthwise than there
     * are corners between the squares, and so that is why I'm subtracting one here.
     * 
     *   X--X--X   Note: There are 3 corners (X) across, but 2 line segments (--)
     *   |  |  |     So I need to divide the side of the square grid by 2
     *   X--X--X     instead of 3 to get the distance between corners.
     *   |  |  | 
     *   X--X--X 
     */

    g.rightStepVector = vect3_scale(g.left, -2.0 / scalar);

    //printf("scalar = %d\n", scalar);

    //printf("rightStepVector = ");
    //self.rightStepVector.print(&self.rightStepVector);

    g.downStepVector = vect3_scale(up, -2.0 / scalar);
    
    return g;
}
