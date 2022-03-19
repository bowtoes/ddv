#include "state.h"

#include <errno.h>
#include <math.h>
#include <stdlib.h>
#include <string.h>

#include <raylib.h>
#include <raymath.h>
#include <rlgl.h>

#include <brrtools/brrlog.h>
#include <brrtools/brrheap.h>
#include <brrtools/brrstringr.h>
#include <brrtools/brrpath.h>
#include <brrtools/brrnum.h>

#include "dds.h"
#include "print.h"

typedef enum i_supported_imgs {
	i_support_dds = 0,
	i_support_astc,
	i_support_bmp,
	i_support_gif,
	i_support_hdr,
	i_support_jpg,
	i_support_ktx,
	i_support_pkm,
	i_support_png,
	i_support_psd,
	i_support_pvr,
	i_support_tga,
	_i_support_count
} i_supported_imgs_t;
static const brrstringr_t i_img_extensions[_i_support_count] = {
	brrstringr_literal("dds"),
	brrstringr_literal("astc"),
	brrstringr_literal("bmp"),
	brrstringr_literal("gif"),
	brrstringr_literal("hdr"),
	brrstringr_literal("jpg"),
	brrstringr_literal("ktx"),
	brrstringr_literal("pkm"),
	brrstringr_literal("png"),
	brrstringr_literal("psd"),
	brrstringr_literal("pvr"),
	brrstringr_literal("tga"),
};

static Texture i_bg_checker = {};
static const Image i_img_checker = {
	.width = 16, .height = 16, .mipmaps = 1,
	.format = RL_PIXELFORMAT_UNCOMPRESSED_GRAYSCALE,
	.data = (char[16*16]){
		0x99, 0x99, 0x99, 0x99, 0x99, 0x99, 0x99, 0x99, 0x66, 0x66, 0x66, 0x66, 0x66, 0x66, 0x66, 0x66,
		0x99, 0x99, 0x99, 0x99, 0x99, 0x99, 0x99, 0x99, 0x66, 0x66, 0x66, 0x66, 0x66, 0x66, 0x66, 0x66,
		0x99, 0x99, 0x99, 0x99, 0x99, 0x99, 0x99, 0x99, 0x66, 0x66, 0x66, 0x66, 0x66, 0x66, 0x66, 0x66,
		0x99, 0x99, 0x99, 0x99, 0x99, 0x99, 0x99, 0x99, 0x66, 0x66, 0x66, 0x66, 0x66, 0x66, 0x66, 0x66,
		0x99, 0x99, 0x99, 0x99, 0x99, 0x99, 0x99, 0x99, 0x66, 0x66, 0x66, 0x66, 0x66, 0x66, 0x66, 0x66,
		0x99, 0x99, 0x99, 0x99, 0x99, 0x99, 0x99, 0x99, 0x66, 0x66, 0x66, 0x66, 0x66, 0x66, 0x66, 0x66,
		0x99, 0x99, 0x99, 0x99, 0x99, 0x99, 0x99, 0x99, 0x66, 0x66, 0x66, 0x66, 0x66, 0x66, 0x66, 0x66,
		0x99, 0x99, 0x99, 0x99, 0x99, 0x99, 0x99, 0x99, 0x66, 0x66, 0x66, 0x66, 0x66, 0x66, 0x66, 0x66,
		0x66, 0x66, 0x66, 0x66, 0x66, 0x66, 0x66, 0x66, 0x99, 0x99, 0x99, 0x99, 0x99, 0x99, 0x99, 0x99,
		0x66, 0x66, 0x66, 0x66, 0x66, 0x66, 0x66, 0x66, 0x99, 0x99, 0x99, 0x99, 0x99, 0x99, 0x99, 0x99,
		0x66, 0x66, 0x66, 0x66, 0x66, 0x66, 0x66, 0x66, 0x99, 0x99, 0x99, 0x99, 0x99, 0x99, 0x99, 0x99,
		0x66, 0x66, 0x66, 0x66, 0x66, 0x66, 0x66, 0x66, 0x99, 0x99, 0x99, 0x99, 0x99, 0x99, 0x99, 0x99,
		0x66, 0x66, 0x66, 0x66, 0x66, 0x66, 0x66, 0x66, 0x99, 0x99, 0x99, 0x99, 0x99, 0x99, 0x99, 0x99,
		0x66, 0x66, 0x66, 0x66, 0x66, 0x66, 0x66, 0x66, 0x99, 0x99, 0x99, 0x99, 0x99, 0x99, 0x99, 0x99,
		0x66, 0x66, 0x66, 0x66, 0x66, 0x66, 0x66, 0x66, 0x99, 0x99, 0x99, 0x99, 0x99, 0x99, 0x99, 0x99,
		0x66, 0x66, 0x66, 0x66, 0x66, 0x66, 0x66, 0x66, 0x99, 0x99, 0x99, 0x99, 0x99, 0x99, 0x99, 0x99,
	},
};
static int
i_load_textures(void)
{
	if (IsWindowReady()) {
		i_bg_checker = LoadTextureFromImage(i_img_checker);
	}
	return 0;
}
static void
i_unload_textures(void)
{
	if (IsWindowReady()) {
		if (i_bg_checker.id != 0)
			UnloadTexture(i_bg_checker);
		memset(&i_bg_checker, 0, sizeof(i_bg_checker));
	}
}

