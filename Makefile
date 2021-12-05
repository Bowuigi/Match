CC=cc
OPT=-Os
CFLAGS=-Wall -Wpedantic
DESTDIR=/usr/local

build:
	$(CC) $(OPT) $(CFLAGS) mgr.c match.c -o mgr
	$(CC) $(OPT) $(CFLAGS) test.c match.c -o test

install: build
	cp mgr $(DESTDIR)/bin
