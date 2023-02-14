/***********************************************
** Program Filename: assignment2_prog.cpp
** Author: Allen Chan
** Date: 4/28/19
** Description: Driver file
** Input: int, strings
** Output: pizza shop data
***********************************************/

#include "assignment2.hpp"
#include "restaurant.hpp"

using namespace std;

int main() {
    char letter;
    int choice, choice2, num_pizzas, num_orders;
    fstream b;
    bool verify = true;

    Menu menu_list;
    Restaurant rest_data;

    rest_data.load_data();
    letter = emp_or_cust();

    if(letter == 'E' || letter == 'e'){
        verify = rest_data.login(letter);
        while(choice != 10){
            choice = emp_to_do_choice();
            emp_if_choice(choice, rest_data);
        }
        b.close();
    }
    else if(letter == 'C' || letter == 'c'){
        while(choice2 != 8){
            choice2 = cust_choice();
            cust_if_choice(choice2, rest_data);
        }
    }
    else if(letter == 'Q' || letter == 'q'){
        exit(0);
    }
    return 0;
}