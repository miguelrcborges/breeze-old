#include <stdint.h>
#include <stdio.h>

#include "win_comdefs.h"
#include "win_globals.h"

// Ex Styles
#define TOOLWINDOW 0x00000080L

// Styles
#define DISABLED 0x08000000L
#define POPUP 0x80000000L

enum METRICS_IDS {
	XVRES = 76,
	YVRES = 77,
	WVRES = 78,
	HVRES = 79,
};

w32(int) GetSystemMetrics(int);
w32(handle) FindWindowA(char *className, char *windowName);
w32(handle) CreateWindowExA(uint32_t win_style, char *class, char *name, int ctrl_style,
	int x, int y, int w, int h, handle parent, handle menu, handle instance, void *param
);

char *initShell(void) {
	// handle han = FindWindowA("breezeClass", "breeze");
	handle han = FindWindowA(0, "breeze");
	printf("found %p\n", han);

	if (han != 0) {
		return "breeze is already running.";
	}

	int x, y, w, h;
	x = GetSystemMetrics(XVRES);
	y = GetSystemMetrics(YVRES);
	w = GetSystemMetrics(WVRES);
	h = GetSystemMetrics(HVRES);

	// TODO: Register "breezeClass"
	CreateWindowExA(
		TOOLWINDOW,
		//"breezeClass",
		0,
		"breeze",
		POPUP | DISABLED,
		x, y, w, h,
		0, 0, mainInstance, 0
	);

	while (1);

	return (void *)0;
}
