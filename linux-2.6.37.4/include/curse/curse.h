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
#include "curse_list.h"
#endif

/* -------Curse commands-------
 * 1. list_all							:	<no_argument>
 *   lists all curses in the curse list, implemented and not
 * R: <?>
//IMPORTANT: Depending on the way we do the copy to userspace, this should not even matter. I think it would be better if we went with the proc filesystem mapping solution (it is not a case where the data is time sensitive).
 * 2. activate							:	id of curse to activate
 *   activates the curse with the provided id, or activates the curse system if id is 0
 * R: 1 on success - appropriate code on failure
 * 3. deactivate						:	id of curse to deactivate
 *   deactivates the curse with the provided id or the whole system (disables the curse mechanism) if it is 0
 * R: <same>
 * 4. check_curse_activity				:	id of curse to check
 *   checks if a curse is active (false if the curse mechanism is deactivated)
 * R: 1 if a curse is active - 0 if no curse is active - appropriate code on error
 * 5. check_tainted_process				:	pid_t of the process to check (-1 to check for any process (?TODO)), id of curse to check
 *   check if the requested process has an active curse	(false if the user has not permissions to that process)
 * R: <same>
 * 6. cast (ex deploy (ex unleash))		:	pid_t of the process to target, id of the curse to use
 *   set a curse upon a target
 * R: 1 on success - appropriate code on failure
 * 7. lift (ex retire)					:	<same>
 *   remove a curse from a target
 * R: <same>
 * ------RULES: Rules are static bindings of curses to binaries (paths) instead of processes.------ :: These are supplementary. We may implement them, after the main implementation of the system call.
 * 8. show_rules						:	<no_argument>
 *   show all rules that are currently in the system
 * R: <?>
 * 9. add_rule							:	identifier to the binary (TODO: path/inode(?)), id of the curse to deploy
 *   add a new rule (this adds a binding, and deploys the rule)
 * R: 1 on success - appropriate code on failure
 * 10.rem_rule							:	<same>
 *   remove an existing rule
 * R: 1 on success - appropriate code on failure
 */
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

/* -------Curse status (booleans)-------
 * Implemented: curse has code (vs. placeholders)
 * Activated: curse can become active (is implemented, not launched)
 * Active: currently running (influencing the system) (is implemented, and activated)
 */
/*Lists every possible status for a curse (for userspace portability).*/		//Maybe in bitmask style. :: No need, enum elements are inclusive.
enum curse_status {IMPLEMENTED=0x00, ACTIVATED=0x01, ACTIVE=0x02, INVALID_CURSE=0x04};

/*Structure describing a curse (and its status).*/
struct syscurse {
	struct curse_list_entry *entry;		//Not sure if it should be just struct or pointer, because problems may arise during copy to userspace.
	uint64_t curse_bit;					//Corresponding bitfield for the current curse.
	unsigned int ref_count;
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
int syscurse_activate(uint64_t);
int syscurse_deactivate(uint64_t);
int syscurse_check_curse_activity(uint64_t);
int syscurse_check_tainted_process(uint64_t, pid_t);
int syscurse_cast(uint64_t, pid_t);
int syscurse_lift(uint64_t, pid_t);
int syscurse_show_rules(void);
int syscurse_add_rule(uint64_t, char *);
int syscurse_rem_rule(uint64_t, char *);

/*Proc node pointer.*/
struct proc_dir_entry *dir_node=(struct proc_dir_entry *)NULL, *output_node=(struct proc_dir_entry *)NULL;

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

/*This is the injection wrapper, which must be in kernel space. This basically is an inline or define diretive that checks if curses are activated and if the current process has a curse before calling the proper curse function.*/
inline void curse_k_wrapper (void) {
	//check if curses are enabled
	//check if current has a curse
	//if so, retrieve the pointer from the fun* array and call.
	return;
}

#endif	/* __KERNEL__ */

#endif /* _SYSCURSE_H */
