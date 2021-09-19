/*
 * HttpServer.h
 *
 *  Created on: 9 Sep 2021
 *      Author: ykhan
 */

#ifndef HTTP_HTTPSERVER_H_
#define HTTP_HTTPSERVER_H_

#include <map>
#include "../networking/tcpSocketServer.h"
#include "router.h"
#include "request.h"
#include "response.h"
#include "httpparser.h"
#include <memory>

struct NewConnectionHandler;

class HttpServer {
	friend struct NewConnectionHandler;
private:
	TcpSocketServer m_server;
	std::unique_ptr<Router> m_router{nullptr};
	HttpParser m_httpParser;

public:
	void listen(const Port& p);
	HttpServer();
	~HttpServer();

	void setRouter(const Router& router);

};

#endif /* HTTP_HTTPSERVER_H_ */
