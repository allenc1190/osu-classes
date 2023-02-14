#include "Restaurant.h"
#include "structs.h"
#include <iostream>
#include <string>
#include <cstdlib>
using namespace std;

Restaurant::Restaurant()
{
	cout << "constructor" << endl;
	num_employees = 0;
	name = "";
	phone = "0000000000";
	address = "";
	employees = NULL;
	week = new hours[7];

}


Restaurant::~Restaurant()
{
	cout << "destructor" << endl;
	delete[] employees;
	delete[] week;
}

Restaurant::Restaurant(const Restaurant &other)
{
	cout << "copy constructor" << endl;
	
	this->name = other.name;
	this->phone = other.phone;
	this->address = other.address;

	this->employees = new employee[num_employees];
	for (int i = 0; i < num_employees; i++) {
		this->employees[i] = other.employees[i];
	}
	this->week = new hours[other.num_hours];
	for (int i = 0; i < this->num_hours; i++) {
		this->week[i] = other.week[i];
	}
}

Restaurant &Restaurant::operator=(const Restaurant &other)
{
	cout << "operator overload" << endl;

	this->name = other.name;	
	this->phone = other.phone;
	this->address = other.address;

	if (this->employees != NULL) {
		delete[] employees;
	}
	if (this->week != NULL) {
		delete[] week;
	}
	this->employees = new employee[3];
	for (int i = 0; i < 3; i++) {
		this->employees[i] = other.employees[i];
	}
	this->week = new hours[other.num_hours];
	for (int i = 0; i < this->num_hours; i++) {
		this->week[i] = other.week[i];
	}
	return *this;
}

void Restaurant::set_name(string name) {
	this->name = name;
}

void Restaurant::print_info()
{
	cout << this->name << endl;
	cout << this->phone << endl;
	cout << this->address << endl;
	cout << this->employees << endl;
	cout << this->week << endl;
}


