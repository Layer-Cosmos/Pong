#include "server.h"

static void init_sockaddr(struct sockaddr_in *sockaddr, const int port) {
	sockaddr->sin_family = AF_INET;
	sockaddr->sin_addr.s_addr = htonl(INADDR_ANY);
	sockaddr->sin_port = htons(port);
}

static int init_socket_server(server_t *server) {
	server->sock = socket(AF_INET, SOCK_STREAM, 0);

	if (server->sock == -1)
		perror("socket server");

	return server->sock;
}

static int server_start_listen(server_t *server, const size_t nb_conn) {
	int ret;

	ret = listen(server->sock, nb_conn);

	if (ret == -1) {
		perror("Server can't listen");
	}

	return ret;
}

server_t *server_init(const int port, const size_t nb_conn) {
	server_t *ret;

	struct sockaddr_in serv_addr;

	ret = malloc(sizeof *ret);
	if (ret == NULL)
		return NULL;

	if (init_socket_server(ret) == -1) {
		free(ret);
		return NULL;
	}

	init_sockaddr(&serv_addr, port);
	bind(ret->sock, (struct sockaddr *)&serv_addr, sizeof(serv_addr));

	if (server_start_listen(ret, nb_conn) == -1) {
		free(ret);
		return NULL;
	}

	return ret;
}

int server_wait_conn(server_t *server) {
	int ret;

	server->sock_client = accept(server->sock, (struct sockaddr *)NULL, NULL);
	ret = server->sock_client;
	if (ret == -1)
		perror("Server can't accept connection");

	return ret;
}

int server_send_msg(const server_t *server, const char *msg) {
	return network_msg_send(server->sock_client, msg);
}

char *server_next_msg(const server_t *server) {
	return network_msg_next(server->sock);
}
