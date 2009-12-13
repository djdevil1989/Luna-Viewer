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
include llvfs/CMakeFiles/llvfs.dir/depend.make

# Include the progress variables for this target.
include llvfs/CMakeFiles/llvfs.dir/progress.make

# Include the compile flags for this target's objects.
include llvfs/CMakeFiles/llvfs.dir/flags.make

llvfs/CMakeFiles/llvfs.dir/lldir.o: llvfs/CMakeFiles/llvfs.dir/flags.make
llvfs/CMakeFiles/llvfs.dir/lldir.o: llvfs/lldir.cpp
	$(CMAKE_COMMAND) -E cmake_progress_report /root/FlexLife/trunk/indra/CMakeFiles $(CMAKE_PROGRESS_1)
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Building CXX object llvfs/CMakeFiles/llvfs.dir/lldir.o"
	cd /root/FlexLife/trunk/indra/llvfs && /usr/bin/c++   $(CXX_DEFINES) $(CXX_FLAGS) -o CMakeFiles/llvfs.dir/lldir.o -c /root/FlexLife/trunk/indra/llvfs/lldir.cpp

llvfs/CMakeFiles/llvfs.dir/lldir.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/llvfs.dir/lldir.i"
	cd /root/FlexLife/trunk/indra/llvfs && /usr/bin/c++  $(CXX_DEFINES) $(CXX_FLAGS) -E /root/FlexLife/trunk/indra/llvfs/lldir.cpp > CMakeFiles/llvfs.dir/lldir.i

llvfs/CMakeFiles/llvfs.dir/lldir.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/llvfs.dir/lldir.s"
	cd /root/FlexLife/trunk/indra/llvfs && /usr/bin/c++  $(CXX_DEFINES) $(CXX_FLAGS) -S /root/FlexLife/trunk/indra/llvfs/lldir.cpp -o CMakeFiles/llvfs.dir/lldir.s

llvfs/CMakeFiles/llvfs.dir/lldir.o.requires:
.PHONY : llvfs/CMakeFiles/llvfs.dir/lldir.o.requires

llvfs/CMakeFiles/llvfs.dir/lldir.o.provides: llvfs/CMakeFiles/llvfs.dir/lldir.o.requires
	$(MAKE) -f llvfs/CMakeFiles/llvfs.dir/build.make llvfs/CMakeFiles/llvfs.dir/lldir.o.provides.build
.PHONY : llvfs/CMakeFiles/llvfs.dir/lldir.o.provides

llvfs/CMakeFiles/llvfs.dir/lldir.o.provides.build: llvfs/CMakeFiles/llvfs.dir/lldir.o
.PHONY : llvfs/CMakeFiles/llvfs.dir/lldir.o.provides.build

llvfs/CMakeFiles/llvfs.dir/lllfsthread.o: llvfs/CMakeFiles/llvfs.dir/flags.make
llvfs/CMakeFiles/llvfs.dir/lllfsthread.o: llvfs/lllfsthread.cpp
	$(CMAKE_COMMAND) -E cmake_progress_report /root/FlexLife/trunk/indra/CMakeFiles $(CMAKE_PROGRESS_2)
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Building CXX object llvfs/CMakeFiles/llvfs.dir/lllfsthread.o"
	cd /root/FlexLife/trunk/indra/llvfs && /usr/bin/c++   $(CXX_DEFINES) $(CXX_FLAGS) -o CMakeFiles/llvfs.dir/lllfsthread.o -c /root/FlexLife/trunk/indra/llvfs/lllfsthread.cpp

llvfs/CMakeFiles/llvfs.dir/lllfsthread.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/llvfs.dir/lllfsthread.i"
	cd /root/FlexLife/trunk/indra/llvfs && /usr/bin/c++  $(CXX_DEFINES) $(CXX_FLAGS) -E /root/FlexLife/trunk/indra/llvfs/lllfsthread.cpp > CMakeFiles/llvfs.dir/lllfsthread.i

llvfs/CMakeFiles/llvfs.dir/lllfsthread.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/llvfs.dir/lllfsthread.s"
	cd /root/FlexLife/trunk/indra/llvfs && /usr/bin/c++  $(CXX_DEFINES) $(CXX_FLAGS) -S /root/FlexLife/trunk/indra/llvfs/lllfsthread.cpp -o CMakeFiles/llvfs.dir/lllfsthread.s

