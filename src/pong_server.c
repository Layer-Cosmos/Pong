#include "pong_server.h"

static void send_coordinates(const server_t *server, const char prefix, const size_t x, const size_t y) {
	char *msg;

	msg = malloc(7);
	sprintf(msg, "%c%ld,%ld\n", prefix, x, y);

	server_send_msg(server, msg);

	free(msg);
}

void pong_server_send_ball(const server_t *server, const pong_ball_t *ball) {
	send_coordinates(server, 'b', ball->rect.x, ball->rect.y);
}

void pong_server_send_paddle(const server_t *server, const pong_paddle_t *paddle) {
	send_coordinates(server, 'p', paddle->rect.x, paddle->rect.y);
}
