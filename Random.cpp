#include <iostream>
#include <cstdlib>
#include <ctime>

using namespace std;

#include "Random.h"

Random::Random()
{
	srand((unsigned int)time(NULL));
}

Random::~Random()
{

}

int Random::randomInt(int max)
{
	return rand() % max;
	
}

double Random::randomDouble(int max)
{
	return (rand() % (max*1000)) / 1000.0;
}

double Random::randomPercentage()
{
	return (rand() % 10000) / 10000.0;
}