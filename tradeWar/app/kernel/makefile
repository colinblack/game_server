trunk_path = $(shell pwd | sed "s/\/app.*//")
include $(trunk_path)/app/applib.rules

INC := $(INC) $(COMMON_INC) $(LOGIC_INC) $(DATA_INC) $(PROTOCOL_INC) 

TARGET_DIR_NAME=kernel

include $(trunk_path)/app/applib.mk
