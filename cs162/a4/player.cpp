#include <iostream>
#include <ctime>
#include <vector>
#include "player.hpp"

using namespace std;

/**************************************************
** Function: 
** Description: 
** Parameters: none
** Pre-Conditions: none
** Post-Conditions: none
***************************************************/ 
Player::Player(){
    arrows = 3;
    gold = false; 
}

/**************************************************
** Function: ~Player
** Description: destructor
** Parameters: none
** Pre-Conditions: none
** Post-Conditions: none
***************************************************/ 
Player::~Player(){
    
}

/**************************************************
** Function: print_arrow
** Description: print amount of arrows
** Parameters: none
** Pre-Conditions: none
** Post-Conditions: none
***************************************************/ 
void Player::print_arrow(){
    cout << "Arrows = " << arrows << endl;
}