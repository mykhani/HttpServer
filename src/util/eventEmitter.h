/*
 * EventEmitter.h
 *
 *  Created on: 20 Apr 2021
 *      Author: ykhan
 */

#ifndef UTIL_EVENTEMITTER_H_
#define UTIL_EVENTEMITTER_H_

#include <functional>
#include <vector>
#include <memory>
#include <map>
#include <unordered_map>
#include <iostream>

#include "event.h"

class EventEmitter {
private:
	using EventHandlerVec = std::vector<EventHandler>;
	std::map<int, EventHandlerVec> event_handlers;

public:
	void addEventListener(const int& event_id, EventHandler handler);
	void emit(EventPtr e);
	virtual ~EventEmitter() = 0;
};


#endif /* UTIL_EVENTEMITTER_H_ */
