# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.17

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
CMAKE_COMMAND = /cygdrive/c/Users/ondra/AppData/Local/JetBrains/CLion2020.3/cygwin_cmake/bin/cmake.exe

# The command to remove a file.
RM = /cygdrive/c/Users/ondra/AppData/Local/JetBrains/CLion2020.3/cygwin_cmake/bin/cmake.exe -E rm -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /cygdrive/c/git/pb161/04

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /cygdrive/c/git/pb161/04/cmake-build-debug

# Include any dependencies generated for this target.
include CMakeFiles/g6_eval.dir/depend.make

# Include the progress variables for this target.
include CMakeFiles/g6_eval.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/g6_eval.dir/flags.make

CMakeFiles/g6_eval.dir/g6_eval.cpp.o: CMakeFiles/g6_eval.dir/flags.make
CMakeFiles/g6_eval.dir/g6_eval.cpp.o: ../g6_eval.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/cygdrive/c/git/pb161/04/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/g6_eval.dir/g6_eval.cpp.o"
	/usr/bin/c++.exe  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/g6_eval.dir/g6_eval.cpp.o -c /cygdrive/c/git/pb161/04/g6_eval.cpp

CMakeFiles/g6_eval.dir/g6_eval.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/g6_eval.dir/g6_eval.cpp.i"
	/usr/bin/c++.exe $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /cygdrive/c/git/pb161/04/g6_eval.cpp > CMakeFiles/g6_eval.dir/g6_eval.cpp.i

CMakeFiles/g6_eval.dir/g6_eval.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/g6_eval.dir/g6_eval.cpp.s"
	/usr/bin/c++.exe $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /cygdrive/c/git/pb161/04/g6_eval.cpp -o CMakeFiles/g6_eval.dir/g6_eval.cpp.s

# Object files for target g6_eval
g6_eval_OBJECTS = \
"CMakeFiles/g6_eval.dir/g6_eval.cpp.o"

# External object files for target g6_eval
g6_eval_EXTERNAL_OBJECTS =

g6_eval.exe: CMakeFiles/g6_eval.dir/g6_eval.cpp.o
g6_eval.exe: CMakeFiles/g6_eval.dir/build.make
g6_eval.exe: CMakeFiles/g6_eval.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/cygdrive/c/git/pb161/04/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking CXX executable g6_eval.exe"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/g6_eval.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/g6_eval.dir/build: g6_eval.exe

.PHONY : CMakeFiles/g6_eval.dir/build

CMakeFiles/g6_eval.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/g6_eval.dir/cmake_clean.cmake
.PHONY : CMakeFiles/g6_eval.dir/clean

CMakeFiles/g6_eval.dir/depend:
	cd /cygdrive/c/git/pb161/04/cmake-build-debug && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /cygdrive/c/git/pb161/04 /cygdrive/c/git/pb161/04 /cygdrive/c/git/pb161/04/cmake-build-debug /cygdrive/c/git/pb161/04/cmake-build-debug /cygdrive/c/git/pb161/04/cmake-build-debug/CMakeFiles/g6_eval.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/g6_eval.dir/depend

