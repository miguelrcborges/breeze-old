#ifndef X11_GLOBALS_H
#define X11_GLOBALS_H

#ifdef MAIN
#define PREFIX 
#else
#define PREFIX extern
#endif

PREFIX Display *display;

#endif /* X11_GLOBALS_H */
