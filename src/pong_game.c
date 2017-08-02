#include "pong_game.h"

int pong_game_quit(pong_window_t *win) {
	SDL_DestroyRenderer(win->ren);
	SDL_DestroyWindow(win->win);
	SDL_Quit();

	return 0;
}
