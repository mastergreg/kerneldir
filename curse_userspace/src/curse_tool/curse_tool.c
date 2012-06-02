#include <curse/curse.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <unistd.h>
#include <getopt.h>

int help(void)
{
	printf(
	    "Usage: curse <global action>\n"
	    "Usage: curse <cursename> <action> [<option>]\n"
	    "\n"
	    " Global Actions                     Description\n"
	    "----------------                ---------------------\n"
	    "       -h, -?                   show this help\n"
	    "       -L                       list curses\n"
	    "\n"
	    " Curse Actions                      Description\n"
	    "----------------                ---------------------\n"
	    "       -a                       activate curse <cursename>\n"
	    "       -d                       deactivate curse <cursename>\n"
	    "\n"
	    "       -c                       curse (needs -C <cursename> -P <pid>)\n"
	    "       -l                       lift curse (needs -C <cursename> -P <pid>)\n"
	    "\n"
	    " Specifiers                         Description\n"
	    "----------------                ---------------------\n"
	    "       -P <pid>                 specify PID of target process \n"
	    "       -C <cursename>           specify cursename to use \n"
	    "\n"
	    "   Examples                         Description\n"
	    "----------------                ---------------------\n"
	    "curse -L                        show a list of available curses\n"
	    "curse -a -N nocache             enable curse 'nocache' \n"
	    "curse -c -N nocache -P 7423     curse process 7423 with 'nocache' \n"
	    "\n"
	);
	return 0;
}


/*	a -> Activate curse
 *	d -> Deactivate curse
 *	c -> Cast curse
 *	l -> Lift curse
 *	N -> Name of curse + arg (where applicable)
 *	P -> target Process PID + arg (where applicable)
 *	L -> List Curses
 *	h,? -> Help
 */
static const char *optString = "adclN:P:Lh?";

int main(int argc, char **argv)
{
	int aflag = 0;
	int dflag = 0;
	int cflag = 0;
	int lflag = 0;
	int i, c;

	struct globalArgs_t {
		char *Cursename;		/* -C option */
		int t_PID;				/* -P option */
	} globalArgs;

	globalArgs.Cursename = NULL;
	globalArgs.t_PID = -1;

	opterr = 0;

	while ((c = getopt (argc, argv, optString)) != -1)
		switch (c) {
		case 'a':
			aflag = 1;
			break;
		case 'd':
			dflag = 1;
			break;
		case 'c':
			cflag = 1;
			break;
		case 'l':
			lflag = 1;
			break;
		case 'N':
			globalArgs.Cursename = strdup(optarg);
			break;
		case 'P':
			sscanf(optarg, "%d", &globalArgs.t_PID);
			break;
		case 'h':
			if (optopt == 'c')
				fprintf (stderr, "Option -%c requires an argument.\n", optopt);
			else if (isprint (optopt))
				fprintf (stderr, "Unknown option `-%c'.\n", optopt);
			else
				fprintf (stderr, "Unknown option character `\\x%x'.\n", optopt);
			return 1;
		default:
			/* if we reach this, invalid option is given */
			perror("Invalid Option given");
			return -1;
		}

	if (aflag == 1) {
		if (dflag == 1 || cflag == 1 || lflag == 1) {
			perror("Invalid use of '-a' flag");
			return -2;
		} else if (!globalArgs.Cursename) {
			perror("Missing argument (Curse name)");
			return -3;
		} else {
			//activate curse
		}
	}
	if (dflag == 1) {
		if (aflag == 1 || cflag == 1 || lflag == 1) {
			perror("Invalid use of '-d' flag");
			return -2;
		} else if (!globalArgs.Cursename) {
			perror("Missing argument (Curse name)");
			return -3;
		} else {
			//deactivate curse
		}
	}
	if (cflag == 1) {
		if (dflag == 1 || aflag == 1 || lflag == 1) {
			perror("Invalid use of '-c' flag");
			return -2;
		} else if (!globalArgs.Cursename || globalArgs.t_PID < 0) {
			perror("Missing argument (Curse name or PID)");
			return -3;
		} else {
			//curse smthing
		}
	}
	if (lflag == 1) {
		if (dflag == 1 || cflag == 1 || aflag == 1) {
			perror("Invalid use of '-l' flag");
			return -2;
		} else if (!globalArgs.Cursename || globalArgs.t_PID < 0) {
			perror("Missing argument (Curse name or PID)");
			return -3;
		} else {
			//lift a curse
		}
	}
	printf ("aflag = %d, dflag = %d, cflag = %d, lflag = %d\n", aflag, dflag, cflag, lflag);
	printf("Name = %s, PID = %d\n", globalArgs.Cursename, globalArgs.t_PID);

	for (i = optind; i < argc; i++)
		printf ("Non-option argument %s\n", argv[i]);

	//help();
	return 0;
}
