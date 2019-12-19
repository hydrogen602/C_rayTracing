#ifndef DCOLOR_H_
#define DCOLOR_H_

#include "../header.h"
#include "dataTypes.h"

void dColor_print(dColor_t c);

int dColor_assembleRGB(dColor_t c);

dColor_t dColor_scale(dColor_t c, double sc);

dColor_t dColor_add(dColor_t a, dColor_t b);

dColor_t dColor_sub(dColor_t a, dColor_t b);

bool dColor_equals(dColor_t a, dColor_t b);

#endif
