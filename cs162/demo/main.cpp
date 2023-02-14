#include "dog.hpp"

using namespace std;

int main(){
    string name;
    string breed;
    int weight;
    int num_dog;
    Dog d;

    cout << "What is the name of the dog?: ";
    cin >> name;

    cout << "What is the weight of the dog?: ";
    cin >> weight;

    cout << d.getLifespan(weight) << endl;

    cout << "How many dogs?: ";
    cin >> num_dog;

    int *arr = new int[num_dog];

    for(int i = 0; i < num_dog; i++){
        cout << "What is the name of the dog?: ";
        cin >> name;

        cout << "What is the weight of the dog?: ";
        cin >> weight;

        cout << "what is the breed?: ";
        cin >> breed;

        cout << "name: " << name << endl;
        cout << "weight: " << weight << endl;
        cout << "breed: " << breed << endl;
        cout << d.getLifespan(weight) << endl;
    }

    delete[] arr;
    
    return 0;
}