#ifdef CONFIG_CURSES
#ifndef _RANDOM_OOPS_CURSE
#define _RANDOM_OOPS_CURSE

void random_oops_init (struct task_struct *);
void random_oops_destroy (struct task_struct *);
void random_oops_inject (uint64_t);

#endif	/* _RANDOM_OOPS_CURSE */
#endif /* CONFIG_CURSES */
