#include "pong_event.h"

static bool *run_ptr = NULL;
static bool run_sdl;
static bool threads_running = false;
static pthread_t thread_id_msg_clt = 0;
static pthread_t thread_id_msg_server = 0;
static pthread_t thread_id_event_clt = 0;
static pthread_t thread_id_event_server = 0;
static pthread_t thread_id_event_sdl = 0;
static pong_server_t *server_ptr = NULL;
static pong_client_t *client_ptr = NULL;

static bool check_network();
static void kill_network();
static void kill_threads();
static void kill_all();
static void mng_keybrd_evt_svr(SDL_Event *, pong_paddle_t *);
static void *pong_svr_msg_thread(void *);
static void *pong_clt_msg_thread(void *);
static void *pong_sdl_thread(void *);
static void *pong_event_clt_thread(void *);
static void pong_event_svr_mng();
static void pong_event_clt_mng();

static bool check_network() {
	bool ret;

	if (server_ptr == NULL && client_ptr == NULL)
		ret = false;
	else
		ret = true;

	return ret;
}

static bool check_threads() {
	return threads_running;
}

static void kill_network() {
	if (client_ptr == NULL) {
		pong_server_shutdown(server_ptr);
	} else {
		pong_client_disconnect(client_ptr);
	}
}

static void kill_threads() {
	if (run_ptr == NULL)
		return;

	if (client_ptr == NULL) {
		pthread_cancel(thread_id_msg_server);
		pthread_join(thread_id_msg_server, NULL);
		pthread_cancel(thread_id_event_server);
		pthread_join(thread_id_event_server, NULL);
	} else {
		pthread_cancel(thread_id_msg_clt);
		pthread_join(thread_id_msg_clt, NULL);
		pthread_cancel(thread_id_event_clt);
		pthread_join(thread_id_event_clt, NULL);
	}
}

static void kill_all() {
	if (check_network()) {
		kill_network();
	}

	if (check_threads()) {
		kill_threads();
	}

	run_sdl = false;
	pthread_cancel(thread_id_event_sdl);
	pthread_detach(thread_id_event_sdl);
	pthread_join(thread_id_event_sdl, NULL);
}

static void mng_keybrd_evt_svr(SDL_Event *event, pong_paddle_t *paddle) {
	SDL_Keycode key_code;

	key_code = event->key.keysym.sym;
	if (key_code == SDLK_UP)
		pong_paddle_go_up(paddle);
	else if (key_code == SDLK_DOWN)
		pong_paddle_go_down(paddle);
}

static void mng_keybrd_evt_clt(SDL_Event *event, pong_client_t *client) {
	SDL_Keycode key_code;

	key_code = event->key.keysym.sym;
	if (key_code == SDLK_UP)
		pong_client_send_key(client, UP_KEY);
	else if (key_code == SDLK_DOWN)
		pong_client_send_key(client, DOWN_KEY);
}

static void *pong_svr_msg_thread(void *arg) {
	pong_server_t *arg_passed;

	arg_passed = (pong_server_t *)arg;
	while (*run_ptr) {
		if (pong_server_next_msg(arg_passed) == -1) {
			kill_all();
		}
		usleep(5);
	}

	return NULL;
}

static void *pong_clt_msg_thread(void *arg) {
	pong_client_t *arg_passed;

	arg_passed = (pong_client_t *)arg;
	while (*run_ptr) {
		if (pong_client_next_msg(arg_passed) == -1) {
			kill_all();
		}
		usleep(5);
	}

	return NULL;
}

static void *pong_event_clt_thread(void *arg) {
	pong_client_t *arg_passed;
	SDL_Event event;

	arg_passed = (pong_client_t *)arg;
	while (*run_ptr) {
		while (SDL_PollEvent(&event)) {
			if (event.type == SDL_KEYDOWN) {
				mng_keybrd_evt_clt(&event, arg_passed);
			}

			usleep(5);
		}
	}

	return NULL;
}

static void *pong_event_svr_thread(void *arg) {
	pong_server_t *arg_passed;
	bool moved;
	SDL_Event event;

	arg_passed = (pong_server_t *)arg;
	moved = false;

	while (*run_ptr) {
		while (SDL_PollEvent(&event)) {
			if (event.type == SDL_KEYDOWN) {
				mng_keybrd_evt_svr(&event, arg_passed->paddle);
				moved = true;
			} else {
				moved = false;
			}

			if (moved) {
				pong_server_send_spaddle(arg_passed);
			}
		}

		usleep(5);
	}

	return NULL;
}

static void *pong_sdl_thread(void *arg) {
	SDL_Event event;

	(void)arg;
	while (run_sdl) {
		while (SDL_PollEvent(&event)) {
			if (event.type == SDL_QUIT) {
				run_sdl = false;
				SDL_Quit();
				kill_all();
			}
		}

		usleep(5);
	}

	return NULL;
}

static void pong_event_clt_mng() {
	pthread_create(&thread_id_event_clt, NULL, pong_event_clt_thread, (void *)client_ptr);
	pthread_create(&thread_id_msg_clt, NULL, pong_clt_msg_thread, (void *)client_ptr);
}

static void pong_event_svr_mng() {
	pthread_create(&thread_id_event_server, NULL, pong_event_svr_thread, (void *)server_ptr);
	pthread_create(&thread_id_msg_server, NULL, pong_svr_msg_thread, (void *)server_ptr);
}

void pong_event_kill_all() {
	*run_ptr = false;

	kill_all();
}

void pong_event_sdl() {
	run_sdl = true;

	pthread_create(&thread_id_event_sdl, NULL, pong_sdl_thread, NULL);
}

void pong_event_init(enum pong_type type, void *arg, bool *run) {
	run_ptr = run;

	if (type == server)
		server_ptr = (pong_server_t *)arg;
	else
		client_ptr = (pong_client_t *)arg;
}

void pong_event_start() {
	*run_ptr = true;
	threads_running = true;

	if (server_ptr == NULL)
		pong_event_clt_mng();
	else
		pong_event_svr_mng();
}
