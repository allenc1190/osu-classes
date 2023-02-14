#include <iostream>
#include <fstream>
#include <string>
#include <cstdlib>

#include "pizza.hpp"
#include "assignment2.hpp"

using namespace std;

//constructor
Pizza::Pizza(){
}

//destructor(doesn't work properly if used)
Pizza::~Pizza(){
    //cout << "pizzacpp" << endl;
    //delete [] ingredients;
}

//accessor

//gets pizza name
string Pizza::get_name(){
    return name;
}

//gets number of ingredients
int Pizza::get_num_ingredients(){
    return num_ingredients;
}

//gets the ingredients array
string Pizza::get_ingredients(int i){
    return ingredients[i];
}

//gets small cost for pizza
int Pizza::get_small_cost(){
    return small_cost;
}

//gets medium cost for pizza
int Pizza::get_medium_cost(){
    return medium_cost;
}

//gets large cost for pizza
int Pizza::get_large_cost(){
    return large_cost;
}

//create ingredients array
void Pizza::create_ingredient(){
    ingredients = new string[num_ingredients];
}

//mutator

//sets the number of ingredients
void Pizza::set_num_ingredients(int num){
    num_ingredients = num;
}

//sets the ingredients to the array
void Pizza::set_ingredients(string ingredient_name, int j){
    ingredients[j] = ingredient_name;
}


//sets small cost pizza
void Pizza::set_small_cost(int small_cost){
    this->small_cost = small_cost;
}

//sets medium cost of pizza
void Pizza::set_medium_cost(int medium_cost){
    this->medium_cost = medium_cost;
}

//sets large cost of pizza
void Pizza::set_large_cost(int large_cost){
    this->large_cost = large_cost;
}

//sets name of pizza
void Pizza::set_name(string name){
    this->name = name;
}