#ifdef CONFIG_CURSES
#include <linux/semaphore.h>
#include <linux/sched.h>

#include <curse/no_exit.h>
#include <curse/curse.h>

void no_exit_inject (uint64_t mask)
{
	/* Will only be triggered when process is exiting, in which case it will wait until the curse is lifted to exit */
	int lifted = 0;

	while (!(lifted)) {
		schedule_timeout_interruptible(100);
		if (!(curse_struct(current)->curse_field & mask))
			lifted = 1;
	}

	return;
}

#endif /* CONFIG_CURSES */
