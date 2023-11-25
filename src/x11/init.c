#include <stdio.h>
#include <stdlib.h>
#include <X11/Xlib.h>
#include <X11/Xatom.h>
#include <X11/cursorfont.h>

#include "macros.h"
#include "x11_globals.h"

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

	wm_window = XCreateSimpleWindow(display, root_window, 0, 0, 1, 1, 0, 0, 0);
	XChangeProperty(display, root_window, XInternAtom(display, "_NET_SUPPORTING_WM_CHECK", False),
		XA_WINDOW, 32, PropModeReplace, (unsigned char *) &wm_window, 1);
	XChangeProperty(display, wm_window, XInternAtom(display, "_NET_SUPPORTING_WM_CHECK", False),
		XA_WINDOW, 32, PropModeReplace, (unsigned char *) &wm_window, 1);
	XChangeProperty(display, wm_window, XInternAtom(display, "_NET_WM_NAME", False),
		XInternAtom(display, "UTF8_STRING", False), 8, PropModeReplace, (unsigned char *) "breeze", 5);

	return err;
}

int wmCheckErrorHandler(Display *d, XErrorEvent *e) {
	unused(d);
	unused(e);
	fputs("Another wm is already running.\n", stderr);
	exit(1);
	return 1;
}

int wmErrorHandler(Display *d, XErrorEvent *e) {
	unused(d);
	unused(e);
	fprintf(stderr, "[Xerror] %d at %d\n", (int)e->error_code, (int)e->request_code);
	return 1;
}
