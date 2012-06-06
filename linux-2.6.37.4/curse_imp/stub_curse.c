#ifdef CONFIG_CURSES
#include <linux/sched.h>
#include <linux/types.h>
#include <curse/curse_types.h>

#include <curse/stub_curse.h>

void stub_init (struct task_struct * target)
{
	printk("Open of curse initiated\n");
	return;
}

void stub_destroy (struct task_struct * target)
{
	printk("Close of curse initiated\n");
	return;
}

void stub_inject (uint64_t mask)
{
	printk("Run of curse initiated\n");
	return;
}
#endif	/* CONFIG_CURSES */
