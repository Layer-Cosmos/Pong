#include "pong_client.h"

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

void pong_client_send_key(const client_t *client, const enum key key_pressed) {
	char *msg_to_send;

	msg_to_send = key_msg(key_pressed);
	client_send_msg(client, msg_to_send);

	free(msg_to_send);
}
