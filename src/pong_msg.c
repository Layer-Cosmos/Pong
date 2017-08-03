#include "pong_msg.h"

static char *pong_msg_key(const char *key_str) {
	char *ret;
	size_t key_len;
	size_t end_len;
	size_t pre_len;

	key_len = strlen(key_str);
	pre_len = strlen(KEY_NETWORK_MSG_PREFIX);
	end_len = strlen(END_NETWORK_MSG);

	ret = malloc(key_len + pre_len + end_len + 1);

	strncpy(ret, KEY_NETWORK_MSG_PREFIX, pre_len);
	strncpy(ret + pre_len, key_str, key_len);
	strncpy(ret + pre_len + key_len, END_NETWORK_MSG, end_len);

	return ret;
}

bool pong_msg_is_key(const char *msg) {
	bool ret;

	ret = network_msg_starts_with(msg, KEY_NETWORK_MSG_PREFIX);

	return ret;
}

bool pong_msg_is_paddle(const char *msg) {
	bool ret;

	ret = network_msg_starts_with(msg, PADDLE_NETWORK_MSG_PREFIX);

	return ret;
}

bool pong_msg_is_ball(const char *msg) {
	bool ret;

	ret = network_msg_starts_with(msg, BALL_NETWORK_MSG_PREFIX);

	return ret;
}

char *pong_msg_key_up() {
	char *ret;

	ret = pong_msg_key(KEY_UP_NETWORK_MSG);

	return ret;
}

char *pong_msg_key_down() {
	char *ret;

	ret = pong_msg_key(KEY_DOWN_NETWORK_MSG);

	return ret;
}
