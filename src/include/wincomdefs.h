#ifndef WINCOMDEFS
#define WINCOMDEFS

#define winuserapi __declspec(dllimport)
#define winapi __stdcall
#define w32(type) winuserapi type winapi


#endif /* WINCOMDEFS */
