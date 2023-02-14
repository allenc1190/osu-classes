#include <iostream>
#include <ctime>
#include <vector>
#include "bats.hpp"

using namespace std;

/**************************************************
** Function: Bats
** Description: constructor
** Parameters: none
** Pre-Conditions: none
** Post-Conditions: none
***************************************************/ 
Bats::Bats(){
    message = "You hear wings flapping.";
}

/**************************************************
** Function: get_message
** Description: returns message
** Parameters: none
** Pre-Conditions: none
** Post-Conditions: return message
***************************************************/ 
string Bats::get_message(){
    return message;
}

/**************************************************
** Function: ~Bats
** Description: destructor
** Parameters: none
** Pre-Conditions: none
** Post-Conditions: none
***************************************************/ 
Bats::~Bats(){

}