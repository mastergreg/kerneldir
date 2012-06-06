#ifdef CONFIG_CURSES
#ifdef CONFIG_POISON
#include <linux/kernel.h>
#include <linux/signal.h>
#include <linux/sched.h>
#include <asm/current.h>

#include <curse/poison.h>
#include <curse/curse_externals.h>
#include <curse/curse.h>

/* 	Poison: The cursed process dies after a prespecified number of injections */

void poison_init (struct task_struct *target)
{	
	uint32_t *counter = NULL;

	counter = curse_create_alloc(target, sizeof(uint32_t), 0xDEADBEEF);
	if (counter != NULL) {
		*counter = POISON_DURATION;
	}

	return;
}

void poison_inject (uint64_t mask)
{
	uint32_t *counter = NULL;

	counter = curse_get_mem(current, 0xDEADBEEF);
	--(*counter);
	if (*counter  == 0) {
		debug("process died from poisoning");
		do_exit(SIGKILL);
	}

	return;
}

void poison_destroy (struct task_struct *target)
{
	uint32_t *counter = NULL;

	counter = curse_get_mem(target, 0xDEADBEEF);
	curse_free_alloc(target,counter);
	counter = NULL;

	return;
}

#endif /* CONFIG_POISON */
#endif /* CONFIG_CURSES */
