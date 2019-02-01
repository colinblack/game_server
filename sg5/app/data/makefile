trunk_path = $(shell pwd | sed "s/\/app.*//")
include $(trunk_path)/app/applib.rules

INC := $(INC) $(COMMON_INC) $(PLATFORM_INC) $(KERNEL_INC) $(LOGIC_INC)
LINK := $(LINK) $(COMMON_LIB) $(PLATFORM_LIB) $(KERNEL_LIB)  $(LOGIC_LIB)

TARGET_DIR_NAME=data

include $(trunk_path)/app/applib.mk
