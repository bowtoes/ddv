#include <errno.h>
#include <stdio.h>
#include <string.h>

#include <brrtools/brrheap.h>
#include <brrtools/brrlog.h>
#include <brrtools/brrpath.h>
#include <brrtools/brrstringr.h>

#include "state.h"

int
main(int argc, char **argv)
{
	brrlog_init();
#if defined(NDEBUG) || !defined(DDV_DEBUG)
	gbrrlogctl.debug_enabled = 0;
	SetTraceLogLevel(LOG_ERROR); // Just in case I misuse raylib and it complains
#elif defined(DDV_DEBUG)
	SetTraceLogLevel(LOG_INFO);
#endif

	state_t state = {0};

	if (state_init(&state, argc - 1, (const char **)argv + 1)) {
		return 1;
	}
	BRRLOG_DEB("MODE %s", state.mode == operation_mode_check?"check":"look");
	for (brrsz i = 0; i < state.n_inputs; ++i) {
		BRRLOG_DEB("INPUT %3zu '%s'", i, state.inputs[i].full_path.cstr);
	}
	if (state.selected_input < state.n_inputs)
		BRRLOG_DEB("SELECTED %3zu '%s'", state.selected_input, state.inputs[state.selected_input].full_path.cstr);

	int e = state_execute(&state);
	state_clear(&state);

	brrlog_deinit();
	return e;
}
