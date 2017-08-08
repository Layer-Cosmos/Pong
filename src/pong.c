#include "client.h"
#include "color.h"
#include "pong_ball.h"
#include "pong_paddle.h"
#include "pong_client.h"
#include "pong_game.h"
#include "pong_server.h"
#include "pong_window.h"
#include "pong_field.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

static int manage_events() {
    SDL_Event event;

    SDL_PollEvent(&event);
    if(event.type == SDL_QUIT) {
        return 1;
    }
    return 0;
}

int main() {

	/*pong_client_t client;
	//pong_server_t server;
	//int stop = 0;

	pong_client_init(&client);
	//pong_server_init(&server, 55225, 2);

	server.ball = pong_ball_init(20, 20, color_black());
	server.ball->rect.x = 57845;
	server.ball->rect.y = 7076;
	server.paddle = malloc(sizeof(struct pong_paddle));
	server.paddle->rect.x = 34;
	server.paddle->rect.y = 67;

	//client.ball = malloc(sizeof(struct pong_ball));
	client.paddle_s = malloc(sizeof(struct pong_paddle));
	//176.144.49.140
	pong_client_connect(&client, "176.144.49.140", 55220);
	//pong_server_wait_conn(&server);

	//pong_server_send_spaddle(&server);
	//pong_client_next_msg(&client);
	//printf("%d %d\n", client.paddle_s->rect.x, client.paddle_s->rect.y);
	while(true){
		server.paddle->rect.x++;
		server.paddle->rect.y++;
		pong_server_send_spaddle(&server);
        pong_client_next_msg(&client);
		printf("%d %d\n", client.paddle_s->rect.x, client.paddle_s->rect.y);
	}*/
    pong_paddle_t *paddle;
    pong_window_t *window;
    pong_field_t *field;
    pong_ball_t *ball;

    size_t height = 20;
    size_t width = 20;

    int stop;

    window = pong_window_new(800, color_black());
    field = pong_field_init(window, color_white());
    paddle = pong_paddle_init(50, width, color_white());
    ball = pong_ball_init(20, color_white());

    stop = 0;


    while(!stop){
        stop = manage_events();
        pong_window_draw(window);
        pong_field_draw(field, window);
        pong_paddle_draw(paddle, window, height, width);
        pong_ball_draw(ball, window);
        pong_ball_move(ball, window);
        usleep(1);
    }




    printf("salut");



}
