/*
 * Socket.h
 *
 *  Created on: 14 Apr 2021
 *      Author: ykhan
 */

#ifndef NETWORKING_SOCKET_H_
#define NETWORKING_SOCKET_H_

#include <sys/types.h>
#include <sys/socket.h>
#include <netdb.h>
#include <functional>
#include <memory>
#include <unistd.h>
#include <fcntl.h>

//#include <experimental/optional>
#include <optional>
#include <stdexcept>

#include "hostAddress.h"
#include "port.h"

class Socket;
using SocketPtr = std::shared_ptr<Socket>;

class Socket {
	using DataReadyHandler = std::function<void(Socket& sock, const std::string&)>;

protected:
	int fd{-1}; // socket descriptor
	int family{-1};
	int type{-1};
	bool resusable{false};
	std::shared_ptr<DataReadyHandler> onDataReady{nullptr};

public:
	Socket() = default;
	Socket(int family, int type);
	virtual ~Socket() = 0;
	HostAddress bind(Port port, std::optional<HostAddress> address = std::nullopt);
	operator int(); // to use socket with Linux sockets C API
	void makeReusable();
	void makeNonBlocking();
	int handle();
	void dataReady(const std::string& data);
	void asyncRecv(const DataReadyHandler& handler);
};

#endif /* NETWORKING_SOCKET_H_ */
