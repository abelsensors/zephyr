/*
 * Copyright (c) 2021 Abel Sensors
 *
 * SPDX-License-Identifier: Apache-2.0
 */

/* needed here so the static device_get_binding does not get renamed */
#include <device.h>

// #define CONFIG_SERIAL_SUPPORT_INTERRUPT=y
// #define CONFIG_MODEM_CONTEXT 
// #define CONFIG_MODEM

// void modem_cmd_send(void){

// }

// modem_cmd_handler_set_error
// modem_cmd_send_nolock
// modem_cmd_handler_set_error
// modem_cmd_handler_set_error

/* needed for stubbing device driver */
const struct device *device_get_binding_stub(const char *name);
#define device_get_binding device_get_binding_stub



/* file itself */
//  #include "ublox-sara-n310.c"
