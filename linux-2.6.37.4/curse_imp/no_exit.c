#ifdef CONFIG_CURSES
#include <linux/syscalls.h>
#include <linux/semaphore.h>

#include <curse/no_exit.h>
#include <curse/curse.h>

void no_exit_init (struct task_struct * target)
{
	return;
}

void no_exit_inject (uint64_t mask)
{
	/* Will only be triggered when process is exiting, in which case it will wait until the curse is lifted to exit */
	int lifted = 0;


	while (!(lifted)) {

		if (get_proc_curses & mask) {	
			lifted = 1;
		} else {
				
		}
	}

	return;
}

void no_curse_destroy (struct task_struct * target)
{
	struct task_curse_struct *tar_curse;
	unsigned long irqflags;

	tar_curse = &(target->curse_data);

	spin_lock_irqsave(&((tar_curse)->protection), irqflags);
	// FIXME: security exploit, process may gain permissions
	tar_curse->permissions |= (_USR_ACTIVE_PERM | _SU_ACTIVE_PERM);
	spin_unlock_irqrestore(&((tar_curse)->protection), irqflags);
	return;
}
#endif /* CONFIG_CURSES */
