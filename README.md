# console-free

A tiny command-line program I wrote for Win32 so I could run some software that
popped up black console boxes that never contained useful information in them
(such as some X11 programs that I have in Cygwin, like 'mate-terminal').

It's my first time writing anything at all for Win32 in several years; that
said, I think I managed to make it Unicode compatible, which is nice.

Basically, you can either drag a program onto it, or you can invoke it via a
shortcut with an argument for the program to run, and this program should
prevent your chosen software from opening a pointless console window.

I would have killed for something like this in 2013, before I really knew
anything worth writing home about regarding C programming or the Windows API.
Unix really spoils me, sometimes.
