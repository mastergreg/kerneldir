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

#include <linux/types.h>
//#include "curse_list.h"

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
 * ============RETURN============
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
enum curse_status {IMPLEMENTED=0, ACTIVATED, ACTIVE, INVALID_CURSE};

/*Structure representing an active curse status.*/
/*	//USELESS??
struct curse_list_t {		//Note the _t part.:) : Seriously tho, it should be used in array form, not LL.
	struct syscurse curse_info;
	pid_t curse_target;
	uid_t proc_owner;
};*/

/*Structure describing a curse (and its status).*/
struct syscurse {
	struct curse_list_entry *entry;		//Not sure if it should be just struct or pointer, because problems may arise during copy to userspace.
//	struct curse_list_t curse_status;
	enum curse_status status;
};

//TODO: Cleanup and check comments. Also move around things between kernel and userspace. See header.
//I will add more things later.

//Check with each other to minimize conflicts in source modification.

#ifdef __KERNEL__

//Kernel specific code...
#include <linux/semaphore.h>

//Function prototypes (although forwards are ugly:)). : All the functions return 0 for success, or one of the usual error codes for error.
int syscurse_list_all(void);
int syscurse_activate(int);
int syscurse_deactivate(int);
int syscurse_check_curse_activity(int);
int syscurse_check_tainted_process(pid_t);
int syscurse_cast(int, pid_t);
int syscurse_lift(int, pid_t);
int syscurse_show_rules(void);
int syscurse_add_rule(int, char *);
int syscurse_rem_rule(int, char *);

#include "curse_sched.h"	//Source it here too.

/*This struct is a protective wrapper on a boolean variable (needed for concurrent calls on rw access to it).*/
struct bool_wrapper {
	struct semaphore guard;
	_Bool value;
};

//Since the wrapper that checks is in the header, I think this should be there too.	:: Moved it here. curse_k_wrapper needs it. Not static - prevents reentrancy.
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

//Anything else?...


#endif	/* __KERNEL__ */

#endif /* _SYSCURSE_H */
