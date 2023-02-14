#include <iostream>
#include <fstream>
#include <string>
#include <cstdlib>

using namespace std;

struct wizard {
  string name;
  int id;
  string password;
  string position_title; 
  float beard_length;
};

struct spellbook {
  string title;
  string author;
  int num_pages;
  int edition;
  int num_spells;
  float avg_success_rate;
  struct spell *s;
};

struct spell {
  string name;
  float success_rate;
  string effect; 
};

bool checkstr(string user_input);
spellbook * create_spellbooks(struct spellbook *book);
void get_spellbook_data(spellbook *book, int i, ifstream &b);
spell * create_spells(int i, spellbook book[]);
void get_spell_data(int num, ifstream &b, spellbook *book);
bool ask_login(wizard wizards_list[], int num);
void wizard_array(wizard wizards_list[]);
bool verification(int id, string password, wizard wizards_list[], int &num);
int ask_sort();
void sort_by_pages(spellbook *book, int num);
void sort_by_effect(spellbook *book, int num);
void sort_by_avg(spellbook *book, int num);
int print_or_file();
void print_by_pages(spellbook *book, int num);
void print_by_effect(spellbook *book, int i);
void print_by_avg(spellbook *book, int num);
void if_choice(spellbook *book, int num, int choice, int info);
void print_to_file();