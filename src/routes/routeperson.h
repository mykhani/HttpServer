/*
 * RoutePerson.h
 *
 *  Created on: 10 Sep 2021
 *      Author: ykhan
 */

#ifndef ROUTES_ROUTEPERSON_H_
#define ROUTES_ROUTEPERSON_H_

#include <string>
#include "../http/route.h"
#include "../http/request.h"
#include "../http/response.h"

class Person {
private:
	int m_id;
	std::string m_name;
	std::string m_job;

	friend std::ostream& operator<<(std::ostream& os, const Person& p);

public:
	Person() = default;
	Person(int id, const std::string& name, const std::string& job)
		: m_id{id}, m_name{name}, m_job{job} {}

	int id() const {
		return m_id;
	}

	std::string name() const {
		return m_name;
	}

	std::string job() const {
		return m_job;
	}

	std::string json();
};

class RoutePerson: public Route {
	using Route::Route;
public:
	RoutePerson();

	virtual void handleGet(Request& req, Response& resp) override;
	virtual void handlePost(Request& req, Response& resp) override;
};

#endif /* ROUTES_ROUTEPERSON_H_ */
