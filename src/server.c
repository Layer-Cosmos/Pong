#include "server.h"

static void init_sockaddr(struct sockaddr_in *, const int);
static int init_socket_server(server_t *);
static int server_start_listen(server_t *, const size_t);
static int init_conn(server_t *, struct sockaddr_in *);

static int init_conn(server_t *server, struct sockaddr_in *serv_addr) {

	if (init_socket_server(server) == -1) {
		return -1;
	}

	init_sockaddr(serv_addr, server->port);
	return 0;
}

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

server_t *server_init(const int port) {
	server_t *ret;

	ret = malloc(sizeof *ret);
	if (ret == NULL)
		return NULL;

	ret->port = port;
	ret->sock = -1;
	ret->sock_client = -1;

	return ret;
}

int server_wait_conn(server_t *server, const size_t nb_conn) {
	int ret;
	struct sockaddr_in serv_addr;

	init_conn(server, &serv_addr);

	bind(server->sock, (struct sockaddr *)&(serv_addr), sizeof(serv_addr));

	if (server_start_listen(server, nb_conn) == -1) {
		return -1;
	}

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
	return network_msg_next(server->sock_client);
}

void server_shutdown(const server_t *server) {
	shutdown(server->sock, SHUT_RDWR);
	close(server->sock);
}
