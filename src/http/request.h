/*
 * Request.h
 *
 *  Created on: 9 Sep 2021
 *      Author: ykhan
 */

#ifndef HTTP_REQUEST_H_
#define HTTP_REQUEST_H_

#include <string>
#include <map>
#include <iostream>
#include <memory>

class Router;

using Query = std::map<std::string, std::string>;
using RequestHeaders = std::map<std::string, std::string>;

class Request {
	friend class Router;
private:
	std::string m_uri;
	std::string m_method;
	std::shared_ptr<Query> m_query;
	std::string m_body;
	std::shared_ptr<RequestHeaders> m_headers;

public:
	enum RequestType {
		GET,
		POST,
		PUT,
		DELETE
	};

	inline static std::map<std::string, RequestType> GetRequestType = {
			{"GET", GET},
			{"POST", POST},
			{"PUT", PUT},
			{"DELETE", DELETE}
	};

	Request() = default;
	Request(const std::string& uri, const std::string& method,
			const std::string& body, std::shared_ptr<Query>& query,
			std::shared_ptr<RequestHeaders>& headers);

	std::string method();
	std::shared_ptr<Query> query();
	std::string body();
	std::string setBody(const std::string& body);
	std::shared_ptr<RequestHeaders> headers();
};

#endif /* HTTP_REQUEST_H_ */
