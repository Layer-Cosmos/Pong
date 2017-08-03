#include "pong_ball.h"

pong_ball_t *pong_ball_init(const int velocity, const size_t size, const color_t color) {
	pong_ball_t *ret;

	ret = malloc(sizeof(*ret));

	ret->velocity = velocity;

	ret->rect.h = size;
	ret->rect.w = size;

	ret->color.r = color.r;
	ret->color.g = color.g;
	ret->color.b = color.b;

	return ret;
}

int pong_ball_draw(pong_ball_t *ball, pong_window_t *window, const size_t x, const size_t y) {
	SDL_Renderer *ren;
	color_t *color;

	color = &(ball->color);
	ren = window->ren;
	ball->rect.x = x;
	ball->rect.y = y;

	SDL_SetRenderDrawColor(ren, color->r, color->g, color->b, SDL_ALPHA_OPAQUE);
	SDL_RenderFillRect(ren, &(ball->rect));
	SDL_RenderDrawRect(ren, &(ball->rect));

	return 0;
}
