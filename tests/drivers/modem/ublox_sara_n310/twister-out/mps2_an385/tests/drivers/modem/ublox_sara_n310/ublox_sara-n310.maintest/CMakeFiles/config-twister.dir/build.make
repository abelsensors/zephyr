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
RM = /usr/bin/cmake -E rm -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /home/ilagas/zephyrproject/zephyr/tests/drivers/modem/ublox_sara_n310

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/ilagas/zephyrproject/zephyr/tests/drivers/modem/ublox_sara_n310/twister-out/mps2_an385/tests/drivers/modem/ublox_sara_n310/ublox_sara-n310.maintest

# Utility rule file for config-twister.

# Include the progress variables for this target.
include CMakeFiles/config-twister.dir/progress.make

CMakeFiles/config-twister: zephyr/.config


config-twister: CMakeFiles/config-twister
config-twister: CMakeFiles/config-twister.dir/build.make

.PHONY : config-twister

# Rule to build all files generated by this target.
CMakeFiles/config-twister.dir/build: config-twister

.PHONY : CMakeFiles/config-twister.dir/build

CMakeFiles/config-twister.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/config-twister.dir/cmake_clean.cmake
.PHONY : CMakeFiles/config-twister.dir/clean

CMakeFiles/config-twister.dir/depend:
	cd /home/ilagas/zephyrproject/zephyr/tests/drivers/modem/ublox_sara_n310/twister-out/mps2_an385/tests/drivers/modem/ublox_sara_n310/ublox_sara-n310.maintest && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/ilagas/zephyrproject/zephyr/tests/drivers/modem/ublox_sara_n310 /home/ilagas/zephyrproject/zephyr/tests/drivers/modem/ublox_sara_n310 /home/ilagas/zephyrproject/zephyr/tests/drivers/modem/ublox_sara_n310/twister-out/mps2_an385/tests/drivers/modem/ublox_sara_n310/ublox_sara-n310.maintest /home/ilagas/zephyrproject/zephyr/tests/drivers/modem/ublox_sara_n310/twister-out/mps2_an385/tests/drivers/modem/ublox_sara_n310/ublox_sara-n310.maintest /home/ilagas/zephyrproject/zephyr/tests/drivers/modem/ublox_sara_n310/twister-out/mps2_an385/tests/drivers/modem/ublox_sara_n310/ublox_sara-n310.maintest/CMakeFiles/config-twister.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/config-twister.dir/depend

