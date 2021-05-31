/*
 * Copyright (c) 2021 Abel Sensors
 *
 * SPDX-License-Identifier: Apache-2.0
// //  */

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

#include "n310_stub.h"

#define N310_DEVICE_LABEL DT_LABEL(DT_INST(0, ublox_sara_n310))
#define MAX_BUF 512

static const struct device *dev_ubloxn3;
extern struct socket_op_vtable *offload_socket_fd_op_vtable_mock;
extern struct net_if_api* api_funcs_mock;


static int offload_bind_mock(void *obj, const struct sockaddr *addr,
			     socklen_t addrlen)
{
	printk("offload_bind_mock\n");
	return 0;
}

static int offload_connect_mock(void *obj, const struct sockaddr *addr,
				socklen_t addrlen)
{
	printk("offload_connect_mock");
	return 0;
}

static ssize_t offload_sendto_mock(void *obj, const void *buf, size_t len,
			      int flags, const struct sockaddr *to,
			      socklen_t tolen)
{
	printk("offload_sendto_mock");
	return 0;
}

void test_device_struct(){
        dev_ubloxn3 = device_get_binding(N310_DEVICE_LABEL);
        zassert_not_null(dev_ubloxn3, "N310 device not found");
        struct modem_data *mdm = dev_ubloxn3->data;
        zassert_not_null(mdm, "N310 modem data not found");
}

void test_info_set(){
       zassert_not_null(n310_get_manufacturer(),"N310 Manufacturer not set");
       zassert_not_null(n310_get_iccid(),"N310 iccid not set");
       zassert_not_null(n310_get_model(),"N310 model not set");
       zassert_not_null(n310_get_revision(),"N310 revision not set");
       zassert_not_null(n310_get_imei(),"N310 imei not set");
       zassert_not_null(n310_get_ip(),"N310 IP not set");
}

void test_socket(){
	int ret = create_socket_stub(NULL,NULL);
	zassert_true(ret>=0,"n310 create socket not working");

	/*create socket in user space */
	int sockfd = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP);
	zassert_true(sockfd >= 0, "socket in user space not created");

	struct sockaddr_in addr;
	memset(&addr, 0, sizeof(addr));
	addr.sin_family = AF_INET;
	addr.sin_port = htons(4242);
	inet_pton(AF_INET, "192.168.0.20", &addr.sin_addr);

	ret = connect(sockfd, (const struct sockaddr *)&addr, sizeof(addr));
	zassert_true(ret >= 0, "connect failed");

    char *buffer = "ABDD";
	ret = sendto(sockfd, buffer, strlen(buffer) / 2,
		   RELEASE_AFTER_FIRST_DOWNLINK, (const struct sockaddr *)&addr,
		   sizeof(addr));
	zassert_true(ret >= 0, "send failed");
	
}

void test_status(){	
	int ret = n310_get_state();
	zassert_true(ret>=0,"n310 state not working correctly");
}

void test_main(void)
{
	setup_tests();
	ztest_test_suite(n310_test,
    ztest_unit_test(test_info_set),
    ztest_unit_test(test_device_struct),
    ztest_unit_test(test_status),
    ztest_unit_test(test_socket)	
	);
	ztest_run_test_suite(n310_test);
}



