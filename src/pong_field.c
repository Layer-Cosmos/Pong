//
// Created by layer on 06/08/17.
//
#include "pong_field.h"

pong_field_t *pong_field_init(const size_t height, const size_t width, const color_t color) {
    pong_field_t *ret = {NULL};
    int i;
    //*ret = {NULL};
    ret = malloc(sizeof(*ret) * 6);

    /*ret->color.r = color.r;
    ret->color.g = color.g;
    ret->color.b = color.b;*/

    for(i = 0; i < 16; i++){
        ret[i].color.r = color.r;
        ret[i].color.g = color.g;
        ret[i].color.b = color.b;
        ret[i].rect.h = height;
        ret[i].rect.w = width;
        //ret[i].rect.x = 50;
        //ret[i].rect.y = 20 * i;

    }
    return ret;

}

int pong_field_draw(pong_field_t *field, pong_window_t *window, const size_t x, const size_t y) {
    SDL_Renderer *ren;
    color_t *color;
    int i;

    color = &(field->color);
    ren = window->ren;

    for(i = 0; i < 16; i++){
        field[i].rect.x = x;
        field[i].rect.y = y * i;
        SDL_SetRenderDrawColor(ren, color->r, color->g, color->b, SDL_ALPHA_OPAQUE);
        SDL_RenderFillRect(ren, &(field[i].rect));
        SDL_RenderDrawRect(ren, &(field[i].rect));

    }



    return 0;
}


