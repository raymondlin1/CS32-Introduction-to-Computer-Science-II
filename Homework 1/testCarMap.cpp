#include "CarMap.h"
#include <cassert>
#include <iostream>

//To test all functions of CarMap.cpp
int main()
{
	CarMap c;
	assert(c.addCar("6JNK"));
	assert(!c.addCar("6JNK"));
	assert(c.gas("6JNK") == 0);

	assert(c.addGas("6JNK", 1.0) && c.gas("6JNK") == 1.0);
	assert(!c.addGas("VGA", 2.0));

	assert(c.useGas("6JNK", 1.0) && c.gas("6JNK") == 0);
	assert(!c.useGas("VGA", 1.0));
	assert(!c.useGas("6JNK", -1.0));

	assert(c.fleetSize() == 1);
	std::cerr << "All tests passed." << std::endl;
}