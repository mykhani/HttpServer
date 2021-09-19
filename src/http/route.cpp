/*
 * route.cpp
 *
 *  Created on: 9 Sep 2021
 *      Author: ykhan
 */

#include "route.h"
#include <sstream>
#include <iostream>

using namespace std;

string requestNotImplemented(Request& req) {
	ostringstream oss;

	oss << "Request " << req.method() << " not implemented " << endl;
	return oss.str();
}

Route::Route(const string& path) : m_path{path} {
	// TODO Auto-generated constructor stub

}

Route::~Route() {
	// TODO Auto-generated destructor stub
}

std::string Route::path() {
	return m_path;
}

void Route::handleGet(Request& req, Response& resp) {
	cout << requestNotImplemented(req) << endl;
	resp.setStatus(Response::NOT_FOUND);
}

void Route::handlePost(Request& req, Response& resp) {
	cout << requestNotImplemented(req) << endl;
	resp.setStatus(Response::NOT_FOUND);
}

void Route::handlePut(Request& req, Response& resp) {
	cout << requestNotImplemented(req) << endl;
	resp.setStatus(Response::NOT_FOUND);
}

void Route::handleDelete(Request& req, Response& resp) {
	cout << requestNotImplemented(req) << endl;
	resp.setStatus(Response::NOT_FOUND);
}
