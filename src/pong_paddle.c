#include "pong_paddle.h"

pong_paddle_t *pong_paddle_init(pong_window_t *window, const color_t color, unsigned int player) {
	pong_paddle_t *ret;

	ret = malloc(sizeof(*ret));

	ret->window = window;

	ret->rect.h = 80;
	ret->rect.w = 20;
    ret->velocity = 1;

    if(player == 1){
        ret->rect.x = 20;
        ret->rect.y = (window->height - ret->rect.h) / 2;
    }
    else{
        ret->rect.x = window->width - 40;
        ret->rect.y = (window->height - ret->rect.h) / 2;
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
	if(paddle->rect.y > 0){
		paddle->rect.y -= paddle->velocity;
	}
	else{
		paddle->rect.y = 0;
	}

}

void pong_paddle_go_down(pong_paddle_t *paddle) {
	if((unsigned)paddle->rect.y < paddle->window->height - paddle->rect.h) {
		paddle->rect.y += paddle->velocity;
	}
	else{
		paddle->rect.y = (int)paddle->window->height - paddle->rect.h;
	}
}
