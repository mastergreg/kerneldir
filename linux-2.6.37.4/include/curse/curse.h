/* 
 * This library is the main library for the curse system call.
 * 
 * It is to be included by both userspace and kernel programs, so we take care to define the public interface properly.
 * 
 * Since we want it to be located in the same directory with the curse source file, 
 *  it will be included by it in double quotes, 
 *  but the userspace inclusion is to be done in the normal fashion.
 *
 */


#ifndef _SYSCURSE_H
#define _SYSCURSE_H

#include <linux/types.h>	/*pid_t, uin64_t on kernel.*/
#ifndef __KERNEL__			/*Inclusion of uint64_t on userspace.*/



#include <stdint.h>
#include <curse/curse_list.h>
#endif

/*Curse system call interface.*/
enum curse_command	{	LIST_ALL=0, 
						ACTIVATE, DEACTIVATE, 
						CHECK_CURSE_ACTIVITY, 
						CHECK_TAINTED_PROCESS, 
						CAST, LIFT, 
						SHOW_RULES, 
						ADD_RULE, REM_RULE, 
						ILLEGAL_COMMAND
					};

/*Lists every possible status for a curse (for userspace portability).*/		//Maybe in bitmask style. :: No need, enum elements are inclusive.
enum curse_status {IMPLEMENTED=0x00, ACTIVATED=0x01, ACTIVE=0x02, INVALID_CURSE=0x04};

/*Structure describing a curse (and its status).*/
struct syscurse {
	struct curse_list_entry *entry;		//Not sure if it should be just struct or pointer, because problems may arise during copy to userspace.
	unsigned int ref_count;				//Count of how many active deployments exist for this curse.
	uint64_t curse_bit;					//Corresponding bitfield for the current curse.
	uint8_t permissions;				//Inherritance - UserGroupSuperuser(Permissions) flag field.
	enum curse_status status;
};

/*Procfs entry paths.*/
#define proc_dir_name "curse"
#define proc_out_node_name "listing"

//TODO: Cleanup and check comments. Also move around things between kernel and userspace. See header.
#ifdef __KERNEL__

/*Kernel specific code.*/
#include <linux/semaphore.h>
#include <linux/proc_fs.h>


/*Function prototypes (although forwards are ugly:)).*/
int syscurse_list_all(char *, char **, off_t, int, int *, void *);
int syscurse_activate(curse_id_t);
int syscurse_deactivate(curse_id_t);
int syscurse_check_curse_activity(curse_id_t);
int syscurse_check_tainted_process(curse_id_t, pid_t);
int syscurse_cast(curse_id_t, pid_t);
int syscurse_lift(curse_id_t, pid_t);
int syscurse_show_rules(void);
int syscurse_add_rule(curse_id_t, char *);
int syscurse_rem_rule(curse_id_t, char *);

/*Bitmasks to use for setting and checking the permissions field in struct syscurse.*/
#define _U_M 0x01
#define _G_M 0x02
#define _S_M 0x04
/*Inherritance specific macros (curse-specific inherritance is inserted in permissions field of syscurse struct.*/
#define _INHER_MASK 0x20
#define GET_INHER(_) (((_).permissions) & (_INHER_MASK))
#define SET_INHER(_) (((_).permissions) |= (_INHER_MASK))
#define CLR_INHER(_) (((_).permissions) &= ~(_INHER_MASK))

//Source it here too.
#include "curse_sched.h"

/*This struct is a protective wrapper on a boolean variable (needed for concurrent calls on rw access to it).*/
struct bool_wrapper {
	struct semaphore guard;
	_Bool value;
};

/*Data holding the curse system status.*/
struct bool_wrapper curse_system_active;
/*Pointer to the implemented curse array (loaded at init of syscall).*/
struct syscurse *curse_list_pointer=(struct syscurse *)NULL;
/*Proc node pointer.*/
struct proc_dir_entry *dir_node=(struct proc_dir_entry *)NULL, *output_node=(struct proc_dir_entry *)NULL;

/*This is the injection wrapper, which must be in kernel space. This basically is an inline or define directive that checks if curses are activated and if the current process has a curse before calling the proper curse function.*/
inline void curse_k_wrapper (void) {
	//check if curses are enabled
	struct task_struct *cur;

	if (down_interruptible(&curse_system_active.guard))
		goto out_pos;
	//check if current has a curse
	if (curse_system_active.value == 0)
		goto out_sema_held;
	//if so, retrieve the pointer from the fun* array and call.
	
	//this is a macro in arch/x86/include/asm/current.h
	cur = current;

	//call the curse handler if there is a curse
	//if is used for opt, might integrate the handler here
	//ideas?
	if (cur->curse_data.curse_field)
		printk(KERN_INFO "Gotta do sth now, whaaat?\n");

	//... This is where curse and check take place.

out_sema_held:
	up(&curse_system_active.guard);
out_pos:
	return;
}

#endif	/* __KERNEL__ */

#endif /* _SYSCURSE_H */
