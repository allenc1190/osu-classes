#include <iostream>
#include <fstream>
#include <string>
#include <cstdlib>

#include "pizza.hpp"
#include "menu.hpp"
#include "assignment2.hpp"

using namespace std;

Menu::Menu(){ //constructor
}

//destructor(doesn't work properly if used)
Menu::~Menu(){
    //cout << "menucpp" << endl;
    //delete[] pizzas;
}

//accessor

//gets the number of pizzas
int Menu::get_num_pizzas(){
    return num_pizzas;
}

//creates pizza array
Pizza &Menu::get_pizzas(int i){
    return pizzas[i];
}

//mutator

//sets the number of pizzas
void Menu::set_num_pizzas(int num_pizzas){
    this->num_pizzas = num_pizzas;
}

//sets pizzas into an array
void Menu::set_pizzas(string name, Pizza *pizza, int num_pizzas){
    pizzas = new Pizza[num_pizzas];
    for(int i = 0; i < num_pizzas; i++){
        pizzas[i]=pizza[i];
    }
}