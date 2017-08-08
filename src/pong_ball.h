#ifndef PONG_BALL_H
#define PONG_BALL_H

#include "types.h"

pong_ball_t *pong_ball_move(pong_ball_t *, pong_window_t *);
pong_ball_t *pong_ball_init(const int, const size_t, const color_t);
int pong_ball_draw(pong_ball_t *, pong_window_t *, const size_t, const size_t);

#endif
