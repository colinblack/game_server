trunk_path = $(shell pwd | sed "s/\/app.*//")
include $(trunk_path)/app/applib.rules
INC = -I. $(BASE_INC) $(DBC_INC) $(KERNEL_INC) $(COMMON_INC)

TARGET_DIR_NAME=proto

include $(trunk_path)/app/applib.mk
