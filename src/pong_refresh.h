#ifndef PONG_REFRESH_H
#define PONG_REFRESH_H

#include "pong_ball.h"
#include "pong_client.h"
#include "pong_field.h"
#include "pong_server.h"
#include "pong_window.h"

void pong_refresh_screen_clt(pong_client_t *, pong_window_t *);
void pong_refresh_screen_svr(pong_server_t *, pong_window_t *);

#endif
