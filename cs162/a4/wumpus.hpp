#ifndef wumpus_hpp
#define wumpus_hpp

#include <iostream>
#include <ctime>
#include <vector>
#include "event.hpp"

using namespace std;

class Wumpus : public Event{
    private:
    string message;

    public:
    Wumpus();
    ~Wumpus();
    string get_message();

};

#endif