//
// Created by layer on 06/08/17.
//
#include "pong_field.h"

pong_field_t *pong_field_init(pong_window_t *window, const color_t color) {
    pong_field_t *ret = {NULL};
    int i;
    int nbCube;
    nbCube = window->height / 40;


    ret = malloc(sizeof(*ret) * nbCube);
    ret->nbCube = (window->height / 40);
    ret->middle = (window->width / 2) - 20;
    //printf("%d", ret->nbCube);

    for(i = 0; i < ret->nbCube; i++){
        ret[i].color.r = color.r;
        ret[i].color.g = color.g;
        ret[i].color.b = color.b;
        ret[i].rect.h = 20;
        ret[i].rect.w = 20;
    }
    return ret;

}

int pong_field_draw(pong_field_t *field, pong_window_t *window) {
    SDL_Renderer *ren;
    color_t *color;
    int i;

    color = &(field->color);
    ren = window->ren;

    for(i = 0; i < field->nbCube; i++){
        field[i].rect.x = field->middle;
        field[i].rect.y = (field->rect.h * i) * 2;
        SDL_SetRenderDrawColor(ren, color->r, color->g, color->b, SDL_ALPHA_OPAQUE);
        SDL_RenderFillRect(ren, &(field[i].rect));
        SDL_RenderDrawRect(ren, &(field[i].rect));

    }

    return 0;
}


