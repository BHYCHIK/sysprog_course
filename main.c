#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/init.h>

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
