#ifndef PONG_MSG_H
#define PONG_MSG_H

#include "network_msg.h"
#include "types.h"
#include <stdbool.h>

bool pong_msg_is_key(const char *);
bool pong_msg_is_paddle(const char *);
bool pong_msg_is_ball(const char *);
char *pong_msg_key_up();
char *pong_msg_key_down();

#endif
