/**
 * Additional functions to deal with struc timespec and time. Needed for realtime apps
 *
 * Contributions:
 * Giorgio Butazzo - original author
 */

#include <stdio.h>
#include "timeutil.h"

void time_copy(struct timespec *td, struct timespec ts)
{
	td->tv_sec = ts.tv_sec;
	td->tv_nsec = ts.tv_nsec;
}

void time_add_ms(struct timespec *t, int ms)
{
	t->tv_sec += ms/1000;
	t->tv_nsec += (ms%1000)*1000000;
	if (t->tv_nsec > 1000000000) {
		t->tv_nsec -= 1000000000;
		t->tv_sec += 1;
	}
}

int time_cmp(struct timespec t1, struct timespec t2)
{
	if (t1.tv_sec > t2.tv_sec) return 1;
	if (t1.tv_sec < t2.tv_sec) return -1;
	if (t1.tv_nsec > t2.tv_nsec) return 1;
	if (t1.tv_nsec < t2.tv_nsec) return -1;

	return 0;
}

/**
 * Tries to precisely show the current time. Needed for tests,...
 */
void printf_time() {
	struct timespec t;

	clock_gettime(CLOCK_MONOTONIC, &t);

	printf("sec %lu\n", t.tv_sec);
}
