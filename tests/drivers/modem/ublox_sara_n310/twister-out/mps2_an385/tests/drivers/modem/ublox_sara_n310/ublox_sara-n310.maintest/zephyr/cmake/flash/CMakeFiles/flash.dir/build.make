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

# Utility rule file for flash.

# Include the progress variables for this target.
include zephyr/cmake/flash/CMakeFiles/flash.dir/progress.make

zephyr/cmake/flash/CMakeFiles/flash: zephyr/zephyr.elf
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --blue --bold --progress-dir=/home/ilagas/zephyrproject/zephyr/tests/drivers/modem/ublox_sara_n310/twister-out/mps2_an385/tests/drivers/modem/ublox_sara_n310/ublox_sara-n310.maintest/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Flashing mps2_an385"
	/usr/bin/cmake -E env /usr/bin/python3.6 -m west flash --skip-rebuild

flash: zephyr/cmake/flash/CMakeFiles/flash
flash: zephyr/cmake/flash/CMakeFiles/flash.dir/build.make

.PHONY : flash

# Rule to build all files generated by this target.
zephyr/cmake/flash/CMakeFiles/flash.dir/build: flash

.PHONY : zephyr/cmake/flash/CMakeFiles/flash.dir/build

zephyr/cmake/flash/CMakeFiles/flash.dir/clean:
	cd /home/ilagas/zephyrproject/zephyr/tests/drivers/modem/ublox_sara_n310/twister-out/mps2_an385/tests/drivers/modem/ublox_sara_n310/ublox_sara-n310.maintest/zephyr/cmake/flash && $(CMAKE_COMMAND) -P CMakeFiles/flash.dir/cmake_clean.cmake
.PHONY : zephyr/cmake/flash/CMakeFiles/flash.dir/clean

zephyr/cmake/flash/CMakeFiles/flash.dir/depend:
	cd /home/ilagas/zephyrproject/zephyr/tests/drivers/modem/ublox_sara_n310/twister-out/mps2_an385/tests/drivers/modem/ublox_sara_n310/ublox_sara-n310.maintest && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/ilagas/zephyrproject/zephyr/tests/drivers/modem/ublox_sara_n310 /home/ilagas/zephyrproject/zephyr/cmake/flash /home/ilagas/zephyrproject/zephyr/tests/drivers/modem/ublox_sara_n310/twister-out/mps2_an385/tests/drivers/modem/ublox_sara_n310/ublox_sara-n310.maintest /home/ilagas/zephyrproject/zephyr/tests/drivers/modem/ublox_sara_n310/twister-out/mps2_an385/tests/drivers/modem/ublox_sara_n310/ublox_sara-n310.maintest/zephyr/cmake/flash /home/ilagas/zephyrproject/zephyr/tests/drivers/modem/ublox_sara_n310/twister-out/mps2_an385/tests/drivers/modem/ublox_sara_n310/ublox_sara-n310.maintest/zephyr/cmake/flash/CMakeFiles/flash.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : zephyr/cmake/flash/CMakeFiles/flash.dir/depend

