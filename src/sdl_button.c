#include "sdl_button.h"

static TTF_Font *init_font(const char *font_file, const size_t size) {
	TTF_Font *ret;

	TTF_Init();
	ret = TTF_OpenFont(font_file, size);

	return ret;
}

static bool is_in_range(const SDL_Rect rect, const size_t x, const size_t y) {
	size_t x_max;
	size_t y_max;
	size_t x_min;
	size_t y_min;
	bool ret;

	ret = false;
	x_min = rect.x;
	y_min = rect.y;
	x_max = rect.x + rect.w;
	y_max = rect.y + rect.h;

	if (x >= x_min && x <= x_max) {
		if (y >= y_min && y <= y_max) {
			ret = true;
		}
	}

	return ret;
}

sdl_button_t *sdl_button_init(const SDL_Rect rect, const char *str) {
	sdl_button_t *ret;
	size_t str_len;

	ret = malloc(sizeof(*ret));
	if (ret == NULL)
		return NULL;

	str_len = strlen(str);
	ret->text = malloc(str_len + 1);
	if (ret->text == NULL) {
		free(ret);
		return NULL;
	}

	memmove(ret->text, str, str_len);
	ret->text[str_len] = 0;

	ret->rect.h = rect.h;
	ret->rect.w = rect.w;
	ret->rect.x = rect.x;
	ret->rect.y = rect.y;

	return ret;
}

bool sdl_button_pressed(const sdl_button_t *button) {
	SDL_Event event;
	bool ret;

	ret = false;
	SDL_PollEvent(&event);

	if (event.type == SDL_MOUSEBUTTONUP) {
		if (event.button.button == SDL_BUTTON_LEFT) {
			if (is_in_range(button->rect, event.button.x, event.button.y))
				ret = true;
		}
	}

	return ret;
}

void sdl_button_draw(const sdl_button_t *button, SDL_Window *window) {
	TTF_Font *font;
	SDL_Surface *surface;
	SDL_Texture *texture;
	SDL_Color white;
	SDL_Renderer *renderer;

	white.g = 255;
	white.r = 255;
	white.b = 255;
	white.a = 255;

	font = init_font(FONT_PATH, 24);
	surface = TTF_RenderText_Solid(font, button->text, white);
	renderer = SDL_CreateRenderer(window, -1, 0);
	texture = SDL_CreateTextureFromSurface(renderer, surface);

	SDL_RenderCopy(renderer, texture, NULL, &(button->rect));

	SDL_DestroyTexture(texture);
	SDL_FreeSurface(surface);
}
