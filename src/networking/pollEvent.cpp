/*
 * pollevent.cpp
 *
 *  Created on: 13 Sep 2021
 *      Author: ykhan
 */

#include "pollEvent.h"
#include <stdexcept>

using namespace std;

PollEvent::PollEvent(SocketPtr sock, Type type)
	: m_sock{sock}, m_type{type} {
		m_pfd.fd = m_sock->handle();

		switch (type) {
		case Type::READY_READ:
			m_pfd.events |= POLLIN;
			break;
		case Type::READY_WRITE:
			m_pfd.events |= POLLOUT;
		default:
			throw std::runtime_error("Unknown PollEvent type requested");
		}
}

pollfd PollEvent::getPollDescriptor() {
	return m_pfd;
}

int PollEvent::getSocketDescriptor() const {
	return m_sock->handle();
}

SocketPtr PollEvent::getSocket() const {
	return m_sock;
}

bool PollEvent::isReadyToWrite() const {
	return m_pfd.revents | POLLOUT;
}

bool PollEvent::isReadyToRead() const {
	return m_pfd.revents | POLLIN;
}
