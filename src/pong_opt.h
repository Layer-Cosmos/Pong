#ifndef PONG_OPT_H
#define PONG_OPT_H

#include "pong_client.h"
#include "pong_server.h"
#include "types.h"
#include <stdbool.h>

bool pong_opt_is_server(int, char **);
pong_opt_server_t *pong_opt_get_server(int, char **);
bool pong_opt_is_client(int, char **);
pong_opt_client_t *pong_opt_get_client(int, char **);

#endif
