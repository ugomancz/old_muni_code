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
CMAKE_SOURCE_DIR = /mnt/c/git/pb161/05

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /mnt/c/git/pb161/05/cmake-build-debug

# Include any dependencies generated for this target.
include CMakeFiles/g5_grep.dir/depend.make
# Include the progress variables for this target.
include CMakeFiles/g5_grep.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/g5_grep.dir/flags.make

CMakeFiles/g5_grep.dir/g5_grep.cpp.o: CMakeFiles/g5_grep.dir/flags.make
CMakeFiles/g5_grep.dir/g5_grep.cpp.o: ../g5_grep.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/mnt/c/git/pb161/05/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/g5_grep.dir/g5_grep.cpp.o"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/g5_grep.dir/g5_grep.cpp.o -c /mnt/c/git/pb161/05/g5_grep.cpp

CMakeFiles/g5_grep.dir/g5_grep.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/g5_grep.dir/g5_grep.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /mnt/c/git/pb161/05/g5_grep.cpp > CMakeFiles/g5_grep.dir/g5_grep.cpp.i

CMakeFiles/g5_grep.dir/g5_grep.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/g5_grep.dir/g5_grep.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /mnt/c/git/pb161/05/g5_grep.cpp -o CMakeFiles/g5_grep.dir/g5_grep.cpp.s

# Object files for target g5_grep
g5_grep_OBJECTS = \
"CMakeFiles/g5_grep.dir/g5_grep.cpp.o"

# External object files for target g5_grep
g5_grep_EXTERNAL_OBJECTS =

g5_grep: CMakeFiles/g5_grep.dir/g5_grep.cpp.o
g5_grep: CMakeFiles/g5_grep.dir/build.make
g5_grep: CMakeFiles/g5_grep.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/mnt/c/git/pb161/05/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking CXX executable g5_grep"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/g5_grep.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/g5_grep.dir/build: g5_grep
.PHONY : CMakeFiles/g5_grep.dir/build

CMakeFiles/g5_grep.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/g5_grep.dir/cmake_clean.cmake
.PHONY : CMakeFiles/g5_grep.dir/clean

CMakeFiles/g5_grep.dir/depend:
	cd /mnt/c/git/pb161/05/cmake-build-debug && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /mnt/c/git/pb161/05 /mnt/c/git/pb161/05 /mnt/c/git/pb161/05/cmake-build-debug /mnt/c/git/pb161/05/cmake-build-debug /mnt/c/git/pb161/05/cmake-build-debug/CMakeFiles/g5_grep.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/g5_grep.dir/depend

