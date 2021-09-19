/*
 * HttpServer.cpp
 *
 *  Created on: 9 Sep 2021
 *      Author: ykhan
 */

#include <thread>
#include <map>
#include "httpserver.h"
#include <functional>

using namespace std;

HttpServer::HttpServer() {
//	using std::placeholders::_1;

//	m_server.addEventListener(TcpServerEvents::newConnection, NewConnectionHandler{*this});
	m_server.addEventListener(TcpServerEvents::newConnection, [this](EventPtr e) {
		auto& conn_event = dynamic_cast<NewConnectionEvent&>(*e);
			std::cout << "Thread id: " << this_thread::get_id() << " new Connection event received" << std::endl;

			std::cout  << conn_event.connection;
			auto sock = conn_event.connection->getTcpSocket();

			sock->asyncRecv([this, conn_event](Socket& sk, const string& data) {
				cout << "Received message on socket: " << sk.handle() << endl;

				std::shared_ptr<Request> req = m_httpParser.parse(data);
				std::shared_ptr<Response> resp = make_shared<Response>();

				this->m_router->handleRequest(*req, *resp);

				std::string html = resp->str();

				cout << "Sending response: " << html << endl;

				write(sk, html.c_str(), html.length());

				TcpSocketServer* tcpServer = conn_event.server;
				tcpServer->closeConnection(conn_event.connection->getTcpSocket());
			});
	});

}

HttpServer::~HttpServer() {
	// TODO Auto-generated destructor stub
}

void HttpServer::listen(const Port& p) {
	m_server.listen(p);
}

void HttpServer::setRouter(const Router& router) {
	m_router.reset(new Router{router});
}
