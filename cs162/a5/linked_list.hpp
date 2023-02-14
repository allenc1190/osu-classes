#ifndef linked_list_hpp
#define linked_list_hpp

#include <iostream>
#include <cstdlib>
#include <ctime>
#include "linked_list_node.hpp"
using namespace std;

class Linked_List {
private:
   unsigned int length; // the number of nodes contained in the list
   Linked_List_Node *first; // a pointer to the first node in the list
   // anything else you need...
public:
   int get_length();
   // note: there is no set_length(unsigned int) (the reasoning should be intuitive)
   void print(); // output a list of all integers contained within the list
   void clear(); // delete the entire list (remove all nodes and reset length to 0)
   unsigned int push_front(int); // insert a new value at the front of the list (returns the new length of the list)
   unsigned int push_back(int num); // insert a new value at the back of the list (returns the new length of the list)
   unsigned int insert(int val, unsigned int index); // insert a new value in the list at the specified index (returns the new length of the list)
   void sort_ascending(); // sort the nodes in ascending order. You must implement the recursive Merge Sort algorithm
   void sort_descending(); // sort the nodes in descending order
   // you can add extra member variables or functions as desired
   Linked_List();
   ~Linked_List();
   Linked_List_Node *get_first();
   int enter_number(int num);
   char a_d();
   void set_next(Linked_List_Node *new_node, Linked_List_Node *d);
   void set_first(Linked_List_Node *new_node);
   int count_prime();
   char try_again();
   Linked_List_Node* merge(Linked_List_Node *left, Linked_List_Node *right);
   void merge_sort(Linked_List_Node **L);
   void if_ad(char s);
   char ask_push_back();
   Linked_List_Node* merge_des(Linked_List_Node *left, Linked_List_Node *right);
   void merge_sort_des(Linked_List_Node **L);
   void split(Linked_List_Node *L, Linked_List_Node **left, Linked_List_Node **right);
};

#endif