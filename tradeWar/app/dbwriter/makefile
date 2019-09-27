trunk_path = $(shell pwd | sed "s/\/app.*//")
include $(trunk_path)/make.rules

INC =   -I. $(BASE_INC) $(DBC_INC) $(PENGYOU_INC) $(COMMON_INC) $(KERNEL_INC) $(PLATFORM_INC) $(DATA_INC) $(LOGIC_INC) $(PROTOCOL_INC) -I../mapobj -I../config
LIB	=  $(PENGYOU_LIB) $(DATA_LIB) $(KERNEL_LIB) $(COMMON_LIB) $(DBC_LIB) $(BASE_LIB)

#-D_NEED_CHECK_OPEN

TARGETS = dbwriter
CPPS = $(wildcard ./*.cpp ../protocol/*.cpp) 
OBJS = $(patsubst %.cpp, %.o, $(CPPS))
OBJS_FILTER = $(patsubst %.cpp, %.o, $(CPPS))
LIB_FILTER= $(filter-out ./main.o,$(OBJS))
CFLAGS  = -g -Wall -pipe -fno-ident -MMD -D_GNU_SOURCE -D_REENTRNT -D_DEBUG_BUILD

all: $(TARGETS)
$(TARGETS) : $(OBJS)
	$(CXX) $(OBJS_FILTER) $(CFLAGS) -o $@ $(INC) $(LIB)
#	ar rc libbattle.a $(LIB_FILTER)
%:%.cpp
	$(CXX) $(CFLAGS) -o $@ $< $(INC) $(LIB) $(OBJS)
%:%.c
	$(CXX) $(CFLAGS) -o $@ $< $(INC) $(LIB)
%.o : %.cpp 
	$(CXX) $(INC) -c $(CXXFLAGS) $< -o	$@
clean:
	rm -f *.o *.d $(TARGETS) ../data/*.o ../data/*.d
install:
	cp -f $(TARGETS) /data/release/zzfb_server/bin/zzfb_dbwriter
