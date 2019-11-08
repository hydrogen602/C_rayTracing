#include <stdio.h>
#include <math.h>

#include "../header.h"
#include "dColor.h"

void dColor_print(dColor_t c) {
    printf("Color = (%.3f, %.3f, %.3f)\n", c.r, c.g, c.b);
}

int dColor_assembleRGB(dColor_t c) {
    // r, g, and b should be 0 <= x <= 255
    return (int)(c.r) << 16 | (int)(c.g) << 8 | (int)(c.b);
}

dColor_t dColor_scale(dColor_t c, double sc) {
    dColor_t cNew;
    cNew.r = c.r * sc;
    cNew.g = c.g * sc;
    cNew.b = c.b * sc;
    return cNew;
}

dColor_t dColor_add(dColor_t a, dColor_t b) {
    dColor_t cNew;
    cNew.r = a.r + b.r;
    cNew.g = a.g + b.g;
    cNew.b = a.b + b.b;
    return cNew; 
}

dColor_t dColor_sub(dColor_t a, dColor_t b) {
    dColor_t cNew;
    cNew.r = a.r - b.r;
    cNew.g = a.g - b.g;
    cNew.b = a.b - b.b;
    return cNew; 
}

boolean dColor_equals(dColor_t a, dColor_t b) {
    return fabs(a.r - b.r) < 0.0001 && fabs(a.g - b.g) < 0.0001 && fabs(a.b - b.b) < 0.0001;
}
