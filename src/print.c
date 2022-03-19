#include "print.h"

#include <stdlib.h>
#include <stdio.h>

static const char *const USAGE = "Usage: ddv [OPTION ...] FILE ..."
"\nddv - DDS Viewer"
"\nCompiled on "__DATE__", "__TIME__
#if defined(DDV_DEBUG)
"\nDEBUG build"
#else
"\nRELEASE build"
#endif
;
static const char *const HELP = "Options:"
"\n        -h, -help . . . . . . . . . . . . .  Print this help."
"\n        -v, -version  . . . . . . . . . . .  Print version information."
"\n        -l, -look . . . . . . . . . . . . .  Show a preview window, letting one look at the passed DDS files"
"\n        -c, -check  . . . . . . . . . . . .  Check the DDS file(s) and print some diagnostic information about them."
;
int /* Returns non-void so that 'return print_usage()' is valid */
print_usage(void)
{
	fprintf(stdout, "%s\n%s\n", USAGE, "        -h, -help . . . . . . . . . . . . .  Print help.");
	exit(0);
	return 0;
}
int /* Returns non-void so that 'return print_help()' is valid */
print_help(void)
{
	fprintf(stdout, "%s\n%s\n", USAGE, HELP);
	exit(0);
	return 0;
}
