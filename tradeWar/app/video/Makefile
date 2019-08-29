include ./Inc.mk

LDFLAGS=-g
LIBS= -L../../baselib/lib/  -lkfc -lz -lpthread -L../common/ -lcommon
EXE= zzfb_replay

#################################################################################

#OBJS	:= $(shell ls *.cpp *.c|sed 's/\.cpp/\.o/g'|sed 's/\.c/\.o/g')
OBJS	:= $(shell ls *.cpp|sed 's/\.cpp/\.o/g')

#################################################################################

all	: ${EXE}

${EXE}:${OBJS}
	${CXX} -o $@ $^ ${CFLAGS} ${LIBS}
	
##################################################################################

DEPS = $(patsubst %.o, .%.d, $(OBJS))
-include $(DEPS)

clean:
	rm  .*.d *.o $(EXE) -f
cleanall:
	rm *.o $(EXE) -f
	rm ./log/*.log -f
	rm ./log/day/*.log -f
install:
	cp -f $(EXE) /data/release/zzfb_server/bin/zzfb_replay
kuroky:
	cp -f $(EXE) /data/release/zzfb_kuroky/bin/zzfb_replay
