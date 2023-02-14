#ifndef meerkat_hpp
#define meerkat_hpp

#include <iostream>
#include <cstdlib>
#include <ctime>
#include "animal.hpp"

using namespace std;

class meerkat : public animal{
    private:
    float percent;
    int food_cost;
    int base_cost;
    int revenue;

    public:
    meerkat();
    meerkat(int);
    void operator=(const meerkat &mk);
    int meerkat_food_cost(int meerkat_amt);
    
    
};

#endif