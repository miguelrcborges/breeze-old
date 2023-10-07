#include <windows.h>
#include <stdio.h>

#include "monitor.h"

int WINAPI WinMain(
	HINSTANCE hInstance,
	HINSTANCE pInstance,
	LPSTR lpCmdLine,
	int nShowCmd
) {

	char buffer[1024];
	int cursor = 0;

	processMonitors();

	sprintf(buffer, "%d", monitors_count);
	for (size_t i = 0; i < monitors_count; i += 1) {
		cursor += sprintf(buffer + cursor, "Monitor %zu: %ld %ld %ld %ld\n", i, monitors[i].rect.left, monitors[i].rect.top, monitors[i].rect.right, monitors[i].rect.bottom);
	}

	MessageBoxA(NULL, buffer, "deez nuts", MB_OK);
	puts(buffer);

	// Sleep(10000);
	// ExitWindowsEx(0, 0);
	return 0;
}
