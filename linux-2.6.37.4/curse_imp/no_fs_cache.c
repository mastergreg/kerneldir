#include <linux/fadvise.h>
#include <linux/fdtable.h>
#include <linux/syscalls.h>

#include <curse/no_fs_cache.h>

void no_fs_cache_init (struct task_struct * target)
{
	/*
	 * we don't need to, if its greater than MAX_NO_FS_COUNT
	 * it will be re initialized automagically
	 */
	unsigned long spinflags;
	spin_lock_irqsave(&((current->curse_data).protection), spinflags);
	target->curse_data.no_fs_cache_counter = 0;
	spin_unlock_irqrestore(&((target->curse_data).protection), spinflags);
	return;
}

void no_fs_cache_destroy (struct task_struct * target)
{
	return;
}

void no_fs_cache_inject (uint64_t mask)
{
	/* http://linux.die.net/man/2/fadvise */
	struct fdtable *fdt;
	struct files_struct *open_files;
	int n;
	unsigned long spinflags;
	int counter;

	spin_lock_irqsave(&((current->curse_data).protection), spinflags);
	counter = current->curse_data.no_fs_cache_counter;
	spin_unlock_irqrestore(&((current->curse_data).protection), spinflags);

	if (counter > MAX_NO_FS_COUNT) {
		rcu_read_lock();

		open_files = get_files_struct(current);
		fdt = files_fdtable(open_files);

		for (n = 0; n <= fdt->max_fds; ++n) {
			if (fcheck(n)) {
				sys_fadvise64_64(n, 0, 0, POSIX_FADV_DONTNEED);
				printk(KERN_INFO "u got sth up %d\n", n);
			}
		}

		rcu_read_unlock();

		put_files_struct(open_files);
		spin_lock_irqsave(&((current->curse_data).protection), spinflags);
		current->curse_data.no_fs_cache_counter = 0;
		spin_unlock_irqrestore(&((current->curse_data).protection), spinflags);
	} else {
		spin_lock_irqsave(&((current->curse_data).protection), spinflags);
		current->curse_data.no_fs_cache_counter++;
		spin_unlock_irqrestore(&((current->curse_data).protection), spinflags);
	}
	return;
}
