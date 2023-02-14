/*
	Animal Class
*/
#ifndef ANIMAL_H
#define ANIMAL_H

#include <iostream>
using namespace std;

class Animal {
public:
	Animal();
	Animal(string);
	Animal(string, int);
	Animal& operator++(); // pre-increment
	virtual string get_name();
	// if we wanted to prevent any child class from overriding get_name()
	// we would just mark it as final (shown below):
//	virtual string get_name() final;
	// declare the make_noise function as abstract (a pure virtual function)
	virtual void make_noise(int) = 0;

	friend ostream& operator<<(ostream& out, const Animal& a);

private:
	// nothing here

protected:
	string name;
	int age;

};
#endif
