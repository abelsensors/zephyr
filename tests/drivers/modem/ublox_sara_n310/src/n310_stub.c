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
#include <ztest.h>
#include "modem_cmd_handler.h"
#include "n310_modem_cmd_handler_mock.h"


#include <zephyr.h>
#include <net/socket.h>
#include <drivers/modem/ublox-sara-n310.h>
#include <ztest.h>
#include <device.h>
#include "sockets_internal.h"
#include <sys/fdtable.h>


#include <modem_context.h>
#include <modem_cmd_handler.h>
#include <modem_iface_uart.h>
#include <ztest.h>



static void cmd_handler_process(struct modem_cmd_handler *cmd_handler,
				struct modem_iface *iface)
{
	struct modem_cmd_handler_data *data;
	int err;

	if (!cmd_handler || !cmd_handler->cmd_handler_data ||
	    !iface || !iface->read) {
		return;
	}

	data = (struct modem_cmd_handler_data *)(cmd_handler->cmd_handler_data);

	do {
		err = cmd_handler_process_iface_data(data, iface);
		cmd_handler_process_rx_buf(data);
	} while (err);
}

int modem_cmd_send(struct modem_iface *iface, struct modem_cmd_handler *handler,
		   const struct modem_cmd *handler_cmds,
		   size_t handler_cmds_len, const uint8_t *buf,
		   struct k_sem *sem, k_timeout_t timeout)
{
	if (!iface || !handler || !handler->cmd_handler_data || !buf) {
		// return -EINVAL;
		printk("modem not set correctly");
		printk("iface: %x\n", (unsigned int)iface);
		printk("handler: %x\n", (unsigned int)handler);
		printk("cmd handler data: %x\n", (unsigned int)handler->cmd_handler_data);
		printk("buf: %x\n", (unsigned int)buf);
	}
	int ret = 0;

	if (!iface || !handler || !handler->cmd_handler_data || !buf) {
		return -EINVAL;
	}
struct modem_cmd_handler_data *data;
	bool no_tx_lock = false;

	if (K_TIMEOUT_EQ(timeout, K_NO_WAIT)) {
		/* semaphore is not needed if there is no timeout */
		sem = NULL;
	} else if (!sem) {
		/* cannot respect timeout without semaphore */
		return -EINVAL;
	}

	data = (struct modem_cmd_handler_data *)(handler->cmd_handler_data);
	if (!no_tx_lock) {
		k_sem_take(&data->sem_tx_lock, K_FOREVER);
	}

	ret = modem_cmd_handler_update_cmds(data, handler_cmds,
					    handler_cmds_len, true);
	if (ret < 0) {
		goto unlock_tx_lock;
	}
	if (sem) {
		k_sem_reset(sem);
	}

	// iface->write(iface, buf, strlen(buf));
	// iface->write(iface, data->eol, data->eol_len);

	if (sem) {
		ret = k_sem_take(sem, timeout);

		if (ret == 0) {
			ret = data->last_error;
		} else if (ret == -EAGAIN) {
			ret = -ETIMEDOUT;
		}
	}
	
	/* unset handlers and ignore any errors */
	(void)modem_cmd_handler_update_cmds(data, NULL, 0U, false);

unlock_tx_lock:
	if (!no_tx_lock) {
		k_sem_give(&data->sem_tx_lock);
	}
	return ret;
}

int modem_cmd_send_nolock(struct modem_iface *iface,
			  struct modem_cmd_handler *handler,
			  const struct modem_cmd *handler_cmds,
			  size_t handler_cmds_len,
			  const uint8_t *buf, struct k_sem *sem,
			  k_timeout_t timeout)
{
    printk("modem_cmd_send_nolock");

	return 0;
}



int modem_cmd_handler_init(struct modem_cmd_handler *handler,
			   struct modem_cmd_handler_data *data)
{
    printk("handler_init\n");

    if (!handler || !data) {
	    return -EINVAL;
    }

	if (!data->match_buf_len) {
		return -EINVAL;
	}

	if (data->eol == NULL) {
		data->eol_len = 0;
	} else {
		data->eol_len = strlen(data->eol);
	}

	handler->cmd_handler_data = data;
	handler->process = cmd_handler_process;

