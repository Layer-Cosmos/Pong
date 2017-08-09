#include "pong_paddle.h"

pong_paddle_t *pong_paddle_init(const size_t height, const size_t width, const color_t color) {
	pong_paddle_t *ret;

	ret = malloc(sizeof(*ret));

	ret->rect.h = height;
	ret->rect.w = width;

	ret->color.r = color.r;
	ret->color.g = color.g;
	ret->color.b = color.b;

	return ret;
}

int pong_paddle_draw(pong_paddle_t *paddle, pong_window_t *window, const size_t x, const size_t y) {
	SDL_Renderer *ren;
	color_t *color;

	color = &(paddle->color);
	ren = window->ren;
	paddle->rect.x = x;
	paddle->rect.y = y;

	SDL_SetRenderDrawColor(ren, color->r, color->g, color->b, SDL_ALPHA_OPAQUE);
	SDL_RenderFillRect(ren, &(paddle->rect));
	SDL_RenderDrawRect(ren, &(paddle->rect));

	return 0;
}

void pong_paddle_go_up(pong_paddle_t *paddle) {
	paddle->rect.y--;
}

void pong_paddle_go_down(pong_paddle_t *paddle) {
	paddle->rect.y++;
}
