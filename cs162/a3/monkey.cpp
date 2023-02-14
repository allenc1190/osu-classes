#include <iostream>
#include <cstdlib>
#include <ctime>
#include "monkey.hpp"

using namespace std;

/**************************************************
** Function: monkey
** Description: constructor
** Parameters: none
** Pre-Conditions: none
** Post-Conditions: none
***************************************************/ 
monkey::monkey(): animal(){
    babies = 1;
}

/**************************************************
** Function: meerkat
** Description: constructor
** Parameters: new_age
** Pre-Conditions: none
** Post-Conditions: none
***************************************************/ 
monkey::monkey(int new_age): animal() {
    age = 0;
}

/**************************************************
** Function: operator
** Description: monkey overload
** Parameters: none
** Pre-Conditions: none
** Post-Conditions: none
***************************************************/ 
void monkey::operator=(const monkey &b){
    this->base_cost = b.base_cost;
    this->age = b.age;
    this->babies = b.babies;
    this->food_cost = b.food_cost;
    this->revenue = b.revenue;
}