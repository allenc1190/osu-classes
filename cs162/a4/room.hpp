#ifndef room_hpp
#define room_hpp

#include <iostream>
#include <ctime>
#include <vector>
#include "event.hpp"
#include "bats.hpp"
#include "gold.hpp"
#include "pit.hpp"
#include "wumpus.hpp"
#include "none.hpp"
#include "player.hpp"

using namespace std;

class Room{
    private:
    char player;
    Event *event;
    bool occupied;

    public:
    Room();
    ~Room();
    bool get_occupied();
    void set_event(char m);
    Event* get_event();
    void set_player(Event *temp);
};

#endif