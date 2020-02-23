# 查找当前目录下的所有源文件
# 并将名称保存到 DIR_LIB_SRCS 变量
cmake_minimum_required (VERSION 2.8) 

include_directories(/usr/include/openssl)
include_directories(/data/colin/fmh5_cmake/baselib/include)
include_directories(/data/colin/fmh5_cmake/outerlib/dbc/include/)
include_directories(/data/colin/fmh5_cmake/outerlib/pengyou/include)
include_directories(/data/colin/fmh5_cmake/save/)
include_directories(/data/colin/fmh5_cmake/app/pb/)
include_directories(/data/colin/fmh5_cmake/proto/)
#include_directories(../../app/common/)
#include_directories(../../app/kernel/)
#include_directories(../../app/config/)
include_directories(/data/colin/fmh5_cmake/cgiapp/common)
include_directories(/data/colin/fmh5_cmake/cgiapp/platform)
include_directories(/data/colin/fmh5_cmake/cgiapp/kernel)
include_directories(/data/colin/fmh5_cmake/cgiapp/data)
include_directories(/data/colin/fmh5_cmake/cgiapp/logic)

link_directories(/usr/lib64/openssl)
link_directories(/data/colin/fmh5_cmake/baselib/lib)
link_directories(/data/colin/fmh5_cmake/outerlib/dbc/lib/)
link_directories(/data/colin/fmh5_cmake/outerlib/pengyou/lib)
link_directories(/data/colin/fmh5_cmake/save)
#link_directories(/data/colin/fmh5_cmake/app/pb/)
link_directories(/data/colin/fmh5_cmake/proto)
#link_directories(../../app/common/)
#link_directories(../../app/kernel)
#link_directories(../../app/config/)
link_directories(/data/colin/fmh5_cmake/cgiapp/common)
link_directories(/data/colin/fmh5_cmake/cgiapp/platform)
link_directories(/data/colin/fmh5_cmake/cgiapp/kernel)
link_directories(/data/colin/fmh5_cmake/cgiapp/data)
link_directories(/data/colin/fmh5_cmake/cgiapp/logic)

link_libraries(sg17cgikernel)
link_libraries(sg17base)
link_libraries(sg17proto)
link_libraries(sg17cgicommon)
link_libraries(sg17cgiplatform)
link_libraries(sg17cgilogic)
link_libraries(sg17cgidata)
link_libraries(dbs-gcc-4.4)

file( GLOB APP_SOURCES RELATIVE "${CMAKE_CURRENT_SOURCE_DIR}" "${CMAKE_CURRENT_SOURCE_DIR}/*.cpp")
foreach(testsourcefile IN LISTS APP_SOURCES)
    # I used a simple string replace, to cut off .cpp.
    string( REPLACE ".cpp" "" testname ${testsourcefile} )
    add_executable( ${testname} ${testsourcefile} )
    # Make sure YourLib is linked to each app
    target_link_libraries( ${testname} pthread protobuf fcgi curl)
endforeach( testsourcefile ${APP_SOURCES} )

#aux_source_directory(. DIR_LIB_SRCS)
# 生成链接库
#add_library(sg17cgilogic  SHARED ${DIR_LIB_SRCS})
#target_link_libraries(libsg17cgicommon libsg17common libsg17kernel liblibsg17proto libsg17cgicommon)


