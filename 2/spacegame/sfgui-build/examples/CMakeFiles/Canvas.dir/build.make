# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.3

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
CMAKE_SOURCE_DIR = /home/artem/artem/MIPT/infa/project/SFGUI-0.3.1

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/artem/artem/MIPT/infa/project/sfgui-build

# Include any dependencies generated for this target.
include examples/CMakeFiles/Canvas.dir/depend.make

# Include the progress variables for this target.
include examples/CMakeFiles/Canvas.dir/progress.make

# Include the compile flags for this target's objects.
include examples/CMakeFiles/Canvas.dir/flags.make

examples/CMakeFiles/Canvas.dir/Canvas.cpp.o: examples/CMakeFiles/Canvas.dir/flags.make
examples/CMakeFiles/Canvas.dir/Canvas.cpp.o: /home/artem/artem/MIPT/infa/project/SFGUI-0.3.1/examples/Canvas.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/artem/artem/MIPT/infa/project/sfgui-build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object examples/CMakeFiles/Canvas.dir/Canvas.cpp.o"
	cd /home/artem/artem/MIPT/infa/project/sfgui-build/examples && /usr/bin/c++   $(CXX_DEFINES) $(CXX_FLAGS) -o CMakeFiles/Canvas.dir/Canvas.cpp.o -c /home/artem/artem/MIPT/infa/project/SFGUI-0.3.1/examples/Canvas.cpp

examples/CMakeFiles/Canvas.dir/Canvas.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/Canvas.dir/Canvas.cpp.i"
	cd /home/artem/artem/MIPT/infa/project/sfgui-build/examples && /usr/bin/c++  $(CXX_DEFINES) $(CXX_FLAGS) -E /home/artem/artem/MIPT/infa/project/SFGUI-0.3.1/examples/Canvas.cpp > CMakeFiles/Canvas.dir/Canvas.cpp.i

examples/CMakeFiles/Canvas.dir/Canvas.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/Canvas.dir/Canvas.cpp.s"
	cd /home/artem/artem/MIPT/infa/project/sfgui-build/examples && /usr/bin/c++  $(CXX_DEFINES) $(CXX_FLAGS) -S /home/artem/artem/MIPT/infa/project/SFGUI-0.3.1/examples/Canvas.cpp -o CMakeFiles/Canvas.dir/Canvas.cpp.s

examples/CMakeFiles/Canvas.dir/Canvas.cpp.o.requires:

.PHONY : examples/CMakeFiles/Canvas.dir/Canvas.cpp.o.requires

examples/CMakeFiles/Canvas.dir/Canvas.cpp.o.provides: examples/CMakeFiles/Canvas.dir/Canvas.cpp.o.requires
	$(MAKE) -f examples/CMakeFiles/Canvas.dir/build.make examples/CMakeFiles/Canvas.dir/Canvas.cpp.o.provides.build
.PHONY : examples/CMakeFiles/Canvas.dir/Canvas.cpp.o.provides

examples/CMakeFiles/Canvas.dir/Canvas.cpp.o.provides.build: examples/CMakeFiles/Canvas.dir/Canvas.cpp.o


# Object files for target Canvas
Canvas_OBJECTS = \
"CMakeFiles/Canvas.dir/Canvas.cpp.o"

# External object files for target Canvas
Canvas_EXTERNAL_OBJECTS =

examples/Canvas: examples/CMakeFiles/Canvas.dir/Canvas.cpp.o
examples/Canvas: examples/CMakeFiles/Canvas.dir/build.make
examples/Canvas: lib/libsfgui.so
examples/Canvas: /usr/lib64/libsfml-graphics.so
examples/Canvas: /usr/lib64/libsfml-window.so
examples/Canvas: /usr/lib64/libsfml-system.so
examples/Canvas: /usr/lib64/libGL.so
examples/Canvas: /usr/lib64/libSM.so
examples/Canvas: /usr/lib64/libICE.so
examples/Canvas: /usr/lib64/libX11.so
examples/Canvas: /usr/lib64/libXext.so
examples/Canvas: examples/CMakeFiles/Canvas.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/artem/artem/MIPT/infa/project/sfgui-build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking CXX executable Canvas"
	cd /home/artem/artem/MIPT/infa/project/sfgui-build/examples && $(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/Canvas.dir/link.txt --verbose=$(VERBOSE)
	cd /home/artem/artem/MIPT/infa/project/sfgui-build/examples && /usr/bin/cmake -E copy_directory /home/artem/artem/MIPT/infa/project/SFGUI-0.3.1/examples/data /home/artem/artem/MIPT/infa/project/sfgui-build/examples/data

# Rule to build all files generated by this target.
examples/CMakeFiles/Canvas.dir/build: examples/Canvas

.PHONY : examples/CMakeFiles/Canvas.dir/build

examples/CMakeFiles/Canvas.dir/requires: examples/CMakeFiles/Canvas.dir/Canvas.cpp.o.requires

.PHONY : examples/CMakeFiles/Canvas.dir/requires

examples/CMakeFiles/Canvas.dir/clean:
	cd /home/artem/artem/MIPT/infa/project/sfgui-build/examples && $(CMAKE_COMMAND) -P CMakeFiles/Canvas.dir/cmake_clean.cmake
.PHONY : examples/CMakeFiles/Canvas.dir/clean

examples/CMakeFiles/Canvas.dir/depend:
	cd /home/artem/artem/MIPT/infa/project/sfgui-build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/artem/artem/MIPT/infa/project/SFGUI-0.3.1 /home/artem/artem/MIPT/infa/project/SFGUI-0.3.1/examples /home/artem/artem/MIPT/infa/project/sfgui-build /home/artem/artem/MIPT/infa/project/sfgui-build/examples /home/artem/artem/MIPT/infa/project/sfgui-build/examples/CMakeFiles/Canvas.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : examples/CMakeFiles/Canvas.dir/depend
