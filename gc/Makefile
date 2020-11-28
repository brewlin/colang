CC = gcc
SRCS = $(wildcard *.c) $(wildcard *.s)
BIN = gc

all: clean gc ar

clean:
	rm -f gc a.out libgc.a
	rm -rf *.o

gc: $(SRCS)
	$(CC) -g -c  $(SRCS)
ar:
	ar -rc libgc.a gc.o mark_sweep.o root.o

