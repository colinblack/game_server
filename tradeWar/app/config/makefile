trunk_path = $(shell pwd | sed "s/\/app.*//")
include $(trunk_path)/app/applib.rules

INC = -I.  $(BASE_INC) $(FCGI_INC) $(DBC_INC) $(PENGYOU_INC) $(ROCKPAY_INC) $(KERNEL_INC) $(COMMON_INC)

TARGET_DIR_NAME = config

include $(trunk_path)/app/applib.mk
