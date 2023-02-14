#include <iostream>
#include <ctime>
#include <vector>
#include "gold.hpp"

using namespace std;

/**************************************************
** Function: GOld
** Description: constructor
** Parameters: none
** Pre-Conditions: none
** Post-Conditions: none
***************************************************/ 
Gold::Gold(){
    message = "You see a glimmer nearby.";
}

/**************************************************
** Function: get_message
** Description: gets the message
** Parameters: none
** Pre-Conditions: none
** Post-Conditions: retruns message
***************************************************/ 
string Gold::get_message(){
    return message;
}

/**************************************************
** Function: ~Gold
** Description: destructor
** Parameters: none
** Pre-Conditions: none
** Post-Conditions: none
***************************************************/ 
Gold::~Gold(){
    
}