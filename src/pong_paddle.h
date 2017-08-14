#ifndef PONG_PADDLE_H
#define PONG_PADDLE_H

#include "types.h"

pong_paddle_t *pong_paddle_init(size_t x, size_t y, const color_t, unsigned int player);
int pong_paddle_draw(pong_paddle_t *, pong_window_t *);
void pong_paddle_go_up(pong_paddle_t *);
void pong_paddle_go_down(pong_paddle_t *);

#endif
