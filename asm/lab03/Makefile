BASE_DIR := $(shell pwd)

CC = gcc
#CC = g++

CFLAGS=-c -O0 -m32 -gdwarf
LDFLAGS=-m32

SRCS=fun.c 
HDRS=
OBJS=$(SRCS:.c=.o)
#LIBS=../lib/m_time.o
TARGET=

all: cleanscr clean $(OBJS)


$(TARGET): $(OBJS)
	$(CC) $(LDFLAGS) $(OBJS) $(LIBS) -o $@


$(OBJS): $(SRCS) $(HDRS) 
	$(CC) $(CFLAGS) $^ -o $@

clean:
	rm -f $(TARGET) *.o

cleanscr:
	clear
