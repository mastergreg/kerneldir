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

#include <sys/types.h>

/* -------Curse commands-------
 * list_all					: lists all curses, implemented and not.						: <no_argument>
 * activate					: activates a curse (makes it ready for deployment)				: short int representing the serial number of the active bit in curse_id_mask (ex. 16 for 0x8000, 10 for 0x200, ...)
 * deactivate				: deactivates a curse (disables its use until reactivation)		: <same>
 * check_curse_activity		: checks if a curse is active									: <same>
 * check_tainted_process	: check if a process of the current user has an active curse	: pid_t identifying the process to check (-1 to check for any process)
 * deploy (ex unleash)		: set a curse upon a target (if any)							: pid_t representing the process to unleash the curse upon (not applicable in case of no target curses)
 * retire					: remove a curse from a target (if any)							: pid_t representing the process to remove the curse from (not applicable in case of no target curses)
 * -------------  RULES: Rules are static bindings of curses to binaries (paths) instead of processes.  ------------- :: These are supplementary. We may implement them, after the main implementation of the system call.
 * show_rules				: show all rules that are currently in the system				: <no_argument>
 * add_rule					: add a new rule (this adds a binding, and deploys the rule)	: short int representing the serial number of the curse_id_mask, full path to binary
 * rem_rule					: remove an existing rule										: <same>
 */
/*Curse system call interface.*/
enum curse_command {list_all=0, activate, deactivate, check_curse_activity, check_tainted_process, deploy, retire, show_rules, add_rule, rem_rule, illegal_command};

/* -------Curse status (booleans)-------
 * Implemented: curse has code (vs. placeholders)
 * Activated: curse can become active (is implemented, not launched)
 * Active: currently running (influencing the system) (is implemented, and activated)
 */
/*Lists every possible status for a curse (for userspace portability).*/
//TODO: Maybe in bitmask style. :: No need, enum elements are inclusive.
enum curse_status {implemented=0, activated, active, invalid_curse};

/*Structure describing a curse (and its status).*/
struct syscurse {
	struct curse_list_entry *entry;		//Not sure if it should be just struct or pointer, because problems may arise during copy to userspace.
	enum curse_status status;
};

/*Structure representing an active curse status.*/
struct curse_list_t {		//Note the _t part...:)
	struct syscurse curse_info;
	pid_t curse_target;
	uid_t proc_owner;
};							//Should be used in array form.

//TODO: Cleanup and check comments. Also move around things between kernel and userspace. See header.
//I will add more things later.

//Check with each other to minimize conflicts in source modification.

#ifdef __KERNEL__

//Kernel specific code... :: Does it need anything?


#endif

#endif /* _SYSCURSE_H */
