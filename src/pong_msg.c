#include "pong_msg.h"

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
