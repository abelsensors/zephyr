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

# Utility rule file for hardenconfig.

# Include the progress variables for this target.
include CMakeFiles/hardenconfig.dir/progress.make

CMakeFiles/hardenconfig:
	cd /home/ilagas/zephyrproject/zephyr/tests/drivers/modem/ublox_sara_n310/twister-out/mps2_an385/tests/drivers/modem/ublox_sara_n310/ublox_sara-n310.maintest/zephyr/kconfig && /usr/bin/cmake -E env ZEPHYR_BASE=/home/ilagas/zephyrproject/zephyr ZEPHYR_TOOLCHAIN_VARIANT=zephyr PYTHON_EXECUTABLE=/usr/bin/python3.6 srctree=/home/ilagas/zephyrproject/zephyr KERNELVERSION=0x2056300 KCONFIG_CONFIG=/home/ilagas/zephyrproject/zephyr/tests/drivers/modem/ublox_sara_n310/twister-out/mps2_an385/tests/drivers/modem/ublox_sara_n310/ublox_sara-n310.maintest/zephyr/.config ARCH=arm ARCH_DIR=/home/ilagas/zephyrproject/zephyr/arch BOARD_DIR=/home/ilagas/zephyrproject/zephyr/boards/arm/mps2_an385 KCONFIG_BINARY_DIR=/home/ilagas/zephyrproject/zephyr/tests/drivers/modem/ublox_sara_n310/twister-out/mps2_an385/tests/drivers/modem/ublox_sara_n310/ublox_sara-n310.maintest/Kconfig TOOLCHAIN_KCONFIG_DIR=/home/ilagas/zephyr-sdk-0.12.4/cmake/zephyr EDT_PICKLE=/home/ilagas/zephyrproject/zephyr/tests/drivers/modem/ublox_sara_n310/twister-out/mps2_an385/tests/drivers/modem/ublox_sara_n310/ublox_sara-n310.maintest/zephyr/edt.pickle ZEPHYR_CMSIS_MODULE_DIR=/home/ilagas/zephyrproject/modules/hal/cmsis ZEPHYR_ATMEL_MODULE_DIR=/home/ilagas/zephyrproject/modules/hal/atmel ZEPHYR_ALTERA_MODULE_DIR=/home/ilagas/zephyrproject/modules/hal/altera ZEPHYR_CANOPENNODE_MODULE_DIR=/home/ilagas/zephyrproject/modules/lib/canopennode ZEPHYR_CIVETWEB_MODULE_DIR=/home/ilagas/zephyrproject/modules/lib/civetweb ZEPHYR_ESPRESSIF_MODULE_DIR=/home/ilagas/zephyrproject/modules/hal/espressif ZEPHYR_FATFS_MODULE_DIR=/home/ilagas/zephyrproject/modules/fs/fatfs ZEPHYR_CYPRESS_MODULE_DIR=/home/ilagas/zephyrproject/modules/hal/cypress ZEPHYR_INFINEON_MODULE_DIR=/home/ilagas/zephyrproject/modules/hal/infineon ZEPHYR_HAL_NORDIC_MODULE_DIR=/home/ilagas/zephyrproject/modules/hal/nordic ZEPHYR_HAL_NORDIC_KCONFIG=/home/ilagas/zephyrproject/zephyr/modules/hal_nordic/Kconfig ZEPHYR_OPENISA_MODULE_DIR=/home/ilagas/zephyrproject/modules/hal/openisa ZEPHYR_NUVOTON_MODULE_DIR=/home/ilagas/zephyrproject/modules/hal/nuvoton ZEPHYR_MICROCHIP_MODULE_DIR=/home/ilagas/zephyrproject/modules/hal/microchip ZEPHYR_SILABS_MODULE_DIR=/home/ilagas/zephyrproject/modules/hal/silabs ZEPHYR_ST_MODULE_DIR=/home/ilagas/zephyrproject/modules/hal/st ZEPHYR_STM32_MODULE_DIR=/home/ilagas/zephyrproject/modules/hal/stm32 ZEPHYR_TI_MODULE_DIR=/home/ilagas/zephyrproject/modules/hal/ti ZEPHYR_LIBMETAL_MODULE_DIR=/home/ilagas/zephyrproject/modules/hal/libmetal ZEPHYR_QUICKLOGIC_MODULE_DIR=/home/ilagas/zephyrproject/modules/hal/quicklogic ZEPHYR_LVGL_MODULE_DIR=/home/ilagas/zephyrproject/modules/lib/gui/lvgl ZEPHYR_MBEDTLS_MODULE_DIR=/home/ilagas/zephyrproject/modules/crypto/mbedtls ZEPHYR_MCUBOOT_MODULE_DIR=/home/ilagas/zephyrproject/bootloader/mcuboot ZEPHYR_MCUMGR_MODULE_DIR=/home/ilagas/zephyrproject/modules/lib/mcumgr ZEPHYR_NXP_MODULE_DIR=/home/ilagas/zephyrproject/modules/hal/nxp ZEPHYR_OPEN_AMP_MODULE_DIR=/home/ilagas/zephyrproject/modules/lib/open-amp ZEPHYR_LORAMAC_NODE_MODULE_DIR=/home/ilagas/zephyrproject/modules/lib/loramac-node ZEPHYR_OPENTHREAD_MODULE_DIR=/home/ilagas/zephyrproject/modules/lib/openthread ZEPHYR_SEGGER_MODULE_DIR=/home/ilagas/zephyrproject/modules/debug/segger ZEPHYR_SOF_MODULE_DIR=/home/ilagas/zephyrproject/modules/audio/sof ZEPHYR_TINYCBOR_MODULE_DIR=/home/ilagas/zephyrproject/modules/lib/tinycbor ZEPHYR_TINYCRYPT_MODULE_DIR=/home/ilagas/zephyrproject/modules/crypto/tinycrypt ZEPHYR_LITTLEFS_MODULE_DIR=/home/ilagas/zephyrproject/modules/fs/littlefs ZEPHYR_MIPI_SYS_T_MODULE_DIR=/home/ilagas/zephyrproject/modules/debug/mipi-sys-t ZEPHYR_NRF_HW_MODELS_MODULE_DIR=/home/ilagas/zephyrproject/modules/bsim_hw_models/nrf_hw_models ZEPHYR_XTENSA_MODULE_DIR=/home/ilagas/zephyrproject/modules/hal/xtensa ZEPHYR_TRUSTED_FIRMWARE_M_MODULE_DIR=/home/ilagas/zephyrproject/modules/tee/tfm ZEPHYR_TRUSTED_FIRMWARE_M_KCONFIG=/home/ilagas/zephyrproject/zephyr/modules/trusted-firmware-m/Kconfig ZEPHYR_TFM_MCUBOOT_MODULE_DIR=/home/ilagas/zephyrproject/modules/tee/tfm-mcuboot SHIELD_AS_LIST= EXTRA_DTC_FLAGS= DTS_POST_CPP=/home/ilagas/zephyrproject/zephyr/tests/drivers/modem/ublox_sara_n310/twister-out/mps2_an385/tests/drivers/modem/ublox_sara_n310/ublox_sara-n310.maintest/zephyr/mps2_an385.dts.pre.tmp DTS_ROOT_BINDINGS=/home/ilagas/zephyrproject/zephyr/dts/bindings /usr/bin/python3.6 /home/ilagas/zephyrproject/zephyr/scripts/kconfig/hardenconfig.py /home/ilagas/zephyrproject/zephyr/Kconfig

