#include <iostream>
#include <ctime>
#include <vector>
#include "event.hpp"

using namespace std;

/**************************************************
** Function: Event
** Description: constructor
** Parameters: none
** Pre-Conditions: none
** Post-Conditions: none
***************************************************/ 
Event::Event(){
    //message  = " ";
}

/**************************************************
** Function: ~Event
** Description: destructor
** Parameters: none
** Pre-Conditions: none
** Post-Conditions: none
***************************************************/ 
Event::~Event(){
    //cout << "in event dest" << endl;

}

/**************************************************
** Function: get_type
** Description: gets the event type
** Parameters: none
** Pre-Conditions: none
** Post-Conditions: none
***************************************************/ 
char Event::get_type(){
    return type;
}

/**************************************************
** Function: set_type
** Description: sets the event type
** Parameters: none
** Pre-Conditions: none
** Post-Conditions: none
***************************************************/ 
void Event::set_type(char e){
    type = e;
}

/**************************************************
** Function: get_message
** Description: gets message
** Parameters: none
** Pre-Conditions: none
** Post-Conditions: none
***************************************************/ 
string Event::get_message(){
    return message;
}

/**************************************************
** Function: print_message
** Description: prints the message
** Parameters: none
** Pre-Conditions: none
** Post-Conditions: none
***************************************************/ 
void Event::print_message(){
    cout << "message = " << message  << endl;
    //cout << message << endl;
}