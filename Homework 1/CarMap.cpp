#include "CarMap.h"
#include <iostream>

CarMap::CarMap()
{

}

bool CarMap::addCar(std::string license)
{
	if (fleet.contains(license))
	{
		return false;
	}
	else
	{
		fleet.insert(license, 0);
		return true;
	}
}

double CarMap::gas(std::string license) const
{
	if (fleet.contains(license))
	{
		double gals;
		fleet.get(license, gals);
		return gals;
	}
	return -1;
}

bool CarMap::addGas(std::string license, double gallons)
{
	if (fleet.contains(license))
	{
		double gals;
		fleet.get(license, gals);
		if (gals < 0)
			return false;
		else
		{
			fleet.update(license, (gals + gallons));
			return true;
		}
	}
	else
	{
		return false;
	}
}

bool CarMap::useGas(std::string license, double gallons)
{
	if (fleet.contains(license))
	{
		if (gallons < 0 || gallons > gas(license))
			return false;
		else
		{
			fleet.update(license, (gas(license) - gallons));
			return true;
		}
	}
	else
	{
		return false;
	}
}

int CarMap::fleetSize() const
{
	return fleet.size();
}

void CarMap::print() const
{
	for (int i = 0; i < fleetSize(); i++)
	{
		std::string license;
		double gals;
		fleet.get(i, license, gals);
		std::cout << license << " " << gals << std::endl;
	}
}