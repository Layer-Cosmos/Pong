#include "pong_opt.h"

static int option_is_present(const char *, const int, char **);
static int search_for_char(const char *, const char);
static char *get_opt_value(char *);

static int option_is_present(const char *opt, const int argc, char *argv[]) {
	int idx;
	bool is_found;
	size_t ret;
	size_t opt_len;

	is_found = false;
	idx = 0;
	opt_len = strlen(opt);
	while (idx < argc && !is_found) {
		is_found = (strncmp(opt, argv[idx], opt_len) == 0);
		idx++;
	}

	if (!is_found) {
		ret = -1;
	} else {
		ret = idx - 1;
	}

	return ret;
}

static int search_for_char(const char *str, const char c) {
	size_t ret;
	size_t idx;
	bool is_found;
	size_t length;

	length = strlen(str);
	is_found = false;
	idx = 0;
	while (idx < length && !is_found) {
		is_found = (str[idx] == c);
		idx++;
	}

	if (!is_found)
		ret = -1;
	else
		ret = idx - 1;

	return ret;
}

static char *get_opt_value(char *opt) {
	char *ret;
	int idx;

	idx = search_for_char(opt, '=');
	if (idx == -1)
		return NULL;

	ret = (opt + idx + 1);

	return ret;
}

bool pong_opt_is_client(int argc, char *argv[]) {
	int opt_idx;
	bool ret;

	opt_idx = option_is_present("--client", argc, argv);
	ret = (opt_idx != -1);

	return ret;
}

bool pong_opt_is_server(int argc, char *argv[]) {
	int opt_idx;
	bool ret;

	opt_idx = option_is_present("--server", argc, argv);
	ret = (opt_idx != -1);

	return ret;
}

pong_opt_server_t *pong_opt_get_server(int argc, char *argv[]) {
	int idx;
	char *port_str;
	int port;
	pong_opt_server_t *ret;

	ret = NULL;
	idx = option_is_present("--port", argc, argv);

	if (idx == -1)
		return NULL;

	port_str = get_opt_value(argv[idx]);
	port = atoi(port_str);

	if (port == 0)
		return NULL;

	ret = malloc(sizeof(*ret));
	ret->port = port;

	return ret;
}

pong_opt_client_t *pong_opt_get_client(int argc, char *argv[]) {
	int idx;
	char *port_str;
	int port;
	char *ip;
	pong_opt_client_t *ret;

	ret = NULL;
	idx = option_is_present("--port", argc, argv);

	if (idx == -1)
		return NULL;

	port_str = get_opt_value(argv[idx]);
	port = atoi(port_str);

	idx = option_is_present("--ip", argc, argv);
	if (idx == -1)
		return NULL;

	ip = get_opt_value(argv[idx]);

	ret = malloc(sizeof(*ret));
	ret->ip = ip;
	ret->port = port;

	return ret;
}
