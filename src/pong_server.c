#include "pong_server.h"

static char *int_to_str(int nb) {
	int e;
	size_t length;
	char *ret;

	nb = abs(nb);
	e = log10(nb);
	length = e + 1;
	ret = malloc(length + 1);

	while (e >= 0) {
		e = (int)log10(nb);
		ret[e] = (nb / pow(10, e)) + 48;
		nb = nb - pow(10, ret[e] - 48);
	}

	return ret;
}

static size_t msg_size(const char *prefix, const char *x, const char *y) {
	size_t ret;

	ret = strlen(prefix);
	ret += strlen(x);
	ret += strlen(y);
	ret += strlen(END_NETWORK_MSG);

	return ret;
}

static void send_coordinates(const server_t *server, const char *prefix, const size_t x, const size_t y) {
	char *msg;
	size_t size_to_alloc;
	char *str_x;
	char *str_y;

	str_x = int_to_str(x);
	str_y = int_to_str(y);
	size_to_alloc = msg_size(prefix, str_x, str_y);
	msg = malloc(size_to_alloc + 1);
	sprintf(msg, "%s%s,%s%s", prefix, str_x, str_y, END_NETWORK_MSG);

	server_send_msg(server, msg);

	free(str_x);
	free(str_y);
	free(msg);
}

void pong_server_send_ball(const pong_server_t *pg_server) {
	send_coordinates(pg_server->server, BALL_NETWORK_MSG_PREFIX, pg_server->ball->rect.x, pg_server->ball->rect.y);
}

void pong_server_send_spaddle(const pong_server_t *pg_server) {
	send_coordinates(pg_server->server, SPADDLE_NETWORK_MSG_PREFIX, pg_server->paddle->rect.x, pg_server->paddle->rect.y);
}

void pong_server_send_cpaddle(const pong_server_t *pg_server) {
	send_coordinates(pg_server->server, CPADDLE_NETWORK_MSG_PREFIX, pg_server->client->paddle->rect.x, pg_server->paddle->rect.y);
}

void pong_server_init(pong_server_t *pg_server, const int port, const size_t nb_conn) {
	pg_server->server = server_init(port, nb_conn);
	pg_server->ball = NULL;
	pg_server->paddle = NULL;
	pg_server->client = NULL;
}

void pong_server_wait_conn(pong_server_t *pg_server) {
	server_wait_conn(pg_server->server);
}
