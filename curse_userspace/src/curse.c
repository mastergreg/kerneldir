/* -.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.
* File Name : curse.c
* Creation Date : 28-05-2012
* Last Modified : Tue 29 May 2012 03:58:06 PM EEST
* Created By : Greg Liras <gregliras@gmail.com>
_._._._._._._._._._._._._._._._._._._._._.*/

#ifndef _LIB_CURSE_USER
#define _LIB_CURSE_USER

#include <curse/curse.h>
#include <curse/curse_list.h>
#include <curse/curse_types.h>

#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>

#ifdef __i386__
#define __NR_curse 341
#else
#define __NR_curse 303 
#endif

/*Wrapper for encapsulated access to the list. Static and NULL for the first time (protected by a semaphore), if allocated and initialized, it must not need semaphore access.*/
struct curse_list_entry *get_list (void) {
	static struct curse_list_entry *buffered_list=NULL;
	if ((buffered_list!=NULL) || ((/*sema take*/) && (buffered_list==NULL)) || /*Release sema.*/) {
		buffered_list = (struct curse_list_entry *)calloc((MAX_CURSE_NO+1), sizeof(struct curse_list_entry));
		if (buffered_list != NULL) {
			/*Allocate (MAX_CURSE_NO+1)*sizeof(struct curse_list_entry)*/
			/*Call syscall and get list.*/
		}
	}
	return buffered_list;
}

/*Wrapper for returning the index of a curse by searching with a name.*/
int index_from_name (const char *id) {
	/*Search static buffered list (if not null) for occurence. That is until MAX_CURSE_NO.*/

	return id[0];
}

long curse (int command, const char *id, pid_t target) {
	curse = curse_id_from_string(id);
	return syscall(__NR_curse, command, curse, target);
}

#endif
