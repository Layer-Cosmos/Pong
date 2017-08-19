#include "pong.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(int argc, char *argv[]) {
	pong_client_t *pg_client;
	pong_server_t *pg_server;
	pong_field_t *field;
	pong_ball_t *ball_ptr;
	void *opt;
	enum pong_type type;
	pong_window_t *window;
	bool run;

	Uint32 oldTime;
	Uint32 startTime;
	float ftime;

	run = false;
	window = pong_window_new(800, color_black());
	field = pong_field_init(window, color_white());
	pong_event_sdl();

	opt = pong_init_type(argc, argv, &type);
	if (type == server) {
		pg_server = pong_init_network(opt, type);
		pong_event_svr_mng(pg_server, &run);
		pong_init_paddle_svr(pg_server, window);
		pong_init_ball_svr(pg_server);
		ball_ptr = pg_server->ball;
	} else {
		pg_client = pong_init_network(opt, type);
		pong_event_clt_mng(pg_client, &run);
		pong_init_paddle_clt(pg_client, window);
		pong_init_ball_clt(pg_client);
		ball_ptr = pg_client->ball;
	}

	startTime = SDL_GetTicks();
	while (run) {
		oldTime = startTime;
		startTime = SDL_GetTicks();
		ftime = (startTime - oldTime) / 100.0f;

		pong_window_draw(window);
		pong_field_draw(field, window);

		if (type == server) {
			if (ball_ptr->x < window->width / 2) {
				pong_ball_update(ball_ptr, window, pg_server->paddle, ftime);
			} else {
				pong_ball_update(ball_ptr, window, pg_server->paddle_c, ftime);
			}
			pong_refresh_screen_svr(pg_server, window);
		} else
			pong_refresh_screen_clt(pg_client, window);

		pong_ball_draw(ball_ptr, window);
		usleep(10);
	}
}