llvfs/CMakeFiles/llvfs.dir/lllfsthread.o.requires:
.PHONY : llvfs/CMakeFiles/llvfs.dir/lllfsthread.o.requires

llvfs/CMakeFiles/llvfs.dir/lllfsthread.o.provides: llvfs/CMakeFiles/llvfs.dir/lllfsthread.o.requires
	$(MAKE) -f llvfs/CMakeFiles/llvfs.dir/build.make llvfs/CMakeFiles/llvfs.dir/lllfsthread.o.provides.build
.PHONY : llvfs/CMakeFiles/llvfs.dir/lllfsthread.o.provides

llvfs/CMakeFiles/llvfs.dir/lllfsthread.o.provides.build: llvfs/CMakeFiles/llvfs.dir/lllfsthread.o
.PHONY : llvfs/CMakeFiles/llvfs.dir/lllfsthread.o.provides.build

llvfs/CMakeFiles/llvfs.dir/llpidlock.o: llvfs/CMakeFiles/llvfs.dir/flags.make
llvfs/CMakeFiles/llvfs.dir/llpidlock.o: llvfs/llpidlock.cpp
	$(CMAKE_COMMAND) -E cmake_progress_report /root/FlexLife/trunk/indra/CMakeFiles $(CMAKE_PROGRESS_3)
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Building CXX object llvfs/CMakeFiles/llvfs.dir/llpidlock.o"
	cd /root/FlexLife/trunk/indra/llvfs && /usr/bin/c++   $(CXX_DEFINES) $(CXX_FLAGS) -o CMakeFiles/llvfs.dir/llpidlock.o -c /root/FlexLife/trunk/indra/llvfs/llpidlock.cpp

llvfs/CMakeFiles/llvfs.dir/llpidlock.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/llvfs.dir/llpidlock.i"
	cd /root/FlexLife/trunk/indra/llvfs && /usr/bin/c++  $(CXX_DEFINES) $(CXX_FLAGS) -E /root/FlexLife/trunk/indra/llvfs/llpidlock.cpp > CMakeFiles/llvfs.dir/llpidlock.i

llvfs/CMakeFiles/llvfs.dir/llpidlock.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/llvfs.dir/llpidlock.s"
	cd /root/FlexLife/trunk/indra/llvfs && /usr/bin/c++  $(CXX_DEFINES) $(CXX_FLAGS) -S /root/FlexLife/trunk/indra/llvfs/llpidlock.cpp -o CMakeFiles/llvfs.dir/llpidlock.s

llvfs/CMakeFiles/llvfs.dir/llpidlock.o.requires:
.PHONY : llvfs/CMakeFiles/llvfs.dir/llpidlock.o.requires

llvfs/CMakeFiles/llvfs.dir/llpidlock.o.provides: llvfs/CMakeFiles/llvfs.dir/llpidlock.o.requires
	$(MAKE) -f llvfs/CMakeFiles/llvfs.dir/build.make llvfs/CMakeFiles/llvfs.dir/llpidlock.o.provides.build
.PHONY : llvfs/CMakeFiles/llvfs.dir/llpidlock.o.provides

llvfs/CMakeFiles/llvfs.dir/llpidlock.o.provides.build: llvfs/CMakeFiles/llvfs.dir/llpidlock.o
.PHONY : llvfs/CMakeFiles/llvfs.dir/llpidlock.o.provides.build

llvfs/CMakeFiles/llvfs.dir/llvfile.o: llvfs/CMakeFiles/llvfs.dir/flags.make
llvfs/CMakeFiles/llvfs.dir/llvfile.o: llvfs/llvfile.cpp
	$(CMAKE_COMMAND) -E cmake_progress_report /root/FlexLife/trunk/indra/CMakeFiles $(CMAKE_PROGRESS_4)
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Building CXX object llvfs/CMakeFiles/llvfs.dir/llvfile.o"
	cd /root/FlexLife/trunk/indra/llvfs && /usr/bin/c++   $(CXX_DEFINES) $(CXX_FLAGS) -o CMakeFiles/llvfs.dir/llvfile.o -c /root/FlexLife/trunk/indra/llvfs/llvfile.cpp

