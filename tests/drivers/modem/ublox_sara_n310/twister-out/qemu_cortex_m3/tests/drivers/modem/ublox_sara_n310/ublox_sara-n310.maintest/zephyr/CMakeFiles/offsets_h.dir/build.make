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
CMAKE_BINARY_DIR = /home/ilagas/zephyrproject/zephyr/tests/drivers/modem/ublox_sara_n310/twister-out/qemu_cortex_m3/tests/drivers/modem/ublox_sara_n310/ublox_sara-n310.maintest

# Utility rule file for offsets_h.

# Include the progress variables for this target.
include zephyr/CMakeFiles/offsets_h.dir/progress.make

zephyr/CMakeFiles/offsets_h: zephyr/include/generated/offsets.h


zephyr/include/generated/offsets.h: zephyr/CMakeFiles/offsets.dir/arch/arm/core/offsets/offsets.c.obj
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --blue --bold --progress-dir=/home/ilagas/zephyrproject/zephyr/tests/drivers/modem/ublox_sara_n310/twister-out/qemu_cortex_m3/tests/drivers/modem/ublox_sara_n310/ublox_sara-n310.maintest/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Generating include/generated/offsets.h"
	cd /home/ilagas/zephyrproject/zephyr/tests/drivers/modem/ublox_sara_n310/twister-out/qemu_cortex_m3/tests/drivers/modem/ublox_sara_n310/ublox_sara-n310.maintest/zephyr && /usr/bin/python3.6 /home/ilagas/zephyrproject/zephyr/scripts/gen_offset_header.py -i /home/ilagas/zephyrproject/zephyr/tests/drivers/modem/ublox_sara_n310/twister-out/qemu_cortex_m3/tests/drivers/modem/ublox_sara_n310/ublox_sara-n310.maintest/zephyr/CMakeFiles/offsets.dir/arch/arm/core/offsets/offsets.c.obj -o /home/ilagas/zephyrproject/zephyr/tests/drivers/modem/ublox_sara_n310/twister-out/qemu_cortex_m3/tests/drivers/modem/ublox_sara_n310/ublox_sara-n310.maintest/zephyr/include/generated/offsets.h

offsets_h: zephyr/CMakeFiles/offsets_h
offsets_h: zephyr/include/generated/offsets.h
offsets_h: zephyr/CMakeFiles/offsets_h.dir/build.make

.PHONY : offsets_h

# Rule to build all files generated by this target.
zephyr/CMakeFiles/offsets_h.dir/build: offsets_h

.PHONY : zephyr/CMakeFiles/offsets_h.dir/build

zephyr/CMakeFiles/offsets_h.dir/clean:
	cd /home/ilagas/zephyrproject/zephyr/tests/drivers/modem/ublox_sara_n310/twister-out/qemu_cortex_m3/tests/drivers/modem/ublox_sara_n310/ublox_sara-n310.maintest/zephyr && $(CMAKE_COMMAND) -P CMakeFiles/offsets_h.dir/cmake_clean.cmake
.PHONY : zephyr/CMakeFiles/offsets_h.dir/clean

zephyr/CMakeFiles/offsets_h.dir/depend:
	cd /home/ilagas/zephyrproject/zephyr/tests/drivers/modem/ublox_sara_n310/twister-out/qemu_cortex_m3/tests/drivers/modem/ublox_sara_n310/ublox_sara-n310.maintest && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/ilagas/zephyrproject/zephyr/tests/drivers/modem/ublox_sara_n310 /home/ilagas/zephyrproject/zephyr /home/ilagas/zephyrproject/zephyr/tests/drivers/modem/ublox_sara_n310/twister-out/qemu_cortex_m3/tests/drivers/modem/ublox_sara_n310/ublox_sara-n310.maintest /home/ilagas/zephyrproject/zephyr/tests/drivers/modem/ublox_sara_n310/twister-out/qemu_cortex_m3/tests/drivers/modem/ublox_sara_n310/ublox_sara-n310.maintest/zephyr /home/ilagas/zephyrproject/zephyr/tests/drivers/modem/ublox_sara_n310/twister-out/qemu_cortex_m3/tests/drivers/modem/ublox_sara_n310/ublox_sara-n310.maintest/zephyr/CMakeFiles/offsets_h.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : zephyr/CMakeFiles/offsets_h.dir/depend

