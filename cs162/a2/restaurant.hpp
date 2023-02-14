#ifndef restaurant_hpp
#define restaurant_hpp

#include <iostream>
#include <fstream>
#include <string>
#include <cstdlib>

#include "menu.hpp"

using namespace std;

struct employee {
  int id;
  string password;
  string first_name;
  string last_name;
};

struct hours {
  string day;
  string open_hour;
  string close_hour;
};

struct orders{
  int order_num;
  string cust_first;
  string cust_last;
  string cust_cc;
  string cust_phone;
  string cust_pizza;
  string size;
  int pizza_amount;
};

class Restaurant {
  private:
    Menu menu;
    employee* employees;
    hours* week;
    orders *order_list;
    string name;
    string phone;
    string address;
    int num_emp;
    int pizza_num;
    int num_orders;
  public:
    //need to include accessor functions and mutator functions for each private member
    //need to include constructors, copy constructors, assignment operator overload,
    //and destructors where appropriate
    Restaurant();
    ~Restaurant();
    void load_data(); //reads from files to correctly populate menu, employees, hours, etc.
    bool login(char letter);
    void view_menu();
    void view_hours();
    void view_address();
    void view_phone();
    void search_menu_by_price();
    void search_by_ingredients();
    void place_order(Pizza* selection);
    void change_hours();
    void add_to_menu();
    void remove_from_menu();
    void view_orders();
    void remove_orders();
    void set_name(string name);
    void set_phone(string phone);
    void set_address(string address);
    void set_hours(int w, string oh, string ch);
    void load_emp();
    void load_rest_info();
    void load_menu();
    void load_order();
    };



#endif