#ifndef PTASK_H
#define PTASK_H

#include <pthread.h>
#include "timeutil.h"

#define  NUM_TASKS 25 /* max num of strings that can be shown */

struct task_par {
    int arg; /* task argument */
    long wcet; /* in microseconds */
    int period; /* in milliseconds */
    int deadline; /* relative (ms) */
    int priority; /* in [0,99] */
    int dmiss; /* no. of misses */
    struct timespec at; /* next activ. time */
    struct timespec dl; /* abs. deadline */

    int ingredient_id; /* app-dependent field: ingredient id */
};

int     task_create(void* (*task) (void*), int i, int period, int drel, int prio);
int     get_task_index(void* arg);
int     get_task_period(void* arg);
void    set_next_activation(int i);
void    wait_for_period(int i);
int     has_deadline_miss(int i);
int     get_deadline_miss(int i);
void    destroy_task(int id);

// Application-dependent functions
int     getIngredient(int i);
void    setIngredient(int i, int id);

#endif // PTASK_H