#ifdef CONFIG_CURSES
#ifdef CONFIG_NO_FS_CACHE
#include <linux/fadvise.h>
#include <linux/fdtable.h>
#include <linux/syscalls.h>

#include <curse/no_fs_cache.h>
#include <curse/curse.h>
#include <curse/curse_externals.h>

void no_fs_cache_init (struct task_struct *target)
{
	/*
	 * we don't need to, if its greater than MAX_NO_FS_COUNT
	 * it will be re initialized automagically :)
	 */
	uint32_t *counter = NULL;

	counter = curse_create_alloc(target, sizeof(uint32_t), 0x00000002);
	if (counter != NULL) {
		*counter = 0;
	}

	return;
}

void no_fs_cache_destroy (struct task_struct *target)
{
	uint32_t *counter = NULL;

	counter = curse_get_mem(target, 0x00000002);
	curse_free_alloc(target, counter);
	counter = NULL;

	return;
}

//uint32_t testme(uint32_t *a, uint32_t t){(*a)=t; return t;}
//uint32_t testme2(uint32_t *A) {(*A)=0; return 0;}
//uint32_t testme3(uint32_t *a) {(*a)++; return (*a);}
//uint32_t testme4(uint32_t *a) {return (*a);}

void no_fs_cache_inject (uint64_t mask)
{
	/* http://linux.die.net/man/2/fadvise */

	struct fdtable *fdt;
	struct files_struct *open_files;
	int n;
	uint32_t *counter;

	counter = curse_get_mem(current, 0x00000002);
	if (*counter > MAX_NO_FS_COUNT) { 
//	if (testme4(counter) > MAX_NO_FS_COUNT) { 
		rcu_read_lock();

		open_files = get_files_struct(current);
		fdt = files_fdtable(open_files);

//Apparently, the problem is in waiting inside an rcu read-side section.
//Implementation of fadvise64_64 is at http://lxr.free-electrons.com/source/mm/fadvise.c#L86
//also see http://lxr.free-electrons.com/source/include/linux/fs.h#L976 (f_mapping)
//http://lxr.free-electrons.com/source/include/linux/fs.h#L646
//and http://lxr.free-electrons.com/source/fs/file_table.c#L275 .

		for (n = 0; n <= fdt->max_fds; ++n) {
		 	if (fcheck(n)) {
				sys_fadvise64_64(n, 0, 0, POSIX_FADV_DONTNEED);
				debug("%ld's got sth up %d\n", (long)current->pid, n);
			}
		} 

		rcu_read_unlock();
		put_files_struct(open_files);
		
		*counter = 0;
//		testme2(counter);
	} else {
		++(*counter);
//		testme3(counter);
	}

	return;
}

#endif	/* CONFIG_NO_FS_CACHE */
#endif	/* CONFIG_CURSES */
