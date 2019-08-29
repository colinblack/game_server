trunk_path = $(shell pwd | sed "s/\/app.*//")
include $(trunk_path)/make.rules

INC = -I. $(BASE_INC) $(DBC_INC) $(PENGYOU_INC) $(COMMON_INC) $(KERNEL_INC) $(PLATFORM_INC) $(DATA_INC) $(LOGIC_INC) $(PROTOCOL_INC) $(MESSAGE_INC) 
LIB = $(PROTOCOL_LIB) $(MESSAGE_LIB) $(DATA_LIB) $(PLATFORM_LIB) $(KERNEL_LIB) $(DBC_LIB) $(PENGYOU_LIB) $(COMMON_LIB) $(BASE_LIB) $(CURL_LIB) $(PROTOBUF_LIB)

TARGETS = transit
CPPS = $(wildcard ./*.cpp) 
OBJS = $(patsubst %.cpp,%.o,$(CPPS))
DS = $(patsubst %.cpp,%.d,$(CPPS))
OBJS_FILTER = $(patsubst %.cpp,%.o,$(CPPS))

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
	cp -f $(TARGETS) /data/release/zzfb_server/bin/zzfb_transit
