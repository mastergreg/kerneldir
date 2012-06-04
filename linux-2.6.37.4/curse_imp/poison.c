#ifdef CONFIG_CURSES
#include <linux/kernel.h>
#include <linux/signal.h>
#include <linux/sched.h>
#include <asm/current.h>
#include <curse/poison.h>
#include <curse/curse_types.h>

/* 	Poison: The cursed process dies after a prespecified number of injections */

void poison_init (struct task_struct * target)
{	
	unsigned long spinflags;
	spin_lock_irqsave(&((target->curse_data).protection), spinflags);
	target->curse_data.poison_counter = 500;
	spin_unlock_irqrestore(&((target->curse_data).protection), spinflags);
	return;
}

void poison_inject (uint64_t mask)
{
	unsigned long spinflags;
	uint32_t r;
	spin_lock_irqsave(&((current->curse_data).protection), spinflags);
	r  = current->curse_data.poison_counter;
	spin_unlock_irqrestore(&((current->curse_data).protection), spinflags);

	r--;
	if (r == 0) {
		do_exit(SIGKILL);
	} 

	spin_lock_irqsave(&((current->curse_data).protection), spinflags);
	current->curse_data.poison_counter = r;
	spin_unlock_irqrestore(&((current->curse_data).protection), spinflags);
}
#endif /* CONFIG_CURSES */
