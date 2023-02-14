#include <iostream>
#include <ctime>
#include <vector>
#include "pit.hpp"

using namespace std;

/**************************************************
** Function: Pit
** Description: constructor
** Parameters: none
** Pre-Conditions: none
** Post-Conditions: none
***************************************************/ 
Pit::Pit(){
    message = "You feel a breeze.";
}

/**************************************************
** Function: get_message
** Description: gets the message
** Parameters: none
** Pre-Conditions: none
** Post-Conditions: none
***************************************************/ 
string Pit::get_message(){
    return message;
}

/**************************************************
** Function: ~Pit
** Description: destructor
** Parameters: none
** Pre-Conditions: none
** Post-Conditions: none
***************************************************/ 
Pit::~Pit(){

}