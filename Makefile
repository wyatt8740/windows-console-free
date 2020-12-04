CC = i686-w64-mingw32-gcc
CFLAGS += -Wall -municode -mwindows -Wl,--subsystem,windows

console-free.exe: console-free.c
	$(CC) -o $@ $< $(CFLAGS)

.PHONY: clean

clean:
	rm -f console-free.exe
