#include "print.h"

#include <stdlib.h>
#include <stdio.h>

#define USAGE "Usage: ddv [OPTION ...] FILE ..." \
"\nddv - DDS Viewer" \
"\nCompiled on "__DATE__", "__TIME__ \
"\n"
#define HELP "Options:" \
"\n        -h, -help . . . . . . . . . . . . .  Print this help." \
"\n        -v, -version  . . . . . . . . . . .  Print version information." \
"\n        -l, -look . . . . . . . . . . . . .  Show a preview window, letting one look at the passed DDS files" \
"\n        -c, -check  . . . . . . . . . . . .  Check the DDS file(s) and print some diagnostic information about them." \
"\n"
int /* Returns non-void so that 'return print_usage()' is valid */
print_usage(void)
{
	fprintf(stdout, USAGE"        -h, -help . . . . . . . . . . . . .  Print help.\n");
	exit(0);
	return 0;
}
int /* Returns non-void so that 'return print_help()' is valid */
print_help(void)
{
	fprintf(stdout, USAGE HELP);
	exit(0);
	return 0;
}
