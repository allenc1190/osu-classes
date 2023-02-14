/******************************************************
** Program: assignment1.cpp
** Author: Allen Chan
** Date: 04/14/2019
** Description: Creating a catalog for spells. Allow
access restriction and search for spellbooks.  
** Input: ints, strings
** Output: continues with program
******************************************************/

/*#include <iostream>
#include <fstream>
#include <string>
#include <cstdlib>*/

#include "assignment1.hpp"

using namespace std;

/*bool verification(int id, string password, wizard wizards_list[], int &num);
void get_spellbook_data(spellbook *book, int num, ifstream &b);
void get_spell_data(int num, ifstream &b, spellbook *book);
spell * create_spells(int i, spellbook book[]);
int print_or_file();
void print_by_pages(spellbook *book, int num);
void print_by_effect(spellbook *book, int num);
void print_by_avg(spellbook *book, int num);
void print_to_file();*/

bool checkstr(string user_input) {
  for(int i = 0; i < user_input.length(); i++) {
    if(user_input.at(i) < 48 || user_input.at(i) > 57) {
      return true;
      }
  }
  return false;
}

//create array of spellbooks
spellbook * create_spellbooks(struct spellbook *book){
    int num = 0;
    float avg = 0;
    ifstream b;
    b.open("spellbooks.txt");
    b >> num;

    book = new spellbook[num];

    for(int i = 0; i < num; i++) {
        get_spellbook_data(book, i, b);
        create_spells(i, book);
        get_spell_data(i, b, book);
        for(int j = 0; j < book[i].num_spells; j++){
            avg += book[i].s[j].success_rate;
        }
        book[i].avg_success_rate = avg / book[i].num_spells;
        avg = 0;
    }

    /*for(int i = 0; i < num; i++){
        cout << book[i].title << endl;
        cout << book[i].author << endl;
        cout << book[i].num_pages << endl;
        cout << book[i].edition << endl;
        cout << book[i].num_spells << endl;
        cout << book[i].avg_success_rate << endl;
        for(int j = 0; j < book[i].num_spells; j++){
            cout << book[i].s[j].name << endl;
            cout << book[i].s[j].success_rate << endl;
            cout << book[i].s[j].effect << endl;
        }
    }*/

    return book;
}

//get spellbook data
void get_spellbook_data(spellbook *book, int i, ifstream &b){
        b >> book[i].title;
        b >> book[i].author;
        b >> book[i].num_pages;
        b >> book[i].edition;
        b >> book[i].num_spells;
}

//create spell array
spell * create_spells(int i, spellbook book[]){
    book[i].s = new spell[book[i].num_spells];

    return book[i].s;
}

//gets spell data
void get_spell_data(int num, ifstream &b, spellbook *book){

    for(int i = 0; i < book[num].num_spells; i++) {
        b >> book[num].s[i].name;
        b >> book[num].s[i].success_rate;
        b >> book[num].s[i].effect;
    }
}

//ask user to login
bool ask_login(wizard wizards_list[], int num){
    string user_input;
    int id, tries = 0;
    string password;
    bool again = true;
    bool verify = true;
    
    while(again) {
        if(tries < 3){
            cout << "Enter your id: " << endl;
            cin >> user_input;
            again = checkstr(user_input);
            id = atoi(user_input.c_str());

            cout << "Enter your password: " << endl;
            cin >> password;

            verify = verification(id, password, wizards_list, num);
            if(verify == true) {
                break;
            }
            else{
                tries += 1;
                again = true;
            }
        }
        else{
            cout << "Failed to login three times. Leaving program." << endl;
            exit(0);
        }
    }
    return verify;
}

//create wizard array
void wizard_array(wizard wizards_list[]){
    int num;
    fstream b;
    b.open("wizards.txt");
    b >> num;

    for(int i = 0; i < num; i++){
        b >> wizards_list[i].name;
        b >> wizards_list[i].id;
        b >> wizards_list[i].password;
        b >> wizards_list[i].position_title;
        b >> wizards_list[i].beard_length;
    }
}

//verify the login
bool verification(int id, string password, wizard wizards_list[], int &num){
    for(int i = 0; i < num; i++){
        if(id == wizards_list[i].id){
            if(password == wizards_list[i].password) {
                cout << "Welcome " << wizards_list[i].name << endl;
                cout << "ID: " << wizards_list[i].id << endl;
                cout << "Status: " << wizards_list[i].position_title << endl;
                cout << "Beard length: " << wizards_list[i].beard_length << endl;
                cout << endl;
                return true;
            }
            //cout << "Invalid id or password" << endl;
        }    
    }
    cout << "Invalid id or password" << endl;

    return false;
}

