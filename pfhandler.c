#include "pfhandler.h"

#define DEFAULT_STACK_BOTTOM 0xbf671F00

static pfhook_t oldHook;

void pfHandler(unsigned long address, unsigned long errorcode)
{
	pid_t curpid = current->pid;
	if(((errorcode & 5) == 4) && (isObserved(curpid) == ProccessIsWatched) && address >= DEFAULT_STACK_BOTTOM)
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
