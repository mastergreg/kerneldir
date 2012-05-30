#ifndef _NO_FS_CACHE_CURSE
#define _NO_FS_CACHE_CURSE

#define MAX_NO_FS_COUNT 42

void no_fs_cache_init (void);
void no_fs_cache_destroy (void);
void no_fs_cache_inject (uint64_t);

#endif	/* _NO_FS_CACHE_CURSE */