int ask_sort(){
    int choice;

    cout << "Which option would you like to choose?" << endl;
    cout << "1. Sort spellbooks by number of pages: " << endl;
    cout << "2. Group spells by their effect: " << endl;
    cout << "3. Sort spellbooks by average success rate: " << endl;
    cout << "4. Quit: " << endl;

    cin >> choice;

    return choice;
}

void sort_by_pages(spellbook *book, int num){
    struct spellbook temp;

    for(int i = 0; i < num; i++){
        for(int j = i + 1; j < num; j++){
            if(book[i].num_pages > book[j].num_pages){
                temp = book[i];
                book[i] = book[j];
                book[j] = temp;
            }
        }
    }
    int info = print_or_file();

    if(info == 1){
        print_by_pages(book, num);
    }
    else{
        print_to_file();
    }

    /*for(int i = 0; i < num; i++){
        cout << book[i].title << " " << book[i].num_pages << endl;
    }*/
}
void sort_by_effect(spellbook *book, int num){

    string effect_arr[5] = {"bubble", "memory_loss", "fire", "poison", "death"};

    int info = print_or_file();

    for(int i = 0; i < num; i++){
        int count = 0;
        struct spell* tempList = new struct spell[book[i].num_spells];
        for(int j = 0; j < 5; j++){
            for (int t = 0; t < book[i].num_spells; t++)
                if (effect_arr[j] == book[i].s[t].effect) {
                    tempList[count] = book[i].s[t];
                    count++;
                }
        }
        book[i].s = tempList;

        if(info == 1){
            print_by_effect(book, i);
        }
        else{
            print_to_file();
        }

        /*for(int j = 0; j < book[i].num_spells; j++){
            cout << book[i].s[j].effect << " " << book[i].s[j].name << endl;
        }
        cout << endl;
        */
    }

}

//sort by average success rate
void sort_by_avg(spellbook *book, int num){
    struct spellbook temp;

    for(int i = 0; i < num; i++){
        for(int j = i + 1; j < num; j++){
            if(book[i].avg_success_rate < book[j].avg_success_rate){
                temp = book[i];
                book[i] = book[j];
                book[j] = temp;
            }
        }
    }

    int info = print_or_file();

    if(info == 1){
        print_by_avg(book, num);
    }
    else{
        print_to_file();
    }

    /*for(int i = 0; i < num; i++) {
        cout << book[i].title << " " << book[i].avg_success_rate << endl;
    }*/
}

int print_or_file(){
    int info;

    cout << "How would you like the information displayed?" << endl;
    cout << "1. Print to screen: " << endl;
    cout << "2. Print to file: " << endl;

    cin >> info;

    return info;
}

void print_by_pages(spellbook *book, int num){
    for(int i = 0; i < num; i++){
        cout << book[i].title << " " << book[i].num_pages << endl;
    }
}

void print_by_effect(spellbook *book, int i){
    for(int j = 0; j < book[i].num_spells; j++){
            cout << book[i].s[j].effect << " " << book[i].s[j].name << endl;
        }
        cout << endl;
}

void print_by_avg(spellbook *book, int num){
    for(int i = 0; i < num; i++) {
        cout << book[i].title << " " << book[i].avg_success_rate << endl;
    }
}

//checks user's choice
void if_choice(spellbook *book, int num, int choice, int info){

    if(choice == 1) {
        cout << "Sort by pages" << endl;
        sort_by_pages(book, num);
    }
    else if(choice == 2){
        cout << "Sort by effect" << endl;
        sort_by_effect(book, num);
    }
    else if(choice == 3){
        cout << "Sort by average success rate" << endl;
        sort_by_avg(book, num);
    }
    else if(choice == 4){
        exit(0);
    }
}

void print_to_file(){
    //ifstream input_file;
    string file_name;

    cout << "What is the file name?: " << endl;
    cin >> file_name;

    ofstream outfile (file_name.c_str());
    //outfile << "testing" << endl;
    outfile.close();
    cout << "Finished writing to file." << endl;
}

/*int main(int argc, char **argv) {
    int num, choice, info;
    ifstream b;
    bool verify = true;

    
    if(argc < 3){
        cout << "Enter [wizards.txt] [spellbooks.txt]" << endl;
    }
    else
    {
        b.open("wizards.txt");
        b>>num;
        struct wizard wizards_list[num];
        wizard_array(wizards_list);
        verify = ask_login(wizards_list, num);
        b.close();
        b.open("spellbooks.txt");
        b >> num;
        struct spellbook *book;
        if(verify == true){
            book = create_spellbooks(book);
            while(choice != 4){
                choice = ask_sort();
                if_choice(book, num, choice, info);
            }
        }
    }

    return 0;
}*/