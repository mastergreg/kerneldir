#ifdef CONFIG_CURSES
#ifdef CONFIG_TEST
#include <linux/sched.h>
#include <linux/types.h>
#include <curse/curse_types.h>

#include <curse/test_curse.h>
#include <curse/curse_externals.h>

//static char *hi=NULL;

void test_init (struct task_struct *target)
{
	char *hi=NULL;
	printk("Open of curse initiated\n");
	hi = curse_create_alloc(target, 5, 0x01010101);
	printk("Allocated 5 bytes on pointer %p\n", hi);
	if (hi != NULL) {
		snprintf(hi, 5, "%d", target->pid);
		hi[4]='\0';
	}
	return;
}

void test_destroy (struct task_struct *target)
{
	char *hi=NULL;
	printk("Close of curse initiated\n");
	hi = curse_get_mem(target, 0x01010101);
	printk("Freeing data at %p, them being %s on pid %ld\n", hi, hi, (long)target->pid);
	curse_free_alloc(target, hi);
	hi=NULL;
	return;
}

void test_inject (uint64_t mask)
{
	char *hi=NULL;
	printk("Run of curse initiated\n");
	hi = curse_get_mem(current, 0x01010101);
	printk("Allocated data are at %p and are %s\n", hi, hi);
	return;
}

#endif	/* CONFIG_TEST */
#endif	/* CONFIG_CURSES */
