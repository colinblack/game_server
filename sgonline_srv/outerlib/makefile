trunk_path = $(shell pwd | sed "s/\/outerlib.*//")

dirs = pengyou escape #sha1

define do
	@for dir in $(dirs); do \
		make -C $$dir $1; \
	done
endef

all: 
	$(call do, $@)

clean:
	$(call do, $@) 
