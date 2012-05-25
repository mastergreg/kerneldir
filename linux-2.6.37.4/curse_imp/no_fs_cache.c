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
	struct files_struct * open_files = get_files_struct(current);

	sys_fadvise64_64(1,0,0,POSIX_FADV_DONTNEED);
	put_files_struct(open_files);
	return;
}

