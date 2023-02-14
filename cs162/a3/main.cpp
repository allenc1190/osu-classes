#include <iostream>
#include <cstdlib>
#include <ctime>
#include "animal.hpp"
#include "zoo.hpp"

using namespace std;

int main(){
    zoo *z = new zoo();
    z->start_game();
    delete z;

    return 0;
}