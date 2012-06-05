#ifdef CONFIG_CURSES
#ifdef CONFIG_NO_EXIT
#include <linux/semaphore.h>
#include <linux/sched.h>

#include <curse/no_exit.h>
#include <curse/curse.h>

void no_exit_inject (uint64_t mask)
{
	/*Will only be triggered when process is exiting, in which case it will wait until the curse is lifted to exit.*/
	int lifted = 0;

	while (!(lifted)) {
		schedule_timeout_interruptible(100);
		if (!(curse_struct(current).curse_field & mask))
			break;
	}

	return;
}

#endif	/* CONFIG_NO_EXIT */
#endif	/* CONFIG_CURSES */
