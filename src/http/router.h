/*
 * router.h
 *
 *  Created on: 9 Sep 2021
 *      Author: ykhan
 */

#ifndef HTTP_ROUTER_H_
#define HTTP_ROUTER_H_

#include <map>
#include "request.h"
#include "response.h"
#include "route.h"
#include <memory>

class Router {
private:
	std::map<std::string, std::shared_ptr<Route>> m_routes;
	std::shared_ptr<Route> findRoute(Request& req);

public:
	Router();
	virtual ~Router();

	void addRoute(std::shared_ptr<Route> route);
	void handleRequest(Request& req, Response& resp);
};

#endif /* HTTP_ROUTER_H_ */
