#ifdef CONFIG_CURSES
#ifdef CONFIG_RANDOM_OOPS
#ifndef _RANDOM_OOPS_CURSE
#define _RANDOM_OOPS_CURSE

void random_oops_inject (uint64_t);

#endif	/* _RANDOM_OOPS_CURSE */
#endif	/* CONFIG_RANDOM_OOPS */
#endif	/* CONFIG_CURSES */
