#ifndef PONG_SERVER_H
#define PONG_SERVER_H

#include "server.h"
#include "types.h"
#include <math.h>
#include <stdio.h>

void pong_server_send_ball(const server_t *, const pong_ball_t *);
void pong_server_send_paddle(const server_t *, const pong_paddle_t *);

#endif
