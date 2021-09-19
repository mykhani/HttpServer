/*
 * httpparser.cpp
 *
 *  Created on: 13 Sep 2021
 *      Author: ykhan
 */

#include "httpparser.h"
#include <iostream>
#include <sstream>

using namespace std;

HttpParser::HttpParser() {
	// TODO Auto-generated constructor stub

}

HttpParser::~HttpParser() {
	// TODO Auto-generated destructor stub
}

std::string readHeader(const std::string& header, shared_ptr<RequestHeaders> headers) {
	// try the give case
	auto found = headers->find(header);
	if (found != headers->end()) {
		const auto&[headerName, headerValue] = *found;

		return headerValue;
	}

	return "";
}

void parseHeader(std::string&s, shared_ptr<RequestHeaders> headers) {
	istringstream iss{s};

	string key, value;

	std::getline(iss, key, ':');
	std::getline(iss, value);

	headers->insert({trim(key), trim(value)});
}

void parseQuery(std::string& s, shared_ptr<Query> query) {

	istringstream iss{s};

	string key, value;
	string p;

	while (std::getline(iss, p, '&')) {
		istringstream iss2{p};
		std::getline(iss2, key, '=');
		std::getline(iss2, value);

	//		cout << key << endl << value << endl;
		query->insert({key, value});
	}
}

void parseUriQuery(string s, string& uri, shared_ptr<Query> query) {
	istringstream iss{s};
	std::getline(iss, uri, '?');

	std::string paramStr;

	iss >> paramStr;

	parseQuery(paramStr, query);
}

void parseMethodUriProto(const std::string& s,
		string& method, string& uriQuery, string& proto) {
	istringstream iss{s};

	iss >> method >> uriQuery >> proto;
}

void parseRawData(string data, string& method, string &uri,
		string& body, shared_ptr<Query> query,
		std::shared_ptr<RequestHeaders> headers) {
	istringstream iss{data};
	string line;

	string uriQuery;
	string proto;
	string headersBody;

	std::getline(iss, line);


	parseMethodUriProto(line, method, uriQuery, proto);


	while (std::getline(iss, line)) {
		if (line.find(":") != std::string::npos) {
			parseHeader(line, headers);
		} else {
			break;
		}
	}

	// get content length and type maybe
	auto contentLengthHeader = readHeader("Content-Length", headers);

	int bodyLength = contentLengthHeader != "" ? std::stoi(contentLengthHeader) : 0;

	// To get raw data as well, getline() might not work as intended if
	// body consists of raw binary data
	for (int i = 0; i < bodyLength; i++) {
		char byte;
		iss.get(byte);
		body += byte;
	}

	parseUriQuery(uriQuery, uri, query);

	cout << "Headers: " << endl << *headers << endl;
	cout << "Body: " << endl << body << endl;
	cout << "Body length: " << body.length() << endl;

}

std::shared_ptr<Request> HttpParser::parse(const std::string &data) {

	std::string method, uri, body;

	cout << "Raw data: " << endl << data << endl;

	std::shared_ptr<Query> query = make_shared<Query>();
	std::shared_ptr<RequestHeaders> headers = make_shared<RequestHeaders>();

	parseRawData(data, method, uri, body, query, headers);

	auto request = make_shared<Request>(uri, method, body, query, headers);

	return request;
}
