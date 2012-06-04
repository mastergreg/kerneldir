#ifdef CONFIG_CURSES
#ifndef _NO_FS_CACHE_CURSE
#define _NO_FS_CACHE_CURSE

#define MAX_NO_FS_COUNT 10

void no_fs_cache_init (struct task_struct *);
void no_fs_cache_destroy (struct task_struct *);
void no_fs_cache_inject (uint64_t);

#endif	/* _NO_FS_CACHE_CURSE */
#endif /* CONFIG_CURSES */
