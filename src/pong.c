#include "client.h"
#include "color.h"
#include "pong_ball.h"
#include "pong_client.h"
#include "pong_game.h"
#include "pong_server.h"
#include "pong_window.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main() {
	pong_client_t client;
	pong_server_t server;

	pong_client_init(&client);
	pong_server_init(&server, 55218, 2);

	server.ball = pong_ball_init(20, 20, color_black());
	server.ball->rect.x = 57845;
	server.ball->rect.y = 7076;
	server.paddle = malloc(sizeof(struct pong_paddle));
	server.paddle->rect.x = 34;
	server.paddle->rect.y = 67;

	client.ball = malloc(sizeof(struct pong_ball));
	client.paddle_s = malloc(sizeof(struct pong_paddle));

	pong_client_connect(&client, "192.168.1.98", 55218);
	pong_server_wait_conn(&server);

	pong_server_send_spaddle(&server);
	pong_client_next_msg(&client);

	printf("%d %d\n", client.paddle_s->rect.x, client.paddle_s->rect.y);
}
