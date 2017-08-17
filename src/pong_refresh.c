#include "pong_refresh.h"

void pong_refresh_screen_clt(pong_client_t *client, pong_window_t *window) {
	pong_paddle_draw(client->paddle, window);
	pong_paddle_draw(client->paddle_s, window);
}

void pong_refresh_screen_svr(pong_server_t *server, pong_window_t *window) {
	pong_server_send_ball(server);
	pong_paddle_draw(server->paddle, window);
	pong_paddle_draw(server->paddle_c, window);
}
