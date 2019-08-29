trunk_path = $(shell pwd | sed "s/\/app.*//")
include $(trunk_path)/make.rules

INC = -I. $(BASE_INC) $(DBC_INC) $(PENGYOU_INC) $(COMMON_INC) $(KERNEL_INC) $(PLATFORM_INC) $(PROTOCOL_INC) $(DATA_INC) $(MESSAGE_INC) $(CONFIG_INC)
LIB	= $(PROTOCOL_LIB) $(MESSAGE_LIB) $(DATA_LIB) $(CONFIG_LIB) $(PENGYOU_LIB) $(KERNEL_LIB) $(COMMON_LIB) $(DBC_LIB) $(BASE_LIB) $(PROTOBUF_LIB)

TARGETS = allserver
CPPS = $(wildcard ./*.cpp) 
OBJS = $(patsubst %.cpp, %.o, $(CPPS))
OBJS_FILTER = $(patsubst %.cpp, %.o, $(CPPS))
CFLAGS = -g -Wall -pipe -fno-ident -MMD -D_GNU_SOURCE -D_REENTRNT -D_DEBUG_BUILD

all: $(TARGETS)
$(TARGETS) : $(OBJS)
	$(CXX) $(OBJS_FILTER) $(CFLAGS) -o $@ $(INC) $(LIB)
%:%.cpp
	$(CXX) $(CFLAGS) -o $@ $< $(INC) $(LIB) $(OBJS)
%:%.c
	$(CXX) $(CFLAGS) -o $@ $< $(INC) $(LIB)
%.o : %.cpp 
	$(CXX) $(INC) -c $(CXXFLAGS) $< -o	$@
clean:
	rm -f *.o *.d $(TARGETS)
