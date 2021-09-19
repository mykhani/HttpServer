/*
 * router.cpp
 *
 *  Created on: 9 Sep 2021
 *      Author: ykhan
 */

#include "router.h"
#include <iostream>

using namespace std;

Router::Router() {
	// TODO Auto-generated constructor stub

}

Router::~Router() {
	// TODO Auto-generated destructor stub
}

void Router::addRoute(std::shared_ptr<Route> route) {
	m_routes.insert({route->path(), route});
}

std::shared_ptr<Route> Router::findRoute(Request& req) {
	auto path = req.m_uri;

	if (m_routes.find(path) != m_routes.end()) {
		return m_routes[path];
	}

	return {nullptr};

}

void Router::handleRequest(Request& req, Response& resp) {
	auto route = findRoute(req); // find the route

	if (!route) {
		cout << "ERROR: route " << req.m_uri << " not found" << endl;
		resp.setStatus(Response::NOT_FOUND);
		return;
	}

	switch (Request::GetRequestType[req.method()]) {
	case Request::GET:
		route->handleGet(req, resp);
		break;

	case Request::POST:
		route->handlePost(req, resp);
		break;

	default:
		cout << "ERROR: Invalid request received" << endl;
		resp.setStatus(Response::ERROR);
		return;
	}
}
