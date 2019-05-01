trunk_path = $(shell pwd | sed "s/\/outerlib.*//")

dirs = pengyou 

define do
	@for dir in $(dirs); do \
		make -j8 -C $$dir $1; \
	done
endef

all: 
	$(call do, $@)

clean:
	$(call do, $@) 
