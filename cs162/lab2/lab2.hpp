#include <iostream>
#include <fstream>
#include <string>
#include <cstdlib>

using namespace std;

struct student {
  int id;
  string first_name;
  string last_name; 
  string major;
};

student * create_student_db(struct student *info);
void get_student_db_info(student *info, ifstream &b, int i);
int ask_sort();
void if_choice(int choice, student *info, int num);
void sort_by_id(student *info, int num);
void print_id(student *info, int num);
void sort_last_name(student *info, int num);
void print_last_name(student *info, int num);