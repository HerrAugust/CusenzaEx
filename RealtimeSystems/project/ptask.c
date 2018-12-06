/**
  * This module manages real time tasks, which are an extension of pthreads.
  *
  * Contributors:
  * Giorgio Buttazzo - original author
  * Agostino Mascitti - Documentation (Nov 2018)
  */

#include <stdio.h>
#include "ptask.h"

// -------------------------------------------------------------- Globals

// static means var can only be used in this file. without static, var can be used in other files by declaring it global there
static pthread_t 		tid[NUM_TASKS];	// task IDs
static struct task_par 	tp[NUM_TASKS];	// list of tasks attributes

// -------------------------------------------------------------- Code

/**
 * Creates a realtime task with given parameters
 * @param task function to be executed by the task
 * @param i task index (must be diverse for each new task you create)
 * @param period task period
 * @param drel task deadline
 * @param prio task priority
 * @return 0 on success
 */
int task_create( void*(*task)(void *), int i, int period, int drel, int prio) {
	pthread_attr_t myatt;
	struct sched_param mypar;
	int tret;

	tp[i].arg = i;
	tp[i].period = period;
	tp[i].deadline = drel;
	tp[i].priority = prio;
	tp[i].dmiss = 0;

	pthread_attr_init(&myatt);
	pthread_attr_setinheritsched(&myatt, PTHREAD_EXPLICIT_SCHED);
	pthread_attr_setschedpolicy(&myatt, SCHED_RR);

	mypar.sched_priority = tp[i].priority;
	pthread_attr_setschedparam(&myatt, &mypar);
	tret = pthread_create(&tid[i], &myatt, task, (void*)(&tp[i]));

	return tret;
}

/**
 * Returns task index
 * @param arg the task attributes structure
 * @return task index
 */
int get_task_index(void* arg) {
	struct task_par *tp;
	tp = (struct task_par *)arg;

	return tp->arg;
}

/**
 * Returns task period
 * @param arg the task attributes structure
 * @return task period
 */
int get_task_period(void* arg) {
	struct task_par *tp;
	tp = (struct task_par *)arg;

	return tp->period;
}

/**
 * Sets next activation time. Here absolute deadlines are considered
 * @param i task index to be activated
 */
void set_next_activation(int i)
{
	struct timespec t;

	clock_gettime(CLOCK_MONOTONIC, &t);
	time_copy(&(tp[i].at), t);
	time_copy(&(tp[i].dl), t);
	time_add_ms(&(tp[i].at), tp[i].period);
	time_add_ms(&(tp[i].dl), tp[i].deadline);
}

/**
 * Makes task wait for next period
 * @param i task index
 */
void wait_for_period(int i)
{
	clock_nanosleep(CLOCK_MONOTONIC, TIMER_ABSTIME, &(tp[i].at), NULL);

	time_add_ms(&(tp[i].at), tp[i].period);
	time_add_ms(&(tp[i].dl), tp[i].period);
}

/**
 * true if task has missed its current deadline
 * @param i task index
 * @return true if task has missed its current deadline
 */
int has_deadline_miss(int i)
{
	struct timespec now;
	clock_gettime(CLOCK_MONOTONIC, &now);

	if (time_cmp(now, tp[i].dl) > 0) {
		tp[i].dmiss++;
		return 1;
	}

	return 0;
}

/**
 * Number of deadline misses
 * @param i task index
 * @return Number of deadline misses
 */
int get_deadline_miss(int i)
{
    return tp[i].dmiss;
}


//------------------------------------------------------------ App-dependent functions

/**
 * Returns the ingredient ID
 * @param i task ID
 * @return ingredient ID
 */
int     getIngredient(int i) {
    return tp[i].ingredient_id;
}

/**
 * Sets ingredient ID
 * @param i task ID
 * @param ingrID ingredient ID
 */
void    setIngredient(int i, int ingrID) {
    tp[i].ingredient_id = ingrID;
}