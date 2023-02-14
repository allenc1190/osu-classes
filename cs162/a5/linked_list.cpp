/*******************************************************
** Program linked_list.cpp
** Author: Allen Chan
** Date: 6/9/19
** Description: add numbers to a linked list and sorting them
** Input: char and int
** Output: runs program
********************************************************/

#include "linked_list.hpp"

using namespace std;

/**************************************************
** Function: Linked_List
** Description: constructor
** Parameters: none
** Pre-Conditions: none
** Post-Conditions: none
***************************************************/ 
Linked_List::Linked_List(){
    length = 0;
    first = NULL;
}

/**************************************************
** Function: ~Linked_List
** Description: destructor
** Parameters: none
** Pre-Conditions: none
** Post-Conditions: none
***************************************************/ 
Linked_List::~Linked_List(){
    
}

//mutator
/**************************************************
** Function: set_first
** Description: sets the first
** Parameters: Linked_List_Node *first
** Pre-Conditions: none
** Post-Conditions: none
***************************************************/ 
void Linked_List::set_first(Linked_List_Node *first){
    this->first = first;
}

//accessors
/**************************************************
** Function: get_length
** Description: gets the length of the linked list
** Parameters: none
** Pre-Conditions: none
** Post-Conditions: none
***************************************************/ 
int Linked_List::get_length(){
    return length;
}

/**************************************************
** Function: get_first
** Description: gets the first
** Parameters: none
** Pre-Conditions: none
** Post-Conditions: none
***************************************************/ 
Linked_List_Node *Linked_List::get_first(){
    return first;
}

/**************************************************
** Function: enter_number
** Description: user enters number for linked list
** Parameters: int num
** Pre-Conditions: none
** Post-Conditions: none
***************************************************/ 
int Linked_List::enter_number(int num){
    //int num;
    char e;
    bool again = true;
    
    while(again){
        cout << "Please enter a number: ";
        cin >> num;
        push_back(num);

        cout << "Do you want to enter another number? (y or n) ";
        cin >> e;
        //length++;

        if(e == 'n'){
            break;
            again = false;
        }
    }
}

/**************************************************
** Function: set_next
** Description: sets the next val
** Parameters: Linked_List_Node *new_node, Linked_List_Node *d
** Pre-Conditions: none
** Post-Conditions: none
***************************************************/ 
void Linked_List::set_next(Linked_List_Node *new_node, Linked_List_Node *d){
    if(new_node == NULL){
        new_node = d;
    }
    else{
        if(new_node->next != NULL){
            //cout << "test1" << endl;
            set_next(new_node->next, d);
        }
        else if(new_node->next == NULL){
            //cout << "test2" << endl;
            new_node->next = d;
        }
    }
}

/**************************************************
** Function: print
** Description: prints the linked list
** Parameters: none
** Pre-Conditions: none
** Post-Conditions: none
***************************************************/ 
void Linked_List::print(){
    Linked_List_Node *check_node = first;
    while(check_node != NULL){
        cout << check_node->val << " ";
        check_node = (check_node->next);
    }
    cout << endl;
}

/**************************************************
** Function: count_prime
** Description: counts the number of prime numbers in linked list
** Parameters: none
** Pre-Conditions: none
** Post-Conditions: none
***************************************************/ 
int Linked_List::count_prime(){
    Linked_List_Node *check_node = first;
    int count = 0;

    while(check_node != NULL){
        int j = 2;
        int k = 1;
        while(j < check_node->val){
            if(check_node->val % j == 0){
                k = 0;
                break;
            }
            j++;
        }
        if(k == 1){
            count++;
        }
        check_node = check_node->next;
    }

    cout << "You have " << count << " prime number(s) in your list." << endl;
}

/**************************************************
** Function: sort_ascending
** Description: sorts linked list in ascending order
** Parameters: none
** Pre-Conditions: none
** Post-Conditions: none
***************************************************/ 
void Linked_List::sort_ascending(){
    merge_sort(&first);
    print();
}

/**************************************************
** Function: merge
** Description: moves smaller number to the left of linked list
** Parameters: Linked_List_Node *left, Linked_List_Node *right
** Pre-Conditions: none
** Post-Conditions: none
***************************************************/ 
Linked_List_Node* Linked_List::merge(Linked_List_Node *left, Linked_List_Node *right){
    Linked_List_Node *check_node = first;
    Linked_List_Node *L;
    if(left == NULL){
        return right;
    }
    if(right == NULL){
        return left;
    }
    
        if(left->val <= right->val){
            L = left;
            L->next = merge(left->next, right);
        }
        else{
            L = right;
            L->next = merge(left, right->next);
        }
    

    return L;   
}

