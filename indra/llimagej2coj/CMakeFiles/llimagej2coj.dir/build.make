# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 2.6

#=============================================================================
# Special targets provided by cmake.

# Disable implicit rules so canoncical targets will work.
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

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /root/FlexLife/trunk/indra

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /root/FlexLife/trunk/indra

# Include any dependencies generated for this target.
include llimagej2coj/CMakeFiles/llimagej2coj.dir/depend.make

# Include the progress variables for this target.
include llimagej2coj/CMakeFiles/llimagej2coj.dir/progress.make

# Include the compile flags for this target's objects.
include llimagej2coj/CMakeFiles/llimagej2coj.dir/flags.make

llimagej2coj/CMakeFiles/llimagej2coj.dir/llimagej2coj.o: llimagej2coj/CMakeFiles/llimagej2coj.dir/flags.make
llimagej2coj/CMakeFiles/llimagej2coj.dir/llimagej2coj.o: llimagej2coj/llimagej2coj.cpp
	$(CMAKE_COMMAND) -E cmake_progress_report /root/FlexLife/trunk/indra/CMakeFiles $(CMAKE_PROGRESS_1)
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Building CXX object llimagej2coj/CMakeFiles/llimagej2coj.dir/llimagej2coj.o"
	cd /root/FlexLife/trunk/indra/llimagej2coj && /usr/bin/c++   $(CXX_DEFINES) $(CXX_FLAGS) -o CMakeFiles/llimagej2coj.dir/llimagej2coj.o -c /root/FlexLife/trunk/indra/llimagej2coj/llimagej2coj.cpp

llimagej2coj/CMakeFiles/llimagej2coj.dir/llimagej2coj.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/llimagej2coj.dir/llimagej2coj.i"
	cd /root/FlexLife/trunk/indra/llimagej2coj && /usr/bin/c++  $(CXX_DEFINES) $(CXX_FLAGS) -E /root/FlexLife/trunk/indra/llimagej2coj/llimagej2coj.cpp > CMakeFiles/llimagej2coj.dir/llimagej2coj.i

llimagej2coj/CMakeFiles/llimagej2coj.dir/llimagej2coj.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/llimagej2coj.dir/llimagej2coj.s"
	cd /root/FlexLife/trunk/indra/llimagej2coj && /usr/bin/c++  $(CXX_DEFINES) $(CXX_FLAGS) -S /root/FlexLife/trunk/indra/llimagej2coj/llimagej2coj.cpp -o CMakeFiles/llimagej2coj.dir/llimagej2coj.s

llimagej2coj/CMakeFiles/llimagej2coj.dir/llimagej2coj.o.requires:
.PHONY : llimagej2coj/CMakeFiles/llimagej2coj.dir/llimagej2coj.o.requires

llimagej2coj/CMakeFiles/llimagej2coj.dir/llimagej2coj.o.provides: llimagej2coj/CMakeFiles/llimagej2coj.dir/llimagej2coj.o.requires
	$(MAKE) -f llimagej2coj/CMakeFiles/llimagej2coj.dir/build.make llimagej2coj/CMakeFiles/llimagej2coj.dir/llimagej2coj.o.provides.build
.PHONY : llimagej2coj/CMakeFiles/llimagej2coj.dir/llimagej2coj.o.provides

llimagej2coj/CMakeFiles/llimagej2coj.dir/llimagej2coj.o.provides.build: llimagej2coj/CMakeFiles/llimagej2coj.dir/llimagej2coj.o
.PHONY : llimagej2coj/CMakeFiles/llimagej2coj.dir/llimagej2coj.o.provides.build

# Object files for target llimagej2coj
llimagej2coj_OBJECTS = \
"CMakeFiles/llimagej2coj.dir/llimagej2coj.o"

# External object files for target llimagej2coj
llimagej2coj_EXTERNAL_OBJECTS =

llimagej2coj/libllimagej2coj.a: llimagej2coj/CMakeFiles/llimagej2coj.dir/llimagej2coj.o
llimagej2coj/libllimagej2coj.a: llimagej2coj/CMakeFiles/llimagej2coj.dir/build.make
llimagej2coj/libllimagej2coj.a: llimagej2coj/CMakeFiles/llimagej2coj.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --red --bold "Linking CXX static library libllimagej2coj.a"
	cd /root/FlexLife/trunk/indra/llimagej2coj && $(CMAKE_COMMAND) -P CMakeFiles/llimagej2coj.dir/cmake_clean_target.cmake
	cd /root/FlexLife/trunk/indra/llimagej2coj && $(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/llimagej2coj.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
llimagej2coj/CMakeFiles/llimagej2coj.dir/build: llimagej2coj/libllimagej2coj.a
.PHONY : llimagej2coj/CMakeFiles/llimagej2coj.dir/build

llimagej2coj/CMakeFiles/llimagej2coj.dir/requires: llimagej2coj/CMakeFiles/llimagej2coj.dir/llimagej2coj.o.requires
.PHONY : llimagej2coj/CMakeFiles/llimagej2coj.dir/requires

llimagej2coj/CMakeFiles/llimagej2coj.dir/clean:
	cd /root/FlexLife/trunk/indra/llimagej2coj && $(CMAKE_COMMAND) -P CMakeFiles/llimagej2coj.dir/cmake_clean.cmake
.PHONY : llimagej2coj/CMakeFiles/llimagej2coj.dir/clean

llimagej2coj/CMakeFiles/llimagej2coj.dir/depend:
	cd /root/FlexLife/trunk/indra && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /root/FlexLife/trunk/indra /root/FlexLife/trunk/indra/llimagej2coj /root/FlexLife/trunk/indra /root/FlexLife/trunk/indra/llimagej2coj /root/FlexLife/trunk/indra/llimagej2coj/CMakeFiles/llimagej2coj.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : llimagej2coj/CMakeFiles/llimagej2coj.dir/depend

