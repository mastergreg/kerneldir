#ifdef CONFIG_CURSES
#ifdef CONFIG_TEST
#ifndef _TEST_CURSE
#define _TEST_CURSE

void test_init (struct task_struct *);
void test_destroy (struct task_struct *);
void test_inject (uint64_t);

#endif	/* _TEST_CURSE */
#endif	/* CONFIG_TEST */
#endif	/* CONFIG_CURSES */
