#include <X11/Xlib.h>

#include "x11_globals.h"

void initShell(void) {
	display = XOpenDisplay(NULL);
}