void
state_clear(state_t *const state)
{
	if (!state)
		return;

	if (state->inputs)
		brrheap_clear((void**)&state->inputs, &state->n_inputs, sizeof(*state->inputs), (void(*)(void*))brrstringr_free);
	if (state->texture.id)
		UnloadTexture(state->texture);
	memset(state, 0, sizeof(*state));
}

static const state_t *s_current_state = NULL;
static int
i_filter_file(const brrpath_info_t *info)
{
	if (!info->exists || info->type != brrpath_type_file)
		return 1;
	int match = 0;
	for (int i = 0; i < _i_support_count; ++i) {
		if (info->components.extension.cstr && 0 == brrstringr_compare(&info->components.extension, &i_img_extensions[i], 0)) {
			match = 1;
		}
	}
	if (!match)
		return 1;
	for (brrsz i = 0; i < s_current_state->n_inputs; ++i) {
		if (0 == brrstringr_compare(&s_current_state->inputs[i].full_path, &info->full_path, BRRPATH_CASE_SENSITIVE) ||
			(0 == brrstringr_compare(&s_current_state->inputs[i].components.directory, &info->components.directory, BRRPATH_CASE_SENSITIVE) &&
			 0 == brrstringr_compare(&s_current_state->inputs[i].components.base_name, &info->components.base_name, BRRPATH_CASE_SENSITIVE) &&
			 0 == brrstringr_compare(&s_current_state->inputs[i].components.extension, &info->components.extension, BRRPATH_CASE_SENSITIVE))) {
			return 1;
		}
	}
	return 0;
}
static int
i_sort_brrstringr(const void *const a, const void *const b)
{
	const brrstringr_t *const A = (brrstringr_t*)a;
	const brrstringr_t *const B = (brrstringr_t*)b;
	return brrstringr_compare(A, B, BRRPATH_CASE_SENSITIVE);
}
static int
i_walk_input(state_t *const state, const char *arg)
{
	brrstringr_t s = brrstringr_cast(arg);
	brrpath_walk_result_t walk = {0};

	if (brrpath_walk(&walk, &s, (brrpath_walk_options_t){
		.max_depth = 1,
		.min_depth = 0,
		.filter = i_filter_file,
	})) {
		BRRLOG_ERR("Could not walk '%s': %s (%i)", arg, strerror(errno), errno);
		return 1;
	}
	if (brrheap_join((void**)&state->inputs, &state->n_inputs, sizeof(*state->inputs), walk.results, walk.n_results)) {
		BRRLOG_ERR("Failed to join walk results of '%s': %s (%i)", arg, strerror(errno), errno);
		brrpath_walk_result_free(&walk);
		return 1;
	}
	return 0;
}
static int
i_init_walk_dirs(state_t *const state, const char **const inputs, brrsz n_inputs)
{
	if (!n_inputs)
		return 0;

	for (brrsz i = 0; i < n_inputs; ++i) {
		if (i_walk_input(state, inputs[i])) {
			return 1;
		}
	}

	return 0;
}
static int
i_init_simple(state_t *const state, const char **const inputs, brrsz n_inputs)
{
	if (!n_inputs)
		return 0;

	for (brrsz i = 0; i < n_inputs; ++i) {
		const char *arg = inputs[i];
		const brrstringr_t s = brrstringr_cast(arg);

		brrpath_info_t I = {};
		if (brrpath_info_get(&I, &s)) {
			BRRLOG_ERR("Could not get path information for '%s': %s (%i)", arg, strerror(errno), errno);
			return 1;
		} else if (i_filter_file(&I)) {
			if (!I.exists)
				BRRLOG_WAR("Bad input: '%s' does not exist", arg);
			else if (I.type != brrpath_type_file)
				BRRLOG_WAR("Bad input: '%s' is not a file", arg);
			else
				BRRLOG_WAR("Bad input: '%s' (sorry I can't say more)", arg);
			brrpath_info_free(&I);
			continue;
		}

		if (brrheap_append((void**)&state->inputs, &state->n_inputs, sizeof(*state->inputs), &I)) {
			BRRLOG_ERR("Failed to append input filepath to internal buffer '%s': %s (%i)", arg, strerror(errno), errno);
			brrpath_info_free(&I);
			return 1;
		}
	}

	return 0;
}
static int
i_state_parse_arg(state_t *const state, const char *const arg)
{
	if (arg[0] == 0) { /* Argument is of 0 length, very bad! */
		return 1;
	}
#define IF_CHECK_ARG(_cse_, ...) if (brrstringr_cstr_compare(arg, _cse_, __VA_ARGS__, NULL))
#define CHECK_RUN_ARG(_cse_, _run_, ...) IF_CHECK_ARG((_cse_), __VA_ARGS__) { _run_; }
#define CHECK_SET_ARG(_cse_, _var_, _val_, ...) IF_CHECK_ARG((_cse_), __VA_ARGS__) { (_var_) = (_val_); return 1; }
#define CHECK_TOGGLE_ARG(_cse_, _var_, ...) CHECK_SET_ARG(_cse_, _var_, !(_var_), __VA_ARGS__)
	else CHECK_RUN_ARG(1, return print_usage(), "-v", "-version")
	else CHECK_RUN_ARG(1, return print_help(), "-h", "-help")

	else CHECK_SET_ARG(1, state->mode, operation_mode_look, "-l", "-look")
	else CHECK_SET_ARG(1, state->mode, operation_mode_check, "-c", "-check")
	else CHECK_TOGGLE_ARG(1, state->adjacent_files, "-a", "-adjacent")
#undef CHECK_TOGGLE_ARG
#undef CHECK_SET_ARG
#undef CHECK_RUN_ARG
#undef IF_CHECK_ARG
	return 0;
}
static int
i_init_window(state_t *const state)
{
	/* Have to initialize the window yada */
	InitWindow(256, 256, state->inputs[state->selected_input].components.base_name.cstr);
	if (!IsWindowReady())
		return 1;
	SetWindowState(FLAG_WINDOW_RESIZABLE);
	if (i_load_textures()) {
		BRRLOG_ERR("Could not initialize background textures", strerror(errno), errno);
		CloseWindow();
		return 1;
	}
	SetTargetFPS(60); // this is probably unnecessary
	SetExitKey(KEY_Q);

	state->background = background_type_checker;
	state->scale_x = state->scale_y = 1;
	state->ofs_x = state->ofs_y = 0;
	state->filter_on = 1;

	state->monitor = GetCurrentMonitor();
	state->monitor_x = GetMonitorWidth(state->monitor);
	state->monitor_y = GetMonitorHeight(state->monitor);

	return 0;
}
int
state_init(state_t *const state, int argc, const char **const argv)
{
	if (!state)
		return 0;

	state_t s = {};
	s.mode = operation_mode_check;
	//s.adjacent_files = 1;

	/* Grab arguments that aren't flags */
	const char **unhandled = NULL;
	brrsz n_unhandled = 0;
	for (int i = 0; i < argc; ++i) {
		const char *arg = argv[i];
		if (i_state_parse_arg(&s, arg)) {
			/* Argument parsed, continue */
			continue;
		} else {
			/* Unknown argument, has to be a file */
			if (brrheap_append((void **)&unhandled, &n_unhandled, sizeof(*unhandled), &arg)) {
				BRRLOG_ERR("Failed to add '%s' to internal list: %s (%i)", arg, strerror(errno), errno);
				brrheap_clear((void **)&unhandled, &n_unhandled, sizeof(*unhandled), NULL);
				return 1;
			}
		}
	}

	/* Query & filter the given files */
	s_current_state = &s;
	if (!s.adjacent_files) {
		/* No need to query siblings */
		if (i_init_simple(&s, unhandled, n_unhandled)) {
			state_clear(&s);
			brrheap_clear((void **)&unhandled, &n_unhandled, sizeof(*unhandled), NULL);
			return 1;
		}
	} else {
		if (i_init_walk_dirs(&s, unhandled, n_unhandled)) {
			state_clear(&s);
			brrheap_clear((void **)&unhandled, &n_unhandled, sizeof(*unhandled), NULL);
			return 1;
		}
	}
	s_current_state = NULL;

	qsort(s.inputs, s.n_inputs, sizeof(*s.inputs), i_sort_brrstringr);

	/* Select the first given file for looking, if it matches */
	if (s.mode == operation_mode_look && n_unhandled > 0) {
		brrstringr_t S = brrstringr_cast(unhandled[0]);
		brrpath_info_t I = {};
		if (!brrpath_info_get(&I, &S)) {
			for (brrsz i = 0; i < s.n_inputs; ++i) {
				if (s.inputs[i].type == I.type &&
					(0 == brrstringr_compare(&s.inputs[i].full_path, &I.full_path, BRRPATH_CASE_SENSITIVE) ||
					 (0 == brrstringr_compare(&s.inputs[i].components.directory, &I.components.directory, BRRPATH_CASE_SENSITIVE) &&
					  0 == brrstringr_compare(&s.inputs[i].components.base_name, &I.components.base_name, BRRPATH_CASE_SENSITIVE) &&
					  0 == brrstringr_compare(&s.inputs[i].components.extension, &I.components.extension, BRRPATH_CASE_SENSITIVE)
				))) {
					s.selected_input = i;
					break;
				}
			}
			brrpath_info_free(&I);
		}
	}
	brrheap_clear((void **)&unhandled, &n_unhandled, sizeof(*unhandled), NULL);

	if (s.mode == operation_mode_look) {
		s.mod_x = s.mod_y = 0.1;
	}
	s.valid = 1;
	state_clear(state);
	*state = s;
	return 0;
}

