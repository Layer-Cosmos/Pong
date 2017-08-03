#ifndef NETWORK_MSG
#define NETWORK_MSG

#include "types.h"
#include <stdbool.h>

int network_msg_send(const socket_t, const char *msg);
char *network_msg_next(const socket_t);
bool network_msg_starts_with(const char *, const char *);

#endif
