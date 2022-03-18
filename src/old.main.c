#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <raylib.h>
#include <raymath.h>
#include <rlgl.h>
#include <brrtools/brrlog.h>

#define QUICK_ZERO(_v_) memset(&(_v_), 0, sizeof(_v_))
#define V2ZERO ((Vector2){})
#define V2ONE ((Vector2){1.,1.})

typedef struct {
	int nfiles;
	char **files;
	int selectedFile;
} FileList;
void
clearFileList(FileList *const files)
{
	if (files) {
		if (files->files) {
			for (int i = 0; i < files->nfiles; ++i)
				free(files->files[i]);
			free(files->files);
		}
		QUICK_ZERO(*files);
	}
}
int
selectFileList(FileList *const files, int argc, const char **const argv)
{
	if (!files) {
		printf("NULL 'files' argument in '%s'\n", __func__);
		return 1;
	}
	FileList o = {};
	if (argc <= 0) {
		QUICK_ZERO(*files);
		return 0;
	}
	if (!(o.files = malloc(sizeof(*o.files)*(argc)))) {
		printf("Could not allocate space for filename lists: %s (%i)\n", strerror(errno), errno);
		return 1;
	}

	for (int i = 0; i < argc; ++i) {
		const char *c = argv[i];
		int issame = 0;
		for (int j = 0; j < o.nfiles; ++j) {
			if (0 == strcmp(c, o.files[j])) {
				issame = 1;
				break;
			}
		}
		if (issame)
			continue;
		int a = FileExists(c), b = DirectoryExists(c);
		if (a && !b) {
			static const char *imgExtensions[] = {
				".astc",
				".bmp",
				".dds",
				".gif",
				".hdr",
				".jpg",
				".ktx",
				".pkm",
				".png",
				".psd",
				".pvr",
				".tga",
			};
			int e = 0;
			for (; e < (sizeof(imgExtensions)/sizeof(imgExtensions[0])); ++e) {
				if (IsFileExtension(c, imgExtensions[e]))
					break;
			}
			if (e == sizeof(imgExtensions) / sizeof(imgExtensions[0]))
				continue;

			int l = strlen(c);
			char *n = malloc(l + 1);
			if (!n) {
				printf("Could not allocate space for filename '%s': %s (%i)\n", c, strerror(errno), errno);
				clearFileList(&o);
				return 1;
			}
			memcpy(n, c, l);
			n[l] = 0;
			o.files[o.nfiles++] = n;
		}
	}
	if (o.nfiles) {
		char **i = realloc(o.files, sizeof(*o.files)*(o.nfiles));
		if (!i) {
			printf("Failed to resize filename list: %s (%i)\n", strerror(errno), errno);
			clearFileList(&o);
			return 1;
		}
		o.files = i;
	}
	*files = o;
	return 0;
}

