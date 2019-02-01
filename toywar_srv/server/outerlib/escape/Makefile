
OBJECTS = \
	obj/uri.o \
	obj/xhtml.o \
	obj/str.o

LIB_TARGET = $(LIB_DIR)libisdwebcharacter.a

INC_DIR = include/
SRC_DIR = src/
OBJ_DIR = obj/
LIB_DIR = lib/

OBJ_EXT = .o
CXXSRC_EXT = .cpp

INC = -I$(INC_DIR)
LIB = -L$(LIB_DIR)

$(OBJ_DIR)%$(OBJ_EXT): $(SRC_DIR)%$(CXXSRC_EXT)
	@echo
	@echo "Compiling $< ==> $@..."
	$(CXX) $(C_FLAGS) $(INC) -c $< -o $@

$(LIB_TARGET): $(OBJECTS)
	@echo
	@echo "$(OBJECTS) ==> $@"
	$(AR) rc $(LIB_TARGET) $(OBJECTS)

all: lib

lib: $(LIB_TARGET)


clean: clean-lib
	rm -rf $(OBJECTS)

clean-lib:
	rm -rf $(LIB_TARGET)


