# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.14

# Delete rule output on recipe failure.
.DELETE_ON_ERROR:


#=============================================================================
# Special targets provided by cmake.

# Disable implicit rules so canonical targets will work.
.SUFFIXES:


# Remove some rules from gmake that .SUFFIXES does not remove.
SUFFIXES =

.SUFFIXES: .hpux_make_needs_suffix_list


# Suppress display of executed commands.
$(VERBOSE).SILENT:


# A target that is always out of date.
cmake_force:

.PHONY : cmake_force

#=============================================================================
# Set environment variables for the build.

# The shell in which to execute make rules.
SHELL = /bin/sh

# The CMake executable.
CMAKE_COMMAND = /usr/bin/cmake

# The command to remove a file.
RM = /usr/bin/cmake -E remove -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /data/colin/fmh5_cmake

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /data/colin/fmh5_cmake/cmake-build-debug

# Include any dependencies generated for this target.
include cgiapp/cgi/CMakeFiles/CgiOPPOPay.dir/depend.make

# Include the progress variables for this target.
include cgiapp/cgi/CMakeFiles/CgiOPPOPay.dir/progress.make

# Include the compile flags for this target's objects.
include cgiapp/cgi/CMakeFiles/CgiOPPOPay.dir/flags.make

cgiapp/cgi/CMakeFiles/CgiOPPOPay.dir/CgiOPPOPay.cpp.o: cgiapp/cgi/CMakeFiles/CgiOPPOPay.dir/flags.make
cgiapp/cgi/CMakeFiles/CgiOPPOPay.dir/CgiOPPOPay.cpp.o: ../cgiapp/cgi/CgiOPPOPay.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/data/colin/fmh5_cmake/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object cgiapp/cgi/CMakeFiles/CgiOPPOPay.dir/CgiOPPOPay.cpp.o"
	cd /data/colin/fmh5_cmake/cmake-build-debug/cgiapp/cgi && /usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/CgiOPPOPay.dir/CgiOPPOPay.cpp.o -c /data/colin/fmh5_cmake/cgiapp/cgi/CgiOPPOPay.cpp

cgiapp/cgi/CMakeFiles/CgiOPPOPay.dir/CgiOPPOPay.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/CgiOPPOPay.dir/CgiOPPOPay.cpp.i"
	cd /data/colin/fmh5_cmake/cmake-build-debug/cgiapp/cgi && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /data/colin/fmh5_cmake/cgiapp/cgi/CgiOPPOPay.cpp > CMakeFiles/CgiOPPOPay.dir/CgiOPPOPay.cpp.i

cgiapp/cgi/CMakeFiles/CgiOPPOPay.dir/CgiOPPOPay.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/CgiOPPOPay.dir/CgiOPPOPay.cpp.s"
	cd /data/colin/fmh5_cmake/cmake-build-debug/cgiapp/cgi && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /data/colin/fmh5_cmake/cgiapp/cgi/CgiOPPOPay.cpp -o CMakeFiles/CgiOPPOPay.dir/CgiOPPOPay.cpp.s

# Object files for target CgiOPPOPay
CgiOPPOPay_OBJECTS = \
"CMakeFiles/CgiOPPOPay.dir/CgiOPPOPay.cpp.o"

# External object files for target CgiOPPOPay
CgiOPPOPay_EXTERNAL_OBJECTS =

cgiapp/cgi/CgiOPPOPay: cgiapp/cgi/CMakeFiles/CgiOPPOPay.dir/CgiOPPOPay.cpp.o
cgiapp/cgi/CgiOPPOPay: cgiapp/cgi/CMakeFiles/CgiOPPOPay.dir/build.make
cgiapp/cgi/CgiOPPOPay: cgiapp/logic/libsg17cgilogic.so
cgiapp/cgi/CgiOPPOPay: cgiapp/data/libsg17cgidata.so
cgiapp/cgi/CgiOPPOPay: cgiapp/platform/libsg17cgiplatform.so
cgiapp/cgi/CgiOPPOPay: cgiapp/kernel/libsg17cgikernel.so
cgiapp/cgi/CgiOPPOPay: cgiapp/common/libsg17cgicommon.so
cgiapp/cgi/CgiOPPOPay: proto/libsg17proto.so
cgiapp/cgi/CgiOPPOPay: save/libsg17save.so
cgiapp/cgi/CgiOPPOPay: cgiapp/cgi/CMakeFiles/CgiOPPOPay.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/data/colin/fmh5_cmake/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking CXX executable CgiOPPOPay"
	cd /data/colin/fmh5_cmake/cmake-build-debug/cgiapp/cgi && $(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/CgiOPPOPay.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
cgiapp/cgi/CMakeFiles/CgiOPPOPay.dir/build: cgiapp/cgi/CgiOPPOPay

.PHONY : cgiapp/cgi/CMakeFiles/CgiOPPOPay.dir/build

cgiapp/cgi/CMakeFiles/CgiOPPOPay.dir/clean:
	cd /data/colin/fmh5_cmake/cmake-build-debug/cgiapp/cgi && $(CMAKE_COMMAND) -P CMakeFiles/CgiOPPOPay.dir/cmake_clean.cmake
.PHONY : cgiapp/cgi/CMakeFiles/CgiOPPOPay.dir/clean

cgiapp/cgi/CMakeFiles/CgiOPPOPay.dir/depend:
	cd /data/colin/fmh5_cmake/cmake-build-debug && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /data/colin/fmh5_cmake /data/colin/fmh5_cmake/cgiapp/cgi /data/colin/fmh5_cmake/cmake-build-debug /data/colin/fmh5_cmake/cmake-build-debug/cgiapp/cgi /data/colin/fmh5_cmake/cmake-build-debug/cgiapp/cgi/CMakeFiles/CgiOPPOPay.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : cgiapp/cgi/CMakeFiles/CgiOPPOPay.dir/depend

