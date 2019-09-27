trunk_path = $(shell pwd | sed "s/\/app.*//")
include $(trunk_path)/make.rules

INC = -I. $(PROTOCOL_INC) $(MAPOBJ_INC) $(ACTIVITY_INC) $(CONFIG_INC) $(DATA_INC) $(BASE_INC) $(DBC_INC) $(PENGYOU_INC) $(COMMON_INC) $(KERNEL_INC) $(PLATFORM_INC) $(MESSAGE_INC) 
LIB = $(PROTOCOL_LIB) $(CONFIG_LIB) $(DATA_LIB) $(PLATFORM_LIB) $(KERNEL_LIB) $(DBC_LIB) $(MESSAGE_LIB) $(PENGYOU_LIB) $(COMMON_LIB) $(BASE_LIB) $(PROTOBUF_LIB) $(CURL_LIB)
SRC = ./*.cpp $(ACTIVITY_SRC)

TARGETS = login
CPPS = $(wildcard $(SRC)) 
OBJS = $(patsubst %.cpp, %.o, $(CPPS))
DS = $(patsubst %.cpp,%.d,$(CPPS))
OBJS_FILTER = $(patsubst %.cpp, %.o, $(CPPS))
CFLAGS  = -g -Wall -pipe -fno-ident -MMD -D_GNU_SOURCE -D_REENTRNT -D_DEBUG_BUILD -D_COMPILE_LOGIN
all: $(TARGETS)
$(TARGETS) : $(OBJS)
	$(CXX) $(OBJS_FILTER) $(CFLAGS) -o $@ $(INC) $(LIB)
%:%.cpp
	$(CXX) $(CFLAGS) -o $@ $< $(INC) $(LIB) $(OBJS)
%:%.c
	$(CXX) $(CFLAGS) -o $@ $< $(INC) $(LIB)
%.o : %.cpp 
	$(CXX) $(INC) -c $(CXXFLAGS) $< -o $@
clean:
	rm -f *.o *.d $(TARGETS)
install:
	cp -f $(TARGETS) /data/release/zzfb_server/bin/zzfb_login
