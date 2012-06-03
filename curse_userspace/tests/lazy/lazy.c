#include <curse/curse.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>

/* does nothing for 25 seconds, so it can be cursed as we like!*/
int main (int argc, char **argv) {
	sleep(25000);
	return 0;
}
