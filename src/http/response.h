/*
 * Response.h
 *
 *  Created on: 9 Sep 2021
 *      Author: ykhan
 */

#ifndef HTTP_RESPONSE_H_
#define HTTP_RESPONSE_H_

#include <string>
#include <map>

using Headers = std::map<std::string, std::string>;

class Response {
private:
	int m_status;
	std::string m_data;
	Headers m_headers;

public:
	enum status {
		OK,
		NOT_FOUND,
		ERROR,
	};

	Response();
	int status();
	std::string data();
	std::string str();

	void setStatus(int status);
	void setData(const std::string& data);
	void setHeaders(const Headers& headers);
};

#endif /* HTTP_RESPONSE_H_ */
