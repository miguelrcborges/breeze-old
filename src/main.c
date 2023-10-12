#define MAIN
#include <stdio.h>

#include "monitor.h"

#ifdef _WIN32
int __stdcall WinMain(
	void *hInstance,
	void *pInstance,
	char *lpCmdLine,
	int nShowCmd
) {
#else
int main() {
#endif

	char buffer[1024];
	int cursor = 0;

	processMonitors();

	sprintf(buffer, "%d Mointor(s)\n", monitors_count);
	// for (size_t i = 0; i < monitors_count; i += 1) {
	// 	sprintf(buffer, "Monitor %zu: %dx%d @ %dx%d.\n", i, monitors[i].width, monitors[i].height, monitors[i].x, monitors[i].y);
	// }
	puts(buffer);


	return 0;
}
