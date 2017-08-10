#ifndef PONG_BUTTON_H
#define PONG_BUTTON_H

#include "color.h"
#include "types.h"
#include <SDL2/SDL_ttf.h>
#include <stdbool.h>

sdl_button_t *sdl_button_init(const SDL_Rect, const char *);
void sdl_button_draw(const sdl_button_t *, SDL_Window *);
bool sdl_button_pressed(const sdl_button_t *);

#endif
