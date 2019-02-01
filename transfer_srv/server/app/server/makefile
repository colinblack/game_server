trunk_path = $(shell pwd | sed "s/\/app.*//")
include $(trunk_path)/make.rules

INC =   -I. $(BASE_INC) $(DBC_INC) $(PENGYOU_INC) $(COMMON_INC) $(KERNEL_INC) $(PLATFORM_INC) $(DATA_INC) $(LOGIC_INC)
LIB	=   $(LOGIC_LIB) $(DATA_LIB) $(PLATFORM_LIB) $(KERNEL_LIB) $(COMMON_LIB) $(BASE_LIB) $(DBC_LIB) $(PENGYOU_LIB)

#-D_NEED_CHECK_OPEN

TARGETS = toyward crossdomaind
CPPS = $(wildcard *.cpp)
OBJS = $(patsubst %.cpp, %.o, $(CPPS))
OBJS_FILTER = $(filter-out $(patsubst %, %.o, $(TARGETS)), $(patsubst %.cpp, %.o, $(CPPS)))

all: $(TARGETS)
$(TARGETS) : $(OBJS)
	$(CXX) $(OBJS_FILTER) $@.o $(CFLAGS) -o $@ $(INC) $(LIB)
%:%.cpp
	$(CXX) $(CFLAGS) -o $@ $< $(INC) $(LIB) $(OBJS)
%:%.c
	$(CXX) $(CFLAGS) -o $@ $< $(INC) $(LIB)
%.o : %.cpp 
	$(CXX) $(INC) -c $(CXXFLAGS) $< -o	$@
clean:
	@rm -f *.o *.d $(TARGETS)

