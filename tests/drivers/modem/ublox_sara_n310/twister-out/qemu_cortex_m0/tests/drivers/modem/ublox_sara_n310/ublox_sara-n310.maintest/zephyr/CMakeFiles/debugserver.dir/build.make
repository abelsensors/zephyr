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
CMAKE_BINARY_DIR = /home/ilagas/zephyrproject/zephyr/tests/drivers/modem/ublox_sara_n310/twister-out/qemu_cortex_m0/tests/drivers/modem/ublox_sara_n310/ublox_sara-n310.maintest

# Utility rule file for debugserver.

# Include the progress variables for this target.
include zephyr/CMakeFiles/debugserver.dir/progress.make

zephyr/CMakeFiles/debugserver: zephyr/zephyr.elf
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --blue --bold --progress-dir=/home/ilagas/zephyrproject/zephyr/tests/drivers/modem/ublox_sara_n310/twister-out/qemu_cortex_m0/tests/drivers/modem/ublox_sara_n310/ublox_sara-n310.maintest/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "[QEMU] CPU: cortex-m0"
	/home/ilagas/zephyr-sdk-0.12.4/sysroots/x86_64-pokysdk-linux/usr/bin/qemu-system-arm -cpu cortex-m0 -machine microbit -nographic -vga none -net none -pidfile qemu${QEMU_INSTANCE}.pid -chardev pipe,id=con,mux=on,path=/home/ilagas/zephyrproject/zephyr/tests/drivers/modem/ublox_sara_n310/twister-out/qemu_cortex_m0/tests/drivers/modem/ublox_sara_n310/ublox_sara-n310.maintest/qemu-fifo -serial chardev:con -mon chardev=con,mode=readline -serial unix:/tmp/slip.sock${QEMU_INSTANCE} -s -S -kernel /home/ilagas/zephyrproject/zephyr/tests/drivers/modem/ublox_sara_n310/twister-out/qemu_cortex_m0/tests/drivers/modem/ublox_sara_n310/ublox_sara-n310.maintest/zephyr/zephyr.elf

debugserver: zephyr/CMakeFiles/debugserver
debugserver: zephyr/CMakeFiles/debugserver.dir/build.make

.PHONY : debugserver

# Rule to build all files generated by this target.
zephyr/CMakeFiles/debugserver.dir/build: debugserver

.PHONY : zephyr/CMakeFiles/debugserver.dir/build

zephyr/CMakeFiles/debugserver.dir/clean:
	cd /home/ilagas/zephyrproject/zephyr/tests/drivers/modem/ublox_sara_n310/twister-out/qemu_cortex_m0/tests/drivers/modem/ublox_sara_n310/ublox_sara-n310.maintest/zephyr && $(CMAKE_COMMAND) -P CMakeFiles/debugserver.dir/cmake_clean.cmake
.PHONY : zephyr/CMakeFiles/debugserver.dir/clean

zephyr/CMakeFiles/debugserver.dir/depend:
	cd /home/ilagas/zephyrproject/zephyr/tests/drivers/modem/ublox_sara_n310/twister-out/qemu_cortex_m0/tests/drivers/modem/ublox_sara_n310/ublox_sara-n310.maintest && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/ilagas/zephyrproject/zephyr/tests/drivers/modem/ublox_sara_n310 /home/ilagas/zephyrproject/zephyr /home/ilagas/zephyrproject/zephyr/tests/drivers/modem/ublox_sara_n310/twister-out/qemu_cortex_m0/tests/drivers/modem/ublox_sara_n310/ublox_sara-n310.maintest /home/ilagas/zephyrproject/zephyr/tests/drivers/modem/ublox_sara_n310/twister-out/qemu_cortex_m0/tests/drivers/modem/ublox_sara_n310/ublox_sara-n310.maintest/zephyr /home/ilagas/zephyrproject/zephyr/tests/drivers/modem/ublox_sara_n310/twister-out/qemu_cortex_m0/tests/drivers/modem/ublox_sara_n310/ublox_sara-n310.maintest/zephyr/CMakeFiles/debugserver.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : zephyr/CMakeFiles/debugserver.dir/depend

