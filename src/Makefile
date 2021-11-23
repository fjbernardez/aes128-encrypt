CFILES   = $(wildcard *.c)
OBJFILES = $(CFILES:.c=.o)
OUT      = main

CC      = gcc
CFLAGS  = -Wall

$(OUT): $(OBJFILES)

.PHONY: clean

clean:
	rm -f $(OBJFILES) $(OUT)