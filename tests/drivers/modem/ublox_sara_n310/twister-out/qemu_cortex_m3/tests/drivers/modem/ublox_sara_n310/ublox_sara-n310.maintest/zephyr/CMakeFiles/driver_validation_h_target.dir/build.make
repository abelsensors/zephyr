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

# Utility rule file for driver_validation_h_target.

# Include the progress variables for this target.
include zephyr/CMakeFiles/driver_validation_h_target.dir/progress.make

zephyr/CMakeFiles/driver_validation_h_target: zephyr/include/generated/driver-validation.h


zephyr/include/generated/driver-validation.h: ../../../../../../../../../../../scripts/gen_kobject_list.py
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --blue --bold --progress-dir=/home/ilagas/zephyrproject/zephyr/tests/drivers/modem/ublox_sara_n310/twister-out/qemu_cortex_m3/tests/drivers/modem/ublox_sara_n310/ublox_sara-n310.maintest/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Generating include/generated/driver-validation.h"
	cd /home/ilagas/zephyrproject/zephyr/tests/drivers/modem/ublox_sara_n310/twister-out/qemu_cortex_m3/tests/drivers/modem/ublox_sara_n310/ublox_sara-n310.maintest/zephyr && /usr/bin/python3.6 /home/ilagas/zephyrproject/zephyr/scripts/gen_kobject_list.py --validation-output /home/ilagas/zephyrproject/zephyr/tests/drivers/modem/ublox_sara_n310/twister-out/qemu_cortex_m3/tests/drivers/modem/ublox_sara_n310/ublox_sara-n310.maintest/zephyr/include/generated/driver-validation.h --include /home/ilagas/zephyrproject/zephyr/tests/drivers/modem/ublox_sara_n310/twister-out/qemu_cortex_m3/tests/drivers/modem/ublox_sara_n310/ublox_sara-n310.maintest/zephyr/misc/generated/struct_tags.json 

driver_validation_h_target: zephyr/CMakeFiles/driver_validation_h_target
driver_validation_h_target: zephyr/include/generated/driver-validation.h
driver_validation_h_target: zephyr/CMakeFiles/driver_validation_h_target.dir/build.make

.PHONY : driver_validation_h_target

# Rule to build all files generated by this target.
zephyr/CMakeFiles/driver_validation_h_target.dir/build: driver_validation_h_target

.PHONY : zephyr/CMakeFiles/driver_validation_h_target.dir/build

zephyr/CMakeFiles/driver_validation_h_target.dir/clean:
	cd /home/ilagas/zephyrproject/zephyr/tests/drivers/modem/ublox_sara_n310/twister-out/qemu_cortex_m3/tests/drivers/modem/ublox_sara_n310/ublox_sara-n310.maintest/zephyr && $(CMAKE_COMMAND) -P CMakeFiles/driver_validation_h_target.dir/cmake_clean.cmake
.PHONY : zephyr/CMakeFiles/driver_validation_h_target.dir/clean

zephyr/CMakeFiles/driver_validation_h_target.dir/depend:
	cd /home/ilagas/zephyrproject/zephyr/tests/drivers/modem/ublox_sara_n310/twister-out/qemu_cortex_m3/tests/drivers/modem/ublox_sara_n310/ublox_sara-n310.maintest && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/ilagas/zephyrproject/zephyr/tests/drivers/modem/ublox_sara_n310 /home/ilagas/zephyrproject/zephyr /home/ilagas/zephyrproject/zephyr/tests/drivers/modem/ublox_sara_n310/twister-out/qemu_cortex_m3/tests/drivers/modem/ublox_sara_n310/ublox_sara-n310.maintest /home/ilagas/zephyrproject/zephyr/tests/drivers/modem/ublox_sara_n310/twister-out/qemu_cortex_m3/tests/drivers/modem/ublox_sara_n310/ublox_sara-n310.maintest/zephyr /home/ilagas/zephyrproject/zephyr/tests/drivers/modem/ublox_sara_n310/twister-out/qemu_cortex_m3/tests/drivers/modem/ublox_sara_n310/ublox_sara-n310.maintest/zephyr/CMakeFiles/driver_validation_h_target.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : zephyr/CMakeFiles/driver_validation_h_target.dir/depend

