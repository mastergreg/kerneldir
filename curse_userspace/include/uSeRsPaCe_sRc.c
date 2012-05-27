#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <getopt.h>

//#include <curse/curse.h>
#define CURSE_MAX_NAME_SIZE 24		//Just until we test it properly (on a kernel that has the curse; writing externally now).

const char *USAGE_STR =
"Description of use\n\
Dunno ... \n\
-l, --list\n\
	Print the list of available curses on the system and exit.\n\
-A CURSE, --activate=CURSE\n\
	Activate curse with name CURSE.\n\
-D CURSE, --deactivate=CURSE\n\
	Deactivate curse with name CURSE.\n\
-C NAME PID, --cast=NAME,PID\n\
	Cast curse with name NAME on process with pid PID.\n\
-L NAME PID, --lift=NAME,PID\n\
	Lift curse with name NAME from process with pid PID.\n\
-c ID PID, --cast-id=ID,PID\n\
	Deploy curse with id ID on process with pid PID.\n\
-l ID, --lift-id=ID\n\
	Lift curse with id ID from process with pid PID.\n\
-a NAME ATTRIBUTE, --attribute=NAME,ATTRIBUTE\n\
	Change behavior of curse with name NAME based on ATTRIBUTE. Supported attributes are:\n\
		Ie/Id (enable/disable inheritance)\n\
		[U/G/S][e/d] (enable/disable user/group/superuser permissions)\n\
-b ID ATTRIBUTE, --attribute=ID,ATTRIBUTE\n\
	Change behavior of curse with id ID based on ATTRIBUTE. Supported attributes are:\n\
		Ie/Id (enable/disable inheritance)\n\
		[U/G/S][e/d] (enable/disable user/group/superuser permissions)\n\
-t CURSE PID, --check=CURSE,PID\n\
	Check if process with pid PID is tainted by CURSE.\n\
-S, --show-rules\n\
	Displays the rules and exits.\n\
-i, --add-rule=BIN,CURSE\n\
	Add rule for CURSE to be applied on binary file BIN.\n\
-r, --remove-rule=PATH,CURSE\n\
	Remove rule for CURSE from binary file BIN.\n\
-V\n\
	Enable verbose output.\n\
-h, --help\n\
	Print help and exit.\n\
-v, --version\n\
	Print version inforamtion and exit.";

#define PROG_NAME "curse"

#define out_stream(...)	fprintf(stdout, __VA_ARGS__)
#define err_stream(...)	fprintf(stderr, __VA_ARGS__)

void usage (void) {
	out_stream("%s\n", USAGE_STR);
}

void exit_status (int ret) {
	if (!ret)
		usage();
	exit(ret);
}

int main (int argc, char **argv) {
	int ret=0;
	int i;
	/*Slots for arguments-to-parse.*/
	long pid=0;							/*Defaults to 0.*/
	_Bool curse_id_or_name=0;			/*Defaults to name.*/
	char curse[CURSE_MAX_NAME_SIZE];	/*Holds the identifying string (before it is atoi'ed, in case of id).*/
	//...Rules are not here yet.
	/*Slots for getopt arguments.*/
	static char short_rules[] = "";
	static struct option long_options[] = {

	};

	while () {
		/*Do sth*/;
	}

	exit_status(ret);
	return ret;
}
