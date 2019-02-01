CUR_PATH = $(trunk_path)/app/$(TARGET_DIR_NAME)
CPPS = $(wildcard $(CUR_PATH)/*.cpp )
OBJS = $(patsubst $(CUR_PATH)/%.cpp, ./%.o, $(CPPS))
TARGET = lib$(TARGET_DIR_NAME).a

all	: $(TARGET) 

clean : 
	rm -f $(TARGET) *.o

$(TARGET) : $(OBJS)
	$(AR) rc $(TARGET) $?

%.o : $(CUR_PATH)/%.cpp 
	$(CXX) $(INC) -c $(CXXFLAGS) $< -o	$@
