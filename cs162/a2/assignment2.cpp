/***********************************************
** Program Filename: assignment2.cpp
** Author: Allen Chan
** Date: 4/28/19
** Description: implementation file
** Input: int, strings
** Output: pizza shop data
***********************************************/

#include "assignment2.hpp"

using namespace std;


//see who is using the program
char emp_or_cust(){
    char letter;

    cout << "Welcome to Bytes Pizza!" << endl;
    cout << "Are you a customer (C) or employee (E) or would you like to quit(Q)?" << endl;
    cin >> letter;

    return letter;
}

//checks if login is valid
bool verification(int id, string password, employee employee_list[], int num_emp){
    for(int i = 0; i < num_emp; i++){
        if(id == employee_list[i].id){
            if(password == employee_list[i].password) {
                cout << "Welcome " << employee_list[i].first_name << " " << employee_list[i].last_name << endl;
                return true;
            }
        }    
    }
    return false;
}

//get user to choose what they want to do
int emp_to_do_choice(){
    int choice;

    cout << "What would you like to do?" << endl;
    cout << "1. Change hours" << endl;
    cout << "2. View orders" << endl;
    cout << "3. Remove order" << endl;
    cout << "4. Add item from menu" << endl;
    cout << "5. Remove item from menu" << endl;
    cout << "6. View menu" << endl;
    cout << "7. View hours" << endl;
    cout << "8. View address" << endl;
    cout << "9. View phone" << endl;
    cout << "10. Log out" << endl;
    cin >> choice;

    return choice;
}

//run the choice that user made
void emp_if_choice(int choice, Restaurant rest_data){
    if(choice == 1){
        rest_data.change_hours();
    }
    else if(choice == 2){
        rest_data.view_orders();
    }
    else if(choice == 3){
        cout << "in choice 3" << endl;
    }
    else if(choice == 4){
        cout << "in choice 4" << endl;
    }
    else if(choice == 5){
        cout << "in choice 5" << endl;
    }
    else if(choice == 6){
        rest_data.view_menu();
    }
    else if(choice == 7){
        rest_data.view_hours();
    }
    else if(choice == 8){
        rest_data.view_address();
    }
    else if(choice == 9){
        rest_data.view_phone();
    }
    else if(choice == 10){
        cout << "You have been logged out" << endl;
        exit(0);
    }
}

//ask what customer wants to do
int cust_choice(){
    int choice2;

    cout << "What would you like to do?" << endl;
    cout << "1. View menu" << endl;
    cout << "2. Search by cost" << endl;
    cout << "3. Search by ingredients" << endl;
    cout << "4. Place order" << endl;
    cout << "5. View hours" << endl;
    cout << "6. View address" << endl;
    cout << "7. View phone" << endl;
    cout << "8. Log out" << endl;
    cin >> choice2;

    return choice2;
}

//run the choice that the customer chooses to do
void cust_if_choice(int choice2, Restaurant rest_data){
    if(choice2 == 1){
        rest_data.view_menu();
    }
    else if(choice2 == 2){
        cout << "in choice 2" << endl;
    }
    else if(choice2 == 3){
        cout << "in choice 3" << endl;
    }
    else if(choice2 == 4){
        cout << "in choice 4" << endl;
    }
    else if(choice2 == 5){
        rest_data.view_hours();
    }
    else if(choice2 == 6){
        rest_data.view_address();
    }
    else if(choice2 == 7){
        rest_data.view_phone();
    }
    else if(choice2 == 8){
        cout << "You have been logged out" << endl;
        exit(0);
    }
}