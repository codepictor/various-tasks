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
include examples/CMakeFiles/CustomWidget.dir/depend.make

# Include the progress variables for this target.
include examples/CMakeFiles/CustomWidget.dir/progress.make

# Include the compile flags for this target's objects.
include examples/CMakeFiles/CustomWidget.dir/flags.make

examples/CMakeFiles/CustomWidget.dir/CustomWidget.cpp.o: examples/CMakeFiles/CustomWidget.dir/flags.make
examples/CMakeFiles/CustomWidget.dir/CustomWidget.cpp.o: /home/artem/artem/MIPT/infa/project/SFGUI-0.3.1/examples/CustomWidget.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/artem/artem/MIPT/infa/project/sfgui-build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object examples/CMakeFiles/CustomWidget.dir/CustomWidget.cpp.o"
	cd /home/artem/artem/MIPT/infa/project/sfgui-build/examples && /usr/bin/c++   $(CXX_DEFINES) $(CXX_FLAGS) -o CMakeFiles/CustomWidget.dir/CustomWidget.cpp.o -c /home/artem/artem/MIPT/infa/project/SFGUI-0.3.1/examples/CustomWidget.cpp

examples/CMakeFiles/CustomWidget.dir/CustomWidget.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/CustomWidget.dir/CustomWidget.cpp.i"
	cd /home/artem/artem/MIPT/infa/project/sfgui-build/examples && /usr/bin/c++  $(CXX_DEFINES) $(CXX_FLAGS) -E /home/artem/artem/MIPT/infa/project/SFGUI-0.3.1/examples/CustomWidget.cpp > CMakeFiles/CustomWidget.dir/CustomWidget.cpp.i

examples/CMakeFiles/CustomWidget.dir/CustomWidget.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/CustomWidget.dir/CustomWidget.cpp.s"
	cd /home/artem/artem/MIPT/infa/project/sfgui-build/examples && /usr/bin/c++  $(CXX_DEFINES) $(CXX_FLAGS) -S /home/artem/artem/MIPT/infa/project/SFGUI-0.3.1/examples/CustomWidget.cpp -o CMakeFiles/CustomWidget.dir/CustomWidget.cpp.s

examples/CMakeFiles/CustomWidget.dir/CustomWidget.cpp.o.requires:

.PHONY : examples/CMakeFiles/CustomWidget.dir/CustomWidget.cpp.o.requires

examples/CMakeFiles/CustomWidget.dir/CustomWidget.cpp.o.provides: examples/CMakeFiles/CustomWidget.dir/CustomWidget.cpp.o.requires
	$(MAKE) -f examples/CMakeFiles/CustomWidget.dir/build.make examples/CMakeFiles/CustomWidget.dir/CustomWidget.cpp.o.provides.build
.PHONY : examples/CMakeFiles/CustomWidget.dir/CustomWidget.cpp.o.provides

examples/CMakeFiles/CustomWidget.dir/CustomWidget.cpp.o.provides.build: examples/CMakeFiles/CustomWidget.dir/CustomWidget.cpp.o


# Object files for target CustomWidget
CustomWidget_OBJECTS = \
"CMakeFiles/CustomWidget.dir/CustomWidget.cpp.o"

# External object files for target CustomWidget
CustomWidget_EXTERNAL_OBJECTS =

examples/CustomWidget: examples/CMakeFiles/CustomWidget.dir/CustomWidget.cpp.o
examples/CustomWidget: examples/CMakeFiles/CustomWidget.dir/build.make
examples/CustomWidget: lib/libsfgui.so
examples/CustomWidget: /usr/lib64/libsfml-graphics.so
examples/CustomWidget: /usr/lib64/libsfml-window.so
examples/CustomWidget: /usr/lib64/libsfml-system.so
examples/CustomWidget: /usr/lib64/libGL.so
examples/CustomWidget: /usr/lib64/libSM.so
examples/CustomWidget: /usr/lib64/libICE.so
examples/CustomWidget: /usr/lib64/libX11.so
examples/CustomWidget: /usr/lib64/libXext.so
examples/CustomWidget: examples/CMakeFiles/CustomWidget.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/artem/artem/MIPT/infa/project/sfgui-build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking CXX executable CustomWidget"
	cd /home/artem/artem/MIPT/infa/project/sfgui-build/examples && $(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/CustomWidget.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
examples/CMakeFiles/CustomWidget.dir/build: examples/CustomWidget

.PHONY : examples/CMakeFiles/CustomWidget.dir/build

examples/CMakeFiles/CustomWidget.dir/requires: examples/CMakeFiles/CustomWidget.dir/CustomWidget.cpp.o.requires

.PHONY : examples/CMakeFiles/CustomWidget.dir/requires

examples/CMakeFiles/CustomWidget.dir/clean:
	cd /home/artem/artem/MIPT/infa/project/sfgui-build/examples && $(CMAKE_COMMAND) -P CMakeFiles/CustomWidget.dir/cmake_clean.cmake
.PHONY : examples/CMakeFiles/CustomWidget.dir/clean

examples/CMakeFiles/CustomWidget.dir/depend:
	cd /home/artem/artem/MIPT/infa/project/sfgui-build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/artem/artem/MIPT/infa/project/SFGUI-0.3.1 /home/artem/artem/MIPT/infa/project/SFGUI-0.3.1/examples /home/artem/artem/MIPT/infa/project/sfgui-build /home/artem/artem/MIPT/infa/project/sfgui-build/examples /home/artem/artem/MIPT/infa/project/sfgui-build/examples/CMakeFiles/CustomWidget.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : examples/CMakeFiles/CustomWidget.dir/depend

