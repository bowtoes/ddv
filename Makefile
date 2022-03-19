.PHONY: all clean setup info vnd

prgName:=ddv
prefix:=/addtl

srcDir:=src
srcIn:=\
	main.c \
	dds.c \
	state.c \
	print.c \

hdrIn:=\
	dds.h \
	state.h \
	print.h \

outDir:=_build
vndDir:=vnd
vndOut=$(raylibOut) $(brrtoolsOut)

objDir := $(outDir)/obj
objOut := $(addprefix $(objDir)/,$(patsubst $(srcDir)/%,%,$(srcIn:.c=.o)))

STRIP := strip -s -M -v -x

_cc_warnings=-Wall -Wextra\
	-Werror=implicit-function-declaration -Werror=missing-declarations\
	-Wno-unused-function -Wno-sign-compare -Wno-unused-parameter\
cflags   = -std=c11 -D_XOPEN_SOURCE=500 -D_POSIX_C_SOURCE=200112L -D_GNU_SOURCE $(_cc_warnings) -pedantic -Wall
includes = $(raylibInc) $(brrtoolsInc)
ldflags  = $(vndOut) -lm

all: info setup $(prgName)
info:
	@echo "$(prgName) build"
setup:
	@mkdir -pv $(dir $(objOut)) 2>/dev/null || :

$(objOut): Makefile
$(objDir)/%.o: $(srcDir)/%.c
	$(CC) $(addprefix -I,$(includes)) $(cflags) -c "$<" -o "$@"
obj: info setup $(objOut)

$(prgName): Makefile vnd $(objOut) $(addprefix $(srcDir)/,$(hdrIn))
	$(CC) -o "$@" $(objOut) $(ldflags)

vnd:
vnd-clean:
vnd-again: vnd-clean vnd

clean:
	rm $(objOut) 2>/dev/null ||:
	rm $(prgName) 2>/dev/null ||:
	rm -r $(dir $(objOut)) 2>/dev/null ||:
CLEAN: vnd-clean clean

again: clean all
AGAIN: CLEAN all

ifndef DEBUG
 cflags+=-O3 -Ofast -DNDEBUG
else
 cflags+=-O0 -g -DDDV_DEBUG
 ifndef MEMCHECK
  cflags+=-pg -no-pie -DDDV_MEMCHECK
  ldflags+=-pg -no-pie
 endif
 raylibArg:=RAYLIB_BUILD_MODE=DEBUG
endif
raylibDir := "$(vndDir)"/raylib
raylibCfg := "$(vndDir)"/raylib_config.h
raylibOutDir := "$(outDir)"/"$(raylibDir)"
raylibInc := "$(raylibOutDir)"/include
raylibOut := "$(raylibOutDir)"/libraylib.a
raylibArg := RAYLIB_BUILD_MODE=RELEASE

$(raylibOutDir):
	@mkdir -pv $(raylibOutDir) 2>/dev/null || :
$(raylibCfg):
	@cp -fv "$(raylibCfg)" "$(raylibDir)"/src/config.h
$(raylibOut): Makefile $(raylibCfg) $(raylibOutDir)
	@cd "$(raylibDir)"/src && \
		$(MAKE) \
		PLATFORM=PLATFORM_DESKTOP \
		RAYLIB_MODULE_AUDIO=FALSE \
		RAYLIB_MODULE_MODELS=FALSE \
		RAYLIB_RELEASE_PATH="$(abspath $(raylibOutDir))" \
		$(raylibArg)
	ln -srfT "$(raylibDir)"/src "$(raylibInc)"

raylib: $(raylibOut)
raylib-clean:
	@cd "$(raylibDir)"/src 2>/dev/null && $(MAKE) clean || :
	rm $(raylibOut) 2>/dev/null ||:
	rm -r $(dir $(raylibOut)) 2>/dev/null ||:
raylib-again: raylib-clean raylib

vnd: $(raylibOut)
vnd-clean: raylib-clean

brrtoolsDir := "$(vndDir)"/brrtools
brrtoolsOutDir := "$(outDir)"/"$(brrtoolsDir)"
brrtoolsInc := "$(brrtoolsOutDir)"/include
brrtoolsOut := "$(brrtoolsOutDir)"/lib/libbrrtools.a

brrtoolsDebug :=
ifdef DEBUG
 brrtoolsDebug += DEBUG=$(DEBUG)
 ifdef MEMCHECK
  brrtoolsDebug += MEMCHECK=$(MEMCHECK)
 endif
endif
$(brrtoolsOut): Makefile
	@cd "$(brrtoolsDir)" && \
		$(MAKE) install \
		prefix="$(abspath $(brrtoolsOutDir))" \
		$(brrtoolsDebug) \
		TARGET_MODE=STATIC \
		DO_LDCONFIG=0
brrtools: $(brrtoolsOut)
brrtools-clean:
	@cd "$(brrtoolsDir)" 2>/dev/null && \
		$(MAKE) clean uninstall \
		prefix="$(abspath $(brrtoolsOutDir))" \
		TARGET_MODE=STATIC \
		DO_LDCONFIG=0 || :
	rm $(brrtoolsOut) 2>/dev/null ||:
	rm -r $(dir $(brrtoolsOut)) 2>/dev/null ||:
brrtools-again: brrtools-clean brrtools

vnd: $(brrtoolsOut)
vnd-clean: brrtools-clean

install: $(prgName)
	@cp -fv "$(prgName)" "$(prefix)"/bin
ifndef $(DEBUG)
	$(STRIP) "$(prefix)"/bin/"$(prgName)"
endif
uninstall:
	@rm -fv "$(prefix)"/bin/"$(prgName)" 2>/dev/null ||:
