#include "tasklist.h"

struct listOfObservedProcesses
{
	pid_t observedPid;
	struct list_head list;
};

LIST_HEAD(observedProcesses);

void startObserving(pid_t pid)
{
	struct listOfObservedProcesses* newMemberOfList = (struct listOfObservedProcesses*)
		kmalloc(sizeof(struct listOfObservedProcesses), GFP_KERNEL);
	newMemberOfList->observedPid = pid;
	list_add(&newMemberOfList->list, &observedProcesses);
}

int isObserved(pid_t pid)
{
	struct listOfObservedProcesses* entry;
	list_for_each_entry(entry, &observedProcesses, list)
	{
		if(entry->observedPid)
		{
			return ProccessIsWatched;
		}
	}
	return ProccessIsNotWatched;
}

void deleteTaskList(void)
{
	struct list_head *pos, *q;
	struct listOfObservedProcesses* tmp;
	
	list_for_each_safe(pos, q, &observedProcesses)
	{
		tmp = list_entry(pos, struct listOfObservedProcesses, list);
		list_del(pos);
		kfree(tmp);
	}
}

void stopObserving(pid_t pid)
{
	struct list_head *pos;
	struct listOfObservedProcesses* tmp;
	
	list_for_each(pos, &observedProcesses)
	{
		tmp = list_entry(pos, struct listOfObservedProcesses, list);
		if(tmp->observedPid == pid)
		{
			list_del(pos);
			kfree(tmp);
			return;
		}
	}
}
