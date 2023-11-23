#define MAIN

#include <stdio.h>
#include <string.h>
#include "win_comdefs.h"
#include "win_globals.h"
#include "monitor.h"
#include "macros.h"

char *initShell(void);
static void printUsage(FILE *f);
w32(int) MessageBoxA(handle win, char *msg, char *capt, unsigned int type);

int winapi WinMain(
	handle hInstance,
	handle pInstance,
	char *lpCmdLine,
	int nShowCmd
) {
	unused(hInstance);
	unused(pInstance);
	unused(lpCmdLine);
	unused(nShowCmd);

	if (strlen(lpCmdLine) != 0) {
		if (strcmp(lpCmdLine, "-h") == 0) {
			printUsage(stdout);
			return 0;
		}
		printUsage(stdout);
		return 1;
	}

	mainInstance = hInstance;

	char *err = initShell();
	if (err != NULL) {
		MessageBoxA(mainInstance, err, "Error", 0x30L);
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
	fputs("breeze\n"
	      "Usage: \n"
	      "\tbreeze [OPTION]\n"
	      "\n"
	      "Options:\n"
	      "\t-h : Displays this message\n"
	, f);
}
