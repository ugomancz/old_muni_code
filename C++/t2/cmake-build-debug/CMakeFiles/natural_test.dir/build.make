# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.20

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
CMAKE_SOURCE_DIR = /mnt/c/git/pb161/t2

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /mnt/c/git/pb161/t2/cmake-build-debug

# Include any dependencies generated for this target.
include CMakeFiles/natural_test.dir/depend.make
# Include the progress variables for this target.
include CMakeFiles/natural_test.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/natural_test.dir/flags.make

CMakeFiles/natural_test.dir/natural_test.cpp.o: CMakeFiles/natural_test.dir/flags.make
CMakeFiles/natural_test.dir/natural_test.cpp.o: ../natural_test.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/mnt/c/git/pb161/t2/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/natural_test.dir/natural_test.cpp.o"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/natural_test.dir/natural_test.cpp.o -c /mnt/c/git/pb161/t2/natural_test.cpp

CMakeFiles/natural_test.dir/natural_test.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/natural_test.dir/natural_test.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /mnt/c/git/pb161/t2/natural_test.cpp > CMakeFiles/natural_test.dir/natural_test.cpp.i

CMakeFiles/natural_test.dir/natural_test.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/natural_test.dir/natural_test.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /mnt/c/git/pb161/t2/natural_test.cpp -o CMakeFiles/natural_test.dir/natural_test.cpp.s

# Object files for target natural_test
natural_test_OBJECTS = \
"CMakeFiles/natural_test.dir/natural_test.cpp.o"

# External object files for target natural_test
natural_test_EXTERNAL_OBJECTS =

natural_test: CMakeFiles/natural_test.dir/natural_test.cpp.o
natural_test: CMakeFiles/natural_test.dir/build.make
natural_test: CMakeFiles/natural_test.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/mnt/c/git/pb161/t2/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking CXX executable natural_test"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/natural_test.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/natural_test.dir/build: natural_test
.PHONY : CMakeFiles/natural_test.dir/build

CMakeFiles/natural_test.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/natural_test.dir/cmake_clean.cmake
.PHONY : CMakeFiles/natural_test.dir/clean

CMakeFiles/natural_test.dir/depend:
	cd /mnt/c/git/pb161/t2/cmake-build-debug && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /mnt/c/git/pb161/t2 /mnt/c/git/pb161/t2 /mnt/c/git/pb161/t2/cmake-build-debug /mnt/c/git/pb161/t2/cmake-build-debug /mnt/c/git/pb161/t2/cmake-build-debug/CMakeFiles/natural_test.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/natural_test.dir/depend

