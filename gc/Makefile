CC = gcc
SRCS = $(wildcard *.c) $(wildcard *.s)
BIN = gc

pack: clean gcpack ar
run: clean gcrun

clean:
	rm -f gc a.out
	rm -rf *.o

gcpack: $(SRCS)
	$(CC) -g -c $(SRCS)
gcrun: $(SRCS)
	$(CC) -g  $(SRCS)
ar:
	ar -rc libgc.a gc.o mark_sweep.o root.o list.o Array.o
