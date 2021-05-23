#ifndef _N310_STUB_H_
#define _N310_STUB_H_

 #include <device.h>
#include <sys_clock.h>
#include <modem_context.h>
#include <modem_cmd_handler.h>
#include <modem_iface_uart.h>
#include <ztest.h>
#include "modem_cmd_handler.h"
#include "modem_socket.h"
#include "sockets_internal.h"

// void init_offload_socket();

// struct socket_op_vtable *offload_socket_fd_op_vtable_mock;
int create_socket_stub(struct modem_socket *sock, const struct sockaddr *addr);
void modem_net_iface_init_mock(struct net_if *iface);

ssize_t offload_recvfrom_stub(void *obj, void *buf, size_t len, int flags,
			      struct sockaddr *from, socklen_t *fromlen);


#endif