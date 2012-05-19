/*
 * This file contains the source code for the curse system call.
 * 
 * [The functions used by the system call are declared prior to the call source and sourced below it.]
 *
 */
#include <linux/linkage.h>
#include <linux/kernel.h>

#include "curse.h"
#include "curse_list.h"

//TODO: Forward declarations for helpful functions.


SYSCALL_DEFINE3(curse, int curse_cmd, int, curse_no, pid_t, target)
{
	printk(KERN_INFO "Master, you gave me command %d with curse %d on pid %ld.\n", curse_cmd, curse_no, (long)target);
	return (cmd+curse_no+((int)pid));
}

//TODO: Source for helpful functions.

/*	//Stub to check compilation of curse_list library.
int main (void) {
	struct curse_list_entry *hi;
	hi=&curse_full_list[0];
	printf("name is %s and id is %lu\n", hi->curse_name, (unsigned long)hi->curse_id);
	printf("haha\n");
	return 0;
}*/
