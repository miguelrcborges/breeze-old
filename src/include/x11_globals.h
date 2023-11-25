#ifndef X11_GLOBALS_H
#define X11_GLOBALS_H

#ifdef MAIN
#define PREFIX 
#else
#define PREFIX extern
#endif

PREFIX Display *display;
PREFIX Window root_window, wm_window;

#endif /* X11_GLOBALS_H */
