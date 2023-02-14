#include <iostream>
#include <ctime>
#include <vector>
#include "room.hpp"

using namespace std;
/**************************************************
** Function: Room
** Description: constructor
** Parameters: none
** Pre-Conditions: none
** Post-Conditions: none
***************************************************/ 
Room::Room(){
    player = '*';
    occupied = false;
    event = new None();
}

/*bool Room::get_occupied(){
    return occupied;
}*/

/**************************************************
** Function: set_event
** Description: sets event
** Parameters: char m
** Pre-Conditions: none
** Post-Conditions: none
***************************************************/ 
void Room::set_event(char m){
    //delete event;
    if(m == 'b'){
        event = new Bats();
        event->set_type('b');
    }
    else if(m == 'p'){
        event = new Pit();
        event->set_type('p');
    }
    else if(m == 'g'){
        event = new Gold();
        event->set_type('g');
    }
    else if(m == 'w'){
        event = new Wumpus();
        event->set_type('w');   
    }
    else if(m == '*'){
        event = new Player();
        event->set_type('*');
    }
    else if(m == ' '){
        event = new None();
        event->set_type(' ');
    }
}

/**************************************************
** Function: ~Room
** Description: destructor
** Parameters: none
** Pre-Conditions: none
** Post-Conditions: none
***************************************************/ 
Room::~Room(){
    //cout << "test2" << endl;
    delete event;
}

/**************************************************
** Function: get_event
** Description: gets the event
** Parameters: none
** Pre-Conditions: none
** Post-Conditions: none
***************************************************/ 
Event* Room::get_event(){
    return event;
}

/**************************************************
** Function: set_player
** Description: sets the player
** Parameters: Event *temp
** Pre-Conditions: none
** Post-Conditions: none
***************************************************/ 
void Room::set_player(Event *temp){
    event = temp;
    event->set_type('*');
}