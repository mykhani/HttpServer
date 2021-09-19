/*
 * Event.h
 *
 *  Created on: 19 Jul 2021
 *      Author: ykhan
 */

#ifndef UTIL_EVENT_H_
#define UTIL_EVENT_H_

#include <memory>
#include <functional>

using namespace std;

class Event {
private:
	int event_id;
public:
	Event(int id);
	virtual ~Event() = 0; // to make it abstract class
	bool operator<(const Event& other) const;
	int id();
};

using EventHandler = std::function<void(std::shared_ptr<Event>)>;
using EventPtr = std::shared_ptr<Event>;

#endif /* UTIL_EVENT_H_ */
