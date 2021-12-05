CC=cc
OPT=-Os
CFLAGS=$(OPT) -Wall -Wpedantic
DESTDIR=/usr/local

build:
	$(CC) $(CFLAGS) mgrep.c match.c -o mgr
	$(CC) $(CFLAGS) test.c match.c -o test

install: build
	cp mgr $(DESTDIR)/bin
