#! /bin/sh
i686-w64-mingw32-gcc console-free.c \
                     -municode \
                     -mwindows \
                     -o console-free.exe \
                     -Wl,--subsystem,windows
