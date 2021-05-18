/*
 * Copyright (c) 2021 Abel Sensors
 *
 * SPDX-License-Identifier: Apache-2.0
 */

/* needed here so the static device_get_binding does not get renamed */
#include <device.h>
#include <sys_clock.h>
#include <modem_context.h>
#include <modem_cmd_handler.h>
#include <modem_iface_uart.h>

// #define CONFIG_SERIAL_SUPPORT_INTERRUPT=y
// #define CONFIG_MODEM_CONTEXT 
// #define CONFIG_MODEM

// void modem_cmd_send(void){

// }




int modem_cmd_send(struct modem_iface *iface,
		   struct modem_cmd_handler *handler,
		   const struct modem_cmd *handler_cmds,
		   size_t handler_cmds_len, const uint8_t *buf,
		   struct k_sem *sem, k_timeout_t timeout)
{
	return 0;
}

int modem_cmd_handler_setup_cmds(struct modem_iface *iface,
				 struct modem_cmd_handler *handler,
				 const struct setup_cmd *cmds, size_t cmds_len,
				 struct k_sem *sem, k_timeout_t timeout)
{
	return 0;
}


int modem_cmd_send_nolock(struct modem_iface *iface,
			  struct modem_cmd_handler *handler,
			  const struct modem_cmd *handler_cmds,
			  size_t handler_cmds_len,
			  const uint8_t *buf, struct k_sem *sem,
			  k_timeout_t timeout)
{
	return 0;
}


int modem_cmd_handler_init(struct modem_cmd_handler *handler,
			   struct modem_cmd_handler_data *data)
{
    return 0;
}


int modem_iface_uart_init(struct modem_iface *iface,
			  struct modem_iface_uart_data *data,
			  const char *dev_name)
{
    return 0;
}

int modem_cmd_handler_set_error(struct modem_cmd_handler_data *data,
				int error_code)
{
    return 0;
}


int modem_cmd_handler_get_error(struct modem_cmd_handler_data *data)
{
	return 0;
}

int modem_cmd_handler_update_cmds(struct modem_cmd_handler_data *data,
				  const struct modem_cmd *handler_cmds,
				  size_t handler_cmds_len,
				  bool reset_error_flag)
{
    return 0;
}

uint32_t z_impl_sys_rand32_get(void)
{
return 3;
}

/* needed for stubbing device driver */
const struct device *device_get_binding_stub(const char *name);
#define device_get_binding device_get_binding_stub
#define  CONFIG_MODEM_UBLOX_SARA_N310_INIT_PRIORITY 80


/* file itself */
 #include "ublox-sara-n310.c"

// extern const struct socket_op_vtable offload_socket_fd_op_vtable;
struct socket_op_vtable* offload_socket_fd_op_vtable_mock = (struct socket_op_vtable*)(&offload_socket_fd_op_vtable);