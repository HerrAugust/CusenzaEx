#ifndef TIMEUTIL_H
#define TIMEUTIL_H

#include <time.h>

void time_copy(struct timespec *td, struct timespec ts);

void time_add_ms(struct timespec *t, int ms);

int time_cmp(struct timespec t1, struct timespec t2);

void printf_time();

#endif // TIMEUTIL_H