#ifndef pet_hpp
#define pet_hpp
#include <iostream>
#include <string>

using namespace std;

class Pet{
    protected:
    string name;
    int weight;

    public:
    Pet();
    ~Pet();
    string getLifespan();

};

#endif