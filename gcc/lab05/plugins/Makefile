BASE_DIR := $(shell pwd)

CC = gcc
#CC = g++

CFLAGS= -c -O0 -m32 -gdwarf -fPIC 
LDFLAGS= -m32 -shared

SRCS=sort1D.c mult10.c min1D.c rev1D.c

HDRS=
OBJS=$(SRCS:.c=.o)
TARGETS=$(OBJS:.o=)


all: cleanscr clean $(OBJS) $(TARGETS)


$(TARGETS): %: %.o
	$(CC) $(LDFLAGS) $< -o $@.so


$(OBJS): $(SRCS)  
	$(CC) $(CFLAGS) $^

clean:
	rm -f *.o *.so

cleanscr:
	clear
