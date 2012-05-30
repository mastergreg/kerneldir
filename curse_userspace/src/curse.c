/* -.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.
 * File Name : curse.c
 * Creation Date : 28-05-2012
 * Last Modified : Wed 30 May 2012 03:51:12 PM EEST
 * Created By : Greg Liras <gregliras@gmail.com>
 * _._._._._._._._._._._._._._._._._._._._.*/

#ifndef _LIB_CURSE_USER
#define _LIB_CURSE_USER

#include <curse/curse.h>
#include <curse/curse_list.h>
#include <curse/curse_types.h>

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <semaphore.h>
#include <sys/types.h>

#ifdef __i386__
#define __NR_curse 341
#else
#define __NR_curse 303
#endif

/*Static shared data.*/
sem_t list_sema;

/*Init-Fin handlers.*/
void __attribute__((costructor)) curse_init_handle() {
    if (!sem_init(&list_sema, 1 /*0 is for thread-shared semas*/ , 1)) {
        //...Error.
        perror("Sema init error");
    }
    //...Other initializations
}
void __attribute__((destructor)) curse_fin_handle() {
    if (!sem_destroy(&list_sema)) {
        //...Error.
        perror("Sema destroy error");
    }
    //...Other
}

/*Wrapper for encapsulated access to the list. Static and NULL for the first time (protected by semaphore), if allocated and initialized, it must not need semaphore access.*/
struct curse_list_entry *get_list (void) {
    static struct curse_list_entry *buffered_list = NULL;
    long maxCurseNum;

    if (buffered_list == NULL) {
        if (!sem_wait(&list_sema)) {	/*Take sema.*/
            if (buffered_list == NULL) {
                /*Call to get max_curse_no*/
                maxCurseNum = syscall(__NR_curse, GET_CURSE_NO, 0, 0, 0, 0);
                /*Allocate (MAX_CURSE_NO+1)*sizeof(struct curse_list_entry)*/
                buffered_list = (struct curse_list_entry *)calloc((maxCurseNum + 1), sizeof(struct curse_list_entry));
                /*Call syscall and get list.*/
                syscall(__NR_curse, LIST_ALL, 0, 0, 0, buffered_list);
			}
			if (sem_post(&list_sema)) {	 /*Release sema.*/
                perror("Semaphore release failed");
            }
        } else {
			perror("Semaphore acquisition failed");
            return NULL;
		}
    }
    return buffered_list;
} 

/*Wrapper for returning the index of a curse by searching with a name.*/
int index_from_name(const char *id) {
    /*Search static buffered list (if not null) for occurence. That is until MAX_CURSE_NO.*/
    int i = 0, found = 0;
    long maxCurseNum = syscall(__NR_curse, GET_CURSE_NO, 0, 0, 0, 0);
	const struct  curse_list_entry *list;

	printf("max number is: %ld\n", maxCurseNum);
    list = get_list();
    if (list != NULL) {
        for(i = 0; i < maxCurseNum; ++i) {
			printf("List name: %s - ID: %s\n", list[i].curse_name, id);
            if (strcmp(list[i].curse_name, id) == 0) {
                found = 1;
                break;
            }
        }
        if (found == 1) {
            return i;
        } else {
            perror("Curse not found");
            return -1;  //not found
        }
    } else {
        perror("Curse list is empty");
        return -2;      //empty
    }
}

long curse(int command, int curse_no, pid_t target, int ctrl, char* userbuf ) {
	return syscall(__NR_curse, command, curse_no, target, ctrl, userbuf);
}

long curse_by_name(int command, const char* name, pid_t target, int ctrl, char* userbuf) {
	int theCurse = index_from_name(name);
	return curse(command, theCurse, target, ctrl, userbuf);
}

/* the usual 3-parameter cases, so we dont have to use dummies all the time*/
long curse3(int command, int curse_no, pid_t target) {
	if ((command == CURSE_CTRL) || (command == LIST_ALL)){
		perror("This curse requires more than 3 arguments");
		return -1;
	} else {
		return curse(command, curse_no, target, 0, NULL);
	}
}

long curse_by_name3(int command, const char* name, pid_t target) {
	if ((command == CURSE_CTRL) || (command == LIST_ALL)) {
		perror("This curse requires more than 3 arguments");
		return -1;
	} else {
		return curse_by_name(command, name, target, 0, NULL);
	}
}
#endif	/* _LIB_CURSE_NO */
