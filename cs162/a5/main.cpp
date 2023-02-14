#include "linked_list_node.hpp"
#include "linked_list.hpp"

//int enter_number(int length);

int main(){
    Linked_List ll;
    char s, e, z;
    bool again = true;
    Linked_List_Node *left = NULL;
    Linked_List_Node *right = NULL;
    Linked_List_Node *L;
    int num;

    while(e != 'n'){
        ll.enter_number(num);
        ll.print();
        s = ll.a_d();
        ll.if_ad(s);
        ll.count_prime();
        e = ll.try_again();
    }

    return 0;
}














/*int enter_number(int length){
    int num;
    char e;
    bool again = true;
    Linked_List l;
    Linked_List_Node *ptr = l.get_first();
    
    while(again){
        //int *arr = new int[length];
        Linked_List_Node new_node;

        //for(int i = 0; i < length + 1; i++){
            //cout << "length = " << length << endl;
            cout << "Please enter a number: ";
            cin >> num;
            if(ptr != NULL){
                new_node.set_val(val);
                ptr->next = &new_node;
                ptr = &new_node;
            }*/

            //arr[i] = num;
            /*for(int j = 0; j < length; j++){
                [i] = arr[j];
            }*/

            /*cout << "Do you want to enter another number? (y or n) ";
            cin >> e;
            length++;

            if(e == 'n'){
                break;
                again = false;
            }*/
        //}
        //again = false;
    /*}

}*/