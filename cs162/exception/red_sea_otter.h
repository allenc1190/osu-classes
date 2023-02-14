/*
	Red Sea Otter Class
*/
#ifndef RED_SEA_OTTER_H
#define RED_SEA_OTTER_H

#include <iostream>
#include "sea_otter.h"

using namespace std;

class Red_Sea_Otter : public Sea_Otter {
public:
	Red_Sea_Otter(string);
	void make_noise(int) override;
	void swim(int) override;

private:
};
#endif
