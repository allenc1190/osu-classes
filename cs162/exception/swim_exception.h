/*
	Swim Exception
*/
#ifndef SWIM_EXCEPTION_H
#define SWIM_EXCEPTION_H

#include <iostream>
#include <exception>

using namespace std;

class Swim_Exception : public exception {
private:
	string name;
	string description;
public:
	Swim_Exception(string, string);
	const char* what() const noexcept;
};
#endif
