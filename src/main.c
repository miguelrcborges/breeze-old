#define MAIN
#include <stdio.h>

#include "monitor.h"

void initShell(void);

#ifdef _WIN32
int __stdcall WinMain(
	void *hInstance,
	void *pInstance,
	char *lpCmdLine,
	int nShowCmd
) {
#else
#include <X11/Xlib.h>
#include <x11_globals.h>

int main() {
#endif

	initShell();

	char buffer[1024];
	int cursor = 0;

	processMonitors();

	cursor += sprintf(buffer + cursor, "%d Monitor(s)\n", monitors_count);
	for (int i = 0; i < monitors_count; i += 1) {
		cursor += sprintf(buffer + cursor, "Monitor %d: %dx%d @ %dx%d.\n", i, monitors[i].width, monitors[i].height, monitors[i].x, monitors[i].y);
	}
	puts(buffer);


	return 0;
}
