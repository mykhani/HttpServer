/*
 * RoutePerson.cpp
 *
 *  Created on: 10 Sep 2021
 *      Author: ykhan
 */

#include "routeperson.h"
#include <sstream>
#include <iostream>
#include <cstdlib>

using namespace std;

std::ostream& operator<<(std::ostream& os, const Person& p) {
	os << "Person {" << endl;
	os << "\t" << "id: " << p.id() << endl;
	os << "\t" << "name: " << p.name() << endl;
	os << "\t" << "job: " << p.job() << endl;
	os << "}";

	return os;
}

int personId = 0;

// Hashmap of persons
map<int, Person> persons;

void sendPerson(Person& person, Response& resp) {
	resp.setStatus(Response::OK);

	std::string json = person.json();
	resp.setData(json);

	Headers headers = {
			{"Content-Length", std::to_string(json.length())},
			{"Content-Type", "application/json; charset=utf-8"},
	};

	resp.setHeaders(headers);
}

void RoutePerson::handleGet(Request& req, Response& resp) {
	auto params = *req.query();
	int id = -1;

	if (auto it = params.find("id"); it != params.end()) {
		id = std::stoi(it->second); // need to handle if query doesn't contain id
	}

	cout << "In person GET, id: " << id << endl;

	if (persons.find(id) != persons.end()) {
		auto person = persons[id];
		cout << person << endl;

		sendPerson(person, resp);
	} else {
		cout << "Failed to find the id: " << id << endl;
		resp.setStatus(Response::NOT_FOUND);
	}
}

void RoutePerson::handlePost(Request& req, Response& resp) {
	auto query = *req.query();

	Person person{personId, query["name"], query["job"]};
	persons.insert({personId, person});
	personId++;

	sendPerson(person, resp);
}

std::string Person::json() {
	ostringstream oss;
	oss << "{";
	oss << "\"" << "id" << "\":\"" << m_id << "\", ";
	oss << "\"" << "name" << "\":\"" << m_name << "\", ";
	oss << "\"" << "job" << "\":\"" << m_job << "\"";
	oss << "}";

	return oss.str();
}
