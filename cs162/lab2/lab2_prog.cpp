#include <iostream>
#include <fstream>
#include <string>
#include <cstdlib>

#include "lab2.hpp"

using namespace std;

int main(){
    ifstream b;
    int num, choice;
    struct student *info;
    b.open("name.txt");
    b >> num;

    if(b.is_open()){
        info = create_student_db(info);
        while(choice != 4){
            choice = ask_sort();
            if_choice(choice, info, num);
        }
    }
    else {
        cout << "files does not exist." << endl;
    }


    return 0;
}