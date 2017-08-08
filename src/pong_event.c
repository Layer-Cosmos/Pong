#include "pong_event.h"

static bool run = false;
static pthread_t thread_id_msg_clt = 0;
static pthread_t thread_id_msg_server = 0;
static pthread_t thread_id_event_clt = 0;
static pthread_t thread_id_event_server = 0;

static void *pong_svr_msg_thread(void *arg) {
	pong_server_t *arg_passed;

	arg_passed = (pong_server_t *)arg;
	while (run) {
		pong_server_next_msg(arg_passed);
		usleep(5);
	}

	return NULL;
}

static void *pong_clt_msg_thread(void *arg) {
	pong_client_t *arg_passed;

	arg_passed = (pong_client_t *)arg;
	while (run) {
		pong_client_next_msg(arg_passed);
		usleep(5);
	}

	return NULL;
}

static void *pong_event_clt_thread(void *arg) {
	pong_client_t *arg_passed;
	SDL_Event event;

	arg_passed = (pong_client_t *)arg;
	while (run) {
		SDL_PollEvent(&event);

		if (event.type == SDL_QUIT) {
			run = false;
		} else if (event.type == SDL_KEYDOWN) {
			pong_client_send_key(arg_passed, UP_KEY);
		} else if (event.type == SDL_KEYUP) {
			pong_client_send_key(arg_passed, DOWN_KEY);
		}

		usleep(5);
	}

	return NULL;
}

static void *pong_event_svr_thread(void *arg) {
	pong_server_t *arg_passed;
	bool moved;
	SDL_Event event;

	arg_passed = (pong_server_t *)arg;
	moved = false;
	while (run) {
		SDL_PollEvent(&event);

		if (event.type == SDL_QUIT) {
			run = false;
		} else if (event.type == SDL_KEYDOWN) {
			pong_paddle_go_down(arg_passed->paddle);
			moved = true;
		} else if (event.type == SDL_KEYUP) {
			pong_paddle_go_up(arg_passed->paddle);
			moved = true;
		} else {
			moved = false;
		}

		if (moved) {
			pong_server_send_spaddle(arg_passed);
		}

		usleep(5);
	}

	return NULL;
}

void pong_event_clt_mng(pong_client_t *client) {
	run = true;

	pthread_create(&thread_id_event_clt, NULL, pong_event_clt_thread, (void *)client);
	pthread_create(&thread_id_msg_clt, NULL, pong_clt_msg_thread, (void *)client);
}

void pong_event_svr_mng(pong_server_t *server) {
	run = true;

	pthread_create(&thread_id_event_server, NULL, pong_event_svr_thread, (void *)server);
	pthread_create(&thread_id_msg_server, NULL, pong_svr_msg_thread, (void *)server);
}

void pong_event_mng_kill() {
	run = false;

	pthread_kill(thread_id_msg_server, SIGSTOP);
	pthread_kill(thread_id_msg_clt, SIGSTOP);
	pthread_kill(thread_id_event_clt, SIGSTOP);
	pthread_kill(thread_id_event_server, SIGSTOP);
}
