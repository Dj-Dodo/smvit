# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.25

# Delete rule output on recipe failure.
.DELETE_ON_ERROR:

#=============================================================================
# Special targets provided by cmake.

# Disable implicit rules so canonical targets will work.
.SUFFIXES:

# Disable VCS-based implicit rules.
% : %,v

# Disable VCS-based implicit rules.
% : RCS/%

# Disable VCS-based implicit rules.
% : RCS/%,v

# Disable VCS-based implicit rules.
% : SCCS/s.%

# Disable VCS-based implicit rules.
% : s.%

.SUFFIXES: .hpux_make_needs_suffix_list

# Command-line flag to silence nested $(MAKE).
$(VERBOSE)MAKESILENT = -s

#Suppress display of executed commands.
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
RM = /usr/bin/cmake -E rm -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /tmp/tmp.TgoBxITzr5

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /tmp/tmp.TgoBxITzr5/cmake-build-debug-raspberry

# Include any dependencies generated for this target.
include CMakeFiles/dht11_reader_cpp.dir/depend.make
# Include any dependencies generated by the compiler for this target.
include CMakeFiles/dht11_reader_cpp.dir/compiler_depend.make

# Include the progress variables for this target.
include CMakeFiles/dht11_reader_cpp.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/dht11_reader_cpp.dir/flags.make

CMakeFiles/dht11_reader_cpp.dir/main.cpp.o: CMakeFiles/dht11_reader_cpp.dir/flags.make
CMakeFiles/dht11_reader_cpp.dir/main.cpp.o: /tmp/tmp.TgoBxITzr5/main.cpp
CMakeFiles/dht11_reader_cpp.dir/main.cpp.o: CMakeFiles/dht11_reader_cpp.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/tmp/tmp.TgoBxITzr5/cmake-build-debug-raspberry/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/dht11_reader_cpp.dir/main.cpp.o"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/dht11_reader_cpp.dir/main.cpp.o -MF CMakeFiles/dht11_reader_cpp.dir/main.cpp.o.d -o CMakeFiles/dht11_reader_cpp.dir/main.cpp.o -c /tmp/tmp.TgoBxITzr5/main.cpp

CMakeFiles/dht11_reader_cpp.dir/main.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/dht11_reader_cpp.dir/main.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /tmp/tmp.TgoBxITzr5/main.cpp > CMakeFiles/dht11_reader_cpp.dir/main.cpp.i

CMakeFiles/dht11_reader_cpp.dir/main.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/dht11_reader_cpp.dir/main.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /tmp/tmp.TgoBxITzr5/main.cpp -o CMakeFiles/dht11_reader_cpp.dir/main.cpp.s

# Object files for target dht11_reader_cpp
dht11_reader_cpp_OBJECTS = \
"CMakeFiles/dht11_reader_cpp.dir/main.cpp.o"

# External object files for target dht11_reader_cpp
dht11_reader_cpp_EXTERNAL_OBJECTS =

dht11_reader_cpp: CMakeFiles/dht11_reader_cpp.dir/main.cpp.o
dht11_reader_cpp: CMakeFiles/dht11_reader_cpp.dir/build.make
dht11_reader_cpp: CMakeFiles/dht11_reader_cpp.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/tmp/tmp.TgoBxITzr5/cmake-build-debug-raspberry/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking CXX executable dht11_reader_cpp"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/dht11_reader_cpp.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/dht11_reader_cpp.dir/build: dht11_reader_cpp
.PHONY : CMakeFiles/dht11_reader_cpp.dir/build

CMakeFiles/dht11_reader_cpp.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/dht11_reader_cpp.dir/cmake_clean.cmake
.PHONY : CMakeFiles/dht11_reader_cpp.dir/clean

CMakeFiles/dht11_reader_cpp.dir/depend:
	cd /tmp/tmp.TgoBxITzr5/cmake-build-debug-raspberry && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /tmp/tmp.TgoBxITzr5 /tmp/tmp.TgoBxITzr5 /tmp/tmp.TgoBxITzr5/cmake-build-debug-raspberry /tmp/tmp.TgoBxITzr5/cmake-build-debug-raspberry /tmp/tmp.TgoBxITzr5/cmake-build-debug-raspberry/CMakeFiles/dht11_reader_cpp.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/dht11_reader_cpp.dir/depend

