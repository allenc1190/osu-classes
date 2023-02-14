#ifndef gold_hpp
#define gold_hpp

#include <iostream>
#include <ctime>
#include <vector>
#include "event.hpp"

using namespace std;

class Gold : public Event{
    private:
    string message;

    public:
    Gold();
    ~Gold();
    string get_message();

};

#endif