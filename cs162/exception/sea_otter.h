/*
	Sea Otter Class
*/
#ifndef SEA_OTTER_H
#define SEA_OTTER_H

#include <iostream>
#include <exception>
#include "animal.h"
#include "swim_exception.h"

using namespace std;

class Sea_Otter : public Animal {
public:
	void make_noise(int) = 0;
	virtual void swim(int) = 0;
	double predict_swim_time(int);

protected:
	// Note that Sea_Otters can also have extra properties in addition
	// to the ones that are inherited.
	int maximum_length;
	// set default swim speed to 0
	double swim_speed = 0;
};
#endif
