# SPDX-License-Identifier: Apache-2.0

cmake_minimum_required(VERSION 3.13.1)
find_package(Zephyr REQUIRED HINTS $ENV{ZEPHYR_BASE})
project(ublox_sara_n310)


zephyr_library_include_directories(
    ${ZEPHYR_BASE}/include
    ${ZEPHYR_BASE}/subsys/net/lib/socks/
    ${ZEPHYR_BASE}/drivers/modem/
)

# zephyr_include_directories(
#     ${ZEPHYR_BASE}/include
#     ${ZEPHYR_BASE}/subsys/net/lib/sockets/
#     #${ZEPHYR_BASE}/drivers/modem/
#     # ${ZEPHYR_BASE}/subsys/net/lib/sockets
# )


# zephyr_include_directories(${ZEPHYR_BASE}/subsys/net/lib/socks)

target_sources(app PRIVATE src/main.c src/n310_stub.c src/n310_modem_cmd_handler_mock.c)









# zephyr_library_include_directories(
# 	${ZEPHYR_BASE}/../modules/lib/openthread/include/
# 	${ZEPHYR_BASE}/../modules/lib/openthread/src/posix/platform/
# 	${ZEPHYR_BASE}/subsys/net/lib/openthread/platform/
# 	${ZEPHYR_BASE}/../modules/lib/openthread/examples/platforms/
# 	)
