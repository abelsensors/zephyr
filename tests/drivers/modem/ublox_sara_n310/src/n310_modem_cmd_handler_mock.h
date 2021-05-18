
 
#include <device.h>
#include <sys_clock.h>
#include <modem_context.h>
#include <modem_cmd_handler.h>
#include <modem_iface_uart.h>
#include <ztest.h>
#include "modem_cmd_handler.h"


 const struct modem_cmd *find_cmd_direct_match(
		struct modem_cmd_handler_data *data);

 const struct modem_cmd *find_cmd_match(
		struct modem_cmd_handler_data *data);

 void skipcrlf(struct modem_cmd_handler_data *data);
 
 int cmd_handler_process_iface_data(struct modem_cmd_handler_data *data,
					  struct modem_iface *iface);

                      
 void cmd_handler_process_rx_buf(struct modem_cmd_handler_data *data);