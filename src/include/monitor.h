#ifndef MONITOR_H
#define MONITOR_H

#ifdef MAIN
#define PREFIX 
#else
#define PREFIX extern
#endif

typedef struct Monitor Monitor;
struct Monitor {
	short width, height;
	short x, y;
};

PREFIX unsigned int monitors_count;
PREFIX Monitor *monitors;

extern void processMonitors();

#endif /* MONITOR_H */
