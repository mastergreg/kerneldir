#include <linux/kernel.h>
#include <linux/signal.h>
#include <curse/poison.h>

/* 	Poison: The cursed process dies after a prespecified number of injections */

void poison_inject (uint64_t mask)
{
	static int r = 10000; 
	r--;
	printk("The clock is ticking for this one...");
	if (r == 0) {
		do_exit(SIGKILL);
	} 
}

