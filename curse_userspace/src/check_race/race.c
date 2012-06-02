#include <curse/curse.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <signal.h>


int main (int argc, char **argv) {
	struct curse_list_entry onoma[10];

	curse(LIST_ALL, 0, 0, 0, onoma);
	raise(SIGSTOP);
	
	return 0;
}
