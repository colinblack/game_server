######################################################################
#                  OpenAPI C++ edtion Makefile                       #
######################################################################
CC         := g++
ROOT_DIR   := $(shell pwd)
SRC_DIR    := $(ROOT_DIR)/src
LIB_DIR    := $(ROOT_DIR)/lib
INC_DIR    := $(ROOT_DIR)/include $(ROOT_DIR)/include/json
LIBTOOL    := libtool

SRC_FILES  := $(wildcard $(SRC_DIR)/*.cpp)
OBJ_FILES  := $(SRC_FILES:.cpp=.o)
LD_LIBS    := curl jsoncpp rt

LIB_NAME   := sg17openapi
LIB_SUFFIX := .so
LIB_TARGET := ./lib/lib$(LIB_NAME)$(LIB_SUFFIX)

.PHONY: all clean 

LDFLAGS    := -L$(LIB_DIR) $(addprefix -l,$(LD_LIBS))
CFLAGS     := -O3 -fPIC -Werror -DCURL_STATICLIB -I$(SRC_DIR) $(addprefix -I,$(INC_DIR))

ifeq ($(DEBUG),yes)
CFLAGS     += -ggdb2 -D__DEBUG 
endif

all: $(LIB_TARGET) ;

$(LIB_TARGET): $(OBJ_FILES)
	#$(AR) -rc $@ $(OBJ_FILES)
	$(CC) -shared -o $(LIB_TARGET:.a=.so) $(OBJ_FILES) 
	@echo *********Build $@ $(LIB_TARGET:.a=.so) Successful*********
	@echo
example: $(LIB_TARGET)
	@cd example && make UST=yes
	@echo ***************Build $@ Successful************

%.o: %.cpp
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	@echo clean...
	@rm -rf $(LIB_TARGET) $(LIB_TARGET:.a=.so) $(OBJ_FILES) $(LIB_TARGET:.a=.bin)
#	@cd example && make clean
