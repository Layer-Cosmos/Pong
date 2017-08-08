#include "client.h"

client_t *client_init() {
	client_t *ret;

	ret = malloc(sizeof(*ret));
	if (ret == NULL)
		return NULL;

	return ret;
}

int client_connect(client_t *client, const char *ip, const int port) {
	struct sockaddr_in serv_addr;

	client->sock = socket(AF_INET, SOCK_STREAM, 0);
	if (client->sock < 0) {
		perror("Client socket");
		return -1;
	}

	serv_addr.sin_family = AF_INET;
	serv_addr.sin_port = htons(port);
	serv_addr.sin_addr.s_addr = inet_addr(ip);

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
