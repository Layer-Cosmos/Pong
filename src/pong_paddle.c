#include "pong_paddle.h"

pong_paddle_t *pong_paddle_init(size_t x, size_t y, const color_t color, unsigned int player) {
	pong_paddle_t *ret;

	ret = malloc(sizeof(*ret));

	ret->rect.h = 80;
	ret->rect.w = 20;

    if(player == 1){
        ret->rect.x = 20;
        ret->rect.y = (y - ret->rect.h) / 2;
    }
    else{
        ret->rect.x = x - 40;
        ret->rect.y = (y - ret->rect.h) / 2;
    }


	ret->color.r = color.r;
	ret->color.g = color.g;
	ret->color.b = color.b;

	return ret;
}

int pong_paddle_draw(pong_paddle_t *paddle, pong_window_t *window) {
	SDL_Renderer *ren;
	color_t *color;

	color = &(paddle->color);
	ren = window->ren;

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
