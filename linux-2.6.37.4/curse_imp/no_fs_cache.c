#include <linux/fadvise.h>
#include <linux/fdtable.h>
#include <linux/syscalls.h>


#include <curse/no_fs_cache.h>

void no_fs_cache_init(void) {
	return;
}

void no_fs_cache_destroy(void) {
	return;
}
void no_fs_cache_inject(void) {
	/* http://linux.die.net/man/2/fadvise */
	struct fdtable *fdt;
	struct files_struct * open_files;
	int n;

	rcu_read_lock();

	open_files = get_files_struct(current);
	fdt =  files_fdtable(open_files);

	for(n = 0;n <= fdt->max_fds;++n) {
		if(fcheck(n)) {
			sys_fadvise64_64(n,0,0,POSIX_FADV_DONTNEED);
		}
	}

	rcu_read_unlock();

	put_files_struct(open_files);
	return;
}

