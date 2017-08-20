//
// Created by layer on 15/08/17.
//

#include "pong_score.h"

void pong_score_add(pong_score_t *score, int player){
    if(player == 1){
        score->player1++;
    } else{
        score->player2++;
    }
}

pong_score_t *pong_score_init(const color_t color, pong_window_t *window){
    pong_score_t *ret;
    if(TTF_Init() == -1){
        printf("TTF_Init: %s\n", TTF_GetError());
        exit(2);
    }

    ret = malloc(sizeof(*ret));

    ret->rect.w = 200;
    ret->rect.h = 100;

    ret->rect.x = (window->width / 2) - (ret->rect.w / 2) - 10;
    ret->rect.y = 0;

    ret->color.r = color.r;
    ret->color.g = color.g;
    ret->color.b = color.b;

    ret->player1 = 0;
    ret->player2 = 0;

    ret->text = TTF_OpenFont(FONT_PATH, 21);
    if(!ret->text){
        printf("TTF_OpenFont: %s\n", TTF_GetError());
    }

    return ret;

}
int pong_score_draw(pong_score_t *score, pong_window_t *window){
    SDL_Color color = { score->color.r, score->color.g, score->color.b, 0};
    SDL_Surface* surface;
    SDL_Texture* texture;

    char affichage[4] = "0 0\0";

    affichage[0] = (char)score->player1 + 48;
    affichage[2] = (char)score->player2 + 48;

    surface = TTF_RenderText_Solid(score->text, &affichage[0], color);
    texture = SDL_CreateTextureFromSurface(window->ren, surface);

    SDL_RenderCopy(window->ren, texture, NULL, &score->rect);
    SDL_DestroyTexture(texture);
    SDL_FreeSurface(surface);

    return 0;
}


