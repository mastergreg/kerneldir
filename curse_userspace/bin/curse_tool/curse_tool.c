#include <curse/curse.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

int help(void) {
    printf(
       "Usage: curse <global action>\n"
       "Usage: curse <cursename> <action> [<option>]\n"
       "\n"
       " Global Actions                   Description\n"
       "----------------        ---------------------\n"
       "     help               show this help\n"
       "     list               list curses\n"
       "\n"
       " Curse Actions                    Description\n"
       "----------------        ---------------------\n"
       "       ?                show curse global status (enabled/disabled)\n"
       "       +                enable curse <cursename>\n"
       "       -                disable curse <cursename>\n"
       "\n"
       "     <pid>+             curse <pid> with <cursename>\n"
       "     <pid>-             lift curse <cursename> from pid\n"
       "     <pid>?             show <cursename> status for pid\n"
       "\n"
       "   Examples                        Description\n"
       "----------------        ---------------------\n"
       "curse list              show a list of available curses\n"
       "curse nocache ?         show if curse 'nocache' is enabled \n"
       "curse nocache +         enable curse 'nocache' \n"
       "curse nocache 7423?     show if process 7423 is cursed with 'nocache' \n"
       "curse nocache 7423+     curse process 7423 with 'nocache' \n"
       "\n"
    );
    exit(-1);
    return -1;
}

/* ? */

int main(int argc, char **argv) {
    long r;

    /* ? */
    return help();

}
