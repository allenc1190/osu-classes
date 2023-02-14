/*******************************************************
** Program linked_list_node.cpp
** Author: Allen Chan
** Date: 6/9/19
** Description: info for the nodes
** Input: none
** Output: none
********************************************************/

#include "linked_list_node.hpp"

using namespace std;

/**************************************************
** Function: Linked_List_Node
** Description: constructor
** Parameters: none
** Pre-Conditions: none
** Post-Conditions: none
***************************************************/ 
Linked_List_Node::Linked_List_Node(){
    next = NULL;
}

/**************************************************
** Function: ~Linked_List_Node
** Description: Deconstructor
** Parameters: none
** Pre-Conditions: none
** Post-Conditions: none
***************************************************/ 
Linked_List_Node::~Linked_List_Node(){
    
}

//mutator
/**************************************************
** Function: set_val
** Description: sets the val
** Parameters: int val
** Pre-Conditions: none
** Post-Conditions: none
***************************************************/ 
void Linked_List_Node::set_val(int val){
    this->val = val;
}

/**************************************************
** Function: set_next
** Description: sets the next pointer
** Parameters: Linked_List_Node *next
** Pre-Conditions: none
** Post-Conditions: none
***************************************************/ 
Linked_List_Node *Linked_List_Node::set_next(Linked_List_Node *next){
    this->next = next;
}

//accessor
/**************************************************
** Function: get_next
** Description: gets the next
** Parameters: none
** Pre-Conditions: none
** Post-Conditions: none
***************************************************/ 
Linked_List_Node *Linked_List_Node::get_next(){
    return next;
}