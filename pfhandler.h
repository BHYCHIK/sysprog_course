#ifndef _BHYCHIK_pfhandler_H_
#define _BHYCHIK_pfhandler_H_

#include <linux/pfhook.h>
#include <linux/sched.h>

#include "tasklist.h"

void initPfHandler(void);
void unloadPfHandler(void);

#endif