hardenconfig: CMakeFiles/hardenconfig
hardenconfig: CMakeFiles/hardenconfig.dir/build.make

.PHONY : hardenconfig

# Rule to build all files generated by this target.
CMakeFiles/hardenconfig.dir/build: hardenconfig

.PHONY : CMakeFiles/hardenconfig.dir/build

CMakeFiles/hardenconfig.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/hardenconfig.dir/cmake_clean.cmake
.PHONY : CMakeFiles/hardenconfig.dir/clean

CMakeFiles/hardenconfig.dir/depend:
	cd /home/ilagas/zephyrproject/zephyr/tests/drivers/modem/ublox_sara_n310/twister-out/mps2_an385/tests/drivers/modem/ublox_sara_n310/ublox_sara-n310.maintest && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/ilagas/zephyrproject/zephyr/tests/drivers/modem/ublox_sara_n310 /home/ilagas/zephyrproject/zephyr/tests/drivers/modem/ublox_sara_n310 /home/ilagas/zephyrproject/zephyr/tests/drivers/modem/ublox_sara_n310/twister-out/mps2_an385/tests/drivers/modem/ublox_sara_n310/ublox_sara-n310.maintest /home/ilagas/zephyrproject/zephyr/tests/drivers/modem/ublox_sara_n310/twister-out/mps2_an385/tests/drivers/modem/ublox_sara_n310/ublox_sara-n310.maintest /home/ilagas/zephyrproject/zephyr/tests/drivers/modem/ublox_sara_n310/twister-out/mps2_an385/tests/drivers/modem/ublox_sara_n310/ublox_sara-n310.maintest/CMakeFiles/hardenconfig.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/hardenconfig.dir/depend

