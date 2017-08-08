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

#define END_NETWORK_MSG "\n"
#define MSG_BUFFER_SIZE 2048

#define BALL_NETWORK_MSG_PREFIX "b_"
#define SPADDLE_NETWORK_MSG_PREFIX "sp_"
#define CPADDLE_NETWORK_MSG_PREFIX "cp_"
#define KEY_NETWORK_MSG_PREFIX "k_"
#define KEY_DOWN_NETWORK_MSG "down"
#define KEY_UP_NETWORK_MSG "up"

#define SDL_ERROR fprintf(stderr, "SDL Error: %s", SDL_GetError())

struct server;
struct client;
struct pong_ball;
struct network_msg;
struct pong_paddle;
struct pong_window;
struct color;
struct pong_client;
struct pong_server;

enum key {
	DOWN_KEY,
	UP_KEY
};

enum info_type {
	PADDLE,
	BALL
};

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
	float velocityX;
	float velocityY;
	size_t size;
	size_t angle;
	SDL_Rect rect;
	color_t color;
};

typedef struct pong_paddle pong_paddle_t;
struct pong_paddle {
	size_t velocity;
	color_t color;
	SDL_Rect rect;
};

typedef struct pong_field pong_field_t;
struct pong_field {
	color_t color;
	SDL_Rect rect;
    int nbCube;
    int middle;
};

typedef struct pong_window pong_window_t;
struct pong_window {
	SDL_Window *win;
	SDL_Renderer *ren;
	color_t bg_color;
	size_t height;
	size_t width;
};

typedef struct pong_client pong_client_t;
struct pong_client {
	client_t *client;
	pong_ball_t *ball;
	pong_paddle_t *paddle;
	pong_paddle_t *paddle_s;
};

typedef struct pong_server pong_server_t;
struct pong_server {
	server_t *server;
	pong_client_t *client;
	pong_ball_t *ball;
	pong_paddle_t *paddle;
};

#endif
