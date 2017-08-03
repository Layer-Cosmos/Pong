#include "coordinates.h"

void coordinates_decrease(SDL_Rect *rect) {
	rect->x--;
	rect->y--;
}

void coordinates_decrease_x(SDL_Rect *rect) {
	rect->x--;
}

void coordinates_decrease_y(SDL_Rect *rect) {
	rect->y--;
}
