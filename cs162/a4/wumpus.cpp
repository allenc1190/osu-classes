#include <iostream>
#include <ctime>
#include <vector>
#include "wumpus.hpp"

using namespace std;

/**************************************************
** Function: Wumpus
** Description: constructor
** Parameters: none
** Pre-Conditions: none
** Post-Conditions: none
***************************************************/ 
Wumpus::Wumpus(){
    message = "You smell a terrible stench.";
}

/**************************************************
** Function: get_message
** Description: gets the message
** Parameters: none
** Pre-Conditions: none
** Post-Conditions: none
***************************************************/ 
string Wumpus::get_message(){
    return message;
}

/**************************************************
** Function: ~Wumpus
** Description: destructor
** Parameters: none
** Pre-Conditions: none
** Post-Conditions: none
***************************************************/ 
Wumpus::~Wumpus(){
    
}