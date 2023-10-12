#include <stdlib.h>
#include <X11/Xlib.h>
#include "x11_globals.h"
#ifndef NO_XINERAMA
#include <X11/extensions/Xinerama.h>
#endif

#include "monitor.h"

void processMonitors() {
	if (monitors != NULL)
		free(monitors);

#ifndef NO_XINERAMA
	if (XineramaIsActive(display)) {
		XineramaScreenInfo *info = XineramaQueryScreens(display, &monitors_count);


		monitors = malloc(sizeof(*monitors) * monitors_count);
		for (int i = 0; i < monitors_count; i += 1) {
			monitors[i].x = info[i].x_org;
			monitors[i].y = info[i].y_org;
			monitors[i].width = info[i].width;
			monitors[i].height = info[i].height;
		}

		XFree(info);
	} else 
#endif
	{
		monitors_count = 1;
		int screen = DefaultScreen(display);
		monitors = malloc((sizeof(*monitors)));
		monitors->x = 0;
		monitors->y = 0;
		monitors->width = DisplayWidth(display, screen);
		monitors->height = DisplayHeight(display, screen);
	}
}
