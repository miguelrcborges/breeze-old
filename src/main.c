#define VERSION "0.0.1"
#define MAIN
#include <stdio.h>
#include <string.h>

#include "monitor.h"

#define UNUSED(x) (void)(x)

char *initShell(void);
static void printUsage(FILE *f);

#ifdef _WIN32
int __stdcall WinMain(
	void *hInstance,
	void *pInstance,
	char *lpCmdLine,
	int nShowCmd
) {
	UNUSED(hInstance);
	UNUSED(pInstance);
	UNUSED(lpCmdLine);
	UNUSED(nShowCmd);

	if (strlen(lpCmdLine) != 0) {
		if (strcmp(lpCmdLine, "-h") == 0) {
			printUsage(stdout);
			return 0;
		}
		printUsage(stdout);
		return 1;
	}

#else
#include <X11/Xlib.h>
#include <x11_globals.h>

int main(int argc, char **argv) {

	if (argc == 2) {
		if (strcmp(argv[1], "-h") == 0) {
			printUsage(stdout);
			return 0;
		} else {
			printUsage(stderr);
			return 1;
		}
	} else if (argc != 1) {
		printUsage(stderr);
		return 1;
	}
#endif

	char *err = initShell();
	if (err != NULL) {
		fputs(err, stderr);
		return 1;
	}

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

void printUsage(FILE *f) {
	fputs("breeze v" VERSION " - Cross Platform Shell\n"
	      "Usage: \n"
	      "\tbreeze [OPTION]\n"
	      "\n"
	      "Options:\n"
	      "\t-h : Displays this message\n"
	, f);
}