llvfs/CMakeFiles/llvfs.dir/llvfile.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/llvfs.dir/llvfile.i"
	cd /root/FlexLife/trunk/indra/llvfs && /usr/bin/c++  $(CXX_DEFINES) $(CXX_FLAGS) -E /root/FlexLife/trunk/indra/llvfs/llvfile.cpp > CMakeFiles/llvfs.dir/llvfile.i

llvfs/CMakeFiles/llvfs.dir/llvfile.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/llvfs.dir/llvfile.s"
	cd /root/FlexLife/trunk/indra/llvfs && /usr/bin/c++  $(CXX_DEFINES) $(CXX_FLAGS) -S /root/FlexLife/trunk/indra/llvfs/llvfile.cpp -o CMakeFiles/llvfs.dir/llvfile.s

llvfs/CMakeFiles/llvfs.dir/llvfile.o.requires:
.PHONY : llvfs/CMakeFiles/llvfs.dir/llvfile.o.requires

llvfs/CMakeFiles/llvfs.dir/llvfile.o.provides: llvfs/CMakeFiles/llvfs.dir/llvfile.o.requires
	$(MAKE) -f llvfs/CMakeFiles/llvfs.dir/build.make llvfs/CMakeFiles/llvfs.dir/llvfile.o.provides.build
.PHONY : llvfs/CMakeFiles/llvfs.dir/llvfile.o.provides

llvfs/CMakeFiles/llvfs.dir/llvfile.o.provides.build: llvfs/CMakeFiles/llvfs.dir/llvfile.o
.PHONY : llvfs/CMakeFiles/llvfs.dir/llvfile.o.provides.build

llvfs/CMakeFiles/llvfs.dir/llvfs.o: llvfs/CMakeFiles/llvfs.dir/flags.make
llvfs/CMakeFiles/llvfs.dir/llvfs.o: llvfs/llvfs.cpp
	$(CMAKE_COMMAND) -E cmake_progress_report /root/FlexLife/trunk/indra/CMakeFiles $(CMAKE_PROGRESS_5)
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Building CXX object llvfs/CMakeFiles/llvfs.dir/llvfs.o"
	cd /root/FlexLife/trunk/indra/llvfs && /usr/bin/c++   $(CXX_DEFINES) $(CXX_FLAGS) -o CMakeFiles/llvfs.dir/llvfs.o -c /root/FlexLife/trunk/indra/llvfs/llvfs.cpp

llvfs/CMakeFiles/llvfs.dir/llvfs.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/llvfs.dir/llvfs.i"
	cd /root/FlexLife/trunk/indra/llvfs && /usr/bin/c++  $(CXX_DEFINES) $(CXX_FLAGS) -E /root/FlexLife/trunk/indra/llvfs/llvfs.cpp > CMakeFiles/llvfs.dir/llvfs.i

llvfs/CMakeFiles/llvfs.dir/llvfs.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/llvfs.dir/llvfs.s"
	cd /root/FlexLife/trunk/indra/llvfs && /usr/bin/c++  $(CXX_DEFINES) $(CXX_FLAGS) -S /root/FlexLife/trunk/indra/llvfs/llvfs.cpp -o CMakeFiles/llvfs.dir/llvfs.s

llvfs/CMakeFiles/llvfs.dir/llvfs.o.requires:
.PHONY : llvfs/CMakeFiles/llvfs.dir/llvfs.o.requires

llvfs/CMakeFiles/llvfs.dir/llvfs.o.provides: llvfs/CMakeFiles/llvfs.dir/llvfs.o.requires
	$(MAKE) -f llvfs/CMakeFiles/llvfs.dir/build.make llvfs/CMakeFiles/llvfs.dir/llvfs.o.provides.build
.PHONY : llvfs/CMakeFiles/llvfs.dir/llvfs.o.provides

llvfs/CMakeFiles/llvfs.dir/llvfs.o.provides.build: llvfs/CMakeFiles/llvfs.dir/llvfs.o
.PHONY : llvfs/CMakeFiles/llvfs.dir/llvfs.o.provides.build

