#include <iostream>
#include <cstdlib>
#include <ctime>
#include "sea_otter.hpp"

using namespace std;

/**************************************************
** Function: sea_otter
** Description: constructor
** Parameters: none
** Pre-Conditions: none
** Post-Conditions: none
***************************************************/ 
sea_otter::sea_otter() : animal(){
    babies = 2;
    revenue = 5000 * .05;
}

/**************************************************
** Function: sea_otter
** Description: constructor for age of animal
** Parameters: new_age
** Pre-Conditions: none
** Post-Conditions: none
***************************************************/ 
sea_otter::sea_otter(int new_age): animal() {
    age = 0;
}

/**************************************************
** Function: operator
** Description: sea otter operator
** Parameters: sea_otter&o
** Pre-Conditions: none
** Post-Conditions: none
***************************************************/ 
void sea_otter::operator=(const sea_otter &o){
    this->base_cost = o.base_cost;
    this->age = o.age;
    this->babies = o.babies;
    this->food_cost = o.food_cost;
    this->revenue = o.revenue;
}