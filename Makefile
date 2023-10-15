CC ?= clang

CFLAGS ?= -Og -Wall -Wextra -pedantic -Wno-unused-parameter
CFLAGS += -Isrc/include
LINKS_X11 = -lX11 
LINKS_WINDOWS = -luser32

SRC = src/main.c $(shell find src/common -type f) 
SRC_X11 = $(SRC) $(shell find src/x11 -type f)
SRC_WIN = $(SRC) $(shell find src/windows -type f)


ifdef NO_XINERAMA
	CFLAGS += -DNO_XINERAMA
else
	LINKS_X11 += -lXinerama 
endif


.PHONY: no_target x11 windows win

no_target:
	@echo Specify a target to compile to.

x11: breeze
windows win: breeze.exe

breeze: $(SRC_X11)
	$(CC) $(CFLAGS) $(LINKS_X11) $^ -o $@

breeze.exe: $(SRC_WIN)
	$(CC) $(CFLAGS) $(LINKS_WINDOWS) $^ -o $@
