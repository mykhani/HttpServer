/*
 * EventEmitter.cpp
 *
 *  Created on: 16 Jun 2021
 *      Author: ykhan
 */
#include "eventEmitter.h"

EventEmitter::~EventEmitter() {}

void EventEmitter::addEventListener(const int& event_id,
		EventHandler handler) {
	event_handlers[event_id].push_back(handler);
}

void EventEmitter::emit(EventPtr e) {
	auto event_id = e->id();

	const auto &handlers = event_handlers[event_id];

	for (const auto &handle : handlers) {
		handle(e);
	}
}

