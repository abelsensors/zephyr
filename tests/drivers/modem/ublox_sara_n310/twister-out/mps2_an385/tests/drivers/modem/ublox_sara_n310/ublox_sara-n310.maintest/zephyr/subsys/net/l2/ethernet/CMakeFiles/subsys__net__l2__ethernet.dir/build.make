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

# Include any dependencies generated for this target.
include zephyr/subsys/net/l2/ethernet/CMakeFiles/subsys__net__l2__ethernet.dir/depend.make

# Include the progress variables for this target.
include zephyr/subsys/net/l2/ethernet/CMakeFiles/subsys__net__l2__ethernet.dir/progress.make

# Include the compile flags for this target's objects.
include zephyr/subsys/net/l2/ethernet/CMakeFiles/subsys__net__l2__ethernet.dir/flags.make

zephyr/subsys/net/l2/ethernet/CMakeFiles/subsys__net__l2__ethernet.dir/ethernet.c.obj: zephyr/subsys/net/l2/ethernet/CMakeFiles/subsys__net__l2__ethernet.dir/flags.make
zephyr/subsys/net/l2/ethernet/CMakeFiles/subsys__net__l2__ethernet.dir/ethernet.c.obj: ../../../../../../../../../../../subsys/net/l2/ethernet/ethernet.c
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/ilagas/zephyrproject/zephyr/tests/drivers/modem/ublox_sara_n310/twister-out/mps2_an385/tests/drivers/modem/ublox_sara_n310/ublox_sara-n310.maintest/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building C object zephyr/subsys/net/l2/ethernet/CMakeFiles/subsys__net__l2__ethernet.dir/ethernet.c.obj"
	cd /home/ilagas/zephyrproject/zephyr/tests/drivers/modem/ublox_sara_n310/twister-out/mps2_an385/tests/drivers/modem/ublox_sara_n310/ublox_sara-n310.maintest/zephyr/subsys/net/l2/ethernet && ccache /home/ilagas/zephyr-sdk-0.12.4/arm-zephyr-eabi/bin/arm-zephyr-eabi-gcc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -o CMakeFiles/subsys__net__l2__ethernet.dir/ethernet.c.obj   -c /home/ilagas/zephyrproject/zephyr/subsys/net/l2/ethernet/ethernet.c

zephyr/subsys/net/l2/ethernet/CMakeFiles/subsys__net__l2__ethernet.dir/ethernet.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/subsys__net__l2__ethernet.dir/ethernet.c.i"
	cd /home/ilagas/zephyrproject/zephyr/tests/drivers/modem/ublox_sara_n310/twister-out/mps2_an385/tests/drivers/modem/ublox_sara_n310/ublox_sara-n310.maintest/zephyr/subsys/net/l2/ethernet && /home/ilagas/zephyr-sdk-0.12.4/arm-zephyr-eabi/bin/arm-zephyr-eabi-gcc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /home/ilagas/zephyrproject/zephyr/subsys/net/l2/ethernet/ethernet.c > CMakeFiles/subsys__net__l2__ethernet.dir/ethernet.c.i

zephyr/subsys/net/l2/ethernet/CMakeFiles/subsys__net__l2__ethernet.dir/ethernet.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/subsys__net__l2__ethernet.dir/ethernet.c.s"
	cd /home/ilagas/zephyrproject/zephyr/tests/drivers/modem/ublox_sara_n310/twister-out/mps2_an385/tests/drivers/modem/ublox_sara_n310/ublox_sara-n310.maintest/zephyr/subsys/net/l2/ethernet && /home/ilagas/zephyr-sdk-0.12.4/arm-zephyr-eabi/bin/arm-zephyr-eabi-gcc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /home/ilagas/zephyrproject/zephyr/subsys/net/l2/ethernet/ethernet.c -o CMakeFiles/subsys__net__l2__ethernet.dir/ethernet.c.s

