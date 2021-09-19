/*
 * TcpSocketServer.cpp
 *
 *  Created on: 17 Apr 2021
 *      Author: ykhan
 */

#include "tcpSocketServer.h"
#include <iostream>
#include <sstream>
#include <thread>
#include <cstring>

using namespace std;

void tcpServerBackgroundTask(TcpSocketServer& server) {
	int ret;

	PollEvent serverIncomingConnection{server.sock, PollEvent::Type::READY_READ};
	server.addPollEvent(serverIncomingConnection);

	// listen is non-blocking
	ret = listen(*server.sock, server.queued_connections);
	if (ret) {
		cout << "tcp server failed to start listening" << endl;
		return;
	}

	cout << "Started thread " << this_thread::get_id()
			<< " listening on " << server.address
			<< " port " << server.port << endl;


//	auto event = pollfd{server.sock.handle(), POLLIN};
//	server.poll_events.emplace_back(event);

	while (true) {
		auto events = server.pollEvents(POLLING_TIMEOUT);

//		auto poll_count = poll(server.poll_events.data(), server.poll_events.size(), POLLING_TIMEOUT);

//		cout << "poll count: " << poll_count << endl;
		// get each event and check if it read or write
		for (auto &event : events) {
//		for (int i = 0; pollEvents > 0 && i < server.polledSockets.size(); i++) {
			// check if data is available to read
			if (event.isReadyToRead()) {
				if (event.getSocket() == server.sock) {

					// accept new incoming connection
					sockaddr client_info;
					socklen_t client_info_size = sizeof(client_info);

					int conn_handle = accept(*server.sock, &client_info, &client_info_size);

					auto client_sock = make_shared<TcpSocket>(conn_handle);
					HostAddress client_addr = HostAddress::fromSockAddr(&client_info);

					client_sock->makeNonBlocking();
					server.addConnection(client_sock, client_addr);
					server.addPollEvent({client_sock, PollEvent::Type::READY_READ});
				} else {
					// received some data on a connection
					char buf[65536]; // 64kB BUFFER
					ostringstream oss; // to create output string
					int bytes_received = 0;
					int ret;

					do {
						ret = read(event.getSocketDescriptor(), (void*)buf, sizeof(buf));
						if (ret <= 0) {
							if (ret == 0) {
								cout << "Connection closed by client" << endl;
							} else if (errno == EAGAIN || errno == EWOULDBLOCK) {
								cout << "No more data, read returned: " << ret
									 << ", error: " << strerror(errno) << endl;
							} else {
								cout << "Error while reading, read returned: " << ret
									 << ", error: " << strerror(errno) << endl;
								// invalidate bytes received
								bytes_received = -1;

								// remove socket
								auto client_sock = std::dynamic_pointer_cast<TcpSocket>(event.getSocket());

								server.closeConnection(client_sock);
//								server.polledEvents.erase(event.getSocketDescriptor());
							}
							break;
						} else { // data received
							for (int i = 0; i < ret; i++) {
								oss.put(buf[i]);
							}

							bytes_received += ret;
						}
					} while (ret > 0);

//					bytes_received = read(server.poll_events[i].fd, (void*)buf, sizeof(buf));
					if (bytes_received > 0) {
						int desc = event.getSocketDescriptor();

						ConnectionPtr conn;
						// map i to client socket
						if (server.connections.find(desc) != server.connections.end()) {
							conn = server.connections[desc];
							conn->getTcpSocket()->dataReady(oss.str());
						}
					}
				}
			}
		}
	}
}

TcpSocketServer::TcpSocketServer(int _queued_connections)
		: queued_connections{_queued_connections}, sock{new TcpSocket{}} {
}

void TcpSocketServer::listen(Port port, std::optional<HostAddress> address) {
	HostAddress bind_address;

	// mark server socket as reusable
	sock->makeReusable();

	// make socket non-blocking
	sock->makeNonBlocking();

	try {
		bind_address = sock->bind(port, address);
	} catch (std::exception& e) {
		cout << "Failed to bind the socket, error: " << strerror(errno);
		ostringstream oss;

		oss << "Failed to listen on ";
		if (address)
			oss << "address : " << address.value();

		oss << " port: " << port
			<< " error: " << e.what() << endl;

		throw std::runtime_error{oss.str()};
	}

	this->address = bind_address;
	this->port = port;

	std::thread background_task{tcpServerBackgroundTask, std::ref(*this)};

	background_task.detach();

//	throw std::runtime_error("Method not implemented!");
}

void TcpSocketServer::addConnection(TcpSocketPtr client_sock, HostAddress& client_addr) {

//	auto event = pollfd{static_cast<int>(client_sock.handle()), POLLIN};
//	poll_events.push_back(event);

	ConnectionPtr conn{new Connection{client_addr, std::move(client_sock)}};

	this->connections.insert({conn->getTcpSocket()->handle(), conn});

	auto newConnectionEvent = make_shared<NewConnectionEvent>(conn, this);

	emit(newConnectionEvent);
}

void TcpSocketServer::closeConnection(TcpSocketPtr client_sock) {
	auto handle = client_sock->handle();

//	auto match = [handle](pollfd& poll) {
//		return poll.fd == handle;
//	};

	// remove polling descriptor
	this->polledEvents.erase(handle);
//	poll_events.erase(std::remove_if(poll_events.begin(), poll_events.end(), match), poll_events.end());
	// remove the connection
	this->connections.erase(handle);

	// close the socket descriptor
	close(handle);
}

void TcpSocketServer::addPollEvent(const PollEvent& event) {
	auto fd = event.getSocketDescriptor();
	polledEvents.insert({fd, event});
}

void TcpSocketServer::removePollEvent(const PollEvent& event) {
	auto fd = event.getSocketDescriptor();
	polledEvents.erase(fd);
}

vector<PollEvent> TcpSocketServer::pollEvents(int timeout) {
	vector<pollfd> pfds;
	vector<PollEvent> result;

	for (auto&[fd, event] : polledEvents) {
		pfds.push_back(event.getPollDescriptor());
	}

	int count = poll(pfds.data(), pfds.size(), timeout);

	for (int i = 0; count > 0 && i < pfds.size(); i++) {
		auto &event = polledEvents[pfds[i].fd];
		if (event.isReadyToRead() || event.isReadyToWrite()) {
			result.push_back(event);
			count--;
		}
	}

	return result;

}
