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
TRGS=$(OBJS:.o=)
#LIBS=../lib/../m_time.o
TARGET=

all: cleanscr clean $(OBJS) $(TRGS) 


$(TRGS): %: %.o  
	$(CC) $(LGLAGS) $< -o $@


$(TARGET): $(OBJS)
	$(CC) $(LDFLAGS) $^ $(LIBS) -o $(TARGET)


$(OBJS): %.o: %.c $(HRCS) 
	$(CC) $(CFLAGS) $< -o $@


clean:
	rm -f $(TARGET) $(OBJS)

cleanscr:
	clear
