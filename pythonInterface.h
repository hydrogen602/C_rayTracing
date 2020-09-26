#include "header.h"
#include "dataTypes/dataTypes.h"

void initTriangle(triangle_t * t, double ax, double ay, double az, double bx, double by, double bz, double cx, double cy, double cz);

void initScene(scene_t * sc, unsigned int size, triangle_t * tri, unsigned int triLen);

int generateImage(byte* rgb, scene_t * sc);
