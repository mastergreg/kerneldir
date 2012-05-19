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

//Function prototypes (although I hate forwards, we have to provide the interface).
//All the functions return 0 for success, or one of the usual error codes for error.
int syscurse_list_all(void);
int syscurse_activate(int);
int syscurse_deactivate(int);
int syscurse_check_curse_activity(int);
int syscurse_check_tainted_process(pid_t);
int syscurse_deploy(int, pid_t);
int syscurse_retire(int, pid_t);
int syscurse_show_rules(void);
int syscurse_add_rule(int, char *);
int syscurse_rem_rule(int, char *);

SYSCALL_DEFINE3(curse, int curse_cmd, int, curse_no, pid_t, target)
{
	printk(KERN_INFO "Master, you gave me command %d with curse %d on pid %ld.\n", curse_cmd, curse_no, (long)target);
	return (cmd+curse_no+((int)pid));
}

//TODO: Source helpful functions.


/*	//Stub to check compilation of curse_list library.
int main (void) {
	struct curse_list_entry *hi;
	hi=&curse_full_list[0];
	printf("name is %s and id is %lu\n", hi->curse_name, (unsigned long)hi->curse_id);
	printf("haha\n");
	return 0;
}*/