/**************************************************
** Function: merge_des
** Description: moves larger numbers to the left of linked list
** Parameters: nLinked_List_Node *left, Linked_List_Node *right
** Pre-Conditions: none
** Post-Conditions: none
***************************************************/ 
Linked_List_Node* Linked_List::merge_des(Linked_List_Node *left, Linked_List_Node *right){
    Linked_List_Node *check_node = first;
    Linked_List_Node *L;
    if(left == NULL){
        return right;
    }
    if(right == NULL){
        return left;
    }
    
        if(left->val >= right->val){
            L = left;
            L->next = merge_des(left->next, right);
        }
        else{
            L = right;
            L->next = merge_des(left, right->next);
        }
    

    return L;   
}

/**************************************************
** Function: merge_sort
** Description: sorts the numbers
** Parameters: Linked_List_Node **L
** Pre-Conditions: none
** Post-Conditions: none
***************************************************/ 
void Linked_List::merge_sort(Linked_List_Node **L){
    Linked_List_Node *head = *L;
    Linked_List_Node *left = NULL;
    Linked_List_Node *right = NULL;

    if((head->next == NULL) || (head == NULL)){
        return;
    }
    else{
        split(head, &left, &right);
        merge_sort(&left);
        merge_sort(&right);
        *L = merge(left, right);
    }
}

/**************************************************
** Function: merge_sort_des
** Description: sorts linked list in descending order
** Parameters: Linked_List_Node **L
** Pre-Conditions: none
** Post-Conditions: none
***************************************************/ 
void Linked_List::merge_sort_des(Linked_List_Node **L){
    Linked_List_Node *head = *L;
    Linked_List_Node *left = NULL;
    Linked_List_Node *right = NULL;

    if((head->next == NULL) || (head == NULL)){
        return;
    }
    else{
        split(head, &left, &right);
        merge_sort_des(&left);
        merge_sort_des(&right);
        *L = merge_des(left, right);
    }
}

/**************************************************
** Function: split
** Description: splits half of the linked list to be left and other half to be right
** Parameters: Linked_List_Node *L, Linked_List_Node **left, Linked_List_Node **right
** Pre-Conditions: none
** Post-Conditions: none
***************************************************/ 
void Linked_List::split(Linked_List_Node *L, Linked_List_Node **left, Linked_List_Node **right){
    Linked_List_Node *check_node = L;
    Linked_List_Node *fast = L->next;
    Linked_List_Node *slow = L;


    while(fast != NULL){
        fast = fast->next;
        if(fast != NULL){
            slow = slow->next;
            fast = fast->next;
        }
    }

    *left = L;
    *right = slow->next;
    slow->next = NULL;
}

/**************************************************
** Function: a_d
** Description: ask if user wants ascending or descending
** Parameters: none
** Pre-Conditions: none
** Post-Conditions: none
***************************************************/ 
char Linked_List::a_d(){
    char s;

    cout << "Sort ascending or descending (a or d)?: ";
    cin >> s;

    return s;
}

/**************************************************
** Function: if_ad
** Description: sort linked list according to user input
** Parameters: char s
** Pre-Conditions: none
** Post-Conditions: none
***************************************************/ 
void Linked_List::if_ad(char s){
    if(s == 'a'){
        sort_ascending();
    }
    else if(s == 'd'){
        sort_descending();
    }
}

/**************************************************
** Function: try_again
** Description: ask user if they want to try again
** Parameters: none
** Pre-Conditions: none
** Post-Conditions: none
***************************************************/ 
char Linked_List::try_again(){
    char e;

    cout << "Do you want to do this again? (y or n): ";
    cin >> e;

    if(e == 'n'){
        clear();
        exit(0);
    }
    else if(e == 'y'){
        clear();
    }

    return e;
}

/**************************************************
** Function: sort_descending
** Description: sorts the linked list in descending order
** Parameters: none
** Pre-Conditions: none
** Post-Conditions: none
***************************************************/ 
void Linked_List::sort_descending(){
    Linked_List_Node *check_node = first;

    merge_sort_des(&first);
    print();
}

/**************************************************
** Function: clear
** Description: clears the linked list to empty and length to 0
** Parameters: none
** Pre-Conditions: none
** Post-Conditions: none
***************************************************/ 
void Linked_List::clear(){
    Linked_List_Node *check_node = first;
    length = 0;

    while(check_node != NULL){
        first = check_node->next;
        delete check_node;
        check_node = first;
    }
}

/**************************************************
** Function: push_back
** Description: put the number to the end of linked list
** Parameters: int num
** Pre-Conditions: none
** Post-Conditions: none
***************************************************/ 
unsigned int Linked_List::push_back(int num){
    Linked_List_Node *new_node = new Linked_List_Node;
    Linked_List_Node *check_node;
    new_node->next = NULL;

    new_node->set_val(num);
        if(first == NULL){
            first = new_node;
        }  
        else{
            check_node = first;
            while(check_node->next != NULL){
                check_node = (check_node->next);
            }
            set_next(check_node, new_node);
        }
        length++;

    return length;
}