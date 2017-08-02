#include "color.h"

const color_t color_black() {
	static color_t black;

	black.r = 0;
	black.g = 0;
	black.b = 0;

	return black;
}

const color_t color_white() {
	static color_t white;

	white.r = 255;
	white.b = 255;
	white.g = 255;

	return white;
}
