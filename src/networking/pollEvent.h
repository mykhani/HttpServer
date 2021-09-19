/*
 * pollevent.h
 *
 *  Created on: 13 Sep 2021
 *      Author: ykhan
 */

#ifndef SRC_NETWORKING_POLLEVENT_H_
#define SRC_NETWORKING_POLLEVENT_H_

#include "socket.h"
#include <poll.h>
#include <functional>

class PollEvent {
	friend struct std::hash<PollEvent>;
public:
	enum class Type {
		READY_READ,
		READY_WRITE
	};

	PollEvent() = default;
	PollEvent(SocketPtr sock, Type type);
	pollfd getPollDescriptor();
	int getSocketDescriptor() const;
	SocketPtr getSocket() const;
	bool isReadyToRead() const;
	bool isReadyToWrite() const;

private:
	SocketPtr m_sock;
	Type m_type;
	pollfd m_pfd{0};
};

template<>
struct std::hash<PollEvent> {
	inline size_t operator() (const PollEvent& event) const {
		auto hash = std::hash<int>{}(event.m_sock->handle());

		return hash;
	}
};

#endif /* SRC_NETWORKING_POLLEVENT_H_ */
