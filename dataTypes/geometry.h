#include "../header.h"
#include "dataTypes.h"

#define isSphere(geo) ((geo).type == SPHERE_TYPE)

#define isTriangle(geo) ((geo).type == TRIANGLE_TYPE)

geometry_t newGeometrySp(sphere_t sp);

geometry_t newGeometryTr(triangle_t tr);

dColor_t getColor(geometry_t geo);

vect3_t getNormal(geometry_t *geo, ray_t ray);

sphere_t * getSphere(geometry_t * geo);

triangle_t * getTriangle(geometry_t * geo);
