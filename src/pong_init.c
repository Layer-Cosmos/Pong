#include "pong_init.h"

static bool get_type(int, char **, enum pong_type *);
static pong_server_t *init_server(const pong_opt_server_t *);
static pong_client_t *init_client(const pong_opt_client_t *);

static pong_server_t *init_server(const pong_opt_server_t *opt) {
	pong_server_t *ret;

	ret = malloc(sizeof(*ret));
	pong_server_init(ret, opt->port);

	return ret;
}

static pong_client_t *init_client(const pong_opt_client_t *opt) {
	pong_client_t *ret;

	ret = malloc(sizeof(*ret));
	pong_client_init(ret, opt->ip, opt->port);

	return ret;
}

static bool get_type(int argc, char *argv[], enum pong_type *type) {
	bool is_server;
	bool is_client;

	is_server = pong_opt_is_server(argc, argv);
	is_client = pong_opt_is_client(argc, argv);

	if ((is_server && is_client) || (!is_server && !is_client)) {
		fprintf(stderr, "Please define server OR client");
		return false;
	}

	if (is_server)
		*type = server;
	else
		*type = client;

	return true;
}

void *pong_init_type(int argc, char *argv[], enum pong_type *type) {
	void *ret;

	if (!get_type(argc, argv, type))
		return NULL;

	if (*type == server) {
		ret = pong_opt_get_server(argc, argv);
		if (((pong_opt_server_t *)ret)->port == 0) {
			fprintf(stderr, "Please specify port!\n");
			return NULL;
		}
	} else {
		ret = pong_opt_get_client(argc, argv);
		if (((pong_opt_client_t *)ret)->port == 0 ||
		    ((pong_opt_client_t *)ret)->ip == NULL) {
			fprintf(stderr, "Please specify port!\n");
			return NULL;
		}
	}

	return ret;
}

void *pong_init_network(void *opt, enum pong_type type) {
	void *ret;

	if (type == server)
		ret = init_server(opt);
	else
		ret = init_client(opt);

	return ret;
}

void pong_init_paddle_clt(pong_client_t *client, pong_window_t *window) {
	client->paddle_s = pong_paddle_init(window, color_white(), 1);
	client->paddle = pong_paddle_init(window, color_white(), 2);
}

void pong_init_paddle_svr(pong_server_t *server, pong_window_t *window) {
	server->paddle = pong_paddle_init(window, color_white(), 1);
	server->paddle_c = pong_paddle_init(window, color_white(), 2);
}

void pong_init_ball_clt(pong_client_t *client) {
	client->ball = pong_ball_init(20, color_white());
}

void pong_init_ball_svr(pong_server_t *server) {
	server->ball = pong_ball_init(20, color_white());
}
