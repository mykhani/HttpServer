/*
 * hostAddress.cpp
 *
 *  Created on: 19 Jul 2021
 *      Author: ykhan
 */
#include "hostAddress.h"
#include <arpa/inet.h>

std::ostream& operator<<(std::ostream& os, const HostAddress& host_address) {
	os << host_address.address;
	return os;
}

HostAddress HostAddress::fromSockAddr(sockaddr* sa) {
	char ipaddr[INET_ADDRSTRLEN];

	sockaddr_in *sa_in = reinterpret_cast<sockaddr_in*>(sa);
	inet_ntop(sa_in->sin_family, &sa_in->sin_addr, ipaddr, sizeof(ipaddr));

	return {ipaddr};
}
