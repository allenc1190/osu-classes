#ifndef animal_hpp
#define animal_hpp

#include <iostream>
#include <cstdlib>
#include <ctime>

using namespace std;

class animal{
    protected:
    int base_cost;
    int age;
    int babies;
    int food_cost;

    public:
    animal();
    ~animal();
    int get_age();
    void inc_age();

};

#endif