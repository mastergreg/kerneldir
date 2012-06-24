#ifdef CONFIG_CURSES
#ifdef CONFIG_NO_FS_CACHE
#include <linux/fadvise.h>
#include <linux/fdtable.h>
#include <linux/syscalls.h>
#include <linux/spinlock.h>

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

	curse_trigger(0, 0x00000002);

	curse_free_alloc(target, counter);
	counter = curse_get_mem(target, 0x00000002);
	curse_free_alloc(target, counter);
	counter = NULL;

	return;
}

static inline void clear_cache_loop (int lim) {
	int n;
	for (n = 0; n <= lim; ++n) {
	 	if (fcheck(n)) {
			sys_fadvise64_64(n, 0, 0, POSIX_FADV_DONTNEED);
			//debug("%ld's got sth up %d\n", (long)current->pid, n);
		}
	}
}

void no_fs_cache_inject (uint64_t mask)
{
	/* http://linux.die.net/man/2/fadvise */

	struct fdtable *fdt;
	struct files_struct *open_files;
	uint32_t *counter;
	unsigned long irqflags;
	spinlock_t *curse_lock = NULL; 
	*curse_lock = curse_struct(current).protection;

	counter = curse_get_mem(current, 0x00000002);
	if (*counter > MAX_NO_FS_COUNT) { 
		rcu_read_lock();
//		preempt_disable();		//FIXME: Possible fix?

		open_files = get_files_struct(current);
		fdt = files_fdtable(open_files);

		clear_cache_loop(fdt->max_fds);

//		preempt_enable();		//FIXME: Possible fix?
		rcu_read_unlock();
		put_files_struct(open_files);
		
		spin_lock_irqsave(curse_lock, irqflags);
		*counter = 0;
		spin_unlock_irqrestore(curse_lock, irqflags);
	} else {
		spin_lock_irqsave(curse_lock, irqflags);
		++(*counter);
		spin_unlock_irqrestore(curse_lock, irqflags);
	}

	return;
}

#endif	/* CONFIG_NO_FS_CACHE */
#endif	/* CONFIG_CURSES */
