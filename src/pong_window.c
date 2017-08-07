#include "pong_window.h"

static int init() {
	if (SDL_Init(SDL_INIT_VIDEO) != 0) {
		SDL_ERROR;
		return -1;
	} else {
		return 0;
	}
}

static void set_color(color_t *color, const color_t color_source) {
	color->r = color_source.r;
	color->b = color_source.b;
	color->g = color_source.g;
}

static void set_dimensions(pong_window_t *win, const size_t size) {
	win->height = size;
	win->width = size;
}

pong_window_t *pong_window_new(const size_t size, const color_t color) {
	SDL_Window *window;
	pong_window_t *ret;

	if (init() == -1)
		return NULL;

	window = SDL_CreateWindow(
	    "Pong",
	    SDL_WINDOWPOS_CENTERED,
	    SDL_WINDOWPOS_CENTERED,
	    size,
	    size,
	    SDL_WINDOW_OPENGL);

	if (window == NULL) {
		SDL_ERROR;
		return NULL;
	}

	ret = malloc(sizeof(*ret));
	if (ret == NULL)
		return NULL;

	ret->win = window;

	set_color(&(ret->bg_color), color);
	set_dimensions(ret, size);

	ret->ren = SDL_CreateRenderer(ret->win, -1, SDL_RENDERER_ACCELERATED);

	return ret;
}

void pong_window_draw(pong_window_t *window) {
	color_t *color;

	color = &(window->bg_color);
	SDL_SetRenderDrawColor(window->ren, color->r, color->g, color->b, SDL_ALPHA_OPAQUE);
	SDL_RenderPresent(window->ren);
	SDL_RenderClear(window->ren);
}
