#include "dog.hpp"

using namespace std;

Dog::Dog(){

}

Dog::~Dog(){

}

string Dog::getLifespan(int weight){
    if(weight > 100){
        return "about 7 years";
    }
    else if(weight < 100){
        return "about 13 years";
    }
}