#include "dog.hpp"

using namespace std;

int main(){
    int weight;
    string breed;
    string name;
    Pet p;
    Dog d;
    int num;
    bool again = true;

    cout << "What is the name?: ";
    cin >> name;

    cout << "What is the weight?: ";
    cin >> weight;

    cout << p.getLifespan() << endl;

    cout << "How many dogs?: ";
        cin >> num;
        
        int *arr = new int[num];

    for(int i = 0; i < num; i++){
        cout << "what is the name?: ";
        cin >> name;

        cout << "What is the breed?: ";
        cin >> breed;

        cout << "What is the weight?: ";
        cin >> weight;

        cout << "Name: " << name << endl;
        cout << "Breed: " << breed << endl;
        cout << "Weight: " << weight << endl;
        cout << d.getLifespan(weight) << endl;
        
    }
    delete[] arr;
    return 0;
}