#ifdef CONFIG_CURSES
#ifdef CONFIG_TEST
#include <linux/sched.h>
#include <linux/types.h>
#include <curse/curse_types.h>

#include <curse/test_curse.h>
#include <curse/curse_externals.h>

static char *hi=NULL;

void test_init (struct task_struct *target)
{
	static int shit=0;
	shit++;
	printk("Open of curse initiated\n");
	hi = curse_get_alloc(target, 5);
	printk("Allocated 5 bytes on pointer %p\n", hi);
	if (hi != NULL) {
		snprintf(hi, 4, "%d", shit);
		hi[4]='\0';
	}
	return;
}

void test_destroy (struct task_struct *target)
{
	printk("Close of curse initiated\n");
	printk("Freeing data at %p\n", hi);
//	curse_free_alloc(target, hi);
	hi=NULL;
	return;
}

void test_inject (uint64_t mask)
{
	printk("Run of curse initiated\n");
	printk("Allocated data are at %p and are %s\n", hi, hi);
	return;
}

#endif	/* CONFIG_TEST */
#endif	/* CONFIG_CURSES */
