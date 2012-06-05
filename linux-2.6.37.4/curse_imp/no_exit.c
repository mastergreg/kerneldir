#ifdef CONFIG_CURSES
#include <linux/syscalls.h>			//WHY all these? NO sema in here and no syscalls>>>>>>>>>>>>!!!!!!!!!!!!
#include <linux/semaphore.h>

#include <curse/no_exit.h>
#include <curse/curse.h>

void no_exit_init (struct task_struct *target)
{
	return;
}

void no_exit_inject (uint64_t mask)
{
	/* Will only be triggered when process is exiting, in which case it will wait until the curse is lifted to exit */
	int lifted = 0;

	while (!(lifted)) {
		// wait on condition
		//if (!((get_curse_struct(current).curse_field) & mask))	//OR without the "get_" part??
		//	break;
	}

	return;
}

void no_curse_destroy (struct task_struct *target)
{
	struct task_curse_struct *tar_curse;
	unsigned long irqflags;

	//What do you want to go here?

	return;
}

#endif /* CONFIG_CURSES */
