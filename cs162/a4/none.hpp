#ifndef none_hpp
#define none_hpp

#include <iostream>
#include <ctime>
#include <vector>
#include "event.hpp"

using namespace std;

class None : public Event{
    private:
    string message;

    public:
    None();
    ~None();
    string get_message();


};

#endif