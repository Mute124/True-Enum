#include "TrueEnum.h"

inline void SettingAndGettingExample() {
	using namespace TrueEnum;

	// First we create a TrueEnumStr object, Look at CustomGettersAndSetters.cpp for how to customize it. This is all you need to get it to work.
	TrueEnumStr enumObj;

	// set an enum value, lets go with "two"
	// Here we basically set the template argument to int, name it "two" and set it to 2. Simple right?
	enumObj.addEnum<int>("number", 2);

	// Lets print it to the console!
	// Very similar to before, we just set the template arg to int, and pass in it's name!
	// The output should be 2
	std::cout << "Before we change it: " << enumObj.getEnum<int>("number") << std::endl;

	// What if we want to change it's value?
	// Here are are using the setEnum method, which takes in the name of the enum and the new value.
	enumObj.setEnum<int>("number", 3);

	// if we print it again, it should be 3
	std::cout << "After we change it: " << enumObj.getEnum<int>("number") << std::endl;

	// That's it! Barely anything you gotta do to get it to work.
}
