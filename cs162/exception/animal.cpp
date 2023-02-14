/*
	Animal Class
*/
#include <iostream>
#include "animal.h"

using namespace std;

Animal::Animal(string name) {
	cout << "Alternate animal constructor called" << endl;
	this->name = name;
	this->age = 0;
}

Animal::Animal(string name, int age) {
	cout << "Alternate animal constructor called" << endl;
	this->name = name;
	this->age = age;
}

Animal::Animal() {
	cout << "Default animal constructor called" << endl;
	this->name = "Specimen Unknown";
	this->age = 0;
}

// overload the pre-increment operator
Animal& Animal::operator++() {
	++age;
	return *this;
}

string Animal::get_name() {
	return name;
}

void Animal::make_noise(int num) {
	for (int i = 0; i < num; i++)
		cout << "???" << " ";
	cout << endl;
}

// overload the stream operator
ostream& operator<<(ostream& out, const Animal& a) {
	out << "Name: " << a.name << ", Age: " << a.age;
	return out;
}
