/*
 * Connection.cpp
 *
 *  Created on: 20 Apr 2021
 *      Author: ykhan
 */

#include "connection.h"

Connection::Connection(const HostAddress& _client_addr, const TcpSocketPtr& _sock)
		: client_addr{_client_addr}, sock{_sock} {
}

TcpSocketPtr Connection::getTcpSocket() {
	return sock;
}
