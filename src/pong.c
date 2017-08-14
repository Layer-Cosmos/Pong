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
    pong_paddle_t *paddle2;
    pong_window_t *window;
    pong_field_t *field;
    pong_ball_t *ball;

    Uint32 oldTime;
    //Uint32 currentFrame = 0;
    //Uint32 frames = 0;
    Uint32 startTime = SDL_GetTicks();
    float ftime;


    //nextTime = SDL_GetTicks() + TICK_INTERVAL;

    //size_t height = 20;
    //size_t width = 20;

    int stop;

    window = pong_window_new(800, color_black());
    field = pong_field_init(window, color_white());
    paddle = pong_paddle_init(window->width, window->height, color_white(), 1);
    paddle2 = pong_paddle_init(window->width, window->height, color_white(), 2);
    ball = pong_ball_init(20, color_white());

    stop = 0;
    //int deltaAccumulator = 0;

    while(!stop){
        oldTime = startTime;
        startTime = SDL_GetTicks();
        ftime = (startTime - oldTime) / 100.0f;
        //tempsActuel = SDL_GetTicks();

        /*nextTime = SDL_GetTicks() / 1000;
        int delta = nextTime - startTime;
        startTime = nextTime;
        deltaAccumulator += delta;
        frames++;
        if(frames == 10){
            int avgDelta = deltaAccumulator / 10;
            int fps = 1 / avgDelta;
            frames = 0;
            deltaAccumulator = 0;
            printf("FPS : %d", fps);
        }*/

        /*if(1000/30>SDL_GetTicks()-startTime){
            SDL_Delay(1000/30-(SDL_GetTicks()-startTime));
        }*/
        stop = manage_events();
        pong_window_draw(window);
        pong_field_draw(field, window);
        pong_paddle_draw(paddle, window);
        pong_paddle_draw(paddle2, window);
        pong_ball_draw(ball, window);
        if(ball->x < window->width / 2) {
            pong_ball_update(ball, window, paddle, ftime);
        } else{
            pong_ball_update(ball, window, paddle2, ftime);
        }

        SDL_Delay(16);


    }


}
