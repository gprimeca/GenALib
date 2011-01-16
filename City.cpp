#include <iostream>
#include <cmath>
#include <ctime>

#include "City.h"

using namespace std;

City::City()
{
	//srand(time(NULL));
	x = rand() % 1000;
	y = rand() % 1000;
	z = rand() % 1000;
}

City::City(const City & other)
	: x(other.x), y(other.y), z(other.z)
{

}

City::City(int in_x, int in_y, int in_z)
	: x(in_x), y(in_y), z(in_z)
{

}

City::~City()
{

}

void City::setCoordinates(int in_x, int in_y, int in_z)
{
	x = in_x;
	y = in_y;
	z = in_z;
}

int City::getX() const { return x; }
int City::getY() const { return y; }
int City::getZ() const { return z; }

bool operator==(const City & c1, const City & c2)
{
	return (c1.getX() == c2.getX() &&
		    c1.getY() == c2.getY() &&
			c1.getZ() == c2.getZ());
}

bool operator!=(const City & c1, const City & c2)
{
	return !(c1 == c2);
}