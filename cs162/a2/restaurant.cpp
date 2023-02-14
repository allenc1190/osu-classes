#include <iostream>
#include <fstream>
#include <string>
#include <cstdlib>

#include "menu.hpp"
#include "restaurant.hpp"
#include "assignment2.hpp"

using namespace std;

//constructor
Restaurant::Restaurant(){
    week = new hours[7];
}

//ask for login if employee
bool Restaurant::login(char letter){
    int id;
    string password;
    bool verify = true;
    bool again = true;

    while(again){
        if(letter == 'E' || letter == 'e'){
            cout << "Enter your ID: ";
            cin >> id;

            cout << "Enter your password: " << endl;
            cin >> password;

            verify = verification(id, password, employees, num_emp);
            if(verify == true) {
                break;
            }
            else{
                cout << "Invalid id or password" << endl;
            }
        }
    }
}

//load employee data
void Restaurant::load_emp(){
    fstream b;
    string unused3;
    num_emp = 0;

    b.open("employee.txt");
    while(getline(b, unused3)){
        ++num_emp;
    }
    employees = new employee[num_emp];
    b.close();
    b.open("employee.txt");
    for(int i = 0; i < num_emp; i++){
        b >> employees[i].id;
        b >> employees[i].password;
        b >> employees[i].first_name;
        b >> employees[i].last_name;
    }
    b.close();
}

//load restaurant info data
void Restaurant::load_rest_info(){
    fstream r;

    r.open("restaurant_info.txt");
    getline(r, name);
    getline(r, phone);
    getline(r, address);

    for(int i = 0; i < 7; i++){
        r >> week[i].day;
        r >> week[i].open_hour;
        r >> week[i].close_hour;
    }
    r.close();
}

//loads menu data
void Restaurant::load_menu(){
    fstream t;
    int n;
    string s, unused2;
    pizza_num = 0;

    t.open("menu.txt");
    while(getline(t, unused2)){
        ++pizza_num;
    }
    t.close();

    Pizza *pizzas = new Pizza[pizza_num];
    menu.set_pizzas(name, pizzas, pizza_num);
    delete[] pizzas;

    t.open("menu.txt");
    for(int i = 0; i < pizza_num; i++){
        t >> s;
        menu.get_pizzas(i).set_name(s);
        t >> n;
        menu.get_pizzas(i).set_small_cost(n);
        t >> n;
        menu.get_pizzas(i).set_medium_cost(n);
        t >> n;
        menu.get_pizzas(i).set_large_cost(n);
        t >> n;
        menu.get_pizzas(i).set_num_ingredients(n);
        menu.get_pizzas(i).create_ingredient();
        for(int j = 0; j < menu.get_pizzas(i).get_num_ingredients(); j++){
            t >> s;
            menu.get_pizzas(i).set_ingredients(s, j);
        }
    }
    t.close();
}

//load order data
void Restaurant::load_order(){
    fstream d;
    string unused;
    num_orders = 0;

    d.open("orders.txt");
    while(getline(d, unused)){
        ++num_orders;
    }
    order_list = new orders[num_orders];
    d.close();
    d.open("orders.txt");

    for(int i = 0; i < num_orders; i++){
        d >> order_list[i].order_num;
        d >> order_list[i].cust_first;
        d >> order_list[i].cust_last;
        d >> order_list[i].cust_cc;
        d >> order_list[i].cust_phone;
        d >> order_list[i].cust_pizza;
        d >> order_list[i].size;
        d >> order_list[i].pizza_amount;
    }
    d.close();
}

//loads all data
void Restaurant::load_data(){
    load_emp();
    load_menu();
    load_rest_info();
    load_order();
}

//views orders
void Restaurant::view_orders(){
    num_orders;

    for(int i = 0; i < num_orders; i++){
        cout << order_list[i].order_num << " ";
        cout << order_list[i].cust_first << " ";
        cout << order_list[i].cust_last << " ";
        cout << order_list[i].cust_cc << " ";
        cout << order_list[i].cust_phone << " ";
        cout << order_list[i].cust_pizza << " ";
        cout << order_list[i].size << " ";
        cout << order_list[i].pizza_amount << " ";
        cout << endl;
    }
}

//ask user to change hours
void Restaurant::change_hours(){
    string day;
    int open, close;
    this->view_hours();
    cout << "What day would you like to change?" << endl;
    cin >> day;
    cout << "What is the opening time?" << endl;
    cin >> open;
    cout << "What is the closing time?" << endl;
    cin >> close;

}

//view hours
void Restaurant::view_hours(){
    for(int i = 0; i < 7; i++){
        cout << week[i].day << " ";
        cout << week[i].open_hour << " ";
        cout << week[i].close_hour << " ";
        cout << endl;
    }
}

//views the address
void Restaurant::view_address(){
    cout << address << endl;
}

//views the phone number
void Restaurant::view_phone(){
    cout << phone << endl;
}

//views the menu
void Restaurant::view_menu(){
    pizza_num;

    for(int i = 0; i < pizza_num; i++){
        cout << "Pizza: " << menu.get_pizzas(i).get_name() << endl;
        cout << "small cost = $" << menu.get_pizzas(i).get_small_cost() << endl;
        cout << "medium cost = $" << menu.get_pizzas(i).get_medium_cost() << endl;
        cout << "large cost = $" << menu.get_pizzas(i).get_large_cost() << endl;
        menu.get_pizzas(i).get_num_ingredients();
        cout << "ingredients: " << endl;
        for(int j = 0; j < menu.get_pizzas(i).get_num_ingredients(); j++){
            cout << menu.get_pizzas(i).get_ingredients(j) << endl;
        }
        cout << endl;
    }
}

//destructor(doesn't work properly if used)
Restaurant::~Restaurant(){
    //cout << "rest cpp" << endl;
    //delete[] employees;
    //delete[] week;
    //delete[] order_list;
}

//sets the hours
void Restaurant::set_hours(int w, string oh, string ch){
    week[w].open_hour = oh;
    week[w].close_hour = ch;
}

//s;ets the address name
void Restaurant::set_name(string name){
    this->name = name;
}

//sets the phone number
void Restaurant::set_phone(string phone){
    this->phone = phone;
}

//sets address
void Restaurant::set_address(string address){
    this->address = address;
}