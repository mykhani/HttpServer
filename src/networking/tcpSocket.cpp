/*
 * TcpSocket.cpp
 *
 *  Created on: 14 Apr 2021
 *      Author: ykhan
 */

#include "tcpSocket.h"
#include <iostream>

TcpSocket::TcpSocket()
		: Socket{PF_INET, SOCK_STREAM} {
	auto fd = socket(this->family, this->type, 0);
	if (fd < 0)
		throw std::runtime_error{"Failed to create the TcpSocket"};

	this->fd = fd;
}

TcpSocket::TcpSocket(int fd) : Socket{PF_INET, SOCK_STREAM} {
	this->fd = fd;
}

TcpSocket::TcpSocket(TcpSocket&& other) {
	if (other.fd > 0) {
		this->fd = other.fd;
		other.fd = -1;
	}
}

TcpSocket::~TcpSocket() {
	if (this->fd > 0) {
		close(this->fd);
		std::cout << "Closed TCP socket with descriptor: " << this->fd << std::endl;
	}
}