llvfs/CMakeFiles/llvfs.dir/llvfsthread.o: llvfs/CMakeFiles/llvfs.dir/flags.make
llvfs/CMakeFiles/llvfs.dir/llvfsthread.o: llvfs/llvfsthread.cpp
	$(CMAKE_COMMAND) -E cmake_progress_report /root/FlexLife/trunk/indra/CMakeFiles $(CMAKE_PROGRESS_6)
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Building CXX object llvfs/CMakeFiles/llvfs.dir/llvfsthread.o"
	cd /root/FlexLife/trunk/indra/llvfs && /usr/bin/c++   $(CXX_DEFINES) $(CXX_FLAGS) -o CMakeFiles/llvfs.dir/llvfsthread.o -c /root/FlexLife/trunk/indra/llvfs/llvfsthread.cpp

llvfs/CMakeFiles/llvfs.dir/llvfsthread.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/llvfs.dir/llvfsthread.i"
	cd /root/FlexLife/trunk/indra/llvfs && /usr/bin/c++  $(CXX_DEFINES) $(CXX_FLAGS) -E /root/FlexLife/trunk/indra/llvfs/llvfsthread.cpp > CMakeFiles/llvfs.dir/llvfsthread.i

llvfs/CMakeFiles/llvfs.dir/llvfsthread.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/llvfs.dir/llvfsthread.s"
	cd /root/FlexLife/trunk/indra/llvfs && /usr/bin/c++  $(CXX_DEFINES) $(CXX_FLAGS) -S /root/FlexLife/trunk/indra/llvfs/llvfsthread.cpp -o CMakeFiles/llvfs.dir/llvfsthread.s

llvfs/CMakeFiles/llvfs.dir/llvfsthread.o.requires:
.PHONY : llvfs/CMakeFiles/llvfs.dir/llvfsthread.o.requires

llvfs/CMakeFiles/llvfs.dir/llvfsthread.o.provides: llvfs/CMakeFiles/llvfs.dir/llvfsthread.o.requires
	$(MAKE) -f llvfs/CMakeFiles/llvfs.dir/build.make llvfs/CMakeFiles/llvfs.dir/llvfsthread.o.provides.build
.PHONY : llvfs/CMakeFiles/llvfs.dir/llvfsthread.o.provides

llvfs/CMakeFiles/llvfs.dir/llvfsthread.o.provides.build: llvfs/CMakeFiles/llvfs.dir/llvfsthread.o
.PHONY : llvfs/CMakeFiles/llvfs.dir/llvfsthread.o.provides.build

llvfs/CMakeFiles/llvfs.dir/lldir_linux.o: llvfs/CMakeFiles/llvfs.dir/flags.make
llvfs/CMakeFiles/llvfs.dir/lldir_linux.o: llvfs/lldir_linux.cpp
	$(CMAKE_COMMAND) -E cmake_progress_report /root/FlexLife/trunk/indra/CMakeFiles $(CMAKE_PROGRESS_7)
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Building CXX object llvfs/CMakeFiles/llvfs.dir/lldir_linux.o"
	cd /root/FlexLife/trunk/indra/llvfs && /usr/bin/c++   $(CXX_DEFINES) $(CXX_FLAGS) -o CMakeFiles/llvfs.dir/lldir_linux.o -c /root/FlexLife/trunk/indra/llvfs/lldir_linux.cpp

llvfs/CMakeFiles/llvfs.dir/lldir_linux.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/llvfs.dir/lldir_linux.i"
	cd /root/FlexLife/trunk/indra/llvfs && /usr/bin/c++  $(CXX_DEFINES) $(CXX_FLAGS) -E /root/FlexLife/trunk/indra/llvfs/lldir_linux.cpp > CMakeFiles/llvfs.dir/lldir_linux.i

llvfs/CMakeFiles/llvfs.dir/lldir_linux.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/llvfs.dir/lldir_linux.s"
	cd /root/FlexLife/trunk/indra/llvfs && /usr/bin/c++  $(CXX_DEFINES) $(CXX_FLAGS) -S /root/FlexLife/trunk/indra/llvfs/lldir_linux.cpp -o CMakeFiles/llvfs.dir/lldir_linux.s

llvfs/CMakeFiles/llvfs.dir/lldir_linux.o.requires:
.PHONY : llvfs/CMakeFiles/llvfs.dir/lldir_linux.o.requires

llvfs/CMakeFiles/llvfs.dir/lldir_linux.o.provides: llvfs/CMakeFiles/llvfs.dir/lldir_linux.o.requires
	$(MAKE) -f llvfs/CMakeFiles/llvfs.dir/build.make llvfs/CMakeFiles/llvfs.dir/lldir_linux.o.provides.build