typedef struct i_texidx {
	brrbl reset_offset;
	brrbl reset_scale;
	brrbl reset_window_size;
	brrbl reset_window_pos;
} i_texidx_t;
static const i_texidx_t no_reset = {
	.reset_window_pos = 0,
	.reset_window_size = 0,
	.reset_offset = 0,
	.reset_scale = 0,
};
static const i_texidx_t light_reset = {
	.reset_window_pos = 0,
	.reset_window_size = 0,
	.reset_offset = 0,
	.reset_scale = 0,
};
static const i_texidx_t full_reset = {
	.reset_window_pos = 1,
	.reset_window_size = 1,
	.reset_offset = 1,
	.reset_scale = 1,
};
static int
i_select_texture_index(state_t *const state, int offset, i_texidx_t options)
{
	brrsz next = brrnum_wrap(state->selected_input + offset, state->n_inputs, 0);
	brrpath_info_t P = state->inputs[next];
	Image I = {};
	if (P.components.extension.cstr && 0 == brrstringr_compare(&P.components.extension, &i_img_extensions[i_support_dds], 0)) {
		if (dds_load_to_image(&I, &P.full_path)) {
			BRRLOG_ERR("Failed to load DDS image '%s': %s (%i)", P.full_path.cstr, strerror(errno), errno);
			return 1;
		}
	} else {
		I = LoadImage(P.full_path.cstr);
	}

	if (!I.data) {
		BRRLOG_ERR("Failed to load image '%s': %s (%i)", P.full_path.cstr, strerror(errno), errno);
		return 1;
	}
	Texture t = LoadTextureFromImage(I);
	if (!t.id) {
		BRRLOG_ERR("Failed to load texture from image '%s': %s (%i)", P.full_path.cstr, strerror(errno), errno);
		UnloadImage(I);
		return 1;
	}
	UnloadImage(I);

	if (state->texture.id)
		UnloadTexture(state->texture);
	state->texture = t;

	if (state->filter_on)
		SetTextureFilter(state->texture, TEXTURE_FILTER_TRILINEAR);
	else
		SetTextureFilter(state->texture, TEXTURE_FILTER_POINT);

	if (options.reset_offset) {
		state->ofs_x = state->ofs_y = 0;
	}
	if (options.reset_scale) {
		state->scale_x = state->scale_y = 1;
	}
	/* I hate vector math */
	int tx = state->texture.width * state->scale_x;
	int ty = state->texture.height * state->scale_y;
	int tex_increase_x = tx > state->screen_width;
	int tex_increase_y = ty > state->screen_height;
	int need_resize = next != state->selected_input && (tex_increase_x || tex_increase_y);
	if (options.reset_window_size || need_resize) {
		if (tex_increase_x || options.reset_window_size)
			state->screen_width = fminf(tx, state->monitor_x);
		if (tex_increase_y || options.reset_window_size)
			state->screen_height = fminf(ty, state->monitor_y);
		SetWindowSize(state->screen_width, state->screen_height);
	}
	if (options.reset_window_pos) {
		int x = .5 * (state->monitor_x - state->screen_width);
		int y = .5 * (state->monitor_y - state->screen_height);
		SetWindowPosition(x, y);
	}
	if (options.reset_offset || need_resize) {
		state->ofs_x = state->ofs_y = 0;
	}

	float S = 100 * fmaxf(state->scale_x, state->scale_y);
	const char *newTitle = NULL;
	if (S > 1) {
		newTitle = TextFormat("%i%% %i/%i %ix%i : %s", (int)S, next + 1, state->n_inputs, t.width, t.height, P.full_path.cstr);
	} else {
		newTitle = TextFormat("%f%% %i/%i %ix%i : %s", (int)S, next + 1, state->n_inputs, t.width, t.height, P.full_path.cstr);
	}
	SetWindowTitle(newTitle);

	state->selected_input = next;
	BRRLOG_NOR("Image of %ix%i", state->texture.width, state->texture.height);

	return 0;
}
static int
i_state_update(state_t *const state)
{
	state_t s = *state;

	/* Preupdate */
	s.screen_width = GetScreenWidth();
	s.screen_height = GetScreenHeight();
	{
		Vector2 a = GetWindowPosition();
		s.screen_x = (int)a.x; s.screen_y = (int)a.y;
		Vector2 v = GetMousePosition();
		s.mouse_x = v.x; s.mouse_y = v.y;
	}

	typedef enum mod {
		mod_none = 0,
		mod_shift = 1,
		mod_ctrl = 2,
		mod_alt = 4,
	} mod_t;
	int key = 0;
	mod_t mod = mod_none;
	while (true) {
		int i = GetKeyPressed();
		if (!i)
			break;
		key = i;
	}
	if (IsKeyDown(KEY_LEFT_SHIFT) || IsKeyDown(KEY_RIGHT_SHIFT))
		mod |= mod_shift;
	if (IsKeyDown(KEY_LEFT_CONTROL) || IsKeyDown(KEY_RIGHT_CONTROL))
		mod |= mod_ctrl;
	if (IsKeyDown(KEY_LEFT_ALT) || IsKeyDown(KEY_RIGHT_ALT))
		mod |= mod_alt;

	int mouse_pressed = -1;
	int mouse_down = -1;
	if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT))
		mouse_pressed = MOUSE_BUTTON_LEFT;
	else if (IsMouseButtonPressed(MOUSE_BUTTON_RIGHT))
		mouse_pressed = MOUSE_BUTTON_RIGHT;
	else if (IsMouseButtonPressed(MOUSE_BUTTON_MIDDLE))
		mouse_pressed = MOUSE_BUTTON_MIDDLE;
	if (IsMouseButtonDown(MOUSE_BUTTON_LEFT))
		mouse_down = MOUSE_BUTTON_LEFT;
	else if (IsMouseButtonDown(MOUSE_BUTTON_RIGHT))
		mouse_down = MOUSE_BUTTON_RIGHT;
	else if (IsMouseButtonDown(MOUSE_BUTTON_MIDDLE))
		mouse_down = MOUSE_BUTTON_MIDDLE;

	float scroll = GetMouseWheelMove();

	/* Update */
	if (mouse_down == MOUSE_BUTTON_LEFT) {
		Vector2 o = GetMouseDelta();
		s.ofs_x += o.x;
		s.ofs_y += o.y;
	} else if (mouse_pressed == MOUSE_BUTTON_RIGHT) {
		i_select_texture_index(&s, 1, no_reset);
	}

	if (!key && scroll) {
		/* please don't ask me how this math works */
		float mx = 1. + s.mod_x * scroll;
		s.scale_x *= mx;
		float rx = s.mouse_x - mx * (s.mouse_x - s.ofs_x);
		s.ofs_x = rx;

		float my = 1. + s.mod_y * scroll;
		s.scale_y *= my;
		float ry = s.mouse_y - my * (s.mouse_y - s.ofs_y);
		s.ofs_y = ry;

	} else if (key == KEY_T) {
		s.background = (s.background + 1) % _background_type_count;

	} else if (key == KEY_SPACE) {
		i_select_texture_index(&s, 0, full_reset);
	} else if (key == KEY_F) {
		s.filter_on = !s.filter_on;
		i_select_texture_index(&s, 0, no_reset);

	} else if (key == KEY_N || key == KEY_RIGHT) {
		i_select_texture_index(&s, mod!=mod_shift?1:-1, light_reset);
	} else if (key == KEY_P || key == KEY_LEFT) {
		i_select_texture_index(&s, mod!=mod_shift?-1:1, light_reset);
	} else if (key == KEY_PAGE_UP) {
		i_select_texture_index(&s, -5, light_reset);
	} else if (key == KEY_PAGE_DOWN) {
		i_select_texture_index(&s, 5, light_reset);
	} else if (key == KEY_HOME) {
		i_select_texture_index(&s, -s.selected_input, light_reset);
	} else if (key == KEY_END) {
		i_select_texture_index(&s, s.n_inputs - s.selected_input - 1, light_reset);
	}

	/* Postupdate */
	s.scale_x = Clamp(s.scale_x, 0.0001, 1000);
	s.scale_y = Clamp(s.scale_y, 0.0001, 1000);
	s.ofs_x = Clamp(s.ofs_x, -s.texture.width * s.scale_x, s.screen_width);
	s.ofs_y = Clamp(s.ofs_y, -s.texture.height * s.scale_y, s.screen_height);
	s.frame++;

	*state = s;

	return 0;
}
static int
i_state_draw(state_t *const state)
{
	const state_t s = *state;
	if (!s.valid)
		return 0;

	BeginDrawing();
	if (s.background == background_type_white) {
		ClearBackground(WHITE);
	} else {
		ClearBackground(BLACK);
		if (s.background == background_type_checker) {
			Rectangle bgs = {0, 0, i_bg_checker.width, i_bg_checker.height};
			Rectangle bgd = {0, 0, s.screen_width, s.screen_height};
			DrawTextureTiled(i_bg_checker, bgs, bgd, (Vector2){0}, 0., 1., (Color){255, 255, 255, 255});
		}
	}

	Rectangle ts = {0, 0, s.texture.width, s.texture.height};
	Rectangle td = {s.ofs_x, s.ofs_y, s.texture.width * s.scale_x, s.texture.height * s.scale_y};
	DrawTexturePro(s.texture, ts, td, (Vector2){0}, 0, (Color){255, 255, 255, 255});

	EndDrawing();

	return 0;
}

static int
i_state_check(state_t *const state)
{


	return 0;
}

int
state_execute(state_t *const state)
{
	if (!state || !state->valid)
		return 1;
	if (!state->n_inputs) {
		BRRLOG_NOR("No inputs given, nothing to do");
		return 0;
	}

	if (state->mode == operation_mode_check) {
		return i_state_check(state);
	} else {
		if (i_init_window(state)) {
			BRRLOG_ERR("Could not initialize graphics context: %s (%i)", strerror(errno), errno);
			state_clear(state);
			return 1;
		}
		if (i_select_texture_index(state, 0, full_reset))
			return 1;

		while (state->valid && !WindowShouldClose()) {
			i_state_update(state);
			i_state_draw(state);
		}

		return 0;
	}
}
