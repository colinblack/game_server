# 新增时注意顺序，依赖关系
trunk_path = $(shell pwd | sed "s/\/baselib.*//")
include $(trunk_path)/make.rules
target = $(trunk_path)/baselib/lib/libsg17base.so
objs = $(trunk_path)/baselib/obj/*.o


dirs = markupstl \
	   base \
	   str4i \
	   htmltmpl \
	   commlog \
	   jsoncpp \
	   network \
	   ptlogin \
	   online_count \
	   dbc_ext 

.PHONY: all clean $(dirs)

all: $(dirs)
	$(CXX) $(CXXFLAGS) -shared -o $(target) $(objs)

clean: $(dirs)
	@rm $(target) $(objs)

$(dirs):
	$(MAKE) -j8 -C $@ $(MAKECMDGOALS)



