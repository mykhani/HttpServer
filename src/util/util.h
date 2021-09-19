/*
 * util.h
 *
 *  Created on: 13 Sep 2021
 *      Author: ykhan
 */

#ifndef SRC_UTIL_UTIL_H_
#define SRC_UTIL_UTIL_H_

#include <string>
#include <iostream>
#include <map>

std::string& ltrim(std::string& s);
std::string& rtrim(std::string& s);
std::string& trim(std::string& s);

std::ostream& operator<<(std::ostream& os, std::map<std::string, std::string>& m);

#endif /* SRC_UTIL_UTIL_H_ */
