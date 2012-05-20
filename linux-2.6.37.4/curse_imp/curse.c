/*
 * This file contains the source code for the curse system call.
 * 
 * [The functions used by the system call are declared prior to the call source and sourced below it.]
 *
 */
 
#include <linux/linkage.h>
#include <linux/syscalls.h>
#include <linux/kernel.h>
//TODO: Maybe we need to add sys/types for pid_t and uid_t, but curse.h has it too. Nevertheless, better be prepared than sorry (there are sentinels NEwAE):)

#include "curse.h"
#include "curse_list.h"

//Function prototypes (although I hate forwards, we have to provide the interface).
//All the functions return 0 for success, or one of the usual error codes for error.
static inline int syscurse_list_all(void);
static inline int syscurse_activate(void);
static inline int syscurse_deactivate(void);
static inline int syscurse_check_curse_activity(int);
static inline int syscurse_check_tainted_process(pid_t);
static inline int syscurse_deploy(int, pid_t);
static inline int syscurse_retire(int, pid_t);
static inline int syscurse_show_rules(void);
static inline int syscurse_add_rule(int, char *);
static inline int syscurse_rem_rule(int, char *);
//TODO: Some functions should not return int, but a pointer to an array (for example syscurse_list_all, I think).
//IMPORTANT: Depending on the way we do the copy to userspace, this should not even matter. I think it would be better if we went with the proc filesystem mapping solution (it is not a case where the data is time sensitive).

/*This is the system call source base function.*/
SYSCALL_DEFINE3(curse, int, curse_cmd, int, curse_no, pid_t, target /*I think it need a char * too.*/)		//asmlinkage long sys_curse(int curse_cmd, int curse_no, pid_t target)
{
	printk(KERN_INFO "Master, you gave me command %d with curse %d on pid %ld.\n", curse_cmd, curse_no, (long)target);
/*
	long ret=-EINVAL;
	int cmd_norm=(int)curse_cmd;
	switch(cmd_norm) {
		case list_all:
			
		case activate:
			
		case deactivate:
			
		case check_curse_activity:
			
		case check_tainted_process:
			
		case deploy:

		case retire:
			
		case show_rules:
			//Stub (for now, fall-throughs)
		case add_rule:
			//Stub
		case rem_rule:
			printk(KERN_INFO "This operation is unsupported at this time.");
			goto out;
		default:
			goto out;
	}

out:
	return ret;
*/
	return (long)(curse_cmd+curse_no+(int)target);
}

//TODO: Source helpful functions.
static inline int syscurse_list_all (void) {
	//...
	return 0;
}
static inline int syscurse_activate (void) {
	//...
	return 0;
}
static inline int syscurse_deactivate (void) {
	//...
	return 0;
}
static inline int syscurse_check_curse_activity (int curse_no) {
	//...
	return 0;
}
static inline int syscurse_check_tainted_process (pid_t target) {
	//...
	return 0;
}
static inline int syscurse_deploy (int curse_no, pid_t target) {
	//...
	return 0;
}
static inline int syscurse_retire (int curse_no, pid_t target) {
	//...
	return 0;
}
static inline int syscurse_show_rules (void) {
	return 0;
}
static inline int syscurse_add_rule (int curse, char *path) {
	return 0;
}
static inline int syscurse_rem_rule (int curse, char *path) {
	return 0;
}

/*	//Stub to check compilation of curse_list library.
int main (void) {
	struct curse_list_entry *hi;
	hi=&curse_full_list[0];
	printf("name is %s and id is %lu\n", hi->curse_name, (unsigned long)hi->curse_id);
	printf("haha\n");
	return 0;
}*/
