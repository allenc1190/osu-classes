#ifndef ptt_hpp
#define pit_hpp

#include <iostream>
#include <ctime>
#include <vector>
#include "event.hpp"

using namespace std;

class Pit : public Event{
    private:
    string message;

    public:
    Pit();
    ~Pit();
    string get_message();

};

#endif