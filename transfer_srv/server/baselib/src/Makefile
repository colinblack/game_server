# 新增时注意顺序，依赖关系
trunk_path = $(shell pwd | sed "s/\/baselib.*//")
include $(trunk_path)/make.rules


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

clean: $(dirs)

$(dirs):
	$(MAKE) -C $@ $(MAKECMDGOALS)



