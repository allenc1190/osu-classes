#ifndef menu_hpp
#define menu_hpp

#include <iostream>
#include <fstream>
#include <string>
#include <cstdlib>

#include "pizza.hpp"

using namespace std;

class Menu {
  private:
    int num_pizzas;
    Pizza *pizzas;
  public:
    //need to include accessor functions and mutator functions for each private member
    //need to include constructors, copy constructors, assignment operator overload,
    //and destructors where appropriate
    Menu();
    ~Menu();
    int get_num_pizzas();
    Pizza &get_pizzas(int i);
    Menu search_pizza_by_cost(int upper_bound, string size);
    Menu search_pizza_by_ingredients_to_include(string* ingredients, int num_ingredients);
    Menu search_pizza_by_ingredients_to_exclude(string* ingredients, int num_ingredients);
    void add_to_menu(Pizza pizza_to_add);
    void remove_from_menu(int index_of_pizza_on_menu);
    void set_num_pizzas(int num_pizzas);
    void set_pizzas(string name, Pizza *pizza, int num_pizzas);
};

#endif