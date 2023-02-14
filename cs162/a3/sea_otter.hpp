#ifndef sea_otter_hpp
#define sea_otter_hpp

#include <iostream>
#include <cstdlib>
#include <ctime>
#include "animal.hpp"

using namespace std;

class sea_otter : public animal{
    private:
    float percent;
    int food_cost;
    int base_cost;
    int revenue;

    public:
    sea_otter();
    sea_otter(int);
    int otter_food_cost(int otter_amt);
    void operator=(const sea_otter &o);
    
};

#endif