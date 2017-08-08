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

bool pong_msg_is_key_up(const char *msg) {
	bool ret;
	int cmp_res;
	size_t key_msg_pre_len;
	size_t key_up_msg_len;

	key_up_msg_len = strlen(KEY_UP_NETWORK_MSG);
	key_msg_pre_len = strlen(KEY_NETWORK_MSG_PREFIX);

	cmp_res = strncmp(msg + key_msg_pre_len, KEY_UP_NETWORK_MSG, key_up_msg_len);
	ret = cmp_res == 0 ? true : false;

	return ret;
}

bool pong_msg_is_key_down(const char *msg) {
	bool ret;
	int cmp_res;
	size_t key_msg_pre_len;
	size_t key_down_msg_len;

	key_down_msg_len = strlen(KEY_DOWN_NETWORK_MSG);
	key_msg_pre_len = strlen(KEY_NETWORK_MSG_PREFIX);

	cmp_res = strncmp(msg + key_msg_pre_len, KEY_DOWN_NETWORK_MSG, key_down_msg_len);
	ret = cmp_res == 0 ? true : false;

	return ret;
}

bool pong_msg_is_spaddle(const char *msg) {
	bool ret;

	ret = network_msg_starts_with(msg, SPADDLE_NETWORK_MSG_PREFIX);

	return ret;
}

bool pong_msg_is_cpaddle(const char *msg) {
	bool ret;

	ret = network_msg_starts_with(msg, CPADDLE_NETWORK_MSG_PREFIX);

	return ret;
}

bool pong_msg_is_ball(const char *msg) {
	bool ret;

	ret = network_msg_starts_with(msg, BALL_NETWORK_MSG_PREFIX);

	return ret;
}

bool pong_msg_is_lost(const char *msg) {
	bool ret;

	ret = network_msg_starts_with(msg, LOST_NETWORK_MSG);

	return ret;
}

bool pong_msg_is_won(const char *msg) {
	bool ret;

	ret = network_msg_starts_with(msg, WON_NETWORK_MSG);

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
