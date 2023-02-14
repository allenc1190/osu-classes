/*
	Sea Otter Class
*/
#include <iostream>
#include "sea_otter.h"

using namespace std;

// predict the time to swim a certain distance
double Sea_Otter::predict_swim_time(int distance) {
	if (swim_speed == 0) {
		// throw a double to indicate that there's a problem
		//throw swim_speed;
		// throw a generic exception
		//throw exception();
		// throw a detailed exception using the class we created
		throw Swim_Exception(name, "Invalid speed");
	}
	return distance/swim_speed;
}
