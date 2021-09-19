/*
 * util.cpp
 *
 *  Created on: 13 Sep 2021
 *      Author: ykhan
 */

#include "util.h"
#include <algorithm>

using namespace std;

std::string& ltrim(std::string& s) {
	// find the iterator to first non-whitespace character
	auto it = std::find_if(s.begin(), s.end(), [](char c) {
		return !std::isspace(c);
	});

//	int distance = std::distance(s.begin(), it);

	// erase whitespace from start to first non-whitespace character
	s.erase(s.begin(), it);

	return s;
}

std::string& rtrim(std::string& s) {
	// find the iterator to first non-whitespace character
	auto it = std::find_if(s.rbegin(), s.rend(), [](char c) {
		return !std::isspace(c);
	});

//	int distance = std::distance(s.begin(), it.base());

	// erase whitespace from end to first non-whitespace character
	s.erase(it.base(), s.end());

	return s;
}

std::string& trim(std::string& s) {
	return rtrim(ltrim(s));
}

std::ostream& operator<<(std::ostream& os, std::map<std::string, std::string>& m) {
	os << "{" << endl;
	for (const auto&[key, value] : m) {
		os << "\t" << key << " : " << value << endl;
	}

	os << "}";

	return os;
}
