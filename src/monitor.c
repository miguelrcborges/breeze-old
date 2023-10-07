#define MAIN
#include <windows.h>

#include "monitor.h"

static BOOL processMonitorsCallback(HMONITOR _, HDC __, LPRECT rect, LPARAM ___);

void processMonitors() {
	monitors_count = 0;

	if (monitors != NULL) {
		free(monitors);
		monitors = NULL;
	}

	EnumDisplayMonitors(NULL, NULL, processMonitorsCallback, 0);
}

static BOOL processMonitorsCallback(HMONITOR _, HDC __, LPRECT rect, LPARAM ___) {
	monitors_count += 1;

	if (monitors == NULL) {
		monitors = malloc(sizeof(*monitors));
	} else {
		monitors = realloc(monitors, monitors_count * sizeof(*monitors));
	}

	monitors[monitors_count - 1].rect = *rect;

	return TRUE;
}
