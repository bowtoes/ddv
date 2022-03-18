#ifndef state_h
#define state_h

#include <raylib.h>

#include <brrtools/brrstringr.h>
#include <brrtools/brrpath.h>

typedef enum operation_mode {
	operation_mode_look = 0,
	operation_mode_check,
	_operation_mode_count,
} operation_mode_t;

typedef enum background_type {
	background_type_black = 0,
	background_type_white,
	background_type_checker,
	_background_type_count,
} background_type_t;

typedef struct state {
	operation_mode_t mode;
	brrbl valid;
	brrbl adjacent_files;
	brrbl filter_on;

	brrpath_info_t *inputs;
	brrsz n_inputs;
	brrsz selected_input;

	Texture texture;
	background_type_t background;

	int monitor;
	int monitor_x;
	int monitor_y;

	int screen_x;
	int screen_y;

	int screen_width;
	int screen_height;

	float ofs_x;
	float ofs_y;

	float scale_x;
	float scale_y;

	float mouse_x;
	float mouse_y;

	float mod_x;
	float mod_y;

	int frame;
} state_t;

void
state_clear(state_t *const state);
int
state_init(state_t *const state, int argc, const char **const argv);

int
state_execute(state_t *const state);

int
state_update(state_t *const state);
int
state_draw(state_t *const state);

#endif /* state_h */
