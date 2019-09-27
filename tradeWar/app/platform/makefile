trunk_path = $(shell pwd | sed "s/\/app.*//")
include $(trunk_path)/app/applib.rules

INC := $(INC) $(COMMON_INC) $(KERNEL_INC)

TARGET_DIR_NAME=platform

include $(trunk_path)/app/applib.mk

