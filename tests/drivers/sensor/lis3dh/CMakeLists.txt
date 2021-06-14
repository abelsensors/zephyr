#
# Copyright (c) 2018, Yannis Damigos
#
# SPDX-License-Identifier: Apache-2.0
#

cmake_minimum_required(VERSION 3.13.1)
find_package(Zephyr REQUIRED HINTS $ENV{ZEPHYR_BASE})
project(lis2dh)


zephyr_library_sources(
    # ${ZEPHYR_BASE}/drivers/sensor/lis2dh/lis2dh_trigger.c
    # ${ZEPHYR_BASE}/drivers/sensor/lis2dh/lis2dh.c
    # ${ZEPHYR_BASE}/drivers/sensor/lis2dh/lis2dh_spi.c
   ${ZEPHYR_BASE}/drivers/sensor/lis2dh/lis2dh.h
)

zephyr_library_include_directories(
    ${ZEPHYR_BASE}/drivers/sensor/lis2dh/
	)

FILE(GLOB app_sources src/*.c)
target_sources(app PRIVATE ${app_sources})
