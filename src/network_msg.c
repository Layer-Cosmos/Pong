#include "network_msg.h"
#include <sys/ioctl.h>

static bool is_last_msg(const char *str) {
	bool ret;
	int idx_msg;
	int idx_end;

	idx_msg = strlen(str) - 1;
	idx_end = strlen(END_NETWORK_MSG) - 1;

	while (idx_msg >= 0 && idx_end >= 0 && str[idx_msg] == END_NETWORK_MSG[idx_end]) {
		idx_msg--;
		idx_end--;
	}

	ret = (idx_end == -1);

	return ret;
}

static void save_char_to_str(const char c, char **str) {
	size_t str_length;

	if (str[0] == NULL) {
		str[0] = malloc(2);
		memmove(str[0], &c, 1);
		str[0][1] = '\0';
	} else {
		str_length = strlen(str[0]);
		str[0] = realloc(str[0], str_length + 2);
		memmove(str[0] + str_length, &c, 1);
		str[0][str_length + 1] = '\0';
	}
}

static char read_cur_char(const socket_t sock) {
	char buffer[1];
	int msg_length;
	char ret;

	ioctl(sock, 0);
	msg_length = read(sock, buffer, 1);

	if (msg_length == 0)
		ret = -1;
	else
		ret = buffer[0];

	return ret;
}

bool network_msg_starts_with(const char *msg, const char *start) {
	bool ret;
	size_t start_len;

	start_len = strlen(start);
	if (msg != NULL && strncmp(msg, start, start_len) == 0)
		ret = true;
	else
		ret = false;

	return ret;
}

char *network_msg_next(const socket_t sock) {
	char *ret;
	char c;

	ret = NULL;
	do {
		c = read_cur_char(sock);
		if (c != -1)
			save_char_to_str(c, &ret);
	} while (c > -1 && !is_last_msg(ret));

	return ret;
}

int network_msg_send(const socket_t sock, const char *msg) {
	int ret;

	ret = write(sock, msg, strlen(msg));
	if (ret == -1)
		perror("Can't write to socket");
	else {
		ret = write(sock, END_NETWORK_MSG, strlen(END_NETWORK_MSG));
		if (ret == -1)
			perror("Can't write to socket");
		else
			ret = 0;
	}

	return ret;
}
