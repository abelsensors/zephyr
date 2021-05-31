# SPDX-License-Identifier: Apache-2.0

cmake_minimum_required(VERSION 3.13.1)
find_package(Zephyr REQUIRED HINTS $ENV{ZEPHYR_BASE})
project(ublox_sara_n310)


zephyr_library_include_directories(
    ${ZEPHYR_BASE}/include
    ${ZEPHYR_BASE}/subsys/net/lib/socks/
    ${ZEPHYR_BASE}/drivers/modem/
)

target_sources(app PRIVATE src/main.c src/n310_stub.c )
