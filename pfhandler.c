#include "pfhandler.h"

static pfhook_t oldHook;

void pfHandler(unsigned long address, unsigned long errorcode)
{
	pid_t curpid = current->pid;
	if(((errorcode & 5) == 4) && (isObserved(curpid) == ProccessIsWatched))
	{
		printk(KERN_INFO "STACKWATCH: pagefault at %lu for %d proccess\n", address, curpid);
	}
}

void initPfHandler(void)
{
	oldHook = setPfHook(pfHandler);
}

void unloadPfHandler(void)
{
	setPfHook(oldHook);
}
