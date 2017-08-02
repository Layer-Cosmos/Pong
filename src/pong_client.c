#include "pong_client.h"

void pong_client_send_key(const client_t *client, const enum key key_pressed) {

	if (key_pressed == DOWN_KEY)
		client_send_msg(client, "kdown\n");
	else if (key_pressed == UP_KEY)
		client_send_msg(client, "kup\n");
}
