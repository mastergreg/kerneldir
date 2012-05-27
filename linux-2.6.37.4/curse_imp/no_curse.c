#include <linux/fadvise.h>
#include <linux/fdtable.h>
#include <linux/syscalls.h>

#include <curse/no_fs_cache.h>

void no_curse_inject (void) {
/*
	rcu_read_lock();

	//FIXME: How to stop a process from cursing another one?
	if () {
		
	}

	rcu_read_unlock();
*/
	return;
}

