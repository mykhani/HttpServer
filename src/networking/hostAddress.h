/*
 * HostAddress.h
 *
 *  Created on: 17 Apr 2021
 *      Author: ykhan
 */

#ifndef NETWORKING_HOSTADDRESS_H_
#define NETWORKING_HOSTADDRESS_H_

#include <string>
#include <iostream>
#include <sys/socket.h>

class HostAddress {
private:
	std::string address;
	friend std::ostream& operator<<(std::ostream& os, const HostAddress& host_address);

public:
	HostAddress() = default;
	HostAddress(const std::string& _address) :
			address{_address} {
	}

	HostAddress(const HostAddress& other) {
		address = other.address;
	}

	operator const char* () {
		return address.c_str();
	}

	static HostAddress fromSockAddr(sockaddr* info);
};

#endif /* NETWORKING_HOSTADDRESS_H_ */
