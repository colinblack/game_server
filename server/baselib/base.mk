CUR_PATH = $(trunk_path)/baselib/src/$(TARGET_DIR_NAME)
SRCS = $(shell find $(CUR_PATH) -name "*.cpp" | sed "s/\/.*$(TARGET_DIR_NAME)\///g")
BIN  = $(LIB_DIR)lib$(TARGET_DIR_NAME).a 


all:$(BIN) install 
$(BIN): $(SRCS:.cpp=.o) 
#	$(AR) -r $@ $^
	cp -f ./*.o $(OBJ_DIR)

%.o: %.c makefile
	$(CC) $(CFLAGS) $(INC) -c -o $@ $<
	@-mv -f $*.d .dep.$@
%.o: %.cc makefile
	$(CXX) $(CXXFLAGS) $(INC) -c -o $@ $<
	@-mv -f $*.d .dep.$@
%.o: %.cpp makefile
#	@echo $(CFLAGS)
	$(CXX) $(CXXFLAGS) $(INC) -c -o $@ $<
	@-mv -f $*.d .dep.$@
install:  $(TARGET_HEADERS)

$(H_DIR)/%.h : %.h
	cp $< $@

clean:
	rm -f *.o .po *.so *.d .dep.* $(BIN)
	sh ../clean_h.sh
-include /dev/null $(wildcard .dep.*) 

test:
	echo $(trunk_path)
