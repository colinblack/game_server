# Makefile公共规则定义
#
# I LIKE MAKEFILE

CC = gcc
CXX = g++
CFLAGS = -Wall -g 

#INC_MYSQL	:= -I/data/mysql/include/
#LIB_MYSQL	:= -L/data/mysql/lib/mysql/

INCLUDE = -I ../kernel/ -I../common/ -I../black/ -I ../../baselib/include/ 

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
