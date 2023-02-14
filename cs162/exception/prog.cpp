/*
	Written by Justin Goins as a demonstration of exception handling,
	inheritance, and polymorphism.
*/
#include <iostream>
#include "animal.h"
#include "monkey.h"
#include "sea_otter.h"
#include "teal_sea_otter.h"
#include "red_sea_otter.h"

using namespace std;

/*
	Illustrate how to utilize exceptions
*/
int main() {

	// Cannot instantiate an Animal (since Animal is an abstract class)
//	Animal a1("Generic Animal");
	Monkey m1("Curious George");
	// Cannot instantiate a Sea_Otter (since Sea_Otter is also an abstract class)
//	Sea_Otter s1("Otter Pop");
	Teal_Sea_Otter tso1("Teal Otter Pop");
	Red_Sea_Otter rso1("Red Otter Pop");

	Animal *aptr1 = &m1;
	Animal *aptr2 = &tso1;
	Animal *aptr3 = &rso1;

	// illustrate polymorphism in action:
	cout << "aptr1 says: " << endl;
	aptr1->make_noise(3); // runs the Animal version
	cout << "aptr2 says: " << endl;
	aptr2->make_noise(3); // runs the Teal Sea Otter version
	cout << "aptr3 says: " << endl;
	aptr3->make_noise(3); // runs the Red Sea Otter version

	Sea_Otter *tmp;
	// the following line will not compile...
	//tmp = aptr2;

	// instead, we need to cast the pointer
	tmp = static_cast<Sea_Otter *>(aptr2);
	tmp->swim(4);
	tmp = static_cast<Sea_Otter *>(aptr3);
	tmp->swim(6);

	/*
		The following incorrect code will compile but is deadly during runtime!!
		In other words, it's not a valid cast and will likely cause
		a segfault.
	*/
	// we try to cast an Animal* (pointing to a Monkey) into a Sea_Otter*
	//tmp = static_cast<Sea_Otter *>(aptr1);
	//tmp->swim(8);

	// The safe strategy in this situation is to use a dynamic_cast
	// This will check the type of object at runtime
	tmp = dynamic_cast<Sea_Otter *>(aptr1);
	if (tmp != nullptr)
		tmp->swim(13);
	else
		cout << "Could not dynamically cast aptr1 into a Sea_Otter*" << endl;

	// try another dynamic cast with a Teal_Sea_Otter
	tmp = dynamic_cast<Sea_Otter *>(aptr2);
	if (tmp != nullptr)
		tmp->swim(12);
	else
		cout << "Could not dynamically cast aptr2 into a Sea_Otter*" << endl;

	// add some blank space
	cout << endl << endl;

	// show how to catch a custom exception
	try {
		int distance = 30;
		cout << tso1.get_name() << " will take " << tso1.predict_swim_time(distance) << " seconds to swim " << distance << "meters" << endl;
		cout << "Everything was executed!" << endl;
	} catch (double e_val) {
		cout << "Caught exception of type double with value: " << e_val << endl;
	} catch (Swim_Exception e_val) {
		// in this example we don't do anything to fit the problem
		// instead, we wil just print the exception information
		cout << "Caught exception: " << e_val.what() << endl;
	}

	// add some blank space
	cout << endl << endl;

	// demonstrate another try-catch block
	try {
		Animal &a_ref = m1;
		// The following dynamic cast is invalid and will result in the
		// generation of an exception
		Sea_Otter &otter_ref = dynamic_cast<Sea_Otter &>(a_ref);
		otter_ref.make_noise(2);
	} catch (exception& e) {
		cout << "Caught system exception while trying to cast a reference." << endl;
	}

	// display farewell message
	cout << "Program finished" << endl;

	return 0;
}
