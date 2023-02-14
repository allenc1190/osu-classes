#ifndef linked_list_node_hpp
#define linked_list_node_hpp

#include <iostream>
#include <cstdlib>
#include <ctime>
using namespace std;

class Linked_List_Node {
public:
   int val; // the value that this node stores
   Linked_List_Node *next; // a pointer to the next node in the list
   // you can add constructors or other functionality if you you find it useful or necessary
   Linked_List_Node();
   ~Linked_List_Node();
   void set_val(int val);
   Linked_List_Node *set_next(Linked_List_Node *next);
   Linked_List_Node *get_next();

};

#endif