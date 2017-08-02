#include "pong_ball.h"
#include "pong_game.h"
#include "pong_window.h"

static int manage_events() {
	SDL_Event event;

	SDL_PollEvent(&event);
	if (event.type == SDL_QUIT) {
		return 1;
	}

	return 0;
}

int main() {
	pong_ball_t *ball;
	pong_window_t *window;
	size_t x, y;
	int stop;
	color_t ball_color;
	color_t bg_color;

	ball_color.b = 0;
	ball_color.g = 0;
	ball_color.r = 0;

	bg_color.r = 255;
	bg_color.g = 255;
	bg_color.b = 255;

	window = pong_window_new(300, bg_color);

	ball = pong_ball_init(1, 20, ball_color);
	x = 20;
	y = 20;
	stop = 0;

	while (!stop) {
		stop = manage_events();

		pong_window_draw(window);
		pong_ball_draw(ball, window, x, y);

		//pong_ball_draw(ball, window, x, y);
		usleep(5);
	}

	pong_game_quit(window);
}
