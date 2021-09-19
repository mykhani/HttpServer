/*
 * Connection.h
 *
 *  Created on: 20 Apr 2021
 *      Author: ykhan
 */

#ifndef NETWORKING_CONNECTION_H_
#define NETWORKING_CONNECTION_H_

#include <memory>
#include "hostAddress.h"
#include "tcpSocket.h"

class Connection;
using ConnectionPtr = std::shared_ptr<Connection>;

// for tcp based connection-oriented sockets, irrelevant for udp
class Connection {
private:
	HostAddress client_addr;
	TcpSocketPtr sock;


public:
	Connection() = default;
	Connection(const HostAddress& _client_addr, const TcpSocketPtr& _sock);
	TcpSocketPtr getTcpSocket();
};

#endif /* NETWORKING_CONNECTION_H_ */
