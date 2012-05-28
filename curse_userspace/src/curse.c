/* -.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.
* File Name : curse.c
* Creation Date : 28-05-2012
* Last Modified : Mon 28 May 2012 02:49:34 PM EEST
* Created By : Greg Liras <gregliras@gmail.com>
_._._._._._._._._._._._._._._._._._._._._.*/


#include <curse/curse.h>
#include <curse/curse_list.h>
#include <curse/curse_types.h>



#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>

#ifdef __i386__
# define __NR_curse 341
#else
# define __NR_curse 303 
#endif


curse_id_t curse_id_from_string(const char *id) {

	return id[0];
}

long curse (int command, const char *id, pid_t target) {
	int curse = curse_id_from_string(id);
	return syscall(__NR_curse, command, curse, target);
}


