PREFIX?=/usr/X11R6
CFLAGS?=-Os -pedantic -Wall
BIN_DIR?=/usr/bin
DESKTOP_ENTRY?=/usr/share/xsessions/

all:
	$(CC) $(CFLAGS) -I$(PREFIX)/include tinywm.c -L$(PREFIX)/lib -lX11 -o tinywm

clean:
	rm -f tinywm
install:
	cp -f tinywm $(BIN_DIR)
	cp -f tinywm.desktop $(DESKTOP_ENTRY)
