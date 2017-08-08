#ifndef CLIENT_H
#define CLIENT_H

#include "network_msg.h"
#include "types.h"

client_t *client_init();
int client_connect(client_t *, const char *, const int port);
void client_disconnect(client_t *);
int client_send_msg(const client_t *, const char *);
char *client_msg_next(const client_t *);
int client_connect_send(const client_t *);

#endif
