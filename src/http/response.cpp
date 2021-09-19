/*
 * Response.cpp
 *
 *  Created on: 9 Sep 2021
 *      Author: ykhan
 */

#include "response.h"
#include <sstream>

using namespace std;

Response::Response() {
	// TODO Auto-generated constructor stub

}

int Response::status() {
	return m_status;
}

std::string Response::data() {
	return m_data;
}

void printHeaders(ostringstream& oss, Headers& headers) {
	for (const auto&[key, value] : headers) {
		oss << key << ": " << value << "\n";
	}
}

std::string Response::str() {

	ostringstream oss;

	switch (m_status) {
	case OK:
		oss << "HTTP/1.1 200 OK\n";
		break;

	case NOT_FOUND:
		oss << "HTTP/1.1 404 NOT_FOUND\n";
	}

	if (m_headers.size() > 0) {
		printHeaders(oss, m_headers);
	}

	oss << endl;

	if (m_data != "") {
		oss << m_data;
	}

	return oss.str();
}

void Response::setStatus(int status) {
	m_status = status;
}

void Response::setData(const std::string& data) {
	m_data = data;
}

void Response::setHeaders(const Headers& headers) {
	m_headers = headers;
}