	k_sem_init(&data->sem_tx_lock,    1, 1);
	k_sem_init(&data->sem_parse_lock, 1, 1);


    return 0;
}


int modem_iface_uart_init(struct modem_iface *iface,
			  struct modem_iface_uart_data *data,
			  const char *dev_name)
{
    printk("uart_init\n");
	/* get UART device */
	const struct device *dev = device_get_binding(dev_name);
	// const struct device *prev = iface->dev;

	if (!dev) {
		printk("no dev in uart init\n");
		return -ENODEV;
	}

	/* Check if there's already a device inited to this iface. If so,
	 * interrupts needs to be disabled on that too before switching to avoid
	 * race conditions with modem_iface_uart_isr.
	 */
	// if (prev) {
	// 	uart_irq_tx_disable(prev);
	// 	uart_irq_rx_disable(prev);
	// }

	// uart_irq_rx_disable(dev);
	// uart_irq_tx_disable(dev);
	// iface->dev = dev;

	// modem_iface_uart_flush(iface);
	// uart_irq_callback_set(iface->dev, modem_iface_uart_isr);
	// uart_irq_rx_enable(iface->dev);

	// if (prev) {
	// 	uart_irq_rx_enable(prev);
	// }

	return 0;
}

int modem_cmd_handler_set_error(struct modem_cmd_handler_data *data,
				int error_code)
{
    printk("set_error");
	if (!data) {
		printk("no data!\n");
		return -EINVAL;
	}

	data->last_error = error_code;
    return 0;
}


int modem_cmd_handler_get_error(struct modem_cmd_handler_data *data)
{
    printk("get_error");
if (!data) {
	printk("no data set!\n");
		return -EINVAL;
	}

	return data->last_error;
}

int modem_cmd_handler_update_cmds(struct modem_cmd_handler_data *data,
				  const struct modem_cmd *handler_cmds,
				  size_t handler_cmds_len,
				  bool reset_error_flag)
{
    printk("modem_cmd_handler_update_cmds\n");

	if (!data) {
		printk("no data!");
		return -EINVAL;
	}

	data->cmds[CMD_HANDLER] = handler_cmds;
	data->cmds_len[CMD_HANDLER] = handler_cmds_len;
	if (reset_error_flag) {
		data->last_error = 0;
	}
    return 0;
}

int z_impl_sys_rand32_get(void)
{
	printk("z_impl_sys_rand32_get\n");
	return 32;
}


/* run a set of AT commands */
int modem_cmd_handler_setup_cmds(struct modem_iface *iface,
				 struct modem_cmd_handler *handler,
				 const struct setup_cmd *cmds, size_t cmds_len,
				 struct k_sem *sem, k_timeout_t timeout)
{
	int ret = 0, i;

	for (i = 0; i < cmds_len; i++) {
		if (i) {
			//k_sleep(K_MSEC(50));
		}

		if (cmds[i].handle_cmd.cmd && cmds[i].handle_cmd.func) {
			ret = modem_cmd_send(iface, handler,
					     &cmds[i].handle_cmd, 1U,
					     cmds[i].send_cmd,
					     sem, timeout);
		} else {
			ret = modem_cmd_send(iface, handler,
					     NULL, 0, cmds[i].send_cmd,
					     sem, timeout);
		}

		if (ret < 0) {
			printk("!!!!!!!!!!!!!");
	//		LOG_ERR("command %s ret:%d",
		//		log_strdup(cmds[i].send_cmd), ret);
			break;
		}
	}

	return ret;
}



/* needed for stubbing device driver */
const struct device *device_get_binding_stub(const char *name);
#define device_get_binding device_get_binding_stub
#define  CONFIG_MODEM_UBLOX_SARA_N310_INIT_PRIORITY 80

#define k_sleep k_sleep_stub
void k_sleep_stub(k_timeout_t a) {}

/* file itself */
 #include "ublox-sara-n310.c"

//extern const struct socket_op_vtable offload_socket_fd_op_vtable;
//struct socket_op_vtable* offload_socket_fd_op_vtable_mock = (struct socket_op_vtable*)(&offload_socket_fd_op_vtable);