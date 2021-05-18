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


#define N310_DEVICE_LABEL DT_LABEL(DT_INST(0, ublox_sara_n310))
#define MAX_BUF 512


// struct fd_op_vtable {
// 	ssize_t (*read)(void *obj, void *buf, size_t sz);
// 	ssize_t (*write)(void *obj, const void *buf, size_t sz);
// 	int (*close)(void *obj);
// 	int (*ioctl)(void *obj, unsigned int request, va_list args);
// };

// struct socket_op_vtable {
// 	struct fd_op_vtable fd_vtable;
// 	int (*bind)(void *obj, const struct sockaddr *addr, socklen_t addrlen);
// 	int (*connect)(void *obj, const struct sockaddr *addr,
// 		       socklen_t addrlen);
// 	int (*listen)(void *obj, int backlog);
// 	int (*accept)(void *obj, struct sockaddr *addr, socklen_t *addrlen);
// 	ssize_t (*sendto)(void *obj, const void *buf, size_t len, int flags,
// 			  const struct sockaddr *dest_addr, socklen_t addrlen);
// 	ssize_t (*recvfrom)(void *obj, void *buf, size_t max_len, int flags,
// 			    struct sockaddr *src_addr, socklen_t *addrlen);
// 	int (*getsockopt)(void *obj, int level, int optname,
// 			  void *optval, socklen_t *optlen);
// 	int (*setsockopt)(void *obj, int level, int optname,
// 			  const void *optval, socklen_t optlen);
// 	ssize_t (*sendmsg)(void *obj, const struct msghdr *msg, int flags);
// 	int (*getsockname)(void *obj, struct sockaddr *addr,
// 			   socklen_t *addrlen);
// };

extern struct socket_op_vtable* offload_socket_fd_op_vtable_mock;
//  struct socket_op_vtable* offload_socket_fd_op_vtable_mock;

//static struct socket_op_vtable_mock* offload_socket_fd_op_vtable_mock;


static const struct device *dev_ubloxn3;

void setup_tests(void)
{
	
	/* these need to be implemented */
	// 	.read = NULL,
	// 	.write = NULL,
	// 	.close = offload_close,
	// 	.ioctl = NULL,
	// },
	offload_socket_fd_op_vtable_mock->fd_vtable.read = NULL;
	offload_socket_fd_op_vtable_mock->bind = NULL;
	offload_socket_fd_op_vtable_mock->connect = NULL;
	offload_socket_fd_op_vtable_mock->sendto = NULL;
	offload_socket_fd_op_vtable_mock->recvfrom = NULL;
	offload_socket_fd_op_vtable_mock->listen = NULL;
	offload_socket_fd_op_vtable_mock->accept = NULL;
	offload_socket_fd_op_vtable_mock->sendmsg = NULL;
	offload_socket_fd_op_vtable_mock->getsockopt = NULL;
	offload_socket_fd_op_vtable_mock->setsockopt = NULL;
}

void test_testing(void){
        zassert_true(1, NULL);
        zassert_false(0, NULL);
        zassert_is_null(NULL, NULL);
        zassert_not_null("foo", NULL);
        zassert_equal(1, 1, NULL);
        zassert_equal_ptr(NULL, NULL, NULL);
}

void test_device_struct(){
        dev_ubloxn3 = device_get_binding(N310_DEVICE_LABEL);
        zassert_not_null(dev_ubloxn3, "N310 device not found");
        struct modem_data *mdm = dev_ubloxn3->data;
        zassert_not_null(mdm, "N310 modem data not found");

        // zassert_not_null(mdm->net_iface, "Net interface null");
        // uint8_t mac_addr[6] = mdm->mac_addr;
        // zassert_equal(mac_addr[0], 0, "");
        // zassert_equal(mac_addr[1], 0x10, "");
        // zassert_equal((uint32_t *)(data->mac_addr + 2), )
}

