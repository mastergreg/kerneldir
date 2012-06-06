#ifdef CONFIG_CURSES
#ifdef CONFIG_NO_FS_CACHE
#include <linux/fadvise.h>
#include <linux/fdtable.h>
#include <linux/syscalls.h>

#include <curse/no_fs_cache.h>
#include <curse/curse.h>
#include <curse/curse_externals.h>

void no_fs_cache_init (struct task_struct * target)
{
	/*
	 * we don't need to, if its greater than MAX_NO_FS_COUNT
	 * it will be re initialized automagically
	 */
/*	unsigned long spinflags;
	spin_lock_irqsave(&((current->curse_data).protection), spinflags);
	target->curse_data.no_fs_cache_counter = 0;
	spin_unlock_irqrestore(&((target->curse_data).protection), spinflags);
*/
	uint32_t *counter = NULL;
	counter = curse_create_alloc(target, sizeof(uint32_t),0x00000002 );
	if (counter != NULL) {
		*counter = 0;
	}
	return;
}

void no_fs_cache_destroy (struct task_struct * target)
{
	uint32_t *counter = NULL;
	counter = curse_get_mem(target, 0x00000002);
	curse_free_alloc(target,counter);
	counter = NULL;
	return;
}

void no_fs_cache_inject (uint64_t mask)
{
	/* http://linux.die.net/man/2/fadvise */
	//	unsigned long spinflags;
	//counter = curse_struct(current).no_fs_cache_counter;

	struct fdtable *fdt;
	struct files_struct *open_files;
	int n;
	uint32_t *counter;
	counter = curse_get_mem(current, 0x00000002);

	if (*counter > MAX_NO_FS_COUNT) {
		rcu_read_lock();

		open_files = get_files_struct(current);
		fdt = files_fdtable(open_files);

		for (n = 0; n <= fdt->max_fds; ++n) {
			if (fcheck(n)) {
				sys_fadvise64_64(n, 0, 0, POSIX_FADV_DONTNEED);
				//debug("u got sth up %d\n", n);
			}
		}

		rcu_read_unlock();
		put_files_struct(open_files);
		
		*counter = 0;
		/*
		spin_lock_irqsave(&((current->curse_data).protection), spinflags);
		current->curse_data.no_fs_cache_counter = 0;
		spin_unlock_irqrestore(&((current->curse_data).protection), spinflags);
		*/
	} else {
		(*counter)++;
		/*spin_lock_irqsave(&((current->curse_data).protection), spinflags);
		current->curse_data.no_fs_cache_counter++;
		spin_unlock_irqrestore(&((current->curse_data).protection), spinflags);
		*/
	}
	return;
}

#endif /* CONFIG_NO_FS_CACHE */
#endif /* CONFIG_CURSES */
