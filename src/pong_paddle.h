#ifndef PONG_PADDLE_H
#define PONG_PADDLE_H

#include "types.h"

pong_paddle_t *pong_paddle_init(const size_t, const size_t, const color_t);
int pong_paddle_draw(pong_paddle_t *, pong_window_t *, const size_t, const size_t);


#endif
