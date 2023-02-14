#include <iostream>
#include <cstdlib>
#include <ctime>
#include "animal.hpp"

using namespace std;

/************************************************
** Function: animal
** Description: set up animal base cost
** Parameters: none
** Pre-Conditions: none
** Post-Conditions: none
*************************************************/ 
animal::animal(){
    base_cost = 40;
}

/**********************************************
** Function: get_age
** Description: gets the age of the animal
** Parameters: none
** Pre-Conditions: none
** Post-Conditions: none
***********************************************/ 
int animal::get_age() {
    return age;
}

/***********************************************
** Function: inc_age
** Description: increases the animal's age by 1
** Parameters: none
** Pre-Conditions: none
** Post-Conditions: none
***********************************************/ 
void animal::inc_age(){
    age += 1;
}

animal::~animal(){
    
}