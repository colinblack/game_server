trunk_path = $(shell pwd | sed "s/\/access.*//")
include $(trunk_path)/make.rules

INC =   -I. $(BASE_INC) $(FCGI_INC) $(DBC_INC) $(PENGYOU_INC) $(PROTO_INC)
LIB	=   $(BASE_LIB) $(FCGI_LIB) $(DBC_LIB) $(PENGYOU_LIB) 

TARGETS = access 
CPPS = $(wildcard  ./*.cpp) 
OBJS = $(patsubst %.cpp, %.o, $(CPPS))
OBJS_FILTER = $(patsubst %.cpp, %.o, $(CPPS))
LIB_FILTER= $(filter-out ./main.o,$(OBJS_FILTER))

all: $(TARGETS)
$(TARGETS) : $(OBJS)
	$(CXX) $(OBJS_FILTER) $(CFLAGS) -o $@ $(INC) -Xlinker "-(" $(LIB) -Xlinker  "-)" -pthread -I/usr/local/include  -pthread -lprotobuf -lpthread  
%:%.cpp
	$(CXX) $(CFLAGS) -o $@ $< $(INC) $(LIB) $(OBJS)
%:%.c
	$(CXX) $(CFLAGS) -o $@ $< $(INC) $(LIB)
%.o : %.cpp 
	$(CXX) $(INC) -c $(CXXFLAGS) $< -o	$@
clean:
	@rm -f *.o *.d $(TARGETS) 
install:
#	cp -f $(TARGETS) /data/release/lh_kuroky/access/bin/kuroky_access


