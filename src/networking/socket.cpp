/*
 * Socket.cpp
 *
 *  Created on: 14 Apr 2021
 *      Author: ykhan
 */


#include <arpa/inet.h>
#include <errno.h>
#include <sstream>
#include <cstring>
#include <iostream>
#include "socket.h"

using namespace std;

Socket::Socket(int _family, int _type)
		: family{_family}, type{_type}, fd{-1} {
}

Socket::~Socket() {
}

HostAddress Socket::bind(Port port, std::optional<HostAddress> address) {
	int ret = -1;

	addrinfo hints;
	addrinfo *results;

	memset(&hints, 0, sizeof(hints));

	hints.ai_family = family;
	hints.ai_socktype = type;
	hints.ai_flags = AI_PASSIVE; // for server

	HostAddress bound_address;

	errno = 0;
	// if address not specified, use the ip address of the system
	if (address) {
		ret = getaddrinfo(address.value(), port, &hints, &results);
	} else {
		ret = getaddrinfo(NULL, port, &hints, &results);
	}



	if (ret) {
		std::ostringstream oss;
		oss << "getaddrinfo failed, ret: " << ret << " error: " << strerror(errno);
		throw std::runtime_error{oss.str()};
	}

	addrinfo *curr;
	for (curr = results; curr; curr = curr->ai_next) {
//		sockaddr_in *sa = reinterpret_cast<sockaddr_in*>(curr->ai_addr);
//		inet_ntop(curr->ai_family, &(sa->sin_addr), ipaddr, sizeof(ipaddr));
		HostAddress host_address = HostAddress::fromSockAddr(curr->ai_addr);
		cout << host_address << endl;

		if (!address) {
			break;
		} else {
			if (host_address == address.value()) {
				break;
			}
		}
	}

	ret = ::bind(fd, curr->ai_addr, curr->ai_addrlen);
	if (ret) {
		std::ostringstream oss;
		std::string err;

		oss << "bind failed, error: " << strerror(errno);
		err = oss.str();
		cout << err;
		throw std::runtime_error{err};
	}

	bound_address = HostAddress::fromSockAddr(curr->ai_addr);

	freeaddrinfo(results);

	return bound_address;
//	ret = bind(fd, struct sockaddr *my_addr, int addrlen);
}

Socket::operator int() {
	return fd;
}

void Socket::makeReusable() {
	if (!resusable && fd) {
		int option = 1;
		setsockopt(fd, SOL_SOCKET, SO_REUSEADDR, &option, sizeof(option));
	}
}

int Socket::handle() {
	return fd;
}

void Socket::dataReady(const std::string& data) {
	if (onDataReady)
		(*onDataReady)(*this, data);
}

void Socket::asyncRecv(const DataReadyHandler& handler) {
	onDataReady = make_shared<DataReadyHandler>(handler);
}

void Socket::makeNonBlocking() {
	if (fd < 0) {
		throw std::runtime_error("Cannot make non-blocking, invalid socket descriptor");
	}

	int ret = fcntl(fd, F_SETFL, O_NONBLOCK);
	if (ret < 0) {
		ostringstream oss;
		oss << "Failed to make non-blocking, error: " << strerror(errno);
		throw std::runtime_error(oss.str());
	}
}
