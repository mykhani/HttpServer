/*
 * event.cpp
 *
 *  Created on: 19 Jul 2021
 *      Author: ykhan
 */

#include "event.h"

Event::Event(int id) : event_id{id} {}

Event::~Event() {}


bool Event::operator<(const Event& other) const {
	return event_id < other.event_id;
}

int Event::id() {return event_id;}
