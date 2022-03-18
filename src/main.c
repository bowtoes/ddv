#include <stdio.h>

#include <errno.h>
#include <string.h>

#include <brrtools/brrstringr.h>
#include <brrtools/brrlog.h>
#include <brrtools/brrpath.h>
#include <brrtools/brrheap.h>

#include "state.h"

#if 0
static int
i_filter_file(const brrpath_info_t *info)
{
	if (info->exists && info->type == brrpath_type_file)
		return 0;
	return 1;
}
int
main(int argc, char **argv)
{
	brrlog_init();

	for (int i = 1; i < argc; ++i) {
		const char *const arg = argv[i];
		const brrstringr_t a = brrstringr_cast(arg);
		brrpath_stat_result_t st = {};
		if (brrpath_stat(&st, &a)) {
			BRRLOG_ERR("Could not stat '%s': %s (%i)", arg, strerror(errno), errno);
			continue;
		} else if (!st.exists) {
			BRRLOG_WAR("Bad input: '%s' does not exist", arg);
			continue;
		}

		brrpath_walk_result_t walk = {};
		if (brrpath_walk(&walk, &a, (brrpath_walk_options_t){
			.max_depth = 2,
			.min_depth = 0,
			.filter = i_filter_file,
		})) {
			BRRLOG_ERR("Could not walk '%s': %s (%i)", arg, strerror(errno), errno);
			continue;
		}
		for (brrsz i = 0; i < walk.n_results; ++i) {
			BRRLOG_NOR("RES '%s'", walk.results[i].full_path.cstr);
		}

		brrpath_walk_result_free(&walk);
	}

	brrlog_deinit();
}

#else
int
main(int argc, char **argv)
{
	brrlog_init();
	SetTraceLogLevel(LOG_ERROR); // Just in case I misuse raylib and it complains

	state_t state = {};

	if (state_init(&state, argc - 1, (const char **)argv + 1)) {
		return 1;
	}
	BRRLOG_DEB("MODE %s", state.mode == operation_mode_check?"check":"look");
	for (brrsz i = 0; i < state.n_inputs; ++i) {
		BRRLOG_NOR("INPUT %3zu '%s'", i, state.inputs[i].full_path.cstr);
	}
	if (state.selected_input < state.n_inputs)
		BRRLOG_DEB("SELECTED %3zu '%s'", state.selected_input, state.inputs[state.selected_input].full_path.cstr);

	int e = state_execute(&state);
	state_clear(&state);

	brrlog_deinit();
	return e;
}
#endif
