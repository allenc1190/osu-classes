/*
	Swim Exception Class
*/
#include <iostream>
#include "swim_exception.h"

using namespace std;

// define a constructor that sets the following variables:
// name - name of the swimming animal
// description - explanation of the exception
Swim_Exception::Swim_Exception(string name, string tmp) : name(name), description(tmp) {
}

const char* Swim_Exception::what() const noexcept {
	string error_message = name + " encountered a critical exception: ";
	error_message += description;
	return error_message.c_str();
}