.PHONY : llvfs/CMakeFiles/llvfs.dir/lldir_linux.o.provides

llvfs/CMakeFiles/llvfs.dir/lldir_linux.o.provides.build: llvfs/CMakeFiles/llvfs.dir/lldir_linux.o
.PHONY : llvfs/CMakeFiles/llvfs.dir/lldir_linux.o.provides.build

# Object files for target llvfs
llvfs_OBJECTS = \
"CMakeFiles/llvfs.dir/lldir.o" \
"CMakeFiles/llvfs.dir/lllfsthread.o" \
"CMakeFiles/llvfs.dir/llpidlock.o" \
"CMakeFiles/llvfs.dir/llvfile.o" \
"CMakeFiles/llvfs.dir/llvfs.o" \
"CMakeFiles/llvfs.dir/llvfsthread.o" \
"CMakeFiles/llvfs.dir/lldir_linux.o"

# External object files for target llvfs
llvfs_EXTERNAL_OBJECTS =

llvfs/libllvfs.a: llvfs/CMakeFiles/llvfs.dir/lldir.o
llvfs/libllvfs.a: llvfs/CMakeFiles/llvfs.dir/lllfsthread.o
llvfs/libllvfs.a: llvfs/CMakeFiles/llvfs.dir/llpidlock.o
llvfs/libllvfs.a: llvfs/CMakeFiles/llvfs.dir/llvfile.o
llvfs/libllvfs.a: llvfs/CMakeFiles/llvfs.dir/llvfs.o
llvfs/libllvfs.a: llvfs/CMakeFiles/llvfs.dir/llvfsthread.o
llvfs/libllvfs.a: llvfs/CMakeFiles/llvfs.dir/lldir_linux.o
llvfs/libllvfs.a: llvfs/CMakeFiles/llvfs.dir/build.make
llvfs/libllvfs.a: llvfs/CMakeFiles/llvfs.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --red --bold "Linking CXX static library libllvfs.a"
	cd /root/FlexLife/trunk/indra/llvfs && $(CMAKE_COMMAND) -P CMakeFiles/llvfs.dir/cmake_clean_target.cmake
	cd /root/FlexLife/trunk/indra/llvfs && $(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/llvfs.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
llvfs/CMakeFiles/llvfs.dir/build: llvfs/libllvfs.a
.PHONY : llvfs/CMakeFiles/llvfs.dir/build

llvfs/CMakeFiles/llvfs.dir/requires: llvfs/CMakeFiles/llvfs.dir/lldir.o.requires
llvfs/CMakeFiles/llvfs.dir/requires: llvfs/CMakeFiles/llvfs.dir/lllfsthread.o.requires
llvfs/CMakeFiles/llvfs.dir/requires: llvfs/CMakeFiles/llvfs.dir/llpidlock.o.requires
llvfs/CMakeFiles/llvfs.dir/requires: llvfs/CMakeFiles/llvfs.dir/llvfile.o.requires
llvfs/CMakeFiles/llvfs.dir/requires: llvfs/CMakeFiles/llvfs.dir/llvfs.o.requires
llvfs/CMakeFiles/llvfs.dir/requires: llvfs/CMakeFiles/llvfs.dir/llvfsthread.o.requires
llvfs/CMakeFiles/llvfs.dir/requires: llvfs/CMakeFiles/llvfs.dir/lldir_linux.o.requires
.PHONY : llvfs/CMakeFiles/llvfs.dir/requires

llvfs/CMakeFiles/llvfs.dir/clean:
	cd /root/FlexLife/trunk/indra/llvfs && $(CMAKE_COMMAND) -P CMakeFiles/llvfs.dir/cmake_clean.cmake
.PHONY : llvfs/CMakeFiles/llvfs.dir/clean

llvfs/CMakeFiles/llvfs.dir/depend:
	cd /root/FlexLife/trunk/indra && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /root/FlexLife/trunk/indra /root/FlexLife/trunk/indra/llvfs /root/FlexLife/trunk/indra /root/FlexLife/trunk/indra/llvfs /root/FlexLife/trunk/indra/llvfs/CMakeFiles/llvfs.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : llvfs/CMakeFiles/llvfs.dir/depend
