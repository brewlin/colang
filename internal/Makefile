CC = gcc

LD = gcc

CFLAGS = -g -Wall -std=gnu99 -I ../

LDFLAGS = -g

RM = rm -f

SRCS = $(wildcard *.c)
OBJS = $(addsuffix .o, $(basename $(SRCS)))
PROG = test

all: $(PROG)

$(PROG): $(OBJS)
	$(LD) $(LDFLAGS) $(OBJS) -o $(PROG)

%.o: %.c
	$(CC) $(CFLAGS) -c $<

.PHONY: clean
clean:
	$(RM) $(PROG) $(OBJS)
