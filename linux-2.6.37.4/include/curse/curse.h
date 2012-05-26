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

#ifndef __KERNEL__			/*Inclusion of uint64_t on userspace.*/
#include <stdint.h>
#endif
#include <curse/curse_types.h>

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

/*Procfs entry paths.*/
#define PROC_DIR_NAME "curse"
#define PROC_OUT_NODE_NAME "listing"

//TODO: Cleanup and check comments. Also move around things between kernel and userspace. See header.
#ifdef __KERNEL__

/*Kernel specific libraries.*/
#include <linux/semaphore.h>
#include <linux/proc_fs.h>
#include <linux/types.h>	/*pid_t, uin64_t on kernel.*/
#include <asm/atomic.h>

/*Structure describing a curse (and its status).*/
struct syscurse { 
	struct curse_list_entry *entry;		//Not sure if it should be just struct or pointer, because problems may arise during copy to userspace.
	atomic_t ref_count;					//Count of how many active deployments exist for this curse.
	uint64_t curse_bit;					//Corresponding bitfield for the current curse.
	uint8_t permissions;				//Inheritance - UserGroupSuperuser(Permissions) flag field.
	enum curse_status status;			//Activation status for this curse.
};

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
/*Inheritance specific macros (curse-specific inheritance is inserted in permissions field of syscurse struct.*/
#define _INHER_MASK 0x20
#define GET_INHER(_) (((_).permissions) & (_INHER_MASK))
#define SET_INHER(_) (((_).permissions) |= (_INHER_MASK))
#define CLR_INHER(_) (((_).permissions) &= ~(_INHER_MASK))

/*This struct is a protective wrapper on a boolean variable (needed for concurrent calls on rw access to it).*/
//TODO: clean this mess, it should be in curse 0x0 of curse_list_pointer
struct bool_wrapper {
	struct semaphore guard;
	_Bool value;
};

/*Data holding the curse system status.*/
extern struct bool_wrapper curse_system_active;
/*Pointer to the implemented curse array (loaded at init of syscall).*/
extern struct syscurse *curse_list_pointer;
/*Proc node pointer.*/
extern struct proc_dir_entry *dir_node, *output_node;

/*This macro gives encapsulated access to the curse system general status.*/
#define CURSE_SYSTEM_Q (atomic_read(&(curse_list_pointer[0].ref_count)))
#define CURSE_SYSTEM_DOWN atomic_set(&(curse_list_pointer[0].ref_count), 0)
#define CURSE_SYSTEM_UP atomic_set(&(curse_list_pointer[0].ref_count), 1)

#endif	/* __KERNEL__ */

#endif /* _SYSCURSE_H */
