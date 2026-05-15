BASE_DIR := $(shell pwd)

CC = gcc
#CC = g++

CFLAGS=-c -O0 -m32 -gdwarf 
LDFLAGS=-m32 

SRCS=main.c
HDRS=
OBJS=$(SRCS:.c=.o)
#LIBS=../lib/m_time.o
TARGET=program

all: cleanscr clean $(OBJS) $(TARGET)


$(TARGET): $(OBJS)
	$(CC) $(LDFLAGS) $(OBJS)  -o $@


$(OBJS): $(SRCS)  
	$(CC) $(CFLAGS) $^ 

clean:
	rm -f $(TARGET) *.o

cleanscr:
	clear
