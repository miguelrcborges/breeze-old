#include <stdlib.h>
#include <stdint.h>
#include "wincomdefs.h"

#include "monitor.h"

typedef struct winRect 
{
    long left;
    long top;
    long right;
    long bottom;
} winRect;

static int winapi processMonitorsCallback(void *, void *, winRect *rect, int64_t);
w32(int) EnumDisplayMonitors(void *hdc, void *lprcClip, void *lpfnEnum, int64_t dwData);

void processMonitors(void) {
	if (monitors != NULL) {
		free(monitors);
		monitors = NULL;
	}

	EnumDisplayMonitors(NULL, NULL, processMonitorsCallback, 0);
}


int winapi processMonitorsCallback(void *_, void *__, winRect *rect, int64_t ___) {
	monitors_count += 1;

	if (monitors == NULL) {
		monitors = malloc(sizeof(*monitors));
	} else {
		monitors = realloc(monitors, monitors_count * sizeof(*monitors));
	}

	monitors[monitors_count-1].x = rect->left;
	monitors[monitors_count-1].y = rect->top;
	monitors[monitors_count-1].width = rect->right - rect->left;
	monitors[monitors_count-1].height = rect->bottom - rect->top;

	return 1;
}
