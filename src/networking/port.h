/*
 * Port.h
 *
 *  Created on: 19 Apr 2021
 *      Author: ykhan
 */

#ifndef NETWORKING_PORT_H_
#define NETWORKING_PORT_H_

#include <string>
#include <stdlib.h>
#include <sstream>

class Port {
private:
	int port_num;
	friend std::ostream& operator<<(std::ostream& os, const Port& port);
public:
	Port() = default;
	Port(int i);
	Port(std::string_view s);

	// provide an int type conversion operator to use with BSD socket API which
	// uses int for port number
	operator int();
	operator const char* ();
	virtual ~Port();
};

#endif /* NETWORKING_PORT_H_ */
