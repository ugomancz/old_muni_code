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
CMAKE_SOURCE_DIR = /mnt/c/git/pb161/12

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /mnt/c/git/pb161/12/cmake-build-debug

# Include any dependencies generated for this target.
include CMakeFiles/g1_chords.dir/depend.make
# Include the progress variables for this target.
include CMakeFiles/g1_chords.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/g1_chords.dir/flags.make

CMakeFiles/g1_chords.dir/g1_chords.cpp.o: CMakeFiles/g1_chords.dir/flags.make
CMakeFiles/g1_chords.dir/g1_chords.cpp.o: ../g1_chords.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/mnt/c/git/pb161/12/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/g1_chords.dir/g1_chords.cpp.o"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/g1_chords.dir/g1_chords.cpp.o -c /mnt/c/git/pb161/12/g1_chords.cpp

CMakeFiles/g1_chords.dir/g1_chords.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/g1_chords.dir/g1_chords.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /mnt/c/git/pb161/12/g1_chords.cpp > CMakeFiles/g1_chords.dir/g1_chords.cpp.i

CMakeFiles/g1_chords.dir/g1_chords.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/g1_chords.dir/g1_chords.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /mnt/c/git/pb161/12/g1_chords.cpp -o CMakeFiles/g1_chords.dir/g1_chords.cpp.s

# Object files for target g1_chords
g1_chords_OBJECTS = \
"CMakeFiles/g1_chords.dir/g1_chords.cpp.o"

# External object files for target g1_chords
g1_chords_EXTERNAL_OBJECTS =

g1_chords: CMakeFiles/g1_chords.dir/g1_chords.cpp.o
g1_chords: CMakeFiles/g1_chords.dir/build.make
g1_chords: CMakeFiles/g1_chords.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/mnt/c/git/pb161/12/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking CXX executable g1_chords"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/g1_chords.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/g1_chords.dir/build: g1_chords
.PHONY : CMakeFiles/g1_chords.dir/build

CMakeFiles/g1_chords.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/g1_chords.dir/cmake_clean.cmake
.PHONY : CMakeFiles/g1_chords.dir/clean

CMakeFiles/g1_chords.dir/depend:
	cd /mnt/c/git/pb161/12/cmake-build-debug && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /mnt/c/git/pb161/12 /mnt/c/git/pb161/12 /mnt/c/git/pb161/12/cmake-build-debug /mnt/c/git/pb161/12/cmake-build-debug /mnt/c/git/pb161/12/cmake-build-debug/CMakeFiles/g1_chords.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/g1_chords.dir/depend

