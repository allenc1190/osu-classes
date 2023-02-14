#ifndef bats_hpp
#define bats_hpp

#include <iostream>
#include <ctime>
#include <vector>
#include "event.hpp"

using namespace std;

class Bats : public Event{
    private:
    string message;

    public:
    Bats();
    ~Bats();
    string get_message();

};

#endif