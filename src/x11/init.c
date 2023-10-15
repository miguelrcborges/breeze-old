#include <stdio.h>
#include <stdlib.h>
#include <X11/Xlib.h>

#include "x11_globals.h"

#define UNUSED(x) (void)(x)

static int wmCheckErrorHandler(Display *d, XErrorEvent *e);
static int wmErrorHandler(Display *d, XErrorEvent *e);

char *initShell(void) {
	char *err = NULL;
	display = XOpenDisplay(NULL);
	if (display == NULL) {
		err = "Failed to open X display.\n";
	}

	root_window = DefaultRootWindow(display);

	// Proc error handler if one WM is already running
	XSetErrorHandler(wmCheckErrorHandler);
	XSelectInput(display, root_window, SubstructureRedirectMask);
	XSync(display, False);

	XSetErrorHandler(wmErrorHandler);
	XSelectInput(display, root_window, SubstructureNotifyMask|PointerMotionMask);

	return err;
}

int wmCheckErrorHandler(Display *d, XErrorEvent *e) {
	UNUSED(d);
	UNUSED(e);
	fputs("Another wm is already running.\n", stderr);
	exit(1);
	return 1;
}

int wmErrorHandler(Display *d, XErrorEvent *e) {
	UNUSED(d);
	UNUSED(e);
	fprintf(stderr, "[Xerror] %d at %d\n", (int)e->error_code, (int)e->request_code);
	return 1;
}
