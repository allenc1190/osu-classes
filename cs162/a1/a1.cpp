/******************************************************
** Program: a1.cpp
** Author: Allen Chan
** Date: 04/14/2019
** Description: Creating a catalog for spells. Allow
access restriction and search for spellbooks.  
** Input: ints, strings
** Output: continues with program
******************************************************/

#include <iostream>
#include <fstream>
#include <string>
#include <cstdlib>

using namespace std;

bool checkstr(string user_input) {
  for(int i = 0; i < user_input.length(); i++) {
    if(user_input.at(i) < 48 || user_input.at(i) > 57) {
      return true; }
  }
  return false;
}


//spellbook * create_spellbooks(int);

//void get_spellbook_data(spellbook *, int, ifstream &); 

//spell * create_spells(int);

//void get_spell_data(spell *, int, ifstream &);

//void delete_info(wizard **, spellbook **, int);

//ask user to login
void ask_login() {
    string user_input;
    int id, tries = 0;
    char password, *array;

    bool again = true;
    
    //array = new char[];
    
    while(again) {
        if(tries < 3){
            cout << "Enter your id: " << endl;
            cin >> user_input;
            again = checkstr(user_input);
            id = atoi(user_input.c_str());

            cout << "Enter your password: " << endl;
            cin >> password;

            tries += 1;
        }
        else{
            cout << "Failed to login three times. Leaving program." << endl;
            exit(0);
        }
    }
}

void input_wizards(){
    struct wizard *ptr_wizard;
    int int_num_student;
    string t_input, str_num_student;
    ifstream inf ("wizards.txt");
    inf >> str_num_student;
    cout << str_num_student << endl;
    int_num_student = atoi(str_num_student.c_str());
    ptr_wizard = change_name(int_num_student);

    //struct point * = num_student;
    //for(until it hits the end)
}

int main() {
    input_wizards();
    ask_login();

    return 0;
}