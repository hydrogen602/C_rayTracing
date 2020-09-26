#include "../header.h"
#include "dataTypes.h"
#include "vect3.h"
#include "ray.h"
#include "math.h"

#include "triangle.h"

/*
typedef struct _TriangleGeoObject {
    vect3_t a;
    vect3_t b;
    vect3_t c;
    vect3_t n;
    double d;
    dColor_t color;
} triangle_t;
*/

triangle_t newTriangle(vect3_t a, vect3_t b, vect3_t c, dColor_t dc) {
    
    triangle_t t;
    t.a = a;
    t.b = b;
    t.c = c;
    //     private val n: Vect3 = ((c - a) x (c - b)).normalize
    t.n = vect3_normalize( vect3_cross( vect3_sub(c, a), vect3_sub(c, b) ) );
    //     private val d: Double = n * a //if (n * a > 0) n * a else -(n * a) // distance to origin
    t.d = vect3_dot(t.n, a);

    t.color = dc;

    return t;
}

vect3_t triangle_getNormal(triangle_t* tr, __attribute__((unused)) ray_t r) {
    return tr->n; // already normalized
}

double triangle_intersection(triangle_t* tr, ray_t ray) {
    /*
     * val tmp = (d - (n * r.source)) / (n * r.direction)
     * val planeIntersectDis = if (tmp == Double.PositiveInfinity || tmp == Double.NegativeInfinity || tmp < 0) None else Some(tmp)
     * 
     * tmp is infinity if n * r.dir is 0
     */
    double divisor = vect3_dot(tr->n, ray.dir);

    if (fabs(divisor) < 0.00001) {
        return -1;
    }
    else {
        double planeIntersectDis = (tr->d - vect3_dot(tr->n, ray.src)) / divisor;
        if (planeIntersectDis < 0) {
            return -1;
        }
        vect3_t p = ray_extend( ray, planeIntersectDis );

        vect3_t lines[3] = { vect3_sub(p, tr->a), vect3_sub(p, tr->b), vect3_sub(p, tr->c) };

        vect3_t ab = vect3_sub(tr->b, tr->a);
        vect3_t bc = vect3_sub(tr->c, tr->b);
        vect3_t ca = vect3_sub(tr->a, tr->c);

        vect3_t crosses[3] = { ab, bc, ca };
        for (int i = 0; i < 3; ++i) {
            crosses[i] = vect3_normalize( vect3_cross( crosses[i], lines[i] ) );
        }

        return (vect3_equals(crosses[0], crosses[1]) && vect3_equals(crosses[1], crosses[2])) ? planeIntersectDis : -1;
    }
}

