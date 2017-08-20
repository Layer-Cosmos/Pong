#include "client.h"

static void init_ip(client_t *, const char *);

static void init_ip(client_t *client, const char *ip) {
	size_t ip_len;

	ip_len = strlen(ip);

	client->ip = malloc(ip_len + 1);
	memmove(client->ip, ip, ip_len);
	client->ip[ip_len] = '\0';
}

client_t *client_init(const char *ip, const int port) {
	client_t *ret;

	ret = malloc(sizeof(*ret));
	if (ret == NULL)
		return NULL;

	ret->sock = -1;
	init_ip(ret, ip);
	ret->port = port;

	return ret;
}

int client_connect(client_t *client) {
	struct sockaddr_in serv_addr;

	client->sock = socket(AF_INET, SOCK_STREAM, 0);
	if (client->sock < 0) {
		perror("Client socket");
		return -1;
	}

	serv_addr.sin_family = AF_INET;
	serv_addr.sin_port = htons(client->port);
	serv_addr.sin_addr.s_addr = inet_addr(client->ip);

	if (connect(client->sock, (struct sockaddr *)&serv_addr, sizeof(serv_addr)) < 0) {
		perror("Client can't connect");
		return -1;
	}

	return 0;
}

int client_send_msg(const client_t *client, const char *msg) {
	return network_msg_send(client->sock, msg);
}

char *client_msg_next(const client_t *client) {
	return network_msg_next(client->sock);
}

void client_disconnect(client_t *client) {
	close(client->sock);
}
