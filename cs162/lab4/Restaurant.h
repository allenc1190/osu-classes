#pragma once
#include <iostream>
#include "structs.h"
using namespace std;

class Restaurant
{
private:
	//Menu menu;
	int num_employees;
	employee* employees;
	hours* week;
	string name;
	string phone;
	string address;
	int num_hours;
public:
	Restaurant();
	~Restaurant();
	Restaurant(const Restaurant &);
	Restaurant &operator=(const Restaurant &);
	void set_name(string name);
	void print_info();
};

