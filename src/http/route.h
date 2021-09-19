/*
 * route.h
 *
 *  Created on: 9 Sep 2021
 *      Author: ykhan
 */

#ifndef HTTP_ROUTE_H_
#define HTTP_ROUTE_H_

#include <string>
#include "request.h"
#include "response.h"

class Route {
private:
	std::string m_path;

public:
	Route(const std::string& path);
	~Route();

	virtual void handleGet(Request& req, Response& resp);
	virtual void handlePost(Request& req, Response& resp);
	virtual void handlePut(Request& req, Response& resp);
	virtual void handleDelete(Request& req, Response& resp);

	std::string path();


};

#endif /* HTTP_ROUTE_H_ */
