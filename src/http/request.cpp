/*
 * Request.cpp
 *
 *  Created on: 9 Sep 2021
 *      Author: ykhan
 */

#include "request.h"

using namespace std;

Request::Request(const std::string &uri, const std::string &method,
		const std::string &body, std::shared_ptr<Query> &query,
		std::shared_ptr<RequestHeaders> &headers)
	: m_uri { uri }, m_method { method },
	  m_body { body }, m_query { query }, m_headers {headers} {
}

std::string Request::method() {
	return m_method;
}

std::shared_ptr<Query> Request::query() {
	return m_query;
}

std::string Request::body() {
	return m_body;
}

std::string Request::setBody(const std::string &body) {
	m_body = body;
}

std::shared_ptr<RequestHeaders> Request::headers() {
	return m_headers;
}
