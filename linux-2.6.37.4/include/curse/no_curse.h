#ifdef CONFIG_CURSES
#ifdef CONFIG_NO_CURSE
#ifndef _NO_CURSE_CURSE
#define _NO_CURSE_CURSE

void no_curse_inject (uint64_t);
void no_curse_init (struct task_struct *);
void no_curse_destroy (struct task_struct *);

#endif	/* _NO_CURSE_CURSE */
#endif /* CONFIG_NO_CURSE */
#endif /* CONFIG_CURSES */
