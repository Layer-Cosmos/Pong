#include "pong_client.h"

static void client_send_end(const client_t *client) {
	client_send_msg(client, NETWORK_TRANSMISSION_END);
}

static char *key_down_msg() {
	char *ret;
	size_t size_to_alloc;

	size_to_alloc = strlen(KEY_DOWN_NETWORK_MSG) + strlen(END_NETWORK_MSG) + strlen(KEY_NETWORK_MSG_PREFIX) + 1;
	ret = malloc(size_to_alloc);

	sprintf(ret, "%s%s%s", KEY_NETWORK_MSG_PREFIX, KEY_DOWN_NETWORK_MSG, END_NETWORK_MSG);

	return ret;
}

static char *key_up_msg() {
	char *ret;
	size_t size_to_alloc;

	size_to_alloc = strlen(KEY_UP_NETWORK_MSG) + strlen(END_NETWORK_MSG) + strlen(KEY_NETWORK_MSG_PREFIX) + 1;
	ret = malloc(size_to_alloc);

	sprintf(ret, "%s%s%s", KEY_NETWORK_MSG_PREFIX, KEY_UP_NETWORK_MSG, END_NETWORK_MSG);

	return ret;
}

static char *key_msg(const enum key key_pressed) {
	char *ret;

	ret = NULL;
	if (key_pressed == DOWN_KEY)
		ret = key_down_msg();
	else if (key_pressed == UP_KEY)
		ret = key_up_msg();

	return ret;
}

static bool is_number(const char c) {
	bool ret;

	ret = (c <= '9' && c >= '0') ? true : false;

	return ret;
}

static int str_to_int(const char *str, int *nb) {
	size_t length;
	size_t idx;

	length = strlen(str);
	idx = 0;
	*nb = 0;

	while (idx < length && is_number(str[idx])) {
		*nb = 10 * (*nb) + (str[idx] - 48);
		idx++;
	}

	return idx;
}

static void coord_from_str(const char *coord_str, SDL_Rect *rect) {
	int idx;

	idx = str_to_int(coord_str, &(rect->x));
	str_to_int(coord_str + idx + 1, &(rect->y));
}

void pong_client_init(pong_client_t *pg_clt, const char *ip, const int port) {
	pg_clt->client = client_init(ip, port);
	pg_clt->ball = NULL;
	pg_clt->paddle = NULL;
}

void pong_client_connect(pong_client_t *pg_clt) {
	client_connect(pg_clt->client);
}

void pong_client_disconnect(pong_client_t *pg_clt) {
	client_send_end(pg_clt->client);
	client_disconnect(pg_clt->client);
}

void pong_client_send_key(const pong_client_t *client, const enum key key_pressed) {
	char *msg_to_send;

	msg_to_send = key_msg(key_pressed);
	client_send_msg(client->client, msg_to_send);

	free(msg_to_send);
}

int pong_client_next_msg(pong_client_t *pg_clt) {
	char *raw_msg;

	raw_msg = network_msg_next(pg_clt->client->sock);
	if (raw_msg == NULL || pong_msg_is_end(raw_msg))
		return -1;

	if (pong_msg_is_spaddle(raw_msg)) {
		coord_from_str(raw_msg + strlen(SPADDLE_NETWORK_MSG_PREFIX), &(pg_clt->paddle_s->rect));
	} else if (pong_msg_is_cpaddle(raw_msg)) {
		coord_from_str(raw_msg + strlen(CPADDLE_NETWORK_MSG_PREFIX), &(pg_clt->paddle->rect));
	} else if (pong_msg_is_ball(raw_msg)) {
		coord_from_str(raw_msg + strlen(BALL_NETWORK_MSG_PREFIX), &(pg_clt->ball->rect));
	}

	free(raw_msg);
	return 0;
}
