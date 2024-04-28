#pragma once
#include "Examples.h"

int main() {

	// ask user which example they want to run
	int choice;

	std::cout << "What example would you like to run?" << std::endl;

	std::cout << "1. Memory Limits" << std::endl;
	std::cout << "2. Setting and Getting" << std::endl;

	std::cin >> choice;

	switch (choice) {
	case 1:
		MemoryLimitsExample();
		break;

	case 2:
		SettingAndGettingExample();
		break;

	default:
		std::cout << "Invalid choice" << std::endl;
		break;
	}

	return 0;
}
