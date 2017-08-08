#ifndef PONG_SERVER_H
#define PONG_SERVER_H

#include "pong_msg.h"
#include "pong_paddle.h"
#include "server.h"
#include "types.h"
#include <math.h>
#include <stdio.h>

void pong_server_init(pong_server_t *, const int, const size_t);
void pong_server_send_ball(const pong_server_t *);
void pong_server_send_spaddle(const pong_server_t *);
void pong_server_send_cpaddle(const pong_server_t *);
void pong_server_send_lost(const pong_server_t *);
void pong_server_send_won(const pong_server_t *);
void pong_server_wait_conn(pong_server_t *);
void pong_server_shutdown(pong_server_t *);
void pong_server_next_msg(pong_server_t *);

#endif
