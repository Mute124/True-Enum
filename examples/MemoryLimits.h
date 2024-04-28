#include "TrueEnum.h"

inline void MemoryLimitsExample() {
	using namespace TrueEnum;

	// First we create a TrueEnumStr object.
	// You can set the memory limit within the constructor, but for this example we will not.
	TrueEnumStr enumObj;

	// lets set a max memory limit, you must do this before creating any enum objects.
	// In this example, we are setting it to the size of 3 integers.
	enumObj.setTrueEnumMemoryLimit(sizeof(int) * 3);

	// Now lets create 3 enum objects.
	enumObj.addEnum<int>("first", 1);
	enumObj.addEnum<int>("second", 2);
	enumObj.addEnum<int>("third", 3);

	// Now lets print out the enum objects.
	std::cout << "first: " << enumObj.getEnum<int>("first") << std::endl;
	std::cout << "second: " << enumObj.getEnum<int>("second") << std::endl;
	std::cout << "third: " << enumObj.getEnum<int>("third") << std::endl;

	// When ever you are ready to see the memory limit feature, answer this prompt!
	std::cout << "Do you want to add the fourth enum? (y/n): ";
	char input;
	std::cin >> input;

	if (input == 'y') {

		// lets try to be sneaky and add a fourth enum object.
		// It should throw an exception as we have exceeded the memory limit!
		enumObj.addEnum<int>("fourth", 4);
	}
}
