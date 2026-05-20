BASE_DIR := $(shell pwd)

CC = gcc
#CC = g++

#CFLAGS=-c -O0 -m32 -gdwarf
CFLAGS=-c -O0 -gdwarf
#LDFLAGS=-m32
LDFLAGS=

SRC_DIRS = $(BASE_DIR) 
SRCS = $(shell find $(SRC_DIRS) -name "*.c")
HRCS = $(shell find $(SRC_DIRS) -name "*.h")
OBJS=$(SRCS:.c=.o)
#LIBS=../lib/../m_time.o
TARGET=signals

all: cleanscr clean $(OBJS) $(TARGET)


$(TARGET): $(OBJS)
	$(CC) $(LDFLAGS) $^ $(LIBS) -o $(TARGET)

$(OBJS): %.o: %.c $(HRCS) 
	$(CC) $(CFLAGS) $< -o $@

clean:
	rm -f $(TARGET) $(OBJS)

cleanscr:
	clear
