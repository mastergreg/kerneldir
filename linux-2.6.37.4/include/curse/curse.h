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
 * list_all					: lists all curses, implemented and not.						: <no_argument>
 * activate					: activates the curse system (enables the curse mechanism)		: int representing the serial number of the active bit in curse_id_mask (ex. 16 for 0x8000, 10 for 0x200, ...)
 * deactivate				: deactivates the curse system (disables the curse mechanism)	: <same>
 * check_curse_activity		: checks if a curse is active									: <same>
 * check_tainted_process	: check if a process of the current user has an active curse	: pid_t identifying the process to check (-1 to check for any process)
 * cast (ex unleash)		: set a curse upon a target (if any)							: pid_t representing the process to unleash the curse upon (not applicable in case of no target curses)
 * lift					: remove a curse from a target (if any)							: pid_t representing the process to remove the curse from (not applicable in case of no target curses)
 * -------------  RULES: Rules are static bindings of curses to binaries (paths) instead of processes.  ------------- :: These are supplementary. We may implement them, after the main implementation of the system call.
 * show_rules				: show all rules that are currently in the system				: <no_argument>
 * add_rule					: add a new rule (this adds a binding, and deploys the rule)	: integer representing the serial number of the curse_id_mask, full path to binary
 * rem_rule					: remove an existing rule										: <same>
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
enum curse_status {IMPLEMENTED=0, ACTIVATED, ACTIVE, INVALID_CURSE};

/*Structure describing a curse (and its status).*/
struct syscurse {
	struct curse_list_entry *entry;		//Not sure if it should be just struct or pointer, because problems may arise during copy to userspace.
	enum curse_status status;
};

/*Structure representing an active curse status.*/
struct curse_list_t {		//Note the _t part.:) : Seriously tho, it should be used in array form, not LL.
	struct syscurse curse_info;
	pid_t curse_target;
	uid_t proc_owner;
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

/*Data holding the curse system status.*/
//Since the wrapper that checks is in the header, I think this should be there too.	:: Moved it here. curse_k_wrapper needs it. Not static - prevents reentrancy.
struct bool_wrapper curse_system_active;

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
