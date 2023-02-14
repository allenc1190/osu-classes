#ifndef monkey_hpp
#define monkey_hpp

#include <iostream>
#include <cstdlib>
#include <ctime>
#include "animal.hpp"

using namespace std;

class monkey : public animal{
    private:
    float percent;
    int food_cost;
    int base_cost;
    int revenue;

    public:
    monkey();
    monkey(int);
    void operator=(const monkey &b);
    int monkey_food_cost(int monkey_amt);    
};

#endif