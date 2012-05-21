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

//Global data.
/*Static data holding the curse system status.*/
static struct bool_wrapper curse_system_active;	//TODO: Since the wrapper that checks is in the header, I think this should be there too.

//Function prototypes (although I hate forwards, we have to provide the interface).
//All the functions return 0 for success, or one of the usual error codes for error.
static inline int syscurse_list_all(void);
static inline int syscurse_activate(void);
static inline int syscurse_deactivate(void);
static inline int syscurse_check_curse_activity(int);
static inline int syscurse_check_tainted_process(pid_t);
static inline int syscurse_deploy(int, pid_t);
//static inline int syscurse_cast(int, pid_t);
static inline int syscurse_retire(int, pid_t);
//static inline int syscurse_lift(int, pid_t);
static inline int syscurse_show_rules(void);
static inline int syscurse_add_rule(int, char *);
static inline int syscurse_rem_rule(int, char *);
//TODO: Some functions should not return int, but a pointer to an array (for example syscurse_list_all, I think).
//IMPORTANT: Depending on the way we do the copy to userspace, this should not even matter. I think it would be better if we went with the proc filesystem mapping solution (it is not a case where the data is time sensitive).

/*This is the system call source base function.*/
SYSCALL_DEFINE3(curse, int, curse_cmd, int, curse_no, pid_t, target)		//asmlinkage long sys_curse(int curse_cmd, int curse_no, pid_t target)
{	
	long ret=-EINVAL;
	int cmd_norm=(int)curse_cmd;
	/*This flag helps to initialize what needs it in our envirronment.*/
	static int initial_actions_flag=1;		//TODO: Need to figure out a way to test-and-set it atomically.

	if (initial_actions_flag) {		//Conditional wil not be entered but the first time(s).
		if (initial_actions_flag==2)
			goto wait_init;
		initial_actions_flag=2;

		//Initializing actions.
		sema_init(&curse_system_active.guard, 1);
		curse_system_active.value=0;

		initial_actions_flag=0;
	}
wait_init:
		while (initial_actions_flag)
			continue;

	printk(KERN_INFO "Master, you gave me command %d with curse %d on pid %ld.\n", curse_cmd, curse_no, (long)target);
	
	switch(cmd_norm) {
		case LIST_ALL:
            ret = syscurse_list_all();
            break;
		case ACTIVATE:
            ret = syscurse_activate();
            break;
		case DEACTIVATE:
            ret = syscurse_deactivate();
            break;
		case CHECK_CURSE_ACTIVITY:
            ret = syscurse_check_curse_activity(curse_no);
            break;
			
		case CHECK_TAINTED_PROCESS:
            ret = syscurse_check_tainted_process(target);
            break;
			
		case DEPLOY:
            ret = syscurse_deploy(curse_no, target);
            break;

		case RETIRE:
            ret = syscurse_retire(curse_no, target);
            break;
			
		case SHOW_RULES:
			//Stub (for now, fall-throughs)
		case ADD_RULE:
			//Stub
		case REM_RULE:
			printk(KERN_INFO "This operation is unsupported at this time.");
            ret = -EINVAL;
			goto out;
		case ILLEGAL_COMMAND:
		default:
			goto out;
	}

out:
	return ret;
	//return (long)(curse_cmd+curse_no+(int)target);
}

//TODO: Source helpful functions.
static inline int syscurse_list_all (void) {
	//...
	return 0;
}
static inline int syscurse_activate (void) {
	if (!curse_system_active.value) {
		if (down_interruptible(&curse_system_active.guard))
			return -EINTR;
		curse_system_active.value=1;
		up(&curse_system_active.guard);
	}
	return 0;
}
static inline int syscurse_deactivate (void) {
	if (curse_system_active.value) {
		if (down_interruptible(&curse_system_active.guard))
			return -EINTR;
		curse_system_active.value=0;
		up(&curse_system_active.guard);
	}
	//TODO: Do we have to unhook (call close pointer) all the active curses here?
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

