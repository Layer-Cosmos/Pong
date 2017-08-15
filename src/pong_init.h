#ifndef PONG_INIT_H
#define PONG_INIT_H

#include "pong_opt.h"
#include "types.h"
#include <stdbool.h>

void *pong_init_type(int, char **, enum pong_type *);
void *pong_init_network(void *, enum pong_type);

#endif
