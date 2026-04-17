BASE_DIR := $(shell pwd)

CC = gcc
#CC = g++

CFLAGS=-c -O0 -m32 -gdwarf -masm=intel
LDFLAGS=-m32 

SRCS=mem.c 
HDRS=
OBJS=$(SRCS:.c=.o)
#LIBS=../lib/m_time.o
TARGET=mem

all: cleanscr clean $(OBJS) $(TARGET)


$(TARGET): $(OBJS)
	$(CC) $(LDFLAGS) $(OBJS) $(LIBS) -o $@


$(OBJS): $(SRCS) $(HDRS) 
	$(CC) $(CFLAGS) $^ -o $@

clean:
	rm -f $(TARGET) *.o

cleanscr:
	clear
