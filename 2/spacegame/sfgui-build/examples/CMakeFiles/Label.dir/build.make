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
include examples/CMakeFiles/Label.dir/depend.make

# Include the progress variables for this target.
include examples/CMakeFiles/Label.dir/progress.make

# Include the compile flags for this target's objects.
include examples/CMakeFiles/Label.dir/flags.make

examples/CMakeFiles/Label.dir/Label.cpp.o: examples/CMakeFiles/Label.dir/flags.make
examples/CMakeFiles/Label.dir/Label.cpp.o: /home/artem/artem/MIPT/infa/project/SFGUI-0.3.1/examples/Label.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/artem/artem/MIPT/infa/project/sfgui-build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object examples/CMakeFiles/Label.dir/Label.cpp.o"
	cd /home/artem/artem/MIPT/infa/project/sfgui-build/examples && /usr/bin/c++   $(CXX_DEFINES) $(CXX_FLAGS) -o CMakeFiles/Label.dir/Label.cpp.o -c /home/artem/artem/MIPT/infa/project/SFGUI-0.3.1/examples/Label.cpp

examples/CMakeFiles/Label.dir/Label.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/Label.dir/Label.cpp.i"
	cd /home/artem/artem/MIPT/infa/project/sfgui-build/examples && /usr/bin/c++  $(CXX_DEFINES) $(CXX_FLAGS) -E /home/artem/artem/MIPT/infa/project/SFGUI-0.3.1/examples/Label.cpp > CMakeFiles/Label.dir/Label.cpp.i

examples/CMakeFiles/Label.dir/Label.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/Label.dir/Label.cpp.s"
	cd /home/artem/artem/MIPT/infa/project/sfgui-build/examples && /usr/bin/c++  $(CXX_DEFINES) $(CXX_FLAGS) -S /home/artem/artem/MIPT/infa/project/SFGUI-0.3.1/examples/Label.cpp -o CMakeFiles/Label.dir/Label.cpp.s

examples/CMakeFiles/Label.dir/Label.cpp.o.requires:

.PHONY : examples/CMakeFiles/Label.dir/Label.cpp.o.requires

examples/CMakeFiles/Label.dir/Label.cpp.o.provides: examples/CMakeFiles/Label.dir/Label.cpp.o.requires
	$(MAKE) -f examples/CMakeFiles/Label.dir/build.make examples/CMakeFiles/Label.dir/Label.cpp.o.provides.build
.PHONY : examples/CMakeFiles/Label.dir/Label.cpp.o.provides

examples/CMakeFiles/Label.dir/Label.cpp.o.provides.build: examples/CMakeFiles/Label.dir/Label.cpp.o


# Object files for target Label
Label_OBJECTS = \
"CMakeFiles/Label.dir/Label.cpp.o"

# External object files for target Label
Label_EXTERNAL_OBJECTS =

examples/Label: examples/CMakeFiles/Label.dir/Label.cpp.o
examples/Label: examples/CMakeFiles/Label.dir/build.make
examples/Label: lib/libsfgui.so
examples/Label: /usr/lib64/libsfml-graphics.so
examples/Label: /usr/lib64/libsfml-window.so
examples/Label: /usr/lib64/libsfml-system.so
examples/Label: /usr/lib64/libGL.so
examples/Label: /usr/lib64/libSM.so
examples/Label: /usr/lib64/libICE.so
examples/Label: /usr/lib64/libX11.so
examples/Label: /usr/lib64/libXext.so
examples/Label: examples/CMakeFiles/Label.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/artem/artem/MIPT/infa/project/sfgui-build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking CXX executable Label"
	cd /home/artem/artem/MIPT/infa/project/sfgui-build/examples && $(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/Label.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
examples/CMakeFiles/Label.dir/build: examples/Label

.PHONY : examples/CMakeFiles/Label.dir/build

examples/CMakeFiles/Label.dir/requires: examples/CMakeFiles/Label.dir/Label.cpp.o.requires

.PHONY : examples/CMakeFiles/Label.dir/requires

examples/CMakeFiles/Label.dir/clean:
	cd /home/artem/artem/MIPT/infa/project/sfgui-build/examples && $(CMAKE_COMMAND) -P CMakeFiles/Label.dir/cmake_clean.cmake
.PHONY : examples/CMakeFiles/Label.dir/clean

examples/CMakeFiles/Label.dir/depend:
	cd /home/artem/artem/MIPT/infa/project/sfgui-build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/artem/artem/MIPT/infa/project/SFGUI-0.3.1 /home/artem/artem/MIPT/infa/project/SFGUI-0.3.1/examples /home/artem/artem/MIPT/infa/project/sfgui-build /home/artem/artem/MIPT/infa/project/sfgui-build/examples /home/artem/artem/MIPT/infa/project/sfgui-build/examples/CMakeFiles/Label.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : examples/CMakeFiles/Label.dir/depend
