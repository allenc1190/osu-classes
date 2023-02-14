#ifndef pizza_hpp
#define pizza_hpp

#include <iostream>
#include <fstream>
#include <string>
#include <cstdlib>

using namespace std;

class Pizza {
  private:
    string name;
    int small_cost;
    int medium_cost;
    int large_cost;
    int num_ingredients;
    string* ingredients;
  public:
    //need to include accessor functions and mutator functions for each private member
    //need to include constructors, copy constructors, assignment operator overload,
    //and destructors where appropriate
    Pizza();
    ~Pizza();
    void create_ingredient();
    string get_name();
    int get_small_cost();
    int get_medium_cost();
    int get_large_cost();
    int get_num_ingredients();
    string get_ingredients(int i);
    void set_num_ingredients(int num);
    void set_ingredients(string ingredient_name, int j);
    void set_small_cost(int small_cost);
    void set_medium_cost(int medium_cost);
    void set_large_cost(int large_cost);
    void set_name(string name);
};

#endif