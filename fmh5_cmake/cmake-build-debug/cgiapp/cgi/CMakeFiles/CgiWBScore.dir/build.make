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
include cgiapp/cgi/CMakeFiles/CgiWBScore.dir/depend.make

# Include the progress variables for this target.
include cgiapp/cgi/CMakeFiles/CgiWBScore.dir/progress.make

# Include the compile flags for this target's objects.
include cgiapp/cgi/CMakeFiles/CgiWBScore.dir/flags.make

cgiapp/cgi/CMakeFiles/CgiWBScore.dir/CgiWBScore.cpp.o: cgiapp/cgi/CMakeFiles/CgiWBScore.dir/flags.make
cgiapp/cgi/CMakeFiles/CgiWBScore.dir/CgiWBScore.cpp.o: ../cgiapp/cgi/CgiWBScore.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/data/colin/fmh5_cmake/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object cgiapp/cgi/CMakeFiles/CgiWBScore.dir/CgiWBScore.cpp.o"
	cd /data/colin/fmh5_cmake/cmake-build-debug/cgiapp/cgi && /usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/CgiWBScore.dir/CgiWBScore.cpp.o -c /data/colin/fmh5_cmake/cgiapp/cgi/CgiWBScore.cpp

cgiapp/cgi/CMakeFiles/CgiWBScore.dir/CgiWBScore.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/CgiWBScore.dir/CgiWBScore.cpp.i"
	cd /data/colin/fmh5_cmake/cmake-build-debug/cgiapp/cgi && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /data/colin/fmh5_cmake/cgiapp/cgi/CgiWBScore.cpp > CMakeFiles/CgiWBScore.dir/CgiWBScore.cpp.i

cgiapp/cgi/CMakeFiles/CgiWBScore.dir/CgiWBScore.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/CgiWBScore.dir/CgiWBScore.cpp.s"
	cd /data/colin/fmh5_cmake/cmake-build-debug/cgiapp/cgi && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /data/colin/fmh5_cmake/cgiapp/cgi/CgiWBScore.cpp -o CMakeFiles/CgiWBScore.dir/CgiWBScore.cpp.s

# Object files for target CgiWBScore
CgiWBScore_OBJECTS = \
"CMakeFiles/CgiWBScore.dir/CgiWBScore.cpp.o"

# External object files for target CgiWBScore
CgiWBScore_EXTERNAL_OBJECTS =

cgiapp/cgi/CgiWBScore: cgiapp/cgi/CMakeFiles/CgiWBScore.dir/CgiWBScore.cpp.o
cgiapp/cgi/CgiWBScore: cgiapp/cgi/CMakeFiles/CgiWBScore.dir/build.make
cgiapp/cgi/CgiWBScore: cgiapp/logic/libsg17cgilogic.so
cgiapp/cgi/CgiWBScore: cgiapp/data/libsg17cgidata.so
cgiapp/cgi/CgiWBScore: cgiapp/platform/libsg17cgiplatform.so
cgiapp/cgi/CgiWBScore: cgiapp/kernel/libsg17cgikernel.so
cgiapp/cgi/CgiWBScore: cgiapp/common/libsg17cgicommon.so
cgiapp/cgi/CgiWBScore: proto/libsg17proto.so
cgiapp/cgi/CgiWBScore: save/libsg17save.so
cgiapp/cgi/CgiWBScore: cgiapp/cgi/CMakeFiles/CgiWBScore.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/data/colin/fmh5_cmake/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking CXX executable CgiWBScore"
	cd /data/colin/fmh5_cmake/cmake-build-debug/cgiapp/cgi && $(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/CgiWBScore.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
cgiapp/cgi/CMakeFiles/CgiWBScore.dir/build: cgiapp/cgi/CgiWBScore

.PHONY : cgiapp/cgi/CMakeFiles/CgiWBScore.dir/build

cgiapp/cgi/CMakeFiles/CgiWBScore.dir/clean:
	cd /data/colin/fmh5_cmake/cmake-build-debug/cgiapp/cgi && $(CMAKE_COMMAND) -P CMakeFiles/CgiWBScore.dir/cmake_clean.cmake
.PHONY : cgiapp/cgi/CMakeFiles/CgiWBScore.dir/clean

cgiapp/cgi/CMakeFiles/CgiWBScore.dir/depend:
	cd /data/colin/fmh5_cmake/cmake-build-debug && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /data/colin/fmh5_cmake /data/colin/fmh5_cmake/cgiapp/cgi /data/colin/fmh5_cmake/cmake-build-debug /data/colin/fmh5_cmake/cmake-build-debug/cgiapp/cgi /data/colin/fmh5_cmake/cmake-build-debug/cgiapp/cgi/CMakeFiles/CgiWBScore.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : cgiapp/cgi/CMakeFiles/CgiWBScore.dir/depend

