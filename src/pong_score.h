//
// Created by layer on 15/08/17.
//

#ifndef PONG_PONG_SCORE_H
#define PONG_PONG_SCORE_H
#include "types.h"

void pong_score_add(pong_score_t *, int player);
pong_score_t *pong_score_init(const color_t, pong_window_t *);
int pong_score_draw(pong_score_t *, pong_window_t *);

#endif //PONG_PONG_SCORE_H
