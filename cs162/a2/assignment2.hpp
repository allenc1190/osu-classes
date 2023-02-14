#ifndef assignment2_hpp
#define assignment2_hpp

#include <iostream>
#include <fstream>
#include <string>
#include <cstdlib>

#include "restaurant.hpp"

using namespace std;

char emp_or_cust();
bool verification(int id, string password, employee employee_list[], int num_emp);
int emp_to_do_choice();
void emp_if_choice(int choice, Restaurant rest_data);
int cust_choice();
void cust_if_choice(int choice2, Restaurant rest_data);

#endif