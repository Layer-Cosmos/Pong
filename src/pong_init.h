#ifndef PONG_INIT_H
#define PONG_INIT_H

#include "color.h"
#include "pong_ball.h"
#include "pong_opt.h"
#include "pong_paddle.h"
#include "types.h"
#include <stdbool.h>

void *pong_init_type(int, char **, enum pong_type *);
void *pong_init_network(void *, enum pong_type);
void pong_init_paddle_clt(pong_client_t *, pong_window_t *);
void pong_init_paddle_svr(pong_server_t *, pong_window_t *);
void pong_init_ball_svr(pong_server_t *);
void pong_init_ball_clt(pong_client_t *);

#endif
