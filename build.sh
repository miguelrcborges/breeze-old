rm breeze.exe

INCLUDES="-Isrc/include" 
INCLUDES_WINDOWS="/Isrc/include" 
LINKS_WINDOWS="-luser32"

if [ -z "$CFLAGS" ]; then
	CFLAGS="-Og -g -gcodeview"
fi


if [ -n $(uname | grep MINGW) ]; then
	clang $INCLUDES $CFLAGS src/main.c $(find src/windows src/common -type f) $LINKS_WINDOWS -o breeze.exe
elif [ -n $(uname | grep Linux) ]; then
	clang $INCLUDES $CFLAGS src/main.c $(find src/x11 src/common -type f) -o breeze $LINKS_X11
else
	echo Not known host system
fi
