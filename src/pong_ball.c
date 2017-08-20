#include "pong_ball.h"
#include "pong_score.h"
//#include "pong_server.h"

void pong_ball_update(pong_ball_t *ball, pong_window_t *window, pong_paddle_t *paddle, float ftime){



    ball->x += (ball->velocityX * ftime);
    ball->y += (ball->velocityY * ftime);
    ball->rect.x = ball->x;
    ball->rect.y = ball->y;

        if (ball->x > (window->width - 20)) {
            pong_score_add(ball->score, 1);
            ball->velocityX *= -1.0f;
            ball->x = window->width / 2;
            ball->y = window->height / 2;
            //printf("X > \n");
        } else if (ball->x < 0) {
            pong_score_add(ball->score, 2);
            ball->velocityX *= -1.0f;
            ball->x = window->width / 2;
            ball->y = window->height / 2;

            //printf("X < \n");
        }
        if (ball->y > (window->height - 20)) {
            ball->velocityY *= -1.0f;
            ball->y = window->height - ball->rect.h;
            //printf("Y > \n");
        } else if (ball->y < 0) {
            ball->velocityY *= -1.0f;
            ball->y = 0;
            //printf("Y < \n");
        }

    if((paddle->rect.x >= ball->rect.x + ball->rect.w)
            || (paddle->rect.x + paddle->rect.w <= ball->rect.x)
            || (paddle->rect.y >= ball->rect.y + ball->rect.h)
            || (paddle->rect.y + paddle->rect.h <= ball->rect.y)){
    }else{
        //double distanceX = paddle->rect.y + paddle->rect.h / 2. - (ball->rect.y + 10);
        //printf("collision\n");
        //printf("%f\n", distanceX);
        //ball->velocityX = -distanceX * 0.03;
        //ball->velocityX = -distanceX * 0.03;
        //if(ball->velocityX)
        ball->velocityX *= -1.0f;

    }
    /*printf("VelocityY : %f\n", ball->velocityY);
    printf("%d\n", ball->rect.y);
    printf("%d\n", ball->rect.x);
    printf("Y : %f\n", ball->y);
    printf("X : %f\n", ball->x);*/
    //printf("%f\n", ball->velocityX);

    //printf("%d\n", ball->rect.x);

    /*pg_server->ball = ball;
    pong_server_send_ball(pg_server);*/

}

pong_ball_t *pong_ball_init(const size_t size, const color_t color) {
	pong_ball_t *ret;

	ret = malloc(sizeof(*ret));

	ret->velocityX = 10.0f;
	ret->velocityY = 10.0f;

	ret->rect.h = size;
	ret->rect.w = size;

    ret->rect.x = 650;
    ret->rect.y = 20;

    ret->x = 400;
    ret->y = 100;

	ret->color.r = color.r;
	ret->color.g = color.g;
	ret->color.b = color.b;

	return ret;
}

void pong_ball_draw(pong_ball_t *ball, pong_window_t *window) {
	SDL_Renderer *ren;
	color_t *color;

	color = &(ball->color);
	ren = window->ren;

	SDL_SetRenderDrawColor(ren, color->r, color->g, color->b, SDL_ALPHA_OPAQUE);
	SDL_RenderFillRect(ren, &(ball->rect));
	SDL_RenderDrawRect(ren, &(ball->rect));

}
