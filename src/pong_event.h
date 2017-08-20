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

void pong_event_init(enum pong_type, void *, bool *);
void pong_event_start();
void pong_event_kill_all();
void pong_event_sdl();

#endif
