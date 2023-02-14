#include "Restaurant.h"
#include <iostream>

int main()
{
	Restaurant obj;
	obj.set_name("name");

	//copy constructor
	Restaurant obj2 = obj;
	obj.print_info();
	obj2.print_info();

	//operator overload
	


	return 0;
}