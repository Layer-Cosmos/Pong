#ifndef SERVER_H
#define SERVER_H

#include "network_msg.h"
#include "types.h"

server_t *server_init(const int, const size_t);
int server_wait_conn(server_t *);
int server_send_msg(const server_t *, const char *);
char *server_next_msg(const server_t *);

#endif
