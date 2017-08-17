#ifndef PONG_EVENT
#define PONG_EVENT

#include "client.h"
#include "pong_client.h"
#include "pong_game.h"
#include "pong_msg.h"
#include "pong_paddle.h"
#include "pong_server.h"
#include "types.h"
#include <pthread.h>
#include <signal.h>

void pong_event_clt_mng(pong_client_t *, bool *);
void pong_event_svr_mng(pong_server_t *, bool *);

#endif
