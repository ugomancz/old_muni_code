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
include CMakeFiles/g4_collect.dir/depend.make

# Include the progress variables for this target.
include CMakeFiles/g4_collect.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/g4_collect.dir/flags.make

CMakeFiles/g4_collect.dir/g4_collect.cpp.o: CMakeFiles/g4_collect.dir/flags.make
CMakeFiles/g4_collect.dir/g4_collect.cpp.o: ../g4_collect.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/cygdrive/c/git/pb161/10/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/g4_collect.dir/g4_collect.cpp.o"
	/usr/bin/c++.exe $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/g4_collect.dir/g4_collect.cpp.o -c /cygdrive/c/git/pb161/10/g4_collect.cpp

CMakeFiles/g4_collect.dir/g4_collect.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/g4_collect.dir/g4_collect.cpp.i"
	/usr/bin/c++.exe $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /cygdrive/c/git/pb161/10/g4_collect.cpp > CMakeFiles/g4_collect.dir/g4_collect.cpp.i

CMakeFiles/g4_collect.dir/g4_collect.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/g4_collect.dir/g4_collect.cpp.s"
	/usr/bin/c++.exe $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /cygdrive/c/git/pb161/10/g4_collect.cpp -o CMakeFiles/g4_collect.dir/g4_collect.cpp.s

# Object files for target g4_collect
g4_collect_OBJECTS = \
"CMakeFiles/g4_collect.dir/g4_collect.cpp.o"

# External object files for target g4_collect
g4_collect_EXTERNAL_OBJECTS =

g4_collect.exe: CMakeFiles/g4_collect.dir/g4_collect.cpp.o
g4_collect.exe: CMakeFiles/g4_collect.dir/build.make
g4_collect.exe: CMakeFiles/g4_collect.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/cygdrive/c/git/pb161/10/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking CXX executable g4_collect.exe"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/g4_collect.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/g4_collect.dir/build: g4_collect.exe

.PHONY : CMakeFiles/g4_collect.dir/build

CMakeFiles/g4_collect.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/g4_collect.dir/cmake_clean.cmake
.PHONY : CMakeFiles/g4_collect.dir/clean

CMakeFiles/g4_collect.dir/depend:
	cd /cygdrive/c/git/pb161/10/cmake-build-debug && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /cygdrive/c/git/pb161/10 /cygdrive/c/git/pb161/10 /cygdrive/c/git/pb161/10/cmake-build-debug /cygdrive/c/git/pb161/10/cmake-build-debug /cygdrive/c/git/pb161/10/cmake-build-debug/CMakeFiles/g4_collect.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/g4_collect.dir/depend

