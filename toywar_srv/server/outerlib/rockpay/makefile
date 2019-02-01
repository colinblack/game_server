CC         := g++
ROOT_DIR   := $(shell pwd)
SRC_DIR    := $(ROOT_DIR)/src
LIB_DIR    := $(ROOT_DIR)/lib
INC_DIR    := $(ROOT_DIR)/include

SRC_FILES  := $(wildcard $(SRC_DIR)/*.cpp)
OBJ_FILES  := $(SRC_FILES:.cpp=.o)
LD_LIBS    := 

LIB_NAME   := rockpay
LIB_SUFFIX := .a
LIB_TARGET := ./lib/lib$(LIB_NAME)$(LIB_SUFFIX)

.PHONY: all clean

LDFLAGS    := -L$(LIB_DIR) $(addprefix -l,$(LD_LIBS))
CFLAGS     := -g -I$(SRC_DIR) $(addprefix -I,$(INC_DIR))

all: $(LIB_TARGET)

$(LIB_TARGET): $(OBJ_FILES)
	$(AR) -rc $@ $(OBJ_FILES)
	@echo *********Build $@ $(LIB_TARGET:.a=.so) Successful*********

%.o: %.cpp
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	@echo clean...
	@rm -rf $(LIB_TARGET) $(OBJ_FILES)
