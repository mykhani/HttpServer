/*
 * httpparser.h
 *
 *  Created on: 13 Sep 2021
 *      Author: ykhan
 */

#ifndef SRC_HTTP_HTTPPARSER_H_
#define SRC_HTTP_HTTPPARSER_H_

#include "request.h"
#include "../util/util.h"

class HttpParser {
public:
	HttpParser();
	~HttpParser();

	std::shared_ptr<Request> parse(const std::string& data);
};

std::string readHeader(const std::string& header,
					   std::shared_ptr<RequestHeaders> headers);

#endif /* SRC_HTTP_HTTPPARSER_H_ */
