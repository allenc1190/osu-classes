#ifndef player_hpp
#define player_hpp

#include <iostream>
#include <ctime>
#include <vector>
#include "event.hpp"

using namespace std;

class Player : public Event{
    private:
    int arrows;
    bool gold;

    public:
    Player();
    ~Player();
    void print_arrow();
    int shoot_arrow(int arrows);

};

#endif