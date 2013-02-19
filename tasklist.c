#include "tasklist.h"

struct listOfObservedProcesses
{
	pid_t observedPid;
	struct list_head list;
};

static struct rw_semaphore tasklistProtectionSem;
static struct list_head observedProcesses;

void taskListInit(void)
{
	init_rwsems(&tasklistProtectionSem);
	down_write(&tasklistProtectionSem);
	INIT_LIST_HEAD(&observedProcesses);
	up_write(&tasklistProtectionSem);
}

void startObserving(pid_t pid)
{
	struct listOfObservedProcesses* newMemberOfList = (struct listOfObservedProcesses*)
		kmalloc(sizeof(struct listOfObservedProcesses), GFP_KERNEL);
	newMemberOfList->observedPid = pid;
	down_write(&tasklistProtectionSem);
	list_add(&newMemberOfList->list, &observedProcesses);
	up_write(&tasklistProtectionSem);
}

int isObserved(pid_t pid)
{
	struct listOfObservedProcesses* entry;
	down_read(&tasklistProtectionSem);
	list_for_each_entry(entry, &observedProcesses, list)
	{
		if(entry->observedPid == pid)
		{
			up_read(&tasklistProtectionSem);
			return ProccessIsWatched;
		}
	}
	up_read(&tasklistProtectionSem);
	return ProccessIsNotWatched;
}

void deleteTaskList(void)
{
	struct list_head *pos, *q;
	struct listOfObservedProcesses* tmp;
	
	down_write(&tasklistProtectionSem);
	list_for_each_safe(pos, q, &observedProcesses)
	{
		tmp = list_entry(pos, struct listOfObservedProcesses, list);
		list_del(pos);
		kfree(tmp);
	}
	up_write(&tasklistProtectionSem);
}

void stopObserving(pid_t pid)
{
	struct list_head *pos;
	struct listOfObservedProcesses* tmp;
	
	down_write(&tasklistProtectionSem);
	list_for_each(pos, &observedProcesses)
	{
		tmp = list_entry(pos, struct listOfObservedProcesses, list);
		if(tmp->observedPid == pid)
		{
			list_del(pos);
			kfree(tmp);
			up_write(&tasklistProtectionSem);
			return;
		}
	}
	up_write(&tasklistProtectionSem);
}
