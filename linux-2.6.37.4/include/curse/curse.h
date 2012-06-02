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
enum curse_command	{	LIST_ALL=0, CURSE_CTRL,
						ACTIVATE, DEACTIVATE,
						CHECK_CURSE_ACTIVITY,
						CHECK_TAINTED_PROCESS,
						CAST, LIFT, GET_CURSE_NO,
						SHOW_RULES,
						ADD_RULE, REM_RULE,
						ILLEGAL_COMMAND
					};

/*Curse control commands.*/
enum curse_control	{	INH_ON=0, INH_OFF,
						USR_ACTIVE_PERM_ON, USR_ACTIVE_PERM_OFF,
						USR_PASSIVE_PERM_ON, USR_PASSIVE_PERM_OFF,
						//GRP_PERM_ON, GRP_PERM_OFF,
						SU_ACTIVE_PERM_ON, SU_ACTIVE_PERM_OFF,
						SU_PASSIVE_PERM_ON, SU_PASSIVE_PERM_OFF,
					};

/*Lists every possible status for a curse (for userspace portability).*/
enum curse_status {IMPLEMENTED=0x00, ACTIVATED=0x01, CASTED=0x02, INVALID_CURSE=0x04};

/*Procfs entry names.*/
#define PROC_DIR_NAME "curse"
#define PROC_OUT_NODE_NAME "curse_list"

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
	spinlock_t flag_lock;
	uint8_t var_flags;					//Flags field.
	enum curse_status status;			//Activation status for this curse.
	struct curse_fun_element *functions;
};

/*Function prototypes (although forwards are ugly:)).*/
/*
int syscurse_list_all (char __user *);
int syscurse_activate (int);
int syscurse_deactivate (int);
int syscurse_check_curse_activity (int);
int syscurse_check_tainted_process (int, pid_t);
int syscurse_ctrl (int, int, pid_t);
int syscurse_cast (int, pid_t);
int syscurse_lift (int, pid_t);
int syscurse_show_rules (void);
int syscurse_add_rule (int, char __user *);
int syscurse_rem_rule (int, char __user *);
*/

/*Pointer to the implemented curse array (loaded at init of syscall).*/
extern struct syscurse *curse_list_pointer;
/*Proc node pointer.*/
extern struct proc_dir_entry *dir_node, *output_node;

/*Inheritance specific macros (curse-specific inheritance is inserted in var_flags field of syscurse struct.*/
#define _INHER_MASK	0x20
#define GET_INHER(_index) (((curse_list_pointer[_index]).var_flags) & (_INHER_MASK))
#define SET_INHER(_index) (((curse_list_pointer[_index]).var_flags) |= (_INHER_MASK))
#define CLR_INHER(_index) (((curse_list_pointer[_index]).var_flags) &= ~(_INHER_MASK))

/*Bitmasks to use for setting and checking the permissions field in struct tast_curse_struct.*/
#define _USR_ACTIVE_PERM	0x01		/*Active permissions denote a capability to cast/lift.*/
//#define _GRP_ACTIVE_PERM	0x02
#define _SU_ACTIVE_PERM		0x04
#define _USR_PASSIVE_PERM	0x10		/*Passive permissions denote a capability to have a curse cast upon us.*/
//#define _GRP_PASSIVE_PERM	0x20
#define _SU_PASSIVE_PERM	0x40
/*Permission specific macros (first argument is a task_curse_struct variable, and the second a permission mask).*/
#define GET_PERM(el, perm_mask) (((el).permissions) & (perm_mask))
#define SET_PERM(el, perm_mask) (((el).permissions) |= (perm_mask))
#define CLR_PERM(el, perm_mask) (((el).permissions) &= ~(perm_mask))

/*This macro gives encapsulated access to the curse system general status.*/
#define CURSE_SYSTEM_Q (atomic_read(&(curse_list_pointer[0].ref_count)))
#define CURSE_SYSTEM_DOWN atomic_set(&(curse_list_pointer[0].ref_count), 0)
#define CURSE_SYSTEM_UP atomic_set(&(curse_list_pointer[0].ref_count), 1)

#endif	/* __KERNEL__ */

#endif /* _SYSCURSE_H */