typedef struct ProgramState {
	int isInitialized;
	int frame;
	Texture bgs[3];
	int bg;

	FileList files;
	Texture texture;
	int filter;

	Vector2 offset;
	Vector2 scale;
} ProgramState;
void
clearState(ProgramState *const state)
{
	if (state) {
		UnloadTexture(state->bgs[0]);
		UnloadTexture(state->bgs[1]);
		UnloadTexture(state->bgs[2]);

		UnloadTexture(state->texture);
		clearFileList(&state->files);
		QUICK_ZERO(*state);

		if (IsWindowReady())
			CloseWindow();
	}
}
int wrap(signed number, unsigned wrap, int offset)
{
	if (!wrap)
		return 0;
	else if (number >= 0)
		return (signed)((unsigned)number % wrap);
	else
		return (signed)(wrap - 1 - ((unsigned)(-(number + 1)) % wrap)) + offset;
}
const char *
getNewWindowTitle(const ProgramState *const state)
{
	if (!state)
		return NULL;
	const ProgramState s = *state;
	const Texture t = s.texture;
	float S = 100 * fmaxf(s.scale.x, s.scale.y);
	if (S > 1) {
		return TextFormat("%i%% %i/%i %ix%i : %s", (int)S, s.files.selectedFile + 1, s.files.nfiles, t.width, t.height, s.files.files[s.files.selectedFile]);
	} else {
		return TextFormat("%f%% %i/%i %ix%i : %s", S, s.files.selectedFile + 1, s.files.nfiles, t.width, t.height, s.files.files[s.files.selectedFile]);
	}
}
int
stateSelectTexture(ProgramState *const state, int next, int reset_offset, int reset_scale, int reset_window_pos, int reset_window_size)
{
	if (!state) {
		printf("NULL 'state' argument in %s\n", __func__);
		return 1;
	}
	ProgramState s = *state;
	int new = wrap(s.files.selectedFile + next, s.files.nfiles, 0);
	UnloadTexture(s.texture);
	Image I = LoadImage(s.files.files[new]);
	I.mipmaps = 1;
	if (I.format == PIXELFORMAT_UNCOMPRESSED_R8G8B8 && IsFileExtension(s.files.files[new], ".dds")) {
		// Gotta swap RED and BLUE channels on uncompressed, 24-bit RGB DDS files specifically (for some reason)
		char *id = I.data;
		for (int i = 0; i < I.width * I.height * 3; i += 3) {
			char b = id[i];
			id[i] = id[i+2];
			id[i+2]=b;
		}
	}
	s.texture = LoadTextureFromImage(I);
	UnloadImage(I);
	SetTextureFilter(s.texture, s.filter);

	int c = GetCurrentMonitor();
	Vector2 m = {GetMonitorWidth(c), GetMonitorHeight(c)};
	Vector2 S = {GetScreenWidth(), GetScreenHeight()};
	Vector2 t = {s.texture.width, s.texture.height};
	Vector2 T = {(int)(t.x * s.scale.x), (int)(t.y * s.scale.y)};
	Vector2 M = {fminf(T.x, m.x), fminf(T.y, m.y)};
	if (reset_scale)
		s.scale = V2ONE;
	int shouldResetSize = reset_window_size || T.x > S.x || T.y > S.y;
	if (shouldResetSize) {
		SetWindowSize(M.x, M.y);
		S = (Vector2){GetScreenWidth(), GetScreenHeight()};
		s.offset = Vector2Zero();
	}
	if (reset_window_pos /* || shouldResetSize */) {
		Vector2 x = Vector2Scale(Vector2Subtract(m, M), .5);
		SetWindowPosition((int)x.x, (int)x.y);
	}
	if (reset_offset || shouldResetSize) {
		s.offset = Vector2Zero();
	} else /* Center image */ {
//		s.offset = Vector2Scale(Vector2Subtract(S, T), .5);
	}

	s.files.selectedFile = new;
	SetWindowTitle(getNewWindowTitle(&s));

	printf("Image of %fx%f\n", t.x, t.y);

	*state = s;

	return 0;
}
int sortcompare(void *a, void *b)
{
	return strcmp(*(char**)a, *(char**)b);
}
int
initState(ProgramState *const state, int argc, const char **argv)
{
	#include "colors.c"
	if (!state) {
		printf("NULL 'state' argument in %s\n", __func__);
		return 1;
	}
	int nfiles = argc;
	const char **dirfiles = argv;
	const char *firstFile = NULL;
	if (argc > 0) {
		// TODO: Proper walking of present directory to find other fiels
		firstFile = argv[0];
		const char *k = GetDirectoryPath(firstFile);
		if (!ChangeDirectory(k)) {
			printf("Could not change directory to %s\n", k);
			return 1;
		}
		dirfiles = (const char **)GetDirectoryFiles(k, &nfiles);
	}
	qsort(dirfiles, nfiles, sizeof(*dirfiles), sortcompare);

	if (selectFileList(&state->files, nfiles, dirfiles)) {
		BRRLOG_ERR("Could not get list of input files");
		return 1;
	}
	ClearDirectoryFiles();
	if (state->files.nfiles == 0) {
		BRRLOG_NOR("ddv v0.0.0, compiled on "__DATE__" "__TIME__);
		return 1;
	}

	InitWindow(256, 256, "HELP ME");
	if (!IsWindowReady()) {
		BRRLOG_ERR("Could not initialize window");
		clearState(state);
		return 1;
	}
	SetWindowState(FLAG_WINDOW_RESIZABLE);
	SetTargetFPS(60);
	SetExitKey(KEY_Q);
	state->bgs[0] = LoadTextureFromImage(img_checker);
	state->bgs[1] = LoadTextureFromImage(img_black);
	state->bgs[2] = LoadTextureFromImage(img_white);

	state->scale = V2ONE;
	if (firstFile) {
		firstFile = GetFileName(firstFile);
	}
	int selectedFile = 0;
	for (; selectedFile < state->files.nfiles; ++selectedFile) {
		const char *k = state->files.files[selectedFile];
		if (0 == strcmp(firstFile, state->files.files[selectedFile]))
			break;
	}
	if (selectedFile == state->files.nfiles)
		selectedFile = 0;
	state->filter = RL_TEXTURE_FILTER_TRILINEAR;
	stateSelectTexture(state, selectedFile, 1, 1, 1, 1);
	state->bg = 0;

	state->isInitialized = 1;
	return 0;
}
int
updateState(ProgramState *const state)
{
	if (!state || !state->isInitialized)
		return 1;

	ProgramState s = *state;
	Texture t = s.texture;
	Vector2 T = {t.width, t.height};
	Vector2 S = {GetScreenWidth(), GetScreenHeight()};

	if (IsMouseButtonDown(MOUSE_BUTTON_LEFT)) {
		Vector2 d = GetMouseDelta();
		s.offset = Vector2Add(s.offset, d);
		float xm = -s.scale.x * T.x;
		float ym = -s.scale.y * T.y;
		float xM = S.x;
		float yM = S.y;
		s.offset.x = Clamp(s.offset.x, xm, xM);
		s.offset.y = Clamp(s.offset.y, ym, yM);
	} else if (IsMouseButtonPressed(MOUSE_BUTTON_RIGHT)) {
		stateSelectTexture(&s, 1, 0, 0, 0, 0);
	}

	float k = GetMouseWheelMove();
	if (k != 0.) {
		Vector2 point = GetMousePosition();
		Vector2 mod = {0.1, 0.1};
		mod = Vector2AddValue(Vector2Scale(mod, k), 1.);
		Vector2 newScale = Vector2Multiply(s.scale, mod);
		Vector2 relScale = Vector2Divide(newScale, s.scale);
		Vector2 newOfs = Vector2Subtract(point, s.offset);
		Vector2 relOfs = Vector2Multiply(relScale, newOfs);
		s.offset = Vector2Subtract(point, relOfs);
		s.scale = newScale;
	} else if (IsKeyPressed(KEY_SPACE)) {
		s.scale = V2ONE;
		s.offset = V2ZERO;
		stateSelectTexture(&s, 0, 1, 1, 1, 1);
	}
	if (IsKeyPressed(KEY_N) || IsKeyPressed(KEY_RIGHT)) {
		stateSelectTexture(&s, 1, 0, 0, 0, 0);
	} else if (IsKeyPressed(KEY_P) || IsKeyPressed(KEY_LEFT)) {
		stateSelectTexture(&s, -1, 0, 0, 0, 0);
	} else if (IsKeyPressed(KEY_PAGE_UP)) {
		stateSelectTexture(&s, 5, 0, 0, 0, 0);
	} else if (IsKeyPressed(KEY_PAGE_DOWN)) {
		stateSelectTexture(&s, -5, 0, 0, 0, 0);
	} else if (IsKeyPressed(KEY_END)) {
		stateSelectTexture(&s, s.files.nfiles - 1 - s.files.selectedFile, 0, 0, 0, 0);
	} else if (IsKeyPressed(KEY_HOME)) {
		stateSelectTexture(&s, -s.files.selectedFile, 0, 0, 0, 0);
	} else if (IsKeyPressed(KEY_F)) {
		if (s.filter == RL_TEXTURE_FILTER_POINT) {
			SetTextureFilter(s.texture, RL_TEXTURE_FILTER_TRILINEAR);
			s.filter = RL_TEXTURE_FILTER_TRILINEAR;
		} else {
			SetTextureFilter(s.texture, RL_TEXTURE_FILTER_POINT);
			s.filter = RL_TEXTURE_FILTER_POINT;
		}
	}

	if (IsKeyPressed(KEY_T)) {
		s.bg = (s.bg + 1)%3;
	}

	++s.frame;

	if (state->scale.x != s.scale.x || state->scale.y != s.scale.y) {
		SetWindowTitle(getNewWindowTitle(&s));
	}
	*state = s;

	return 0;
}
int
drawState(ProgramState *const state)
{
	if (!state || !state->isInitialized)
		return 1;
	ProgramState s = *state;

	if (s.bg == 0) {
		ClearBackground(BLACK);
		Texture bg = s.bgs[s.bg];
		Rectangle bgsrc = {-s.offset.x, -s.offset.y, bg.width, bg.height};
		Rectangle bgdst = {0, 0, GetScreenWidth(), GetScreenHeight()};
		DrawTextureTiled(bg, bgsrc, bgdst, V2ZERO, 0., 1., (Color){255,255,255,255});
	} else if (s.bg == 1) {
		ClearBackground(BLACK);
	} else {
		ClearBackground(WHITE);
	}

	Texture t = s.texture;
	Rectangle src = {0, 0, t.width, t.height};
	Rectangle dst = {s.offset.x, s.offset.y, t.width * s.scale.x, t.height * s.scale.y};
	DrawTexturePro(t, src, dst, V2ZERO, 0., (Color){255,255,255,255});

	return 0;
}

int
main(int argc, char **argv)
{
	ProgramState state = {};
	brrlog_init();
	SetTraceLogLevel(LOG_ERROR); // Just in case I misuse raylib and it complains

	if (initState(&state, argc - 1, (const char **)argv + 1))
		return 1;

	while (!WindowShouldClose())
	{
		if (updateState(&state))
			break;

		BeginDrawing();
		if (drawState(&state)) {
			EndDrawing();
			break;
		}
		EndDrawing();
	}

	clearState(&state);
	brrlog_deinit();
}
