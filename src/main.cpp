/*
 * main.cpp
 *
 *  Created on: 14 Apr 2021
 *      Author: ykhan
 */
#include <iostream>
#include <string>
#include <memory>
#include <thread>

// HTTP server
#include "http/httpserver.h"

// Routes
#include "routes/routeperson.h"  // Route for URI /person

// utils
#include "util/util.h"

using namespace std;

int main(int argc, char* argv[]) {
	cout << "Main thread id: " << this_thread::get_id() << endl;

	HttpServer server;
	Router router;

	std::shared_ptr<RoutePerson> routePerson = std::make_shared<RoutePerson>("/person");
	router.addRoute(routePerson);

	server.setRouter(router);
	server.listen(Port{9999});

	getchar();
}
