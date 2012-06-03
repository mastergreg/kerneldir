#include <linux/kernel.h>
#include <linux/signal.h>
#include <curse/poison.h>
#include <curse/curse_externals.h>

/* 	Poison: The cursed process dies after a prespecified number of injections */

void poison_init (struct task_struct * target)
{	
	unsigned long spinflags;
	spin_lock_irqsave(&((current->curse_data).protection), spinflags);
	target->curse_data.poison_counter = 10000;
	spin_unlock_irqrestore(&((target->curse_data).protection), spinflags);
	return;
}

void poison_inject (uint64_t mask)
{
	spin_lock_irqsave(&((current->curse_data).protection), spinflags);
	uint32_t r  = target->curse_data.poison_counter;
	spin_unlock_irqrestore(&((current->curse_data).protection), spinflags);

	r--;
	printk("The clock is ticking for this one...");
	if (r == 0) {
		do_exit(SIGKILL);
	} 
}
