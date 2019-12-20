#include "geometry.h"
#include "../header.h"

#include "dataTypes.h"

#include "sphere.h"
#include "triangle.h"

#include <stdio.h>

geometry_t newGeometrySp(sphere_t sp) {
    union _GeometryType generic;
    generic.sp = sp;
    geometry_t geo;
    geo.type = SPHERE_TYPE;
    geo.content = generic;
    return geo;
}

geometry_t newGeometryTr(triangle_t tr) {
    union _GeometryType generic;
    generic.tr = tr;
    geometry_t geo;
    geo.type = TRIANGLE_TYPE;
    geo.content = generic;
    return geo;
}

dColor_t getColor(geometry_t geo) {
    if (geo.type == SPHERE_TYPE) {
        return geo.content.sp.color;
    }
    else if (geo.type == TRIANGLE_TYPE) {
        return geo.content.tr.color;
    }
    printErrMsg("Invalid geometry_t");
    dColor_t c = { 0, 0, 0 };
    return c;
}

vect3_t getNormal(geometry_t *geo, ray_t ray) {
    if (geo->type == SPHERE_TYPE) {
        return sphere_getNormal(&(geo->content.sp), ray);
    }
    else if (geo->type == TRIANGLE_TYPE) {
        return triangle_getNormal(&(geo->content.tr), ray);
    }
    printErrMsg("Invalid geometry_t");
    vect3_t c = { 0, 0, 0 };
    return c;
}

sphere_t * getSphere(geometry_t * geo) {
    if (geo->type != SPHERE_TYPE) {
        printErrMsg("getSphere called on a non-sphere");
    }

    return & (geo->content.sp);
}

triangle_t * getTriangle(geometry_t * geo) {
    if (geo->type != TRIANGLE_TYPE) {
        printErrMsg("getTriangle called on a non-triangle");
    }

    return & (geo->content.tr);
}
