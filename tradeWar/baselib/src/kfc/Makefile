include ./Inc.mk

LIB= ../../lib/libkfc.so
LIBA= ../../lib/libkfc.a

#################################################################################

#OBJS	:= $(shell ls *.cpp *.c|sed 's/\.cpp/\.o/g'|sed 's/\.c/\.o/g')
OBJS	:= $(shell ls *.cpp|sed 's/\.cpp/\.o/g')

#################################################################################

all	: ${LIBA}

$(LIB): $(OBJS)
	rm -f $(LIB)
	$(CC) -shared -o $@ $^

$(LIBA): $(OBJS)
	rm -f $(LIBA)
	ar q $@ $^

DEPS = $(patsubst %.o, .%.d, $(OBJS))
-include $(DEPS)

clean:
	rm  .*.d *.o ${LIB} ${LIBA} -f

install:
