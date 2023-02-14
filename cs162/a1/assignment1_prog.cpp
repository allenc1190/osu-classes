#include "assignment1.hpp"

using namespace std;

int main(int argc, char **argv) {
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
}