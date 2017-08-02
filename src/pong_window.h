#ifndef WINDOW_H
#define WINDOW_H

#include "types.h"

pong_window_t *pong_window_new(const size_t size, const color_t);
void pong_window_draw(pong_window_t *);

#endif
