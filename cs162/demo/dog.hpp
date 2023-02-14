#ifndef dog_hpp
#define dog_hpp
#include <iostream>
#include <string>
#include "pet.hpp"

using namespace std;

class Dog : public Pet{
    private:
    string breed;

    public:
    Dog();
    ~Dog();
    string getLifespan(int weight);
};

#endif