zephyr/subsys/net/l2/ethernet/CMakeFiles/subsys__net__l2__ethernet.dir/arp.c.obj: zephyr/subsys/net/l2/ethernet/CMakeFiles/subsys__net__l2__ethernet.dir/flags.make
zephyr/subsys/net/l2/ethernet/CMakeFiles/subsys__net__l2__ethernet.dir/arp.c.obj: ../../../../../../../../../../../subsys/net/l2/ethernet/arp.c
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/ilagas/zephyrproject/zephyr/tests/drivers/modem/ublox_sara_n310/twister-out/mps2_an385/tests/drivers/modem/ublox_sara_n310/ublox_sara-n310.maintest/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Building C object zephyr/subsys/net/l2/ethernet/CMakeFiles/subsys__net__l2__ethernet.dir/arp.c.obj"
	cd /home/ilagas/zephyrproject/zephyr/tests/drivers/modem/ublox_sara_n310/twister-out/mps2_an385/tests/drivers/modem/ublox_sara_n310/ublox_sara-n310.maintest/zephyr/subsys/net/l2/ethernet && ccache /home/ilagas/zephyr-sdk-0.12.4/arm-zephyr-eabi/bin/arm-zephyr-eabi-gcc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -o CMakeFiles/subsys__net__l2__ethernet.dir/arp.c.obj   -c /home/ilagas/zephyrproject/zephyr/subsys/net/l2/ethernet/arp.c

zephyr/subsys/net/l2/ethernet/CMakeFiles/subsys__net__l2__ethernet.dir/arp.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/subsys__net__l2__ethernet.dir/arp.c.i"
	cd /home/ilagas/zephyrproject/zephyr/tests/drivers/modem/ublox_sara_n310/twister-out/mps2_an385/tests/drivers/modem/ublox_sara_n310/ublox_sara-n310.maintest/zephyr/subsys/net/l2/ethernet && /home/ilagas/zephyr-sdk-0.12.4/arm-zephyr-eabi/bin/arm-zephyr-eabi-gcc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /home/ilagas/zephyrproject/zephyr/subsys/net/l2/ethernet/arp.c > CMakeFiles/subsys__net__l2__ethernet.dir/arp.c.i

zephyr/subsys/net/l2/ethernet/CMakeFiles/subsys__net__l2__ethernet.dir/arp.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/subsys__net__l2__ethernet.dir/arp.c.s"
	cd /home/ilagas/zephyrproject/zephyr/tests/drivers/modem/ublox_sara_n310/twister-out/mps2_an385/tests/drivers/modem/ublox_sara_n310/ublox_sara-n310.maintest/zephyr/subsys/net/l2/ethernet && /home/ilagas/zephyr-sdk-0.12.4/arm-zephyr-eabi/bin/arm-zephyr-eabi-gcc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /home/ilagas/zephyrproject/zephyr/subsys/net/l2/ethernet/arp.c -o CMakeFiles/subsys__net__l2__ethernet.dir/arp.c.s

# Object files for target subsys__net__l2__ethernet
subsys__net__l2__ethernet_OBJECTS = \
"CMakeFiles/subsys__net__l2__ethernet.dir/ethernet.c.obj" \
"CMakeFiles/subsys__net__l2__ethernet.dir/arp.c.obj"

# External object files for target subsys__net__l2__ethernet
subsys__net__l2__ethernet_EXTERNAL_OBJECTS =

