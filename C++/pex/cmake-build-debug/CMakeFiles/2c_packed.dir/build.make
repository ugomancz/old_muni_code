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
CMAKE_SOURCE_DIR = /mnt/c/git/pb161/pex

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /mnt/c/git/pb161/pex/cmake-build-debug

# Include any dependencies generated for this target.
include CMakeFiles/2c_packed.dir/depend.make
# Include the progress variables for this target.
include CMakeFiles/2c_packed.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/2c_packed.dir/flags.make

CMakeFiles/2c_packed.dir/2c_packed.cpp.o: CMakeFiles/2c_packed.dir/flags.make
CMakeFiles/2c_packed.dir/2c_packed.cpp.o: ../2c_packed.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/mnt/c/git/pb161/pex/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/2c_packed.dir/2c_packed.cpp.o"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/2c_packed.dir/2c_packed.cpp.o -c /mnt/c/git/pb161/pex/2c_packed.cpp

CMakeFiles/2c_packed.dir/2c_packed.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/2c_packed.dir/2c_packed.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /mnt/c/git/pb161/pex/2c_packed.cpp > CMakeFiles/2c_packed.dir/2c_packed.cpp.i

CMakeFiles/2c_packed.dir/2c_packed.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/2c_packed.dir/2c_packed.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /mnt/c/git/pb161/pex/2c_packed.cpp -o CMakeFiles/2c_packed.dir/2c_packed.cpp.s

# Object files for target 2c_packed
2c_packed_OBJECTS = \
"CMakeFiles/2c_packed.dir/2c_packed.cpp.o"

# External object files for target 2c_packed
2c_packed_EXTERNAL_OBJECTS =

2c_packed: CMakeFiles/2c_packed.dir/2c_packed.cpp.o
2c_packed: CMakeFiles/2c_packed.dir/build.make
2c_packed: CMakeFiles/2c_packed.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/mnt/c/git/pb161/pex/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking CXX executable 2c_packed"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/2c_packed.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/2c_packed.dir/build: 2c_packed
.PHONY : CMakeFiles/2c_packed.dir/build

CMakeFiles/2c_packed.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/2c_packed.dir/cmake_clean.cmake
.PHONY : CMakeFiles/2c_packed.dir/clean

CMakeFiles/2c_packed.dir/depend:
	cd /mnt/c/git/pb161/pex/cmake-build-debug && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /mnt/c/git/pb161/pex /mnt/c/git/pb161/pex /mnt/c/git/pb161/pex/cmake-build-debug /mnt/c/git/pb161/pex/cmake-build-debug /mnt/c/git/pb161/pex/cmake-build-debug/CMakeFiles/2c_packed.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/2c_packed.dir/depend

