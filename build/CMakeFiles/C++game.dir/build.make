# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.22

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
CMAKE_SOURCE_DIR = /home/aditya/Desktop/C++game

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/aditya/Desktop/C++game/build

# Include any dependencies generated for this target.
include CMakeFiles/C++game.dir/depend.make
# Include any dependencies generated by the compiler for this target.
include CMakeFiles/C++game.dir/compiler_depend.make

# Include the progress variables for this target.
include CMakeFiles/C++game.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/C++game.dir/flags.make

CMakeFiles/C++game.dir/main.cpp.o: CMakeFiles/C++game.dir/flags.make
CMakeFiles/C++game.dir/main.cpp.o: ../main.cpp
CMakeFiles/C++game.dir/main.cpp.o: CMakeFiles/C++game.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/aditya/Desktop/C++game/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/C++game.dir/main.cpp.o"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/C++game.dir/main.cpp.o -MF CMakeFiles/C++game.dir/main.cpp.o.d -o CMakeFiles/C++game.dir/main.cpp.o -c /home/aditya/Desktop/C++game/main.cpp

CMakeFiles/C++game.dir/main.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/C++game.dir/main.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/aditya/Desktop/C++game/main.cpp > CMakeFiles/C++game.dir/main.cpp.i

CMakeFiles/C++game.dir/main.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/C++game.dir/main.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/aditya/Desktop/C++game/main.cpp -o CMakeFiles/C++game.dir/main.cpp.s

# Object files for target C++game
C______game_OBJECTS = \
"CMakeFiles/C++game.dir/main.cpp.o"

# External object files for target C++game
C______game_EXTERNAL_OBJECTS =

C++game: CMakeFiles/C++game.dir/main.cpp.o
C++game: CMakeFiles/C++game.dir/build.make
C++game: /usr/lib/x86_64-linux-gnu/libSM.so
C++game: /usr/lib/x86_64-linux-gnu/libICE.so
C++game: /usr/lib/x86_64-linux-gnu/libX11.so
C++game: /usr/lib/x86_64-linux-gnu/libXext.so
C++game: CMakeFiles/C++game.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/aditya/Desktop/C++game/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking CXX executable C++game"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/C++game.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/C++game.dir/build: C++game
.PHONY : CMakeFiles/C++game.dir/build

CMakeFiles/C++game.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/C++game.dir/cmake_clean.cmake
.PHONY : CMakeFiles/C++game.dir/clean

CMakeFiles/C++game.dir/depend:
	cd /home/aditya/Desktop/C++game/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/aditya/Desktop/C++game /home/aditya/Desktop/C++game /home/aditya/Desktop/C++game/build /home/aditya/Desktop/C++game/build /home/aditya/Desktop/C++game/build/CMakeFiles/C++game.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/C++game.dir/depend