void test_info_set(){
       zassert_not_null(n310_get_manufacturer(),"N310 Manufacturer not set");
       zassert_not_null(n310_get_iccid(),"N310 iccid not set");
       zassert_not_null(n310_get_model(),"N310 model not set");
       zassert_not_null(n310_get_revision(),"N310 revision not set");
       zassert_not_null(n310_get_imei(),"N310 imei not set");
       zassert_not_null(n310_get_ip(),"N310 IP not set");
}

void test_modem_data(){
    //   zassert_not_null(mdata.net_iface,"");
    //` zassert_not_null(mdata.modem_context);
}

void test_status(){
	ztest_returns_value(modem_cmd_send, 0);
	//ztest_return_data(modem_cmd_send,)
	int ret = n310_get_state();
	zassert_true(ret>=0,"n310 state not working correctly");
}

void test_main(void)
{
	setup_tests();
	ztest_test_suite(n310_test,
    ztest_unit_test(test_testing),
    ztest_unit_test(test_info_set),
    ztest_unit_test(test_device_struct),
    ztest_unit_test(test_status)
	//ztest_unit_test(test_get_binding),
	//ztest_unit_test(test_create_socket),
	//ztest_unit_test(test_modem_reset)
	);
	ztest_run_test_suite(n310_test);
}





/*
void test_get_binding(){
    dev_ubloxn3 = device_get_binding(N310_DEVICE_LABEL);
	zassert_not_null(dev_ubloxn3, NULL);
}


void test_create_socket(void){
int ret = n310_get_state();

    zassert_equal(ret, N310_NOT_REGISTERED,NULL);
}

void test_modem_reset(void)
{
	int ret = n310_modem_reset();
	zassert_equal(ret, 0, NULL);
}
*/

/*
int n310_modem_reset(void);

char *n310_get_model(void);
char *n310_get_iccid(void);
char *n310_get_imei(void);
char *n310_get_manufacturer(void);
char *n310_get_revision(void);
char *n310_get_ip(void);
int n310_get_state(void);












void main(void)
{
	static const struct device *dev_ubloxn3;
	struct sockaddr_in addr;

	dev_ubloxn3 = device_get_binding(N310_DEVICE_LABEL);

	if (dev_ubloxn3 == NULL) {
		LOG_ERR("Failed to get device binding.");
		return;
	}

	LOG_INF("Manufacturer: %s", log_strdup(n310_get_manufacturer()));
	LOG_INF("Model: %s", log_strdup(n310_get_model()));
	LOG_INF("Revision: %s", log_strdup(n310_get_revision()));
	LOG_INF("ICCID: %s", log_strdup(n310_get_iccid()));
	LOG_INF("IMEI: %s", log_strdup(n310_get_imei()));
	LOG_INF("IP: %s", log_strdup(n310_get_ip()));
	LOG_INF("Network state: %d", n310_get_state());

	memset(&addr, 0, sizeof(addr));
	addr.sin_family = AF_INET;
	addr.sin_port = htons(4242);
	inet_pton(AF_INET, "192.168.0.20", &addr.sin_addr);

	while (1) {
		char *buffer = "ABDD";
		char recvBuffer[MAX_BUF] = "\0";
		int sockfd = 0, n = 0;

		sockfd = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP);
		if (sockfd < 0) {
			LOG_ERR("Could not create socket. Return value: %d", sockfd);
		}

		n = connect(sockfd, (const struct sockaddr *)&addr, sizeof(addr));
		if (n < 0) {
			LOG_ERR("Bind failed with return value: %d", n);
		}

		n = sendto(sockfd, buffer, strlen(buffer) / 2,
			   RELEASE_AFTER_FIRST_DOWNLINK,
			   (const struct sockaddr *)&addr, sizeof(addr));
		if (n < 0) {
			LOG_ERR("Send failed with return value: %d", n);
		}

		k_msleep(2000);

		n = recvfrom(sockfd, recvBuffer, MAX_BUF, ZSOCK_MSG_DONTWAIT, NULL, NULL);
		if (n <= 0) {
			strcpy(recvBuffer, "No data in buffer.");
		}

		LOG_INF("Received: %s", log_strdup(recvBuffer));

		k_msleep(4000);
		close(sockfd);
		k_msleep(4000);

		n310_modem_reset();
	}
}
*/
