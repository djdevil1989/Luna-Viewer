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

# Utility rule file for linux-crash-logger-strip-target.

linux_crash_logger/CMakeFiles/linux-crash-logger-strip-target: linux_crash_logger/linux-crash-logger-stripped

linux_crash_logger/linux-crash-logger-stripped: linux_crash_logger/linux-crash-logger
	$(CMAKE_COMMAND) -E cmake_progress_report /root/FlexLife/trunk/indra/CMakeFiles $(CMAKE_PROGRESS_1)
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --blue --bold "Generating linux-crash-logger-stripped"
	cd /root/FlexLife/trunk/indra/linux_crash_logger && strip --strip-debug -o linux-crash-logger-stripped linux-crash-logger

linux-crash-logger-strip-target: linux_crash_logger/CMakeFiles/linux-crash-logger-strip-target
linux-crash-logger-strip-target: linux_crash_logger/linux-crash-logger-stripped
linux-crash-logger-strip-target: linux_crash_logger/CMakeFiles/linux-crash-logger-strip-target.dir/build.make
.PHONY : linux-crash-logger-strip-target

# Rule to build all files generated by this target.
linux_crash_logger/CMakeFiles/linux-crash-logger-strip-target.dir/build: linux-crash-logger-strip-target
.PHONY : linux_crash_logger/CMakeFiles/linux-crash-logger-strip-target.dir/build

linux_crash_logger/CMakeFiles/linux-crash-logger-strip-target.dir/clean:
	cd /root/FlexLife/trunk/indra/linux_crash_logger && $(CMAKE_COMMAND) -P CMakeFiles/linux-crash-logger-strip-target.dir/cmake_clean.cmake
.PHONY : linux_crash_logger/CMakeFiles/linux-crash-logger-strip-target.dir/clean

linux_crash_logger/CMakeFiles/linux-crash-logger-strip-target.dir/depend:
	cd /root/FlexLife/trunk/indra && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /root/FlexLife/trunk/indra /root/FlexLife/trunk/indra/linux_crash_logger /root/FlexLife/trunk/indra /root/FlexLife/trunk/indra/linux_crash_logger /root/FlexLife/trunk/indra/linux_crash_logger/CMakeFiles/linux-crash-logger-strip-target.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : linux_crash_logger/CMakeFiles/linux-crash-logger-strip-target.dir/depend