zephyr/subsys/net/l2/ethernet/libsubsys__net__l2__ethernet.a: zephyr/subsys/net/l2/ethernet/CMakeFiles/subsys__net__l2__ethernet.dir/ethernet.c.obj
zephyr/subsys/net/l2/ethernet/libsubsys__net__l2__ethernet.a: zephyr/subsys/net/l2/ethernet/CMakeFiles/subsys__net__l2__ethernet.dir/arp.c.obj
zephyr/subsys/net/l2/ethernet/libsubsys__net__l2__ethernet.a: zephyr/subsys/net/l2/ethernet/CMakeFiles/subsys__net__l2__ethernet.dir/build.make
zephyr/subsys/net/l2/ethernet/libsubsys__net__l2__ethernet.a: zephyr/subsys/net/l2/ethernet/CMakeFiles/subsys__net__l2__ethernet.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/ilagas/zephyrproject/zephyr/tests/drivers/modem/ublox_sara_n310/twister-out/mps2_an385/tests/drivers/modem/ublox_sara_n310/ublox_sara-n310.maintest/CMakeFiles --progress-num=$(CMAKE_PROGRESS_3) "Linking C static library libsubsys__net__l2__ethernet.a"
	cd /home/ilagas/zephyrproject/zephyr/tests/drivers/modem/ublox_sara_n310/twister-out/mps2_an385/tests/drivers/modem/ublox_sara_n310/ublox_sara-n310.maintest/zephyr/subsys/net/l2/ethernet && $(CMAKE_COMMAND) -P CMakeFiles/subsys__net__l2__ethernet.dir/cmake_clean_target.cmake
	cd /home/ilagas/zephyrproject/zephyr/tests/drivers/modem/ublox_sara_n310/twister-out/mps2_an385/tests/drivers/modem/ublox_sara_n310/ublox_sara-n310.maintest/zephyr/subsys/net/l2/ethernet && $(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/subsys__net__l2__ethernet.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
zephyr/subsys/net/l2/ethernet/CMakeFiles/subsys__net__l2__ethernet.dir/build: zephyr/subsys/net/l2/ethernet/libsubsys__net__l2__ethernet.a

.PHONY : zephyr/subsys/net/l2/ethernet/CMakeFiles/subsys__net__l2__ethernet.dir/build

zephyr/subsys/net/l2/ethernet/CMakeFiles/subsys__net__l2__ethernet.dir/clean:
	cd /home/ilagas/zephyrproject/zephyr/tests/drivers/modem/ublox_sara_n310/twister-out/mps2_an385/tests/drivers/modem/ublox_sara_n310/ublox_sara-n310.maintest/zephyr/subsys/net/l2/ethernet && $(CMAKE_COMMAND) -P CMakeFiles/subsys__net__l2__ethernet.dir/cmake_clean.cmake
.PHONY : zephyr/subsys/net/l2/ethernet/CMakeFiles/subsys__net__l2__ethernet.dir/clean

zephyr/subsys/net/l2/ethernet/CMakeFiles/subsys__net__l2__ethernet.dir/depend:
	cd /home/ilagas/zephyrproject/zephyr/tests/drivers/modem/ublox_sara_n310/twister-out/mps2_an385/tests/drivers/modem/ublox_sara_n310/ublox_sara-n310.maintest && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/ilagas/zephyrproject/zephyr/tests/drivers/modem/ublox_sara_n310 /home/ilagas/zephyrproject/zephyr/subsys/net/l2/ethernet /home/ilagas/zephyrproject/zephyr/tests/drivers/modem/ublox_sara_n310/twister-out/mps2_an385/tests/drivers/modem/ublox_sara_n310/ublox_sara-n310.maintest /home/ilagas/zephyrproject/zephyr/tests/drivers/modem/ublox_sara_n310/twister-out/mps2_an385/tests/drivers/modem/ublox_sara_n310/ublox_sara-n310.maintest/zephyr/subsys/net/l2/ethernet /home/ilagas/zephyrproject/zephyr/tests/drivers/modem/ublox_sara_n310/twister-out/mps2_an385/tests/drivers/modem/ublox_sara_n310/ublox_sara-n310.maintest/zephyr/subsys/net/l2/ethernet/CMakeFiles/subsys__net__l2__ethernet.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : zephyr/subsys/net/l2/ethernet/CMakeFiles/subsys__net__l2__ethernet.dir/depend

