CUR_PATH = ./src
CS = $(wildcard $(CUR_PATH)/*.c)
INC = -I./inc
OBJS = $(patsubst $(CUR_PATH)/%.c, ./%.o, $(CS))
TARGET = libmempool.so
GCC  = gcc
CFLAGS = -g -Wall -pipe -fno-ident -MMD -D_GNU_SOURCE -D_REENTRNT -D_DEBUG_BUILD -fPIC 

all : $(TARGET)

clean :
	rm -f $(TARGET) *.o

$(TARGET) : $(OBJS)
	$(GCC) $(OBJS) $(CFLAGS) $(INC) -shared -o ./lib/$(TARGET)
	
%.o : $(CUR_PATH)/%.c
	$(GCC) $(INC) -c $(CFLAGS) $< -o  $@
