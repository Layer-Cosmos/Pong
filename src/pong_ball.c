#include "pong_ball.h"

pong_ball_t *pong_ball_move(pong_ball_t *ball, pong_window_t *window){

    if(ball->rect.x >= 0) {
        if ((unsigned)ball->rect.x >= (window->width - 20)) {
            ball->velocityX = -1.0f;
        } else if (ball->rect.x <= 0) {
            ball->velocityX = 1.0f;
        }
    }
    if(ball->rect.y >= 0) {
        if ((unsigned)ball->rect.y >= (window->height - 20)) {
            ball->velocityY = -1.0f;
        } else if (ball->rect.y <= 0) {
            ball->velocityY = 1.0f;
        }
    }

    ball->rect.x += ball->velocityX;
    ball->rect.y += ball->velocityY;

    printf("%d\n", ball->rect.x);

    return ball;
}

pong_ball_t *pong_ball_init(const size_t size, const color_t color) {
	pong_ball_t *ret;

	ret = malloc(sizeof(*ret));

	ret->velocityX = 1.0f;
	ret->velocityY = 1.0f;

	ret->rect.h = size;
	ret->rect.w = size;

    ret->rect.x = 50;
    ret->rect.y = 20;

	ret->color.r = color.r;
	ret->color.g = color.g;
	ret->color.b = color.b;

	return ret;
}

int pong_ball_draw(pong_ball_t *ball, pong_window_t *window) {
	SDL_Renderer *ren;
	color_t *color;

	color = &(ball->color);
	ren = window->ren;

	SDL_SetRenderDrawColor(ren, color->r, color->g, color->b, SDL_ALPHA_OPAQUE);
	SDL_RenderFillRect(ren, &(ball->rect));
	SDL_RenderDrawRect(ren, &(ball->rect));

	return 0;
}
