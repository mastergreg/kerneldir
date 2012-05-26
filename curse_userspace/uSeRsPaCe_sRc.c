#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

#define out_stream(...)	fprintf(stdout, __VA_ARGS__)
#define err_stream(...)	fprintf(stderr, __VA_ARGS__)

void usage (void) {
	out_stream("Description of use\n");
}
void exit_status (int _) {
	if (!_) {
		err_stream("sample%s\n", "haha");
		err_stream("sample2\n");
		
	}
}

int main (int argc, char **argv) {
	int ret=0;
	
	exit_status(ret);
	return ret;
}
