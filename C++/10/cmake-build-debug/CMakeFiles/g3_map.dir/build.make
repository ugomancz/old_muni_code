# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.19

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
CMAKE_COMMAND = /cygdrive/c/Users/ondra/AppData/Local/JetBrains/CLion2021.1/cygwin_cmake/bin/cmake.exe

# The command to remove a file.
RM = /cygdrive/c/Users/ondra/AppData/Local/JetBrains/CLion2021.1/cygwin_cmake/bin/cmake.exe -E rm -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /cygdrive/c/git/pb161/10

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /cygdrive/c/git/pb161/10/cmake-build-debug

# Include any dependencies generated for this target.
include CMakeFiles/g3_map.dir/depend.make

# Include the progress variables for this target.
include CMakeFiles/g3_map.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/g3_map.dir/flags.make

CMakeFiles/g3_map.dir/g3_map.cpp.o: CMakeFiles/g3_map.dir/flags.make
CMakeFiles/g3_map.dir/g3_map.cpp.o: ../g3_map.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/cygdrive/c/git/pb161/10/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/g3_map.dir/g3_map.cpp.o"
	/usr/bin/c++.exe $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/g3_map.dir/g3_map.cpp.o -c /cygdrive/c/git/pb161/10/g3_map.cpp

CMakeFiles/g3_map.dir/g3_map.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/g3_map.dir/g3_map.cpp.i"
	/usr/bin/c++.exe $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /cygdrive/c/git/pb161/10/g3_map.cpp > CMakeFiles/g3_map.dir/g3_map.cpp.i

CMakeFiles/g3_map.dir/g3_map.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/g3_map.dir/g3_map.cpp.s"
	/usr/bin/c++.exe $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /cygdrive/c/git/pb161/10/g3_map.cpp -o CMakeFiles/g3_map.dir/g3_map.cpp.s

# Object files for target g3_map
g3_map_OBJECTS = \
"CMakeFiles/g3_map.dir/g3_map.cpp.o"

# External object files for target g3_map
g3_map_EXTERNAL_OBJECTS =

g3_map.exe: CMakeFiles/g3_map.dir/g3_map.cpp.o
g3_map.exe: CMakeFiles/g3_map.dir/build.make
g3_map.exe: CMakeFiles/g3_map.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/cygdrive/c/git/pb161/10/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking CXX executable g3_map.exe"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/g3_map.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/g3_map.dir/build: g3_map.exe

.PHONY : CMakeFiles/g3_map.dir/build

CMakeFiles/g3_map.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/g3_map.dir/cmake_clean.cmake
.PHONY : CMakeFiles/g3_map.dir/clean

CMakeFiles/g3_map.dir/depend:
	cd /cygdrive/c/git/pb161/10/cmake-build-debug && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /cygdrive/c/git/pb161/10 /cygdrive/c/git/pb161/10 /cygdrive/c/git/pb161/10/cmake-build-debug /cygdrive/c/git/pb161/10/cmake-build-debug /cygdrive/c/git/pb161/10/cmake-build-debug/CMakeFiles/g3_map.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/g3_map.dir/depend

