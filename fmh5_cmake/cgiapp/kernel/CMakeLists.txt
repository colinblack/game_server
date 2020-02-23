# 查找当前目录下的所有源文件
# 并将名称保存到 DIR_LIB_SRCS 变量
cmake_minimum_required (VERSION 2.8) 

include_directories(/usr/include/openssl)
include_directories(/data/colin/fmh5_cmake/baselib/include)
include_directories(/data/colin/fmh5_cmake/outerlib/dbc/include/)
include_directories(/data/colin/fmh5_cmake/outerlib/pengyou/include)
include_directories(/data/colin/fmh5_cmake/save/)
#include_directories(../../app/pb/)
include_directories(/data/colin/fmh5_cmake/proto/)
#include_directories(../../app/common/)
#include_directories(../../app/kernel/)
#include_directories(../../app/config/)
include_directories(/data/colin/fmh5_cmake/cgiapp/common)
include_directories(/data/colin/fmh5_cmake/cgiapp/kernel)
include_directories(/data/colin/fmh5_cmake/cgiapp/platform)

link_directories(/usr/lib64/openssl)
link_directories(/data/colin/fmh5_cmake/baselib/lib)
link_directories(/data/colin/fmh5_cmake/outerlib/dbc/lib/)
link_directories(/data/colin/fmh5_cmake/outerlib/pengyou/lib)
link_directories(/data/colin/fmh5_cmake/save)
#link_directories(../../app/pb/)
link_directories(/data/colin/fmh5_cmake/proto)
#link_directories(../../app/common/)
#link_directories(../../app/kernel)
#link_directories(../../app/config/)
link_directories(/data/colin/fmh5_cmake/cgiapp/common)
link_directories(/data/colin/fmh5_cmake/cgiapp/kernel)
link_directories(/data/colin/fmh5_cmake/cgiapp/platform)


link_libraries(sg17base)
link_libraries(sg17proto)
link_libraries(sg17save)
link_libraries(dbs-gcc-4.4)
link_libraries(fcgi++)
link_libraries(fcgi)
link_libraries(nsl)
link_libraries(ssl)
link_libraries(sg17openapi)
link_libraries(curl)
link_libraries(z)
link_libraries(dl)
link_libraries(sg17cgicommon)
link_libraries(sg17cgikernel)

aux_source_directory(. DIR_LIB_SRCS)
# 生成链接库
add_library(sg17cgikernel SHARED ${DIR_LIB_SRCS})
#target_link_libraries(libsg17cgicommon libsg17common libsg17kernel liblibsg17proto libsg17cgicommon)


