# Makefile公共规则定义
#
# I LIKE MAKEFILE

CC = gcc
CXX = g++
CFLAGS = -Wall -g 

MYSQL		:= /usr/include/mysql/
INC_MYSQL	:= -I$(MYSQL)/
LIB_MYSQL	:= -L$(MYSQL)/lib/

INCLUDE = -I../../include/ $(INC_MYSQL)

# 自动计算文件的依赖关系
.%.d: %.cpp
	$(CC) $(INCLUDE) -MM $< > $@
	@$(CC) $(INCLUDE) -MM $< | sed s/"^"/"\."/  |  sed s/"^\. "/" "/  | \
	sed s/"\.o"/"\.d"/  >> $@
%.o: %.cpp
	$(CXX) $(CFLAGS) $(INCLUDE) -c $<

.%.d: %.c
	$(CC) $(INCLUDE) -MM $< > $@
	@$(CC) $(INCLUDE) -MM $< | sed s/"^"/"\."/  |  sed s/"^\. "/" "/  | \
	sed s/"\.o"/"\.d"/  >> $@
%.o: %.c
	$(CC) $(CFLAGS) $(INCLUDE) -c $<
