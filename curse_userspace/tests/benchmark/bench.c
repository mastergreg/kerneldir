#include <curse/curse.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <time.h>

#define __NR_curse 303

int main (int argc, char **argv) {
	int i;
	clock_t diff;
	struct curse_list_entry onoma[10];

	printf("Sys curse: 1.000.000 list calls (comparison of library buffering vs. immediate syscall).\n");
	clock();
	for (i=0; i<1000000; i++) {
		curse(LIST_ALL, 0, 0, 0, onoma);
	}
	diff = clock();
	printf("Library calls wasted %lld clock ticks.\n", diff);

	diff = clock();
	for (i=0; i<1000000; i++) {
		syscall(__NR_curse, LIST_ALL, 0, 0, 0, onoma);
	 }
	diff = (clock() - diff);
	printf("Immediate syscall calls wasted %lld clock ticks.\n", (long long)diff);
	
	return 0;
}
