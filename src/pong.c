#include "client.h"
#include "pong_ball.h"
#include "pong_game.h"
#include "pong_window.h"
#include "server.h"

/*static int manage_events() {
	SDL_Event event;

	SDL_PollEvent(&event);
	if (event.type == SDL_QUIT) {
		return 1;
	}

	return 0;
}*/

int main() {
	client_t *client;
	server_t *server;
	char *msg;

	client = client_init();
	server = server_init(51710, 3);

	client_connect(client, "127.0.0.1", 51710);
	server_wait_conn(server);

	client_send_msg(client, "cacaprout");
	msg = server_next_msg(server);

	server_kill(server);
	printf("%s\n", msg);
}
