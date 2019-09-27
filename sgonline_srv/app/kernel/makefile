trunk_path = $(shell pwd | sed "s/\/app.*//")
include $(trunk_path)/app/applib.rules

INC := $(INC) $(COMMON_INC) $(PLATFORM_INC) $(DATA_INC) $(LOGIC_INC)
LINK := $(LINK) $(COMMON_LIB)

TARGET_DIR_NAME=kernel

include $(trunk_path)/app/applib.mk
