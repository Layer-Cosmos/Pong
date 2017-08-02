#ifndef TYPES_H
#define TYPES_H

#include <SDL2/SDL.h>
#include <arpa/inet.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <unistd.h>

#define END_NETWORK_MSG '\n'
#define MSG_BUFFER_SIZE 2048
#define SDL_ERROR fprintf(stderr, "SDL Error: %s", SDL_GetError())

struct server;
struct client;
struct pong_ball;
struct network_msg;
struct position;
struct paddle;
struct pong_window;
struct color;

typedef int socket_t;

typedef struct client client_t;
struct client {
	socket_t sock;
};

typedef struct server server_t;
struct server {
	socket_t sock;
	socket_t sock_client;
};

typedef struct network_msg network_msg_t;
struct network_msg {
	char buffer[MSG_BUFFER_SIZE];
	size_t length;
};

typedef struct color color_t;
struct color {
	Uint8 r;
	Uint8 g;
	Uint8 b;
};

typedef struct pong_ball pong_ball_t;
struct pong_ball {
	size_t velocity;
	size_t size;
	size_t angle;
	SDL_Rect rect;
	color_t color;
};

typedef struct paddle paddle_t;
struct paddle {
	size_t size;
	size_t velocity;
	SDL_Rect rect;
};

typedef struct pong_window pong_window_t;
struct pong_window {
	SDL_Window *win;
	SDL_Renderer *ren;
	color_t bg_color;
	size_t height;
	size_t width;
};

#endif
