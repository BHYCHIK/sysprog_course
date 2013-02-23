#include "input.h"

#define DIRNAME "stackwatcher"
#define SETWATCH_FILE "setwatch"
#define UNSETWATCH_FILE "unsetwatch"

#define BUFLEN 16

static struct proc_dir_entry* procDir;
static struct proc_dir_entry* setwatchFile;
static struct proc_dir_entry* unsetwatchFile;

static ssize_t setwatchWrite( struct file *file, const char *userBuf,
                           size_t count, loff_t *ppos ) 
{
	char kernelBuf[BUFLEN + 1];
	pid_t watchedPid;
	int len, res;
	len = count < BUFLEN ? count : BUFLEN;
	res = copy_from_user(kernelBuf, userBuf, len);
	kernelBuf[len] = '\0';
	if((sscanf(kernelBuf, "%d", &watchedPid)) == 1)
	{
		startObserving(watchedPid);
	}
	return len;
}

static ssize_t unsetwatchWrite( struct file *file, const char *userBuf,
                           size_t count, loff_t *ppos ) 
{
	char kernelBuf[BUFLEN + 1];
	int len, res;
	pid_t watchedPid;
	len = count < BUFLEN ? count : BUFLEN;
	res = copy_from_user(kernelBuf, userBuf, len);
	kernelBuf[len] = '\0';
	if((sscanf(kernelBuf, "%d", &watchedPid)) == 1)
	{
		stopObserving(watchedPid);
	}
	return len;
}

static const struct file_operations setwatchFops = {
   .owner = THIS_MODULE,
   .read  = NULL,
   .write  = setwatchWrite
};

static const struct file_operations unsetwatchFops = {
   .owner = THIS_MODULE,
   .read  = NULL,
   .write  = unsetwatchWrite
};


void initProcfs(void)
{
	procDir = proc_mkdir(DIRNAME, NULL);
	
	setwatchFile = create_proc_entry(SETWATCH_FILE, 0222, procDir);
	setwatchFile->uid = 0;
	setwatchFile->gid = 0;
	setwatchFile->proc_fops = &setwatchFops;
	
	unsetwatchFile = create_proc_entry(UNSETWATCH_FILE, 0222, procDir);
	unsetwatchFile->uid = 0;
	unsetwatchFile->gid = 0;
	unsetwatchFile->proc_fops = &unsetwatchFops;
}

void unloadProcfs(void)
{
	remove_proc_entry(SETWATCH_FILE, procDir);
	remove_proc_entry(UNSETWATCH_FILE, procDir);
	remove_proc_entry(DIRNAME, NULL);
}
