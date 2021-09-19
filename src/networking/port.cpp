/*
 * Port.cpp
 *
 *  Created on: 19 Apr 2021
 *      Author: ykhan
 */

#include "port.h"

std::ostream& operator<<(std::ostream& os, const Port& port) {
	os << port.port_num;
	return os;
}

Port::Port(int i) :
		port_num{i} {
}

Port::Port(std::string_view s) {
	// TODO: verify the port string consists of only numbers
	port_num = atoi(s.data());
}

Port::operator int() {
	return port_num;
}

Port::operator const char* () {
	return std::to_string(port_num).c_str();
}

Port::~Port() {
	// TODO Auto-generated destructor stub
}

