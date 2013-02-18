#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/init.h>

#include "moduleInfo.h"

static int __init start(void)
{
	printk(KERN_ALERT "stackwatch started\n");
	return 0;
}

static void __exit stop(void)
{
	printk(KERN_ALERT "stackwatch stopped\n");
}

module_init(start);
module_exit(stop);

MODULE_LICENSE(THIS_MODULE_LICENSE);
MODULE_AUTHOR(THIS_MODULE_AUTHOR);
MODULE_DESCRIPTION(THIS_MODULE_DESC);
