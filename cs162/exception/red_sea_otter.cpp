/*
	Red Sea Otter Class
*/
#include <iostream>
#include "red_sea_otter.h"

using namespace std;

Red_Sea_Otter::Red_Sea_Otter(string tmp) {
	name = tmp;
	maximum_length = 4;
}

void Red_Sea_Otter::make_noise(int num) {
	for (int i = 0; i < num; i++)
		cout << "Toink" << " ";
	cout << endl;	
}

void Red_Sea_Otter::swim(int num) {
        cout << name << " is swimming underwater for " << num << " meters." << endl;
}
