#include <iostream>
#include <fstream>
#include <string>
#include <cstdlib>

#include "lab2.hpp"

using namespace std;

student * create_student_db(struct student *info){
    int num = 0;
    ifstream b;
    b.open("name.txt");
    b >> num;

    info = new student[num];

    for(int i = 0; i < num; i++){
        get_student_db_info(info, b, i);
        cout << info[i].id << endl;
        cout << info[i].first_name << endl;
        cout << info[i].last_name << endl;
        cout << info[i].major << endl;
        cout << endl;
    }

    return info;
}

void get_student_db_info(student *info, ifstream &b, int i){
    b >> info[i].id;
    b >> info[i].first_name;
    b >> info[i].last_name;
    b >> info[i].major;
}

int ask_sort(){
    int choice;

    cout << "How do you want to sort?" << endl;
    cout << "1. Sort by ID: " << endl;
    cout << "2. Sort by last name: " << endl;
    cout << "3. Sort by major: " << endl;
    cout << "4. Exit: " << endl;

    cin >> choice;

    return choice;
}

void if_choice(int choice, student *info, int num){
    if(choice == 1){
        cout << "Sort by ID" << endl;
        sort_by_id(info, num);
    }
    else if(choice == 2){
        cout << "Sort by last name" << endl;
        sort_last_name(info, num);
    }
    else if(choice == 3){
        cout << "Sort by major" << endl;
    }
    else if(choice == 4){
        cout << "Quitting" << endl;
        exit(0);
    }
}

void sort_by_id(student *info, int num){
    struct student temp;

    for(int i = 0; i < num; i++){
        for(int j = i + 1; j < num; j++){
            if(info[i].id > info[j].id){
                temp = info[i];
                info[i] =info[j];
                info[j] = temp;
            }
        }
    }
    print_id(info, num);
}

void print_id(student *info, int num){
    for(int i = 0; i < num; i++){
        cout << info[i].id << " " << info[i].first_name << " " << info[i].last_name << endl;
    }
}

void sort_last_name(student *info, int num){

    for(int i = 0; i < num; i++){
        struct student *templist = new struct student[i];
        cout << info[i].last_name << endl;
    }

}

/*void print_last_name(student *info, int num){
    for(int i = 0; i < info[num]; i++){
            cout << info[i].last_name << endl;
        }
        cout << endl;
}*/