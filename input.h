#ifndef _BHYCHIK_input_H_
#define _BHYCHIK_input_H_

#include <linux/module.h>
#include <linux/proc_fs.h>
#include <asm/uaccess.h>
#include <linux/string.h>
#include "tasklist.h"

void initProcfs(void);
void unloadProcfs(void);

#endif
