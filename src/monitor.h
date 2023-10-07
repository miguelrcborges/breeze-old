/**
 * Header dependencies:
 * - windows.h.
 */

#ifndef MONITOR_H
#define MONITOR_H

#ifdef MAIN
#define PREFIX 
#else
#define PREFIX extern
#endif

typedef struct Monitor Monitor;
struct Monitor {
	RECT rect;
};

PREFIX unsigned int monitors_count;
PREFIX Monitor *monitors;

extern void processMonitors();

#endif /* MONITOR_H */
