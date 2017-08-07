//
// Created by layer on 06/08/17.
//

#ifndef PONG_PONG_FIELD_H
#define PONG_PONG_FIELD_H

#include "types.h"

pong_field_t *pong_field_init(const size_t, const size_t, const color_t);
int pong_field_draw(pong_field_t *, pong_window_t *, const size_t, const size_t);


#endif //PONG_PONG_FIELD_H
