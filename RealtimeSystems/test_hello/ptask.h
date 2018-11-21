#ifndef PTASK_H
#define PTASK_H

int task_create(void* (*task) (void*), int i, int period, int drel, int prio)

#endif // PTASK_H