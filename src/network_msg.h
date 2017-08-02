#ifndef NETWORK_MSG
#define NETWORK_MSG

#include "types.h"

int network_msg_send(const socket_t, const char *msg);
char *network_msg_next(const socket_t);

#endif
