#ifndef _BHYCHIK_tasklist_H_
#define _BHYCHIK_tasklist_H_

#include <linux/list.h>
#include <linux/slab.h>
#include <linux/rwsem.h>

#define ProccessIsWatched 1
#define ProccessIsNotWatched 0

void taskListInit(void);
void startObserving(pid_t pid);
int isObserved(pid_t pid);
void stopObserving(pid_t pid);
void deleteTaskList(void);

#endif
