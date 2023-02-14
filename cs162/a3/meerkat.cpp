#include <iostream>
#include <cstdlib>
#include <ctime>
#include "meerkat.hpp"

using namespace std;

/**************************************************
** Function: meerkat
** Description: constructor
** Parameters: none
** Pre-Conditions: none
** Post-Conditions: none
***************************************************/ 
meerkat::meerkat() : animal(){
    babies = 5;
}

/**************************************************
** Function: meerkat(int)
** Description: constructor for animal age
** Parameters: none
** Pre-Conditions: none
** Post-Conditions: none
**************************************************/ 
meerkat::meerkat(int) : animal(){
    age = 0;
}

/*************************************************
** Function: operator
** Description: gets the info for the animal
** Parameters: none
** Pre-Conditions: none
** Post-Conditions: none
*************************************************/ 
void meerkat::operator=(const meerkat &mk){
    this->base_cost = mk.base_cost;
    this->age = mk.age;
    this->babies = mk.babies;
    this->food_cost = mk.food_cost;
    this->revenue = mk.revenue;
}