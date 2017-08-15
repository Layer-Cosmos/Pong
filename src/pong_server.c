#include "pong_server.h"

static char *int_to_str(int nb) {
	char *ret;
	size_t length;
	char buff[2048];

	snprintf(buff, 2048, "%d", nb);
	length = strlen(buff);

	ret = malloc(length + 1);
	memmove(ret, buff, length);
	ret[length] = '\0';

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

void pong_server_send_lost(const pong_server_t *pg_server) {
	char *msg;
	size_t length;

	length = strlen(LOST_NETWORK_MSG) + strlen(END_NETWORK_MSG);
	msg = malloc(length + 1);
	snprintf(msg, length, "%s%s", LOST_NETWORK_MSG, END_NETWORK_MSG);
	server_send_msg(pg_server->server, msg);

	free(msg);
}

void pong_server_send_won(const pong_server_t *pg_server) {
	char *msg;
	size_t length;

	length = strlen(WON_NETWORK_MSG) + strlen(END_NETWORK_MSG);
	msg = malloc(length + 1);
	snprintf(msg, length, "%s%s", WON_NETWORK_MSG, END_NETWORK_MSG);
	server_send_msg(pg_server->server, msg);

	free(msg);
}

void pong_server_init(pong_server_t *pg_server, const int port, const size_t nb_conn) {
	pg_server->server = server_init(port, nb_conn);
	pg_server->ball = NULL;
	pg_server->paddle = NULL;
	pg_server->client = malloc(sizeof(*(pg_server->client)));
}

void pong_server_wait_conn(pong_server_t *pg_server) {
	server_wait_conn(pg_server->server);
}

void pong_server_shutdown(pong_server_t *pg_server) {
	server_shutdown(pg_server->server);
}

void pong_server_next_msg(pong_server_t *pg_server) {
	char *raw_msg;

	raw_msg = server_next_msg(pg_server->server);
	if (pong_msg_is_key(raw_msg)) {
		if (pong_msg_is_key_up(raw_msg)) {
			pong_paddle_go_up(pg_server->client->paddle);
			pong_server_send_cpaddle(pg_server);
		} else if (pong_msg_is_key_down(raw_msg)) {
			pong_paddle_go_down(pg_server->client->paddle);
			pong_server_send_cpaddle(pg_server);
		}
	}

	free(raw_msg);
}
