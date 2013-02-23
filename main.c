#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/init.h>

#include "moduleInfo.h"
#include "tasklist.h"
#include "input.h"

static int __init start(void)
{
	printk(KERN_ALERT "stackwatch started\n");
	initProcfs();
	taskListInit();
	return 0;
}

static void __exit stop(void)
{
	unloadProcfs();
	deleteTaskList();
	printk(KERN_ALERT "stackwatch stopped\n");
}

module_init(start);
module_exit(stop);

MODULE_LICENSE(THIS_MODULE_LICENSE);
MODULE_AUTHOR(THIS_MODULE_AUTHOR);
MODULE_DESCRIPTION(THIS_MODULE_DESC);
