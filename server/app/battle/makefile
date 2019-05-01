trunk_path = $(shell pwd | sed "s/\/app.*//")
include $(trunk_path)/app/applib.rules

INC := $(INC) $(COMMON_INC) $(KERNEL_INC) $(APP_PROTO_INC) $(DATA_INC)  $(CONFIG_INC) 
LINK := $(LINK) $(COMMON_LIB) $(KERNEL_LIB) $(APP_PROTO_LIB) $(DATA_LIB) $(CONFIG_LIB) 

TARGET_DIR_NAME=battle

include $(trunk_path)/app/applib.mk